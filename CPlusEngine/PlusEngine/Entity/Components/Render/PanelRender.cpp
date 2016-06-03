#include "PanelRender.h"

namespace CPlusEngine{ namespace Entity{ namespace Component{ namespace Render
{

	PanelRender::PanelRender() : CPlusEngine::Entity::IComponent(CPlusEngine::Entity::ComponentType::CT_RENDER)
	{
		_rect = nullptr;
		_destSize = nullptr;
	}


	PanelRender::~PanelRender()
	{
	}

	void PanelRender::Init()
	{
		// Things we need to do when added to the entity component list
	}

	void PanelRender::Draw(CPlusEngine::Context::SPtr context, iVector2D& dest)
	{
		if (_texture != nullptr)
		{
			if (_rect != nullptr)
			{
				iRect2D src = { _rect->x, _rect->y, _rect->w, _rect->h };
				iRect2D dst = { dest.x, dest.y, _destSize->ToInt().x, _destSize->ToInt().y };
				context->Graphics()->Draw(_texture, src, dst);
			}
			else
			{
				context->Graphics()->Draw(_texture);
			}// Endif _rectr is not null
		}// Endif _texture is not null
	}

	void PanelRender::SetTexture(Texture::SPtr texture)
	{
		if (texture != nullptr)
		{
			_texture = texture;
		}
	}

	void PanelRender::SetRect(iRect2DPtr rect)
	{
		_rect = std::move(rect);
		if (_destSize == nullptr)
		{
			_destSize = iVector2DPtr(new iVector2D(_rect->ToInt().w, _rect->ToInt().h));
		}
	}

	void PanelRender::SetBackSize(iVector2DPtr size)
	{
		_destSize = std::move(size);
	}

} } } }// End namespace CPlusEngine::Entity::Component::Render


