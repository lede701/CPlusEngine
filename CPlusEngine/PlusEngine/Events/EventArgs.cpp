#include "EventArgs.h"

namespace CPlusEngine{ namespace Events
{

	EventArgs::EventArgs(unsigned int eId, EventType inType, void* obj)
	{
		Id = eId;
		Type = inType;
		// Currently object is optional for the event but this may change
		object = obj;
	}


	EventArgs::~EventArgs()
	{
	}

} }

