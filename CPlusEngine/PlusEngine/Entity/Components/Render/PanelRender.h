#ifndef H_PANELRENDER
#define H_PANELRENDER

#include <memory>

#include "../../IComponent.h"
#include "../../../Graphics/GfxTexture.h"
#include "../../../Math/Math.h"

namespace CPlusEngine{ namespace Entity{ namespace Component{ namespace Render
{

	class PanelRender : public CPlusEngine::Entity::IComponent
	{
	public:
		typedef std::unique_ptr<PanelRender> Ptr;
		typedef std::shared_ptr<PanelRender> SPtr;
		typedef PanelRender* RealPtr;

		typedef CPlusEngine::Graphics::GfxTexture Texture;

	private:
		Texture::SPtr _texture;

		iRect2DPtr _rect;
		iVector2DPtr _destSize;

	public:
		PanelRender();
		~PanelRender();

		virtual void Init();

		virtual void Draw(CPlusEngine::Context::SPtr context, iVector2D& dest);

		virtual void SetTexture(Texture::SPtr texture);

		virtual void SetRect(iRect2DPtr rect);
		virtual void SetBackSize(iVector2DPtr size);
	};

} } } }// End namespace CPlusEngine::Entity::Component::Render


#endif