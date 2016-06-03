#ifndef H_IGRAPHICS
#define H_IGRAPHICS

#define LPGRAPHICS CPlusEngine::Graphics::IGraphics*

#include <string>
#include "../Error/EngineError.h"
#include "../Math/Math.h"
#include "../Objects/Cameras/ICamera.h"
/*
#include "..\Objects\IDrawable.h"
#include "..\Objects\Lights\ILight.h"
*/
#include "GfxColor.h"
#include "GfxTexture.h"

namespace CPlusEngine{ namespace Graphics
{
	//using CPlusEngine::Objects::IDrawable;
	using namespace CPlusEngine::Math;

	class IGraphics
	{ 
	public:
		typedef std::unique_ptr<IGraphics> Ptr;
		typedef std::shared_ptr<IGraphics> SPtr;
		typedef CPlusEngine::Objects::Cameras::ICamera::SPtr CameraSPtr;

	public:
		IGraphics();
		virtual ~IGraphics();

		// Initialization method for graphic engine
		virtual void Init() = 0;

		// Error reporting services
		virtual bool IsReady() = 0;
		//virtual CPlusEngine::Error::EngineError::Ptr LastError();

		// Window Utilities
		virtual void SetTitle(const std::string &title) = 0;

		// World Utilities
		virtual iVector2D SceneSize() const = 0;
		virtual void SetSceneSize(int x, int y) = 0;
		virtual void CameraView(CameraSPtr camera) = 0;

		// Screen Utilities
		virtual void SetScreenSize(int x, int y) = 0;
		virtual iVector2D ScreenSize() const = 0;

		// Operating System path to gfx library
		virtual std::string LibPath(const std::string &subpath = "") = 0;

		// Resource Loading
		virtual GfxTexture::SPtr LoadImage(const std::string &file) = 0;
		virtual void SetAlpha(GfxTexture::SPtr texture, float alpha) = 0;

		// Drawing methods
		virtual void StartFrame() = 0;
		virtual void EndFrame() = 0;
		virtual void Draw() = 0;
		virtual void ClearColor(GfxColor clr) = 0;
		virtual GfxColor BackgroundColor() = 0;
		//virtual void Draw(IDrawable* obj) = 0;
		//virtual void Draw(LPLIGHT2D light) = 0;
		virtual void Draw(GfxTexture::Ptr image, const iRect2D &src, const iRect2D &dest) = 0;
		virtual void Draw(GfxTexture::SPtr image, const iRect2D &src, const iRect2D &dest) = 0;
		virtual void Draw(GfxTexture::RealPtr image, const iRect2D &src, const iRect2D &dest) = 0;
		virtual void Draw(GfxTexture::Ptr image, const iRect2D &src, const iRect2D &dest, const fVector2DPtr scale) = 0;
		virtual void Draw(GfxTexture::SPtr image, const iRect2D &src, const iRect2D &dest, const fVector2DPtr scale) = 0;
		virtual void Draw(GfxTexture::RealPtr image, const iRect2D &src, const iRect2D &dest, const fVector2DPtr scale) = 0;
		virtual void Draw(GfxTexture::SPtr image) = 0;
		virtual void Draw(void *object) = 0;

		virtual void DrawLine(fVector2DPtr stPoint, fVector2DPtr enPoint, float thickness = 1.0f, GfxColor clr = GfxColor::White) = 0;
		virtual void DrawText(const std::string &text, GfxColor clr, iVector2DPtr position) = 0;
		virtual void DrawText(const std::string &text, GfxColor clr, const std::string fontName, int pt, iVector2DPtr position) = 0;
		virtual fVector2D Measure(const std::string &text, const std::string &fontName, int pt) = 0;
	};

} }// End namespace CPlusEngine::GRaphics
#endif