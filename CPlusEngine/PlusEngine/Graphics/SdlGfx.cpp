#include "SdlGfx.h"
#include <iostream>
#include <sstream>


namespace CPlusEngine{ namespace Graphics 
{
	SdlGfx::SdlGfx(EventManager::SPtr events)
	{
		_isReady = false;
		_winTitle = "CPlusEngine Title";
		_screenSize.x = 1024;
		_screenSize.y = 576;
		_sceneSize.x = 800;
		_sceneSize.y = 600;
		_frameStarted = false;
		_events = events;
		_camera = nullptr;

		_backColor.r = 0xFF;
		_backColor.g = 0xFF;
		_backColor.b = 0xFF;
		_backColor.a = 0xFF;

		_fontPath = "fonts";
		_textureMap.clear();
	}


	SdlGfx::~SdlGfx()
	{
		// Clean up SDL textures
		for (auto it = _textureMap.begin(); it != _textureMap.end(); ++it)
		{
			GfxTexture::SPtr texture = it->second;
			SDL_DestroyTexture(static_cast<SDL_Texture*>(texture->texture));
		}

		// Clean up all fonts
		if (_fonts.size() > 0)
		{
			for (auto font = _fonts.begin(); font != _fonts.end(); ++font)
			{
				TTF_CloseFont(font->second);
			}
		}

		// Cleanup the SDL system
		cleanup(render, win);
		// Shutdown SDL sub systems
		TTF_Quit();
		IMG_Quit();
		SDL_Quit();
	}

	void SdlGfx::Init()
	{
		DispatchEvent(EventType::ET_GRAPHICS_INIT);
		if (SDL_Init(SDL_INIT_VIDEO) != 0)
		{
			std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
			return;
		}

		unsigned int width = static_cast<unsigned int>(_screenSize.x);
		unsigned int height = static_cast<unsigned int>(_screenSize.y);

		win = SDL_CreateWindow(_winTitle.c_str(), 200, 100, width, height, SDL_WINDOW_SHOWN);
		if (win == nullptr)
		{
			std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
			auto err = new EngineError(1001, "SDL Could creeate window.");
			auto evt = new EventErrorArgs(_events->NextId(), EventType::ET_ERROR, this, err);
			_events->HandleEvent(evt);
			return;
		}

		render = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (render == nullptr)
		{
			std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
			auto err = new EngineError(1002, "SDL Could creeate renderer.");
			auto evt = new EventErrorArgs(_events->NextId(), EventType::ET_ERROR, this, err);
			_events->HandleEvent(evt);
			return;
		}

		// Initialize the image system
		if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
		{
			std::cerr << "Image Init Error: " << SDL_GetError() << std::endl;
			auto err = new EngineError(1002, "SDL Could not initialize the image system.");
			auto evt = new EventErrorArgs(_events->NextId(), EventType::ET_ERROR, this, err);
			_events->HandleEvent(evt);
			return;
		}

		SDL_SetRenderDrawBlendMode(render, SDL_BLENDMODE_BLEND);

		// Initialize TTF system
		if (TTF_Init() == -1)
		{
			auto err = new EngineError(1003, "SDL could not initialize TTF system.");
			auto evt = new EventErrorArgs(_events->NextId(), EventType::ET_ERROR, this, err);
			_events->HandleEvent(evt);
			return;
		}

		std::cerr << "SDL is ready!" << std::endl;

		_isReady = true;
		DispatchEvent(EventType::ET_GRAPHICS_READY);
	}

	bool SdlGfx::IsReady()
	{
		return _isReady;
	}

	EngineError::Ptr SdlGfx::LastError()
	{
		EngineError::Ptr err = nullptr;
		// Check if there is a last err message
		if (_errList.size() > 0)
		{
			err = std::move(_errList.back());
			_errList.pop_back();
		}
		return err;
	}

	std::string SdlGfx::LibPath(const std::string &subpath)
	{
		std::ostringstream out;
#ifdef _WIN32
		const char DS = '\\';
#else
		const char DS = '/';
#endif

		static std::string basePath;
		if (basePath.empty())
		{
			char *tmp = SDL_GetBasePath();
			if (tmp)
			{
				basePath = tmp;
				SDL_free(tmp);
			}
			else
			{
				std::cerr << "Error getting resource path: " << SDL_GetError() << std::endl;
				auto err = new EngineError(1050, "SDL Could get application path");
				auto evt = new EventErrorArgs(_events->NextId(), EventType::ET_ERROR, this, err);
				_events->HandleEvent(evt);
				return "";
			}

		}

		out << basePath << "resources" << DS;
		if (!subpath.empty())
		{
			out << subpath << DS;
		}

		return out.str();
	}


