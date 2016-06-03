#ifndef H_IUPDATEABLE
#define H_IUPDATEABLE

#include <memory>
#include "../Math/Math.h"

namespace CPlusEngine{ namespace Objects
{

	class IUpdateable
	{
	public:
		typedef std::unique_ptr<IUpdateable> UpdateablePtr;

	public:
		virtual void Update(float deltaTime) = 0;

		virtual fVector2DRealPtr Velocity() = 0;
		virtual fVector2DRealPtr Velocity(float x, float y) = 0;
		virtual fVector2DRealPtr Velocity(const fVector2DRealPtr velocity) = 0;
	};

} }

#endif