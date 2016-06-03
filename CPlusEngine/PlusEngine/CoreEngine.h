#ifndef H_COREENGINE
#define H_COREENGINE

#include <memory>
#include <list>
#include <vector>
#include <stack>

#include "Context.h"
#include "Error/EngineError.h"
#include "Events/IHandler.h"
#include "Events/EventType.h"
#include "Events/EventArgs.h"
#include "Entity/Entity.h"
#include "Objects/IDrawable.h"
#include "Objects/IUpdateable.h"

#include "Scene.h"

namespace CPlusEngine
{
	class CoreEngine : public CPlusEngine::Events::IHandler
	{
	public:
		typedef std::unique_ptr<CoreEngine> Ptr;

		// Used as core datastructures
		typedef CPlusEngine::Entity::Entity Entity;
		typedef Entity::Ptr EntityPtr;
		typedef Entity::SPtr EntitySPtr;
		typedef Entity* EntityRealPtr;

		typedef Scene::Ptr ScenePtr;
		typedef Scene::SPtr SceneSPtr;

		typedef CPlusEngine::Objects::IUpdateable* UpdateableRealPtr;
		typedef std::unique_ptr<CPlusEngine::Objects::IUpdateable> UpdateablePtr;
		typedef std::shared_ptr<CPlusEngine::Objects::IUpdateable> UpdateableSPtr;

		typedef CPlusEngine::Objects::IDrawable* DrawableRealPtr;
		typedef std::unique_ptr<CPlusEngine::Objects::IDrawable> DrawablePtr;
		typedef std::shared_ptr<CPlusEngine::Objects::IDrawable> DrawableSPtr;

		typedef CPlusEngine::Events::EventType EventType;
		typedef CPlusEngine::Events::EventArgs EventArgs;

	private:
		bool _isReady;
		bool _runEngine;

		int _fps;

		std::list<Error::EngineError::Ptr> _errList;
		std::vector<SceneSPtr> _sceneStack;

		CPlusEngine::Context::SPtr _context;

	public:
		CoreEngine();
		virtual ~CoreEngine();

		virtual void Init();

#pragma region Game Methods

		virtual bool IsReady();
		virtual void Quit();
		virtual int RunEngine();

		virtual void SetFps(int fps);
		virtual int Fps();

#pragma endregion

#pragma region Scene Methods

		virtual void PushScene(SceneSPtr scene);
		virtual SceneSPtr PopScene();
		virtual SceneSPtr PopScene(SceneSPtr scene);
		virtual void ClearScenes();
		virtual SceneSPtr CurrentScene();

#pragma endregion

#pragma region Error Methods

		virtual Error::EngineError::Ptr LastError();

#pragma endregion
		
#pragma region Context Methods

	virtual CPlusEngine::Context::SPtr Context();
	virtual CPlusEngine::Context::SPtr Context(CPlusEngine::Context::SPtr context);

#pragma endregion

#pragma region IHandler Methods

	virtual void HandleEvent(CPlusEngine::Events::EventType type, CPlusEngine::Events::EventArgs *e);
	virtual void ProcessEvent(EventType type);

#pragma endregion

	};
}// End namespace CPlusEngine



#endif