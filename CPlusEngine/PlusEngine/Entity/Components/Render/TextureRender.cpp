#include "TextureRender.h"

#include <iostream>

namespace CPlusEngine{ namespace Entity{ namespace Component{ namespace Render
{

	TextureRender::TextureRender() : CPlusEngine::Entity::IComponent(CPlusEngine::Entity::ComponentType::CT_RENDER)
	{
		_rect = nullptr;
	}


	TextureRender::~TextureRender()
	{
	}

	void TextureRender::Init()
	{
		// Things we need to do when added to the entity component list
	}

	void TextureRender::Draw(CPlusEngine::Context::SPtr context, iVector2D& dest)
	{
		if (_rect != nullptr)
		{
			iRect2D src(_rect->x, _rect->y, _rect->w, _rect->h, _rect->IsWorld);
			iRect2D dst(dest.x, dest.y, _rect->w, _rect->h, dest.IsWorld);
			context->Graphics()->Draw(_texture, src, dst);
		}
		else
		{
			context->Graphics()->Draw(_texture);
		}
	}

	void TextureRender::SetRect(iRect2DPtr rect)
	{
		_rect = std::move(rect);
	}

	void TextureRender::SetTexture(Texture::SPtr texture)
	{
		// Link our texture to the local object
		_texture = texture;
	}

} } } }// End namespace CPlusEngine::Entity::Component::Render

