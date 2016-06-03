#ifndef H_IDRAWABLE
#define H_IDRAWABLE

#include "../Math/Math.h"
#include "../Graphics/GfxTexture.h"

#include <memory>

namespace CPlusEngine{ namespace Objects
{

	class IDrawable
	{
	public:
		typedef CPlusEngine::Graphics::GfxTexture::Ptr TexturePtr;
		typedef CPlusEngine::Graphics::GfxTexture* TextureRealPtr;
		typedef std::unique_ptr<IDrawable> pDrawable;

	public:
		// Called to draw your object to the texture buffer or what ever you want to call it
		virtual void Draw() = 0;

		// This gets presented to the graphic engine
		virtual iRect2D* TextureRect() = 0;
		virtual TextureRealPtr Texture() = 0;
		virtual void SetTexture(TexturePtr texture) = 0;

	};

} }// End namespace CPlusEngine

#endif