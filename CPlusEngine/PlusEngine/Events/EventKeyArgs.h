#ifndef H_EVENTKEY
#define H_EVENTKEY

#include "EventArgs.h"
#include "../Input/KeyState.h"

namespace CPlusEngine{ namespace Events
{
	using CPlusEngine::Input::KeyState;
	class EventKeyArgs : public EventArgs
	{
	public:
		int Key;
		KeyState State;

		EventKeyArgs(unsigned int eId, EventType inType, void* obj, int inKey, KeyState inState);
		virtual ~EventKeyArgs();
	};

} }// End namespace CPlusEngine::Events

#endif