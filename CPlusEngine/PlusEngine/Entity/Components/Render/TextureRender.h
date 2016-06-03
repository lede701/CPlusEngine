#ifndef H_TEXTURERENDER
#define H_TEXTURERENDER

#include <memory>

#include "../../IComponent.h"
#include "../../../Graphics/GfxTexture.h"
#include "../../../Math/Math.h"

namespace CPlusEngine{ namespace Entity{ namespace Component{ namespace Render
{

	class TextureRender : public CPlusEngine::Entity::IComponent
	{
	public:
		typedef std::unique_ptr<TextureRender> Ptr;
		typedef std::shared_ptr<TextureRender> SPtr;
		typedef TextureRender* RealPtr;

		typedef CPlusEngine::Graphics::GfxTexture Texture;

	private:
		Texture::SPtr _texture;

		iRect2DPtr _rect;

	public:
		TextureRender();
		~TextureRender();

		virtual void Init();

		virtual void Draw(CPlusEngine::Context::SPtr context, iVector2D& dest);

		virtual void SetTexture(Texture::SPtr texture);

		virtual void SetRect(iRect2DPtr rect);
	};

} } } }// End namespace CPlusEngine::Entity::Component::Render



#endif