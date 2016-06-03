#ifndef H_TIMEDEVENT
#define H_TIMEDEVENT

#include <memory>
#include <functional>

#include "ITimeHandler.h"
#include "EventArgs.h"
#include "TimeType.h"

#define LPTIMEDEVENT CPlusEngine::Events::TimedEvent*

namespace CPlusEngine{ namespace Events
{
	struct TimedEvent
	{
	public:
		typedef std::unique_ptr<TimedEvent> Ptr;
		typedef std::shared_ptr<TimedEvent> SPtr;

	public:
		unsigned int Id;
		LPTIMEHANDLER handler;
		std::function<void(TimeType)> function;

		EventType Type;
		TimeType TType;
		int cnt;
		int time;

	};

} }// End namespace CPlusEngine::Events

#endif