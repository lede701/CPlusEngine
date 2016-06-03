#ifndef H_EVENTMOUSEARGS
#define H_EVENTMOUSEARGS

#include "EventArgs.h"
#include "../Input/KeyState.h"

namespace CPlusEngine{ namespace Events
{
	using CPlusEngine::Input::KeyState;

	enum MouseButton{
		MB_NONE,
		MB_LEFT,
		MB_CENTER,
		MB_RIGHT
	};

	class EventMouseArgs : public EventArgs
	{
	private:

	public:
		int x;
		int y;

		MouseButton Button;
		KeyState State;

		EventMouseArgs(unsigned int eId, EventType inType, void* obj);
		virtual ~EventMouseArgs();
	};

} }// End namespace CPlusEngine::Events




#endif