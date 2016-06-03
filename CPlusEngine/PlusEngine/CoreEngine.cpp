#include "CoreEngine.h"

#include <iostream>
#include <time.h>
#include <chrono>
#include <thread>
#include <algorithm>

#include "Events/EventKeyArgs.h"
#include "Input/KeyCodes.h"
#include "Graphics/SplashScreen.h"


namespace CPlusEngine
{

	CoreEngine::CoreEngine()
	{
		_isReady = false;
		_runEngine = false;
		_fps = 30;

		_context = nullptr;
	}


	CoreEngine::~CoreEngine()
	{
	}

	void CoreEngine::Init()
	{
		// No need to have a test error message anymore
		//Error::EngineError::Ptr err(new Error::EngineError(100, "Test error message to verify error system is working."));
		// Move error to stack
		//_errList.push_back(std::move(err));

		if (_context == nullptr)
		{
			Error::EngineError::Ptr err(new Error::EngineError(1001, "No context defined.  Did you try and add a context?"));
			// Move error to stack
			_errList.push_back(std::move(err));
			return;
		}

		_context->Graphics()->Init();
		if (!_context->Graphics()->IsReady())
		{
			Error::EngineError::Ptr err(new Error::EngineError(1002, "Graphics engine failed to initialize!"));
			// Move error to stack
			_errList.push_back(std::move(err));
			return;
		}

		// Try and show core engine splahs screen
		CPlusEngine::Graphics::SplashScreen::Ptr splash(new CPlusEngine::Graphics::SplashScreen(_context));
		splash->Init();
		if (!splash->IsReady())
		{
			// Need to transfer errors from splash screen to engine
			while (Error::EngineError::Ptr err = splash->LastError())
			{
				_errList.push_back(std::move(err));
			}
			return;
		}

		if (!splash->Show())
		{
			_errList.push_back(Error::EngineError::Ptr(new Error::EngineError(1003, "Invalid splash screen!")));
			return;
		}


		// Create a default quit key event on the ESC key
		_context->Events()->Add(static_cast<LPHANDLER>(this), Events::ET_QUIT);
		_context->Events()->Add(static_cast<LPHANDLER>(this), Events::ET_KEYUP);

		_runEngine = true;
		_isReady = true;
		// Notify event system engine is ready
		ProcessEvent(EventType::ET_ENGINE_READY);
	}


#pragma region Game Methods

	bool CoreEngine::IsReady()
	{
		return _isReady;
	}

	void CoreEngine::Quit()
	{
		_runEngine = false;

	}

	int CoreEngine::RunEngine()
	{
		int retVal = 0;
		float frameCount = 0.f;
		unsigned int simCount = 0u;
		
		// Notify event system the engine is starting
		ProcessEvent(EventType::ET_ENGINE_STARTING);
		while (_runEngine)
		{
			static int MS_PER_FRAME = CLOCKS_PER_SEC / _fps;
			static double deltaTime = 1.0f;

			auto time = clock();
			// TODO: Move this event update to a seperate thread
			_context->Events()->Update(deltaTime);

			// Update user input
			_context->Input()->Update(deltaTime);
			// Hmm maybe a stack isn't the best way to go
			for (auto it = _sceneStack.begin(); it != _sceneStack.end(); ++it)
			{
				(*it)->Update(deltaTime);
			}

			if (_sceneStack.size() > 0 && frameCount > MS_PER_FRAME)
			{
				// Draw scene
				_context->Graphics()->StartFrame();
				for (auto it = _sceneStack.begin(); it != _sceneStack.end(); ++it)
				{
					(*it)->Draw(_context);
					if ((*it)->IsBlocking())
					{
						break;
					}
				}
				_context->Graphics()->EndFrame();
				frameCount = 0.f;
				simCount = 0u;
			}// Endif _sceneStack has something to simulate

			// TODO: Diagnose why entity position invalidate when the game loop has free rains
			//*
			int sleepTime = std::max(static_cast<int>(time + MS_PER_FRAME - clock()), 1);
			if (sleepTime > 0)
			{
				// Need to put you to sleep now!
				std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
			}
			//*/

			// Recalculate deltaTime
			deltaTime = double(MS_PER_FRAME) / double(clock() - time);
			frameCount += float(clock() - time);
			++simCount;
		}
		// Notify the event system engine is shutting down
		ProcessEvent(EventType::ET_ENGINE_ENDING);

		return retVal;
	}

