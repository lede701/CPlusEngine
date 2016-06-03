#ifndef H_SDLINPUT
#define H_SDLINPUT

#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")

#include "IInput.h"
#include "../Events/EventArgs.h"
#include "../Events/EventKeyArgs.h"
#include "../Events/EventMouseArgs.h"
#include <SDL.h>

#define MAXBUFFKEYS 282
#define MAXMOUSEKEYS 6

#define MOUSE_BUTTON_LEFT 0
#define MOUSE_BUTTON_RIGHT 1
#define MOUSE_BUTTON_CENTER 2

namespace CPlusEngine{ namespace Input
{ 
	
	using CPlusEngine::Events::EventKeyArgs;
	using CPlusEngine::Events::EventMouseArgs;
	using CPlusEngine::Events::MouseButton;
	using CPlusEngine::Events::EventArgs;

	class SdlInput : public IInput
	{
		bool _keyDown[MAXBUFFKEYS];
		bool _pastDown[MAXBUFFKEYS];
		bool _mouseDown[MAXMOUSEKEYS];
		bool _mousePast[MAXMOUSEKEYS];
		bool _isReady;

		bool _anyKey;

		CPlusEngine::Events::EventManager::SPtr _events;

	public:
		SdlInput();
		virtual ~SdlInput();

		virtual void Init();
		virtual bool IsReady();

		virtual int GetKey();
		virtual int PeekKey();
		virtual bool AnyKey();

		virtual void SetEvents(CPlusEngine::Events::EventManager::SPtr em);

		virtual KeyState GetState(int key);
		virtual KeyState GetMouseState(int btn);

		virtual void Update(double deltaTime);

		virtual void ProcessKeyEvent(int key);
		virtual void ProcessMouseClick(int key);
		virtual void ProcessMouseMove();
	};

} }// End namespace CPlusEngine::Input


#endif