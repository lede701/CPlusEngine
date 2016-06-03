#ifndef H_SCENE
#define H_SCENE

#include <memory>
#include <map>
#include <list>

#include "Entity/Entity.h"
#include "Error/EngineError.h"
#include "Objects/Cameras/ICamera.h"
#include "Context.h"

namespace CPlusEngine
{

	class Scene
	{
	public:
		typedef std::unique_ptr<Scene> Ptr;
		typedef std::shared_ptr<Scene> SPtr;
		typedef CPlusEngine::Entity::Entity::Ptr EntityPtr;
		typedef CPlusEngine::Entity::Entity::SPtr EntitySPtr;

		typedef CPlusEngine::Objects::Cameras::ICamera::Ptr CameraPtr;
		typedef CPlusEngine::Objects::Cameras::ICamera::SPtr CameraSPtr;

		typedef CPlusEngine::Error::EngineError EngineError;
		typedef EngineError::Ptr EngineErrorPtr;

		typedef CPlusEngine::Context::SPtr ContextSPtr;

	private:
		bool _isReady;
		bool _blocking;
		bool _active;

		CameraSPtr _camera;

		std::list<EngineErrorPtr> _errList;

	public:
#pragma region Ctors

		Scene();
		virtual ~Scene();

		virtual void Init();

#pragma endregion

#pragma region Data Structures
		// Layer,List of entities
		std::map<unsigned int, std::list<EntityPtr>> entityList;

#pragma endregion
		
#pragma region Entity Methods

		virtual void Add(EntityPtr entity);
		virtual void Draw(ContextSPtr context);
		virtual bool IsReady();
		virtual bool IsBlocking();

		virtual void SetActive(bool active);
		virtual bool IsActive();

		virtual void SetBlocking(bool blocking);

#pragma endregion

#pragma region Simulation Methods

		void Update(double deltaTime);

#pragma endregion

#pragma region Camera Methods

		virtual fVector2DPtr WorldPos();
		virtual iRect2D WorldView();
		virtual CameraSPtr Camera();
		virtual void Add(CameraSPtr camera);

#pragma endregion

#pragma region Error Methods

		virtual EngineErrorPtr LastError();

#pragma endregion


	};

}// End namespace CPlusEngine


#endif