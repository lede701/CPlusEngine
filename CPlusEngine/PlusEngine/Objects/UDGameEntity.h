#ifndef H_UDGameObject
#define H_UDGameObject

#include "UGameEntity.h"
#include "IDrawable.h"

namespace CPlusEngine{ namespace Objects
{

	class UDGameEntity : public UGameEntity, public IDrawable
	{
	private:
		TexturePtr _texture;
		iRect2DPtr _rect;

	public:
		UDGameEntity(unsigned int id, TexturePtr texture, iRect2DPtr rect);
		~UDGameEntity();

#pragma region IDrawable Methods

		// Called to draw your object to the texture buffer or what ever you want to call it
		virtual void Draw();

		// This gets presented to the graphic engine
		virtual iRect2D* TextureRect();
		virtual TextureRealPtr Texture();
		virtual void SetTexture(TexturePtr texture);

#pragma endregion
	};

} }// End namespace CPlusengine::Objects


#endif