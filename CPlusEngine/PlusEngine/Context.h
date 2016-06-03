#ifndef H_CONTEXT
#define H_CONTEXT

#include <list>
#include <memory>

#include "Error/EngineError.h"
#include "Graphics/IGraphics.h"
#include "Input/IInput.h"
#include "Events/EventManager.h"
#include "Objects/Cameras/ICamera.h"

namespace CPlusEngine
{

	class Context
	{
	public:
		typedef std::shared_ptr<Context> SPtr;
		typedef CPlusEngine::Error::EngineError EngineError;
		
		typedef EngineError::Ptr EngineErrorPtr;
		typedef CPlusEngine::Input::IInput IInput;
		
		typedef IInput::Ptr InputPtr;
		typedef IInput::SPtr InputSPtr;

		typedef Objects::Cameras::ICamera::SPtr CameraSPtr;

	private:
		CPlusEngine::Graphics::IGraphics::SPtr _gfx;
		CPlusEngine::Events::EventManager::SPtr _events;
		InputSPtr _input;
		CameraSPtr _camera;

		bool _isReady;

		std::list<EngineErrorPtr> _errList;

	public:
		Context();
		~Context();

		virtual void Init();

		virtual CPlusEngine::Graphics::IGraphics::SPtr Graphics();
		virtual CPlusEngine::Graphics::IGraphics::SPtr Graphics(CPlusEngine::Graphics::IGraphics::SPtr gfx);

		virtual CPlusEngine::Events::EventManager::SPtr Events();
		virtual CPlusEngine::Events::EventManager::SPtr Events(CPlusEngine::Events::EventManager::SPtr events);

		virtual InputSPtr Input();
		virtual InputSPtr Input(InputSPtr input);

		virtual CameraSPtr Camera();
		virtual CameraSPtr Camera(CameraSPtr camera);

		virtual bool IsReady();

		virtual EngineErrorPtr LastError();

	};

}// End namespace CPlusEngine






#endif