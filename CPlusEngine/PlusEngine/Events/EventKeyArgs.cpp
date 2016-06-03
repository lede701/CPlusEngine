#include "EventKeyArgs.h"

namespace CPlusEngine{ namespace Events
{

	EventKeyArgs::EventKeyArgs(unsigned int eId, EventType inType, void* obj, int inKey, KeyState inState) : EventArgs(eId, inType, obj)
	{
		Key = inKey;
		State = inState;
	}


	EventKeyArgs::~EventKeyArgs()
	{
	}

} }// End namespace CPlusEngine::Events

