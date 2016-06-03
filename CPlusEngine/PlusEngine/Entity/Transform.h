#ifndef H_TRANSFORM
#define H_TRANSFORM
#include "../Math/Math.h"
#include <memory>

namespace CPlusEngine{ namespace Entity
{

	class Transform
	{
	public:
		typedef std::unique_ptr<Transform> Ptr;
		typedef std::shared_ptr<Transform> SPtr;

	private:
		fVector2DPtr _position;
		fVector2DPtr _rotation;
		fVector2DPtr _scale;

	public:
#pragma region Ctors for Transform Class

		Transform();
		Transform(fVector2DPtr position, fVector2DPtr rotation, fVector2DPtr scale);

		~Transform();

#pragma endregion

#pragma region Position Methods

		fVector2DPtr Position();
		fVector2DPtr Position(float x, float y);
		fVector2DPtr Position(const fVector2D &position);

#pragma endregion

#pragma region Rotation Methods

		fVector2DPtr Rotation();
		fVector2DPtr Rotation(float x, float y);
		fVector2DPtr Rotation(const fVector2D &rotation);

#pragma endregion

#pragma region Scale Methods

		fVector2DPtr Scale();
		fVector2DPtr Scale(float x, float y);
		fVector2DPtr Scale(const fVector2D &scale);

#pragma endregion

	};

} }// End namespace CPlusEngine::Entity

#endif