#include "Camera.h"

#include <iostream>
#include <algorithm>

namespace CPlusEngine{ namespace Objects{ namespace Cameras
{

	Camera::Camera(unsigned int id) : Entity(id)
	{
		_zoom = 1.0;

		_updater = new UpdateCmp(this);
		UpdateCmp::Ptr updater(_updater);
		Add(std::move(updater));
	}


	Camera::~Camera()
	{
	}

	float Camera::Zoom()
	{
		return _zoom;
	}

	void Camera::SetZoom(float zoom)
	{
		if (zoom > 0.f && zoom < 10.f)
		{
			_zoom = zoom;
		}
	}

	void Camera::SetTimeAdjust(float timeAdjust)
	{
		// Pass this value to the updater
		_updater->SetTimeAdjust(timeAdjust);
	}

	void Camera::Update(double deltaTime)
	{
		Entity::Update(deltaTime);
	}

#pragma region Velocity Methods

	// Get camera current velocity
	fVector2D Camera::Velocity()
	{
		return _updater->Velocity();
	}

	// Set velocity and get the new velocity
	fVector2D Camera::Velocity(float x, float y)
	{
		_updater->Velocity(x, y);
		return _updater->Velocity();
	}

	// Set velocity and get the new velocity
	fVector2D Camera::Velocity(const fVector2D &velocity)
	{
		return Velocity(velocity.x, velocity.y);
	}

#pragma endregion

#pragma region View Methods

	iRect2D Camera::View()
	{
		// Set the current view x,y position
		_view.x = int(Position()->x);
		_view.y = int(Position()->y);

		return _view;
	}

	void Camera::SetViewSize(int w, int h)
	{
		// Set width and height values of camera view
		_view.w = w;
		_view.h = h;
	}

	fVector2D Camera::PositionCenter()
	{
		fVector2D center = (*Position().get()) + _centerPoint;
		return center;
	}

#pragma endregion


} } }// End namespace CPlusEngine::Objects::Cameras