	GfxTexture::SPtr SdlGfx::LoadImage(const std::string &file)
	{
		GfxTexture::SPtr gTexture = nullptr;
		auto key = file;
		// Check if texture has already been loaded
		if (_textureMap[key] == nullptr)
		{
			SDL_Texture *texture = IMG_LoadTexture(render, file.c_str());
			if (texture == nullptr)
			{
				auto err = new EngineError(1051, "SDL Could load image");
				auto evt = new EventErrorArgs(_events->NextId(), EventType::ET_ERROR, this, err);
				_events->HandleEvent(evt);
				std::cerr << "SDL Image Error: " << SDL_GetError() << std::endl;
			}
			else
			{
				_textureMap[key] = GfxTexture::SPtr(new GfxTexture(_textureMap.size() + 1, texture));
			}
		}

		gTexture = _textureMap[key];


		return gTexture;
	}

	void SdlGfx::SetAlpha(GfxTexture::SPtr texture, float alpha)/*Alpha Range 0.0 - 1.0*/
	{
		if (alpha >= 0.f && alpha <= 1.f)
		{
			// Convert the percentage to SDL ranged value 0-255
			unsigned char cAlpha = unsigned char(255 * alpha);
			auto t = static_cast<SDL_Texture*>(texture->texture);
			SDL_SetTextureAlphaMod(t, cAlpha);
		}
	}

	void SdlGfx::ClearColor(GfxColor clr)
	{
		_backColor = clr;
	}

	GfxColor SdlGfx::BackgroundColor()
	{
		return _backColor;
	}


	void SdlGfx::StartFrame()
	{
		// Make start frame safe to call multiple times
		if (!_frameStarted)
		{
			SDL_SetRenderDrawColor(render, _backColor.r, _backColor.g, _backColor.b, _backColor.a);
			SDL_RenderClear(render);
			_frameStarted = true;
			DispatchEvent(EventType::ET_STARTFRAME);
		}
	}

	void SdlGfx::EndFrame()
	{
		// Make calling EndFrame safe multiple times
		if (_frameStarted)
		{
			DispatchEvent(EventType::ET_ENDFRAME);
			// Present the buffer to the player
			SDL_RenderPresent(render);
			_frameStarted = false;
			DispatchEvent(EventType::ET_FRAMEDISPLAYED);
		}
	}

	void SdlGfx::Draw()
	{
	}

	void SdlGfx::Draw(void *obj)
	{
	}

	/*
	void SdlGfx::Draw(IDrawable *obj)
	{
		using CPlusEngine::Objects::CGameObject;
		CGameObject* gObj = dynamic_cast<CGameObject*>(obj);
		if (obj != nullptr)
		{
			Rect2D dst;

			dst.x = gObj->Position()->x;
			dst.y = gObj->Position()->y;
			dst.w = obj->Rect()->w;
			dst.h = obj->Rect()->h;
			dst.IsWorld = gObj->Position()->IsWorld;

			Draw(obj->GetTexture(), (*obj->Rect()), dst);
		}
	}

	void SdlGfx::Draw(LPLIGHT2D light)
	{
		// Create destination
		Rect2D *dst = new Rect2D(light->Rect()->x, light->Rect()->y, light->Rect()->w, light->Rect()->h);
		dst->x = light->Position()->x;
		dst->y = light->Position()->y;
		// Draw gobo
		Draw(light->GetGobo(), *light->Rect(), *dst);
		// Clean up my mess
		delete dst;
	}

	void SdlGfx::Draw(ITileMap *map)
	{
		map->Draw(static_cast<LPGRAPHICS>(this));
	}

	*/

	void SdlGfx::Draw(GfxTexture::Ptr image, const iRect2D &src, const iRect2D &dest)
	{
		Draw(std::move(image), src, dest, fVector2DPtr(new fVector2D(1.0f, 1.0f)));
	}

	void SdlGfx::Draw(GfxTexture::SPtr image, const iRect2D &src, const iRect2D &dest)
	{
		Draw(image, src, dest, fVector2DPtr(new fVector2D(1.0f, 1.0f)));
	}

	void SdlGfx::Draw(GfxTexture::RealPtr image, const iRect2D &src, const iRect2D &dest)
	{
		Draw(image, src, dest, fVector2DPtr(new fVector2D(1.0f, 1.0f)));
	}

	void SdlGfx::Draw(GfxTexture::Ptr image, const iRect2D &src, const iRect2D &dest, const fVector2DPtr scale)
	{
		GfxTexture* texture = image.get();
		Draw(texture, src, dest, scale);
	}

	void SdlGfx::Draw(GfxTexture::SPtr image, const iRect2D &src, const iRect2D &dest, const fVector2DPtr scale)
	{
		GfxTexture* texture = image.get();
		Draw(texture, src, dest, scale);
	}

