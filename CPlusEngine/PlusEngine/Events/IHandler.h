#ifndef H_IHANDLER
#define H_IHANDLER

#define LPHANDLER CPlusEngine::Events::IHandler*

#include "EventType.h"
#include "TimeType.h"
#include "EventArgs.h"

namespace CPlusEngine{ namespace Events
{

	class IHandler
	{
	public:
		IHandler();
		virtual ~IHandler();

		// Normal event manager
		virtual void HandleEvent(EventType type, EventArgs *e) = 0;
	};

} } // End namespace CPlusEngine::Events



#endif