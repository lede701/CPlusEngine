#include "Transform.h"
#include <memory>

namespace CPlusEngine{ namespace Entity
{

	Transform::Transform()
	{
		_position = fVector2DPtr(new fVector2D(0.f, 0.f));
		_rotation = fVector2DPtr(new fVector2D(0.f, 0.f));
		_scale = fVector2DPtr(new fVector2D(0.f, 0.f));
	}

	Transform::Transform(fVector2DPtr position, fVector2DPtr rotation, fVector2DPtr scale)
	{
		_position = position;
		_rotation = rotation;
		_scale = scale;
	}

	Transform::~Transform()
	{
	}

#pragma region Position Methods

	fVector2DPtr Transform::Position()
	{
		return _position;
	}

	fVector2DPtr Transform::Position(float x, float y)
	{
		_position->x = x;
		_position->y = y;

		return _position;
	}

	fVector2DPtr Transform::Position(const fVector2D &position)
	{
		return Position(position.x, position.y);
	}

#pragma endregion

#pragma region Rotation Methods

	fVector2DPtr Transform::Rotation()
	{
		return _rotation;
	}

	fVector2DPtr Transform::Rotation(float x, float y)
	{
		_rotation->x = x;
		_rotation->y = y;

		return _rotation;
	}

	fVector2DPtr Transform::Rotation(const fVector2D &rotation)
	{
		return Rotation(rotation.x, rotation.y);
	}

#pragma endregion

#pragma region Scale Methods

	fVector2DPtr Transform::Scale()
	{
		return _scale;
	}

	fVector2DPtr Transform::Scale(float x, float y)
	{
		_scale->x = x;
		_scale->y = y;

		return _scale;
	}

	fVector2DPtr Transform::Scale(const fVector2D &scale)
	{
		return Scale(scale.x, scale.y);
	}

#pragma endregion


} }// End namespace CPlusEngine::Entity

