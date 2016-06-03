#ifndef H_ITIMEHANDLER
#define H_ITIMEHANDLER

#include "TimeType.h"

#define LPTIMEHANDLER CPlusEngine::Events::ITimeHandler*

namespace CPlusEngine{ namespace Events
{

	class ITimeHandler
	{
	public:
		ITimeHandler();
		virtual ~ITimeHandler();

		// Time event handler, should be moved to different interface
		virtual void HandleEvent(TimeType type) = 0;
	};


} } // End namespace CPlusEngine::Events

#endif