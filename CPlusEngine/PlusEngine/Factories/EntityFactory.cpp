#include "EntityFactory.h"

namespace CPlusEngine{ namespace Factories
{
#pragma region Ctors

	EntityFactory::EntityFactory()
	{
	}


	EntityFactory::~EntityFactory()
	{
	}

	void EntityFactory::Init()
	{
		_isReady = false;

		_isReady = true;
	}

#pragma endregion

#pragma region Factory Methods

	unsigned int EntityFactory::NextId()
	{
		_currId = (_currId + 1) % CPE_MAXENTITIES;
		return _currId;
	}

	unsigned int EntityFactory::PrevId()
	{
		unsigned int prevId = (_currId + CPE_MAXENTITIES - 1) % CPE_MAXENTITIES;
		return prevId;
	}

	bool EntityFactory::IsReady()
	{
		return _isReady;
	}

	EntityFactory::EngineError::Ptr EntityFactory::LastError()
	{
		EngineError::Ptr err = nullptr;
		if (_errList.size() > 0)
		{
			// Move last error to err pointer
			err = std::move(_errList.back());
			// Remove blank error from list
			_errList.pop_back();
		}

		return nullptr;
	}

	unsigned int EntityFactory::ErrorCount()
	{
		return _errList.size();
	}

#pragma endregion

#pragma region Entity Methods

	EntityFactory::Entity::Ptr EntityFactory::CreateEntity()
	{
		Entity::Ptr pEntity = nullptr;

		// Create a new entity
		pEntity = Entity::Ptr(new Entity(NextId()));

		// Return new entity
		return pEntity;
	}

	// Auto parent child to provided parent object
	EntityFactory::Entity::Ptr EntityFactory::CreateEntity(Entity::Ptr parent)
	{
		// Create new entity
		Entity::Ptr pEntity(new Entity(NextId()));
		// Add new entity to parent
		parent->Add(std::move(pEntity));
		// Return parent
		return std::move(parent);
	}

	// Use this parenting method when you need to make changes to the child before parenting
	EntityFactory::Entity::Ptr EntityFactory::EntityParent(Entity::Ptr parent, Entity::Ptr child)
	{
		parent->Add(std::move(child));
		return std::move(parent);
	}

	EntityFactory::Entity::Ptr EntityFactory::CreateRender(Entity::Ptr entity, GfxTexture::SPtr texture, iRect2DPtr rect)
	{
		TextureRender::Ptr render(new TextureRender());
		render->SetTexture(texture);
		render->SetRect(std::move(rect));

		entity->Add(Component::Ptr(std::move(render)));

		return std::move(entity);
	}

	EntityFactory::UpdateCmp::Ptr EntityFactory::CreateMover()
	{
		// Create an update component and link it to entity
		UpdateCmp::Ptr mover(new UpdateCmp());
		// Return updated entity
		return mover;
	}

	void EntityFactory::Add(Entity::Ptr entity)
	{
		if (_currScene != nullptr)
		{
			_currScene->Add(std::move(entity));
		}
		else
		{
			// Add error to the stack
			_errList.push_back(EngineError::Ptr(new EngineError(5001, "Factory missing scene so can't add entities.")));
		}
	}

#pragma endregion

#pragma region Scene Methods

	EntityFactory::CPE_Scene::SPtr EntityFactory::Scene()
	{
		return _currScene;
	}

	EntityFactory::CPE_Scene::SPtr EntityFactory::Scene(CPE_Scene::SPtr scene)
	{
		if (scene != nullptr)
		{
			_currScene = scene;
		}

		return _currScene;
	}

	EntityFactory::CPE_Scene::SPtr EntityFactory::CreateScene()
	{
		CPE_Scene::SPtr scene(new CPE_Scene());
		_currScene = std::move(scene);
		return _currScene;
	}

#pragma endregion

} }// End namespace CPlusEngine::Factories


