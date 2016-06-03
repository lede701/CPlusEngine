#include "EventMouseArgs.h"

namespace CPlusEngine{ namespace Events
{

	EventMouseArgs::EventMouseArgs(unsigned int eId, EventType inType, void* obj) : EventArgs(eId, inType, obj)
	{
	}


	EventMouseArgs::~EventMouseArgs()
	{
	}

} }// End namespace CPlusEngine::Events

