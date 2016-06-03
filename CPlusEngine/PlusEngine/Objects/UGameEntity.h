#ifndef H_UGAMEENTITY
#define H_UGAMEENTITY

#include "IUpdateable.h"
#include "../Entity/Entity.h"

namespace CPlusEngine{ namespace Objects
{

	class UGameEntity : public IUpdateable, public CPlusEngine::Entity::Entity
	{
	private:
		fVector2DPtr _velocity;
		fVector2DPtr _currVelocity;

		float _timeStep;
		float _timeInterval;
		bool _easeInOut;

	public:
		UGameEntity(unsigned int id);
		virtual ~UGameEntity();

		bool EaseInOut();
		bool EaseInOut(bool ease);

#pragma region IUpdateable Methods

		virtual void Update(float deltaTime);

		virtual fVector2DRealPtr Velocity();
		virtual fVector2DRealPtr Velocity(float x, float y);
		virtual fVector2DRealPtr Velocity(const fVector2DRealPtr velocity);

#pragma endregion

	};

} }// End namespace CPlusEngine::Objects

#endif