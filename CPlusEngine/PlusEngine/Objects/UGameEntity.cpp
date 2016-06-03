#include "UGameEntity.h"

namespace CPlusEngine{ namespace Objects
{

	UGameEntity::UGameEntity(unsigned int id) : Entity(id)
	{
		_velocity = fVector2DPtr(new fVector2D(0.f, 0.f));
		_easeInOut = true;
		_timeInterval = 0.f;
		_timeStep = 0.f;
	}


	UGameEntity::~UGameEntity()
	{
	}

	bool UGameEntity::EaseInOut()
	{
		return _easeInOut;
	}

	bool UGameEntity::EaseInOut(bool ease)
	{
		_easeInOut = ease;
		return ease;
	}

#pragma region IUpdateable Methods

	void UGameEntity::Update(float deltaTime)
	{
		// Check if we want to use lerp for transitioning
		if (_easeInOut)
		{
			// Check if velocity has changed since the last update
			if (_currVelocity->x != _velocity->x || _currVelocity->y != _velocity->y)
			{
				// Create pointer to velocity object
				fVector2D::Ptr pVel(new fVector2D(_velocity->x, _velocity->y));
				// Lerp to the new velocity
				fVector2D newVel = _velocity->Lerp(pVel.get(), _timeStep);
				// Set current velocity to new velocity
				_currVelocity->x = newVel.x;
				_currVelocity->y = newVel.y;
				// Update time step
				_timeStep += _timeInterval;
			}
			else
			{
				_timeStep = 0.f;
			}
		}
		else
		{
			_currVelocity->x = _velocity->x;
			_currVelocity->y = _velocity->y;
		}

		// Calculate the movement of our object
		float x = (Transform()->Position()->x + _currVelocity->x) * deltaTime;
		float y = (Transform()->Position()->y + _currVelocity->y) * deltaTime;

		Transform()->Position(x, y);
	}

	fVector2DRealPtr UGameEntity::Velocity()
	{
		return _velocity.get();
	}

	fVector2DRealPtr UGameEntity::Velocity(float x, float y)
	{
		return _velocity.get();
	}
	
	fVector2DRealPtr UGameEntity::Velocity(const fVector2DRealPtr velocity)
	{
		Velocity(velocity->x, velocity->y);
		return _velocity.get();
	}

#pragma endregion

} }// End namespace CPlusEngine::Objects
