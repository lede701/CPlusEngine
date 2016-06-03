#include "UDGameEntity.h"

namespace CPlusEngine{ namespace Objects
{

	UDGameEntity::UDGameEntity(unsigned int id, TexturePtr texture, iRect2DPtr rect) : UGameEntity(id)
	{
		_texture = std::move(texture);
		_rect = std::move(rect);
	}


	UDGameEntity::~UDGameEntity()
	{
	}

#pragma region IDrawable Methods

	void Draw()
	{
		// Nothing yet to call in this routine and the simple object
	}

	// This gets presented to the graphic engine
	iRect2D* UDGameEntity::TextureRect()
	{
		return _rect.get();
	}

	IDrawable::TextureRealPtr UDGameEntity::Texture()
	{
		return _texture.get();
	}

	void UDGameEntity::SetTexture(TexturePtr texture)
	{
		_texture = std::move(texture);
	}

#pragma endregion

} }// End namespace CPlusengine::Objects

