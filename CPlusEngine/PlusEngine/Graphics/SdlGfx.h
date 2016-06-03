#ifndef H_SDLGFX
#define H_SDLGFX

//http ://stackoverflow.com/questions/13654753/sdl-drawing-negative-circles-fog-of-war

#include <list>
#include <vector>
#include <map>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "IGraphics.h"
#include "../Events/EventManager.h"
#include "../Events/EventErrorArgs.h"
#include "../Math/Math.h"
#include "../Error/EngineError.h"
#include "../Objects/Cameras/ICamera.h"

#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")
#pragma comment(lib, "SDL2_image.lib")
#pragma comment(lib, "SDL2_ttf.lib")

namespace CPlusEngine{ namespace Graphics 
{
	using namespace CPlusEngine::Math;
	using namespace CPlusEngine::Events;

	class SdlGfx : public IGraphics
	{
	public:
		typedef std::unique_ptr<SdlGfx> Ptr;
		typedef CPlusEngine::Error::EngineError EngineError;

	private:
		bool _isReady;
		SDL_Window *win;
		SDL_Renderer *render;

		std::map<std::string, GfxTexture::SPtr> _textureMap;

		// Font data structures
		std::map<std::string, TTF_Font*> _fonts;
		std::string _fontPath;

		std::string _winTitle;
		iVector2D _sceneSize;
		// This isn't really the world it is more of the camera's view
		CameraSPtr _camera;
		iVector2D _screenSize;

		bool _frameStarted;

		EventManager::SPtr _events;
		std::list<EngineError::Ptr> _errList;
		GfxColor _backColor;

	public:
		SdlGfx(EventManager::SPtr events);
		~SdlGfx();

		// Initialization method for graphic engine
		virtual void Init();

		// Error reporting services
		virtual bool IsReady();
		virtual EngineError::Ptr LastError();

		// Window Utilities
		virtual void SetTitle(const std::string &title);

		// Operating System path to gfx library
		virtual std::string LibPath(const std::string &subpath = "");

		// Resource Loading
		virtual GfxTexture::SPtr LoadImage(const std::string &file);
		virtual void SetAlpha(GfxTexture::SPtr texture, float alpha);

		// World Utilities
		virtual void SetSceneSize(int x, int y);
		virtual iVector2D SceneSize() const;
		virtual void CameraView(CameraSPtr camera);

		// Screen Utilities
		virtual void SetScreenSize(int x, int y);
		virtual iVector2D ScreenSize() const;

		// Drawing methods
		virtual void ClearColor(GfxColor clr);
		virtual GfxColor BackgroundColor();
		virtual void StartFrame();
		virtual void EndFrame();
		virtual void Draw();
		/*
		virtual void Draw(IDrawable *obj);
		virtual void Draw(LPLIGHT2D light);
		virtual void Draw(ITileMap *map);
		*/
		virtual void Draw(GfxTexture::Ptr img, const iRect2D &src, const iRect2D &dest);
		virtual void Draw(GfxTexture::SPtr img, const iRect2D &src, const iRect2D &dest);
		virtual void Draw(GfxTexture::RealPtr img, const iRect2D &src, const iRect2D &dest);
		virtual void Draw(GfxTexture::Ptr img, const iRect2D &src, const iRect2D &dest, const fVector2DPtr scale);
		virtual void Draw(GfxTexture::SPtr img, const iRect2D &src, const iRect2D &dest, const fVector2DPtr scale);
		virtual void Draw(GfxTexture::RealPtr img, const iRect2D &src, const iRect2D &dest, const fVector2DPtr scale);
		virtual void Draw(GfxTexture::SPtr img);
		virtual void Draw(void* obj);

#pragma region Draw Primitives Methods

		virtual void DrawLine(fVector2DPtr stPoint, fVector2DPtr enPoint, float thickness = 1.0f, GfxColor clr = GfxColor::White);

#pragma endregion

#pragma region Font Methods

		virtual void LoadFont(const std::string &fontName, int pt);
		virtual void SetFontPath(const std::string &fontPath);
		virtual void DrawText(const std::string &text, GfxColor clr, iVector2DPtr position);
		virtual void DrawText(const std::string &text, GfxColor clr, const std::string fontName, int pt, iVector2DPtr position);
		virtual fVector2D Measure(const std::string &text, const std::string &fontName, int pt);

#pragma endregion

		// Event System
		void DispatchEvent(EventType type);

		template<typename T, typename... Args>
		void cleanup(T *t, Args&&... args);

#pragma region Math Utilities

		SDL_Rect ToRect(const iRect2D &rect) const;
		SDL_Rect ToRect(iRect2D::Ptr rect) const;
		SDL_Rect ToRect(const fVector2D &point) const;
		SDL_Rect ToRect(const fVector2DPtr point) const;

		SDL_Point ToPoint(const iRect2D &rect) const;
		SDL_Point ToPoint(const iRect2D::Ptr recr) const;
		SDL_Point ToPoint(const fVector2D &rect) const;
		SDL_Point ToPoint(const fVector2DPtr rect) const;


#pragma endregion

#pragma region Conversion Methods

		virtual SDL_Texture* VoidToTexture(void* junk);

#pragma endregion

	};

} }// End namespace CPlusEngine::Graphics


#endif