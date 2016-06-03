#include "DGameEntity.h"

namespace CPlusEngine{ namespace Objects
{

	DGameEntity::DGameEntity(unsigned int id, TexturePtr texture, iRect2DPtr rect) : Entity(id)
	{
		_texture = std::move(texture);
		_rect = std::move(rect);
	}


	DGameEntity::~DGameEntity()
	{
	}

	void DGameEntity::Draw()
	{
		// nothing to do for now in this simple entity class
	}

	IDrawable::TextureRealPtr DGameEntity::Texture()
	{
		return _texture.get();
	}

	void DGameEntity::SetTexture(TexturePtr texture)
	{
		_texture = std::move(texture);
	}

	iRect2D* DGameEntity::TextureRect()
	{
		return _rect.get();
	}

} }// End namespace CPlusEngine::Objects

