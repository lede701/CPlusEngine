#ifndef H_CAMERA
#define H_CAMERA

#include <memory>

#include "../../Entity/Entity.h"
#include "../../Entity/Components/Updaters/UpdateCmp.h"
#include "../../Math/Math.h"


namespace CPlusEngine{ namespace Objects{ namespace Cameras
{
	// Need my old camra code
	class Camera : public CPlusEngine::Entity::Entity, public ICamera
	{
	public:
		typedef std::unique_ptr<Camera> Ptr;
		typedef std::shared_ptr<Camera> SPtr;
		typedef Camera* RealPtr;

		typedef CPlusEngine::Entity::Component::Updaters::UpdateCmp UpdateCmp;

	private:
		float _zoom;

		iRect2D _view;
		fVector2D _centerPoint;

		UpdateCmp* _updater;

	public:
		Camera(unsigned int id);
		~Camera();

		virtual float Zoom();
		virtual void SetZoom(float zoom);

		virtual void SetTimeAdjust(float timeAdjust);

		virtual void Update(double deltaTime);

#pragma region Velocity Methods

		virtual fVector2D Velocity();
		virtual fVector2D Velocity(float x, float y);
		virtual fVector2D Velocity(const fVector2D &velocity);

#pragma endregion

#pragma region View Methods

		virtual iRect2D View();
		virtual void SetViewSize(int w, int h);

		virtual fVector2D PositionCenter();

#pragma endregion

	};

} } }// End namespace CPlusEngine::Objects::Cameras


#endif