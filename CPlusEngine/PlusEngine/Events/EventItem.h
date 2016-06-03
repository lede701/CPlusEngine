#ifndef H_EVENTITEM
#define H_EVENTITEM

#include <functional>
#include "EventArgs.h"
#include "IHandler.h"

#define LPEVENTITEM CPlusEngine::Events::EventItem*

#include <memory>

namespace CPlusEngine{ namespace Events
{

	struct EventItem
	{
	public:
		typedef std::unique_ptr<EventItem> Ptr;
		typedef std::shared_ptr<EventItem> SPtr;

	public:
		unsigned int Id;
		LPHANDLER handler;
		std::function<void(EventType, LPEVENTARGS)> function;
		EventType Type;
	};

} }// End namespace CPlusEngine::Events

#endif