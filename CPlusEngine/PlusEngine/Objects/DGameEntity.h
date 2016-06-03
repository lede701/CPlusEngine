#ifndef H_DGAMEENTITY
#define H_DGAMEENTITY

#include "IDrawable.h"
#include "../Entity/Entity.h"

namespace CPlusEngine{ namespace Objects
{

	class DGameEntity : public IDrawable, public CPlusEngine::Entity::Entity
	{
		TexturePtr _texture;
		iRect2DPtr _rect;

	public:
		DGameEntity(unsigned int id, TexturePtr texture, iRect2DPtr rect);
		virtual ~DGameEntity();

#pragma region IDrawable Methods

		virtual void Draw();

		// This gets presented to the graphic engine
		virtual iRect2D* TextureRect();
		virtual TextureRealPtr Texture();
		virtual void SetTexture(TexturePtr texture);

#pragma endregion
	};

} }// End namespace CPlusEngine::Objects


#endif