	void SdlGfx::Draw(GfxTexture* image, const iRect2D &src, const iRect2D &dest, const fVector2DPtr scale)
	{
		if (!_frameStarted)
		{
			StartFrame();
		}
		SDL_Rect SDL_src = ToRect(src);
		SDL_Rect SDL_dest = ToRect(dest);
		if (image == nullptr)
		{
			auto err = new EngineError(2050, "GfxTexture is NULL!");
			auto evt = new EventErrorArgs(_events->NextId(), EventType::ET_ERROR, this, err);
			_events->HandleEvent(evt);
			return;
		}
		// Convert void* to SDL_Textire*
		SDL_Texture* img = VoidToTexture(image->texture);
		// Validate the converion was successful
		if (img == nullptr)
		{
			return;
		}

		// Check if the world is defined and dest is world position
		if (dest.IsWorld && _camera != nullptr)
		{
			// Adjust size based on Camera Zoom
			SDL_dest = ToRect(dest * _camera->Zoom());
			// Adjust destination based on world position
			iRect2D camView = _camera->View();
			SDL_dest.x -= static_cast<int>(camView.x * scale->x);
			SDL_dest.y -= static_cast<int>(camView.y * scale->y);
		}

		SDL_RenderCopy(render, img, &SDL_src, &SDL_dest);
	}

	void SdlGfx::Draw(GfxTexture::SPtr img)
	{

		if (img != nullptr && img->texture != nullptr)
		{
			// Convert void* to SDL_Texture*
			SDL_Texture* pImg = VoidToTexture(img->texture);
			// Setup data structures for texture size
			int w = 0;
			int h = 0;
			int res = SDL_QueryTexture(pImg, nullptr, nullptr, &w, &h);
			// Check if query worked
			if (res == 0)
			{
				// Create the SDL drawing rectangle
				SDL_Rect src{ 0, 0, w, h };
				SDL_RenderCopy(render, pImg, &src, &src);
			}// Endif res equals 0
		}// endif img is not null and img->texture is not null
	}

	void SdlGfx::DrawLine(fVector2DPtr stPoint, fVector2DPtr enPoint, float thickness/* = 1.0f*/, GfxColor clr/* = GfxColor::White*/)
	{
		SDL_Point p1 = ToPoint(stPoint);
		SDL_Point p2 = ToPoint(enPoint);
		SDL_SetRenderDrawColor(render, clr.r, clr.g, clr.b, clr.a);
		SDL_RenderDrawLine(render, p1.x, p1.y, p2.x, p2.y);
	}

	void SdlGfx::SetTitle(const std::string &title)
	{
		_winTitle = title;
	}

	iVector2D SdlGfx::SceneSize() const
	{
		return _sceneSize;
	}

	iVector2D SdlGfx::ScreenSize() const
	{
		return _screenSize;
	}

	void SdlGfx::SetScreenSize(int x, int y)
	{
		_screenSize.x = x;
		_screenSize.y = y;
	}

	void SdlGfx::SetSceneSize(int x, int y)
	{
		_sceneSize.x = x;
		_sceneSize.y = y;
	}

	void SdlGfx::CameraView(CameraSPtr camera)
	{
		_camera = camera;
	}

#pragma region Font Methods

	void SdlGfx::LoadFont(const std::string &fontName, int pt)
	{
		std::string file = LibPath(_fontPath) + fontName;
		std::string key = fontName + std::to_string(pt);
		if (_fonts[key] == nullptr)
		{
			// Load font file
			_fonts[key] = TTF_OpenFont(file.c_str(), pt);
		}
	}

	void SdlGfx::DrawText(const std::string &text, GfxColor clr, const std::string fontName, int pt, iVector2DPtr position)
	{
		// Need to load a font
		std::string fkey = fontName + std::to_string(pt);
		if (_fonts[fkey] == nullptr)
		{
			LoadFont(fontName, pt);
		}
		// Pull font from library
		TTF_Font* font = _fonts[fkey];
		if (font == nullptr)
		{
			// Report error
			auto err = new EngineError(1052, "Font was not able to load!");
			auto evt = new EventErrorArgs(_events->NextId(), EventType::ET_ERROR, this, err);
			_events->HandleEvent(evt);
			return;
		}

		SDL_Color sdlColor = { clr.r, clr.g, clr.b };

		// Need to render the font and text to a surface
		SDL_Surface* sMsg = TTF_RenderText_Blended(font, text.c_str(), sdlColor);

		// Convert surface and draw it to the renderer
		SDL_Texture* tMsg = SDL_CreateTextureFromSurface(render, sMsg);

		// Render texture to the screen
		SDL_Rect pos = { position->x, position->y, sMsg->w, sMsg->h };
		SDL_RenderCopy(render, tMsg, nullptr, &pos);

		// Clean-up but should be moved to resource management instead of here
		SDL_DestroyTexture(tMsg);
		SDL_FreeSurface(sMsg);
	}