	void CoreEngine::SetFps(int fps)
	{
		_fps = fps;
	}

	int CoreEngine::Fps()
	{
		return _fps;
	}


#pragma endregion

#pragma region Scene Methods

	void CoreEngine::PushScene(SceneSPtr scene)
	{
		// Initialize scene
		scene->Init();
		// Check if scene is ready
		if (scene->IsReady())
		{
			// Stack scene
			_sceneStack.push_back(std::move(scene));
			ProcessEvent(EventType::ET_SCENE_LOAD);
		}
		else
		{
			// Report errors from scene to engine
			while (Error::EngineError::Ptr err = std::move(scene->LastError()))
			{
				_errList.push_back(std::move(err));
			}
			// Fire an error event
			EventArgs::Ptr e(new EventArgs(_context->Events()->NextId(), EventType::ET_ERROR, this));
			e->object = this;
			_context->Events()->HandleEvent(std::move(e));
			// Set engine to not ready because of an invalid scene
			_isReady = false;
		}
	}

	CoreEngine::SceneSPtr CoreEngine::PopScene()
	{
		SceneSPtr ptr = std::move(_sceneStack.back());
		_sceneStack.pop_back();
		ProcessEvent(EventType::ET_SCENE_UNLOAD);
		return ptr;
	}

	CoreEngine::SceneSPtr CoreEngine::PopScene(SceneSPtr scene)
	{
		SceneSPtr ptr = PopScene();
		PushScene(std::move(scene));
		return ptr;
	}

	void CoreEngine::ClearScenes()
	{
		_sceneStack.clear();
	}

	CoreEngine::SceneSPtr CoreEngine::CurrentScene()
	{
		return _sceneStack.back();
	}

#pragma endregion

#pragma region Error Methods

	Error::EngineError::Ptr CoreEngine::LastError()
	{
		Error::EngineError::Ptr err = nullptr;
		if (_errList.size() > 0)
		{
			err = std::move(_errList.back());
			// Need to remove defunct pointer from the list
			_errList.pop_back();
		}
		return err;
	}

#pragma endregion

#pragma region Context Methods

	CPlusEngine::Context::SPtr CoreEngine::Context()
	{
		return _context;
	}

	CPlusEngine::Context::SPtr CoreEngine::Context(CPlusEngine::Context::SPtr context)
	{
		context->Init();
		if (context->IsReady())
		{
			_context = context;
		}
		else
		{
			_errList.push_back(Error::EngineError::Ptr(new Error::EngineError(1050, "Context failed to initialize! See context error log for more details.")));
			// Move the errors from the context to the engine error list
			while (Error::EngineError::Ptr err = std::move(context->LastError()))
			{
				_errList.push_back(std::move(err));
			}
		}
		return _context;
	}

#pragma endregion

#pragma region IHandler Methods

	void CoreEngine::HandleEvent(CPlusEngine::Events::EventType type, CPlusEngine::Events::EventArgs *e)
	{
		switch (e->Type)
		{
		case EventType::ET_KEYUP:
			{
				auto ke = static_cast<CPlusEngine::Events::EventKeyArgs*>(e);
				if (ke->Key == KC_ESC)
				{
					Quit();
				}
			}
			break;
		case EventType::ET_QUIT:
			{
				Quit();
			}
			break;
		}
	}

	/// ProcessEvent is used to quickly allow the core engine to send events to the core event system.
	void CoreEngine::ProcessEvent(EventType type)
	{
		// Create an event object
		EventArgs* evt = new EventArgs(_context->Events()->NextId(), type, this);
		// Send event to the event handler
		_context->Events()->HandleEvent(evt);
	}

#pragma endregion


}// End namespace CPlusEngine

