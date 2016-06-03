#include "Scene.h"

namespace CPlusEngine{

	Scene::Scene()
	{
		_isReady = false;
		_camera = nullptr;
		_blocking = false;

		entityList.clear();
	}


	Scene::~Scene()
	{
		entityList.clear();
	}

	void Scene::Init()
	{
		// Set scene readyness to false
		_isReady = false;

		if (_camera == nullptr)
		{
			_errList.push_back(EngineErrorPtr(new EngineError(3001, "No camera defined in scene, make sure you add a camera to your scene!")));
			return;
		}
		_isReady = true;
	}

	bool Scene::IsReady()
	{
		return _isReady;
	}

	bool Scene::IsBlocking()
	{
		return _blocking;
	}

	void Scene::SetActive(bool active)
	{
		_active = active;
		for (auto it = entityList.begin(); it != entityList.end(); ++it)
		{
			for (auto e = (*it).second.begin(); e != (*it).second.end(); ++e)
			{
				(*e)->SetActive(active);
			}
		}
	}

	bool Scene::IsActive()
	{
		return _active;
	}

	void Scene::SetBlocking(bool blocking)
	{
		_blocking = blocking;
	}

	void Scene::Add(EntityPtr entity)
	{
		// Need to search for a camera entity
		entityList[entity->Layer()].push_back(std::move(entity));
	}

	void Scene::Draw(CPlusEngine::Context::SPtr context)
	{
		if (_camera != nullptr)
		{
			context->Graphics()->CameraView(_camera);
		}
		iRect2D view = _camera->View();
		// TODO: Perform objeject culling so we don't draw non viewable entities

		// Go through each entity in the scene and draw them to context
		for (auto it = entityList.begin(); it != entityList.end(); ++it)
		{
			for (auto ent = (*it).second.begin(); ent != (*it).second.end(); ++ent)
			{
				// Need tgo add current camera to context
				(*ent)->Draw(context);
			}
		}
	}

#pragma region Simulation Methods

	void Scene::Update(double deltaTime)
	{
		_camera->Update(deltaTime);
		for (auto it = entityList.begin(); it != entityList.end(); ++it)
		{
			for (auto ent = (*it).second.begin(); ent != (*it).second.end(); ++ent)
			{
				(*ent)->Update(deltaTime);
			}
		}
	}

#pragma endregion

#pragma region Camera Methods

	fVector2DPtr Scene::WorldPos()
	{
		// TODO: Fix camera connection to entity position
		// Possible Fixes: Change the ICamera to inherit from entity.... Might cause entity diamond reference issues
		// This will be a bug because the original position is a float that is now being cast to int and then back to float.  MAJOR loss of data here :(
		fVector2DPtr pos(new fVector2D(float(_camera->View().x), float(_camera->View().y)));
		// This provides the top left corner of the sceen.
		return pos;
	}

	iRect2D Scene::WorldView()
	{
		return _camera->View();
	}

	Scene::CameraSPtr Scene::Camera()
	{
		return _camera;
	}

	void  Scene::Add(CameraSPtr camera)
	{
		if (camera != nullptr)
		{
			_camera = camera;
		}
	}

#pragma endregion

#pragma region Error Methods

	Scene::EngineErrorPtr Scene::LastError()
	{
		EngineErrorPtr err = nullptr;
		if (_errList.size() > 0)
		{
			err = std::move(_errList.back());
			_errList.pop_back();
		}

		return err;
	}

#pragma endregion

}// End namespace CPlusEngine

