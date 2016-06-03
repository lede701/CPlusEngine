#ifndef H_EVENTMANAGER
#define H_EVENTMANAGER

#include <functional>
#include <map>
#include <memory>
#include <vector>

#include "IHandler.h"
#include "ITimeHandler.h"
#include "EventArgs.h"
#include "EventItem.h"
#include "EventType.h"
#include "TimedEvent.h"
#include "TimeType.h"

namespace CPlusEngine{ namespace Events
{

	class EventManager
	{
	public:
		typedef std::unique_ptr<EventManager> Ptr;
		typedef std::shared_ptr<EventManager> SPtr;
		typedef EventManager* RealPtr;

	private:
		int _nextEventId;
		unsigned int _evtCount;
		std::map <EventType, std::vector<EventItem::Ptr>> _eventList;
		std::map<TimeType, std::vector<TimedEvent::Ptr>> _timedList;

		std::vector<EventItem::Ptr> _eventAdd;
		std::vector<unsigned int> _eventRm;
		std::vector<TimedEvent::Ptr> _timedAdd;
		std::vector<unsigned int> _timedRm;

	public:
		EventManager();
		virtual ~EventManager();

		virtual unsigned int NextId();

		virtual unsigned int Add(LPHANDLER evt, EventType type);
		virtual unsigned int Add(std::function<void(EventType, LPEVENTARGS)> function, EventType type);

		virtual unsigned int Add(LPTIMEHANDLER evt, TimeType TType, int interval);
		virtual unsigned int Add(std::function<void(TimeType)> function, TimeType TType, int interval);

		virtual bool Remove(unsigned int Id);

		virtual bool RemoveTimed(unsigned int Id);
		virtual bool RemoveTimed(LPTIMEDEVENT e);

		// Get the total number of events in system
		virtual unsigned int EventCount(); // Would be nice to use auto for here
		virtual unsigned int EventCount(TimeType TType);
		virtual unsigned int EventCount(EventType type);

		// Clear all events!
		virtual void Clear();
		virtual void Clear(TimeType TType);
		virtual void Clear(EventType type);

		virtual void Update(double deltaTime);
		virtual void Update(double deltaTime, TimeType TType);

		virtual void HandleEvent(EventType type, LPEVENTARGS e);
		virtual void HandleEvent(LPEVENTARGS e);
		virtual void HandleEvent(EventArgs::Ptr e);
	};

} }// End namespace CPlusEngine::Events


#endif