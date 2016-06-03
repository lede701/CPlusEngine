#ifndef H_ENTITYFACTORY
#define H_ENTITYFACTORY

#ifndef CPE_MAXENTITIES
#define CPE_MAXENTITIES 10500000
#endif

#include <list>
#include <memory>

#include "../Scene.h"
#include "../Entity/Entity.h"
#include "../Entity/Components/components.h"
#include "../Error/EngineError.h"
#include "../Graphics/GfxTexture.h"

namespace CPlusEngine{ namespace Factories
{

	class EntityFactory
	{
	public:
		typedef std::unique_ptr<EntityFactory> Ptr;
		typedef std::shared_ptr<EntityFactory> SPtr;
		typedef EntityFactory* RealPtr;

		// Define easy access to entity system
		typedef CPlusEngine::Entity::Entity Entity;

		// Define easy access to entity components
		typedef CPlusEngine::Entity::IComponent Component;
		typedef CPlusEngine::Entity::Component::Render::TextureRender TextureRender;
		typedef CPlusEngine::Entity::Component::Updaters::UpdateCmp UpdateCmp;

		// Define easy access to scene
		typedef CPlusEngine::Scene CPE_Scene;

		// Define easy access to EngineError
		typedef CPlusEngine::Error::EngineError EngineError;

		// Define easy access to graphic class
		typedef CPlusEngine::Graphics::GfxTexture GfxTexture;

	private:
		unsigned int _currId;
		bool _isReady;

		Scene::SPtr _currScene;

		std::list<EngineError::Ptr> _errList;

	public:
#pragma region Ctors

		EntityFactory();
		virtual ~EntityFactory();

		virtual void Init();

#pragma endregion

#pragma region Factory Methods

		virtual bool IsReady();

		virtual unsigned int NextId();
		virtual unsigned int PrevId();

		EngineError::Ptr LastError();
		unsigned int ErrorCount();

#pragma endregion

#pragma region Entity Methods

		virtual Entity::Ptr CreateEntity();
		virtual Entity::Ptr CreateEntity(Entity::Ptr parent);
		virtual Entity::Ptr EntityParent(Entity::Ptr parent, Entity::Ptr child);

		virtual Entity::Ptr CreateRender(Entity::Ptr entity, GfxTexture::SPtr texture, iRect2DPtr rect);
		virtual UpdateCmp::Ptr CreateMover();

		virtual void Add(Entity::Ptr entity);


#pragma endregion

#pragma region Scene Methods

		// Get current scene
		virtual CPE_Scene::SPtr Scene();
		// Set current scene
		virtual CPE_Scene::SPtr Scene(CPE_Scene::SPtr scene);

		// Create new scene and make it current scene
		virtual CPE_Scene::SPtr CreateScene();

#pragma endregion

	};

} }// End namespace CPlusEngine::Factories



#endif