	void SdlGfx::DrawText(const std::string &text, GfxColor clr, iVector2DPtr position)
	{
		// Call the real draw text utility that uses a variable font name
		DrawText(text, clr, "arial-plain.ttf", 24, std::move(position));
	}

	void SdlGfx::SetFontPath(const std::string &fontPath)
	{
		_fontPath = fontPath;
	}

	fVector2D SdlGfx::Measure(const std::string &text, const std::string &fontName, int pt)
	{
		// Create font key
		std::string fkey = fontName + std::to_string(pt);
		if (_fonts[fkey] == nullptr)
		{
			LoadFont(fontName, pt);
		}
		// Get font object
		TTF_Font* font = _fonts[fkey];
		if (font == nullptr)
		{
			// Report error
			auto err = new EngineError(1053, "Font was not able to load!");
			auto evt = new EventErrorArgs(_events->NextId(), EventType::ET_ERROR, this, err);
			_events->HandleEvent(evt);
			return fVector2D(0.f, 0.f);
		}

		SDL_Color clr = { 255, 255, 255, 255 };

		// Render font to surface
		SDL_Surface* sMsg = TTF_RenderText_Blended(font, text.c_str(), clr);
		// Get size of surface
		fVector2D size((float)sMsg->w, (float)sMsg->h);

		// Do my SDL clean up because I was a messy boy!
		SDL_FreeSurface(sMsg);

		return size;
	}

#pragma endregion

#pragma region Math Utilities

	SDL_Rect SdlGfx::ToRect(const iRect2D &rect) const
	{
		return SDL_Rect{ rect.x, rect.y, rect.w, rect.h };
	}

	SDL_Rect SdlGfx::ToRect(iRect2D::Ptr rect) const
	{
		return SDL_Rect{ rect->x, rect->y, rect->w, rect->h };
	}

	SDL_Rect SdlGfx::ToRect(const fVector2D &p) const
	{
		return SDL_Rect{ 0, 0, static_cast<int>(p.x), static_cast<int>(p.y) };
	}

	SDL_Rect SdlGfx::ToRect(const fVector2DPtr p) const
	{
		return SDL_Rect{ 0, 0, static_cast<int>(p->x), static_cast<int>(p->y) };
	}

	SDL_Point SdlGfx::ToPoint(const iRect2D &rect) const
	{
		return SDL_Point{ rect.x, rect.y };
	}

	SDL_Point SdlGfx::ToPoint(const iRect2D::Ptr rect) const
	{
		return SDL_Point{ rect->x, rect->y };
	}

	SDL_Point SdlGfx::ToPoint(const fVector2D &p) const
	{
		return SDL_Point{ static_cast<int>(p.x), static_cast<int>(p.y) };
	}

	SDL_Point SdlGfx::ToPoint(const fVector2DPtr p) const
	{
		return SDL_Point{ static_cast<int>(p->x), static_cast<int>(p->y) };
	}


#pragma endregion

#pragma region Conversion Methods

	SDL_Texture* SdlGfx::VoidToTexture(void* junk)
	{
		SDL_Texture *texture = static_cast<SDL_Texture*>(junk);
		// Verify the texture converted properly
		if (texture == nullptr)
		{
			auto err = new EngineError(2051, "SDL Texture pointer is NULL!");
			auto evt = new EventErrorArgs(_events->NextId(), EventType::ET_ERROR, this, err);
			_events->HandleEvent(evt);
		}// Endif texture is null

		return texture;
	}

#pragma endregion

	void SdlGfx::DispatchEvent(EventType type)
	{
		EventArgs* evt = new EventArgs(_events->NextId(), type, this);
		_events->HandleEvent(evt);
	}

	template<typename T, typename... Args>
	void SdlGfx::cleanup(T *t, Args&&... args)
	{
		// Cleanup resource
		cleanup(t);
		// Recurse to clean up the ramining arguments
		cleanup(std::forward<Args>(args)...);
	}

	template<>
	void SdlGfx::cleanup<SDL_Window>(SDL_Window *win)
	{
		if (!win)
		{
			return;
		}
		SDL_DestroyWindow(win);
	}

	template<>
	void SdlGfx::cleanup<SDL_Renderer>(SDL_Renderer *render)
	{
		if (!render)
		{
			return;
		}
		SDL_DestroyRenderer(render);
	}

	template<>
	void SdlGfx::cleanup<SDL_Texture>(SDL_Texture *texture)
	{
		if (!texture)
		{
			return;
		}

		SDL_DestroyTexture(texture);
	}

	template<>
	void SdlGfx::cleanup<SDL_Surface>(SDL_Surface *surface)
	{
		if (!surface)
		{
			return;
		}

		SDL_FreeSurface(surface);
	}

} }// End namespace CPlusEngine::Graphics

