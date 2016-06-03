#ifndef H_UPDATECMP
#define H_UPDATECMP

#include <memory>

#include "../../IComponent.h"
#include "../../Entity.h"
#include "../../../Math/Math.h"

namespace CPlusEngine{ namespace Entity{ namespace Component{ namespace Updaters
{

	class UpdateCmp : public CPlusEngine::Entity::IComponent
	{
	public:
		typedef std::unique_ptr<UpdateCmp> Ptr;
		typedef std::shared_ptr<UpdateCmp> SPtr;

		typedef CPlusEngine::Entity::Entity Entity;
		typedef Entity* EntityRealPtr;

	private:
		EntityRealPtr _parent;

		float _time;
		float _timeAdjust;

		// This is used to track our lerp system
		fVector2D _currVelocity;
		fVector2D _velocity;

		bool _isReady;

	public:
		UpdateCmp();
		UpdateCmp(EntityRealPtr parent);
		virtual ~UpdateCmp();

		virtual void Init();

		virtual void Update(double deltaTime);

		virtual void SetTimeAdjust(float timeAdjust);
		virtual void SetParent(EntityRealPtr parent);

		virtual fVector2D Velocity();
		virtual fVector2D Velocity(float x, float y);
		virtual fVector2D Velocity(const fVector2D &velocity);

	};

} } } }// End namespace CPlusEngine::Entity::Component::Updaters


#endif