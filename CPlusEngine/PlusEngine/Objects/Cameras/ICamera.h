#ifndef H_ICAMERA
#define H_ICAMERA

#include <memory>
#include "../../Math/Math.h"

namespace CPlusEngine{ namespace Objects{ namespace Cameras
{

	class ICamera
	{
	public:
		typedef std::unique_ptr<ICamera> Ptr;
		typedef std::shared_ptr<ICamera> SPtr;
		typedef ICamera* RealPtr;

	public:
#pragma region Ctors

		ICamera();
		virtual ~ICamera();

#pragma endregion

		virtual void Update(double deltaTime) = 0;

#pragma region Zoom Methods

		virtual float Zoom() = 0;
		virtual void SetZoom(float zoom) = 0;

#pragma endregion

#pragma region Velocity Methods

		virtual fVector2D Velocity() = 0;
		virtual fVector2D Velocity(float x, float y) = 0;
		virtual fVector2D Velocity(const fVector2D &velocity) = 0;

#pragma endregion

#pragma region View Methods

		virtual iRect2D View() = 0;
		virtual void SetViewSize(int w, int h) = 0;

		virtual fVector2D PositionCenter() = 0;

#pragma endregion

	};

} } }// End namespace CPlusEngine::Objects::Camera


#endif