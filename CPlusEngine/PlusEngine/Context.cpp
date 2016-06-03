#include "Context.h"

namespace CPlusEngine
{

	Context::Context()
	{
		_gfx = nullptr;
		_events = nullptr;
		_input = nullptr;

		_isReady = false;
		_errList.clear();
	}
	
	Context::~Context()
	{
		_errList.clear();
	}

	void Context::Init()
	{
		_isReady = false;
		// Verify the render context is ready
		if (_gfx == nullptr)
		{
			_errList.push_back(EngineErrorPtr(new EngineError(2001, "Context does not have a valide graphic engine.")));
		}

		if (_events == nullptr)
		{
			_errList.push_back(EngineErrorPtr(new EngineError(2002, "Context does not have a valide event manager.")));
		}

		if (_input == nullptr)
		{
			_errList.push_back(EngineErrorPtr(new EngineError(2003, "Context does not have a valide input system.")));
		}

		// All checks have passed so context is ready!
		_isReady = _errList.size() == 0;
	}

	bool Context::IsReady()
	{
		return _isReady;
	}

	CPlusEngine::Graphics::IGraphics::SPtr Context::Graphics()
	{
		return _gfx;
	}

	CPlusEngine::Graphics::IGraphics::SPtr Context::Graphics(CPlusEngine::Graphics::IGraphics::SPtr gfx)
	{
		_gfx = gfx;
		return _gfx;
	}

	CPlusEngine::Events::EventManager::SPtr Context::Events()
	{
		return _events;
	}

	CPlusEngine::Events::EventManager::SPtr Context::Events(CPlusEngine::Events::EventManager::SPtr events)
	{
		if (events != nullptr)
		{
			_events = events;
		}

		return _events;
	}

	Context::EngineErrorPtr Context::LastError()
	{
		EngineErrorPtr err = nullptr;
		if (_errList.size() > 0)
		{
			err = std::move(_errList.back());
			_errList.pop_back();
		}

		return err;
	}

	Context::InputSPtr Context::Input()
	{
		return _input;
	}

	Context::InputSPtr Context::Input(InputSPtr input)
	{
		if (_events != nullptr)
		{
			// Add event manager to the input system
			input->SetEvents(_events);
			// Initialize input controller
			input->Init();
			if (input->IsReady())
			{
				_input = input;
			}
		}
		else
		{
			_errList.push_back(EngineError::Ptr(new EngineError(2010, "Tried to add an input system without defining an EventManager first.")));
		}

		return _input;
	}

	Context::CameraSPtr Context::Camera()
	{
		return _camera;
	}

	Context::CameraSPtr Context::Camera(CameraSPtr camera)
	{
		// Make sure a valid camera is being set in the context
		if (camera != nullptr)
		{
			_camera = camera;
		}
		else
		{
			// Report the error
			_errList.push_back(EngineError::Ptr(new EngineError(2011, "Invalid camera passed into context!")));
		}

		return _camera;
	}

}// End namespace CPlusEngine

