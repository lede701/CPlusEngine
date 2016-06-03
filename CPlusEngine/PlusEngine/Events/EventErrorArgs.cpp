#include "EventErrorArgs.h"

namespace CPlusEngine{ namespace Events
{

	EventErrorArgs::EventErrorArgs(unsigned int eId, EventType inType, void* obj, EngineError* err) : EventArgs(eId, inType, obj)
	{
		Error = err;
	}


	EventErrorArgs::~EventErrorArgs()
	{
	}

} }// End namespace CPlusEngine::Events


