#include "UpdateCmp.h"

#include <algorithm>
#include <iostream>

namespace CPlusEngine{ namespace Entity{ namespace Component{ namespace Updaters
{

	UpdateCmp::UpdateCmp() : IComponent(ComponentType::CT_UPDATE)
	{
		Init();
	}

	UpdateCmp::UpdateCmp(EntityRealPtr parent) : IComponent(ComponentType::CT_UPDATE)
	{
		_parent = parent;
		Init();
	}


	UpdateCmp::~UpdateCmp()
	{
	}

	void UpdateCmp::Init()
	{
		_isReady = false;
		
		_velocity.x = 0.f;
		_velocity.y = 0.f;
		_currVelocity.x = 0.f;
		_currVelocity.y = 0.f;
		_time = 0.f;
		_timeAdjust = 0.05f;

		_isReady = true;
	}

	void UpdateCmp::Update(double deltaTime)
	{
		// For lerp to work we will need to know the current velocity
		if (_currVelocity.x != Velocity().x || _currVelocity.y != Velocity().y)
		{
			fVector2D nVel = _currVelocity.Lerp(&Velocity(), _time);
			// Proof:
			// So I want to make sure the new velocity is inbetween +- velocity
			// For example we need to make sure the new x value is between -2.0f < nX < 2.0f
			float highX = std::abs(Velocity().x);
			float highY = std::abs(Velocity().y);
			float lowX = std::abs(Velocity().x) * -1;
			float lowY = std::abs(Velocity().y) * -1;

			nVel.x = std::max(lowX, std::min(highX, nVel.x));
			nVel.y = std::max(lowY, std::min(highY, nVel.y));

			_currVelocity = nVel;

			_time += _timeAdjust;
		}
		else
		{
			_time = 0.0f;
		}

		double speedX = double(_currVelocity.x) * deltaTime;
		double speedY = double(_currVelocity.y) * deltaTime;
		float px = _parent->Position()->x + float(speedX);
		float py = _parent->Position()->y + float(speedY);

		_parent->Transform()->Position(px, py);
	}

	void UpdateCmp::SetTimeAdjust(float timeAdjust)
	{
		_timeAdjust = timeAdjust;
	}

	void UpdateCmp::SetParent(EntityRealPtr parent)
	{
		_parent = parent;
	}

	fVector2D UpdateCmp::Velocity()
	{
		return _velocity;
	}

	fVector2D UpdateCmp::Velocity(float x, float y)
	{
		_velocity.x = x;
		_velocity.y = y;

		return _velocity;
	}

	fVector2D UpdateCmp::Velocity(const fVector2D &velocity)
	{
		return Velocity(velocity.x, velocity.y);
	}

} } } }// End namespace CPlusEngine::Entity::Component::Updaters

