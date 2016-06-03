#include "EventManager.h"

namespace CPlusEngine{	namespace Events
{

	EventManager::EventManager()
	{
		_nextEventId = 0;
		_evtCount = 0;
	}


	EventManager::~EventManager()
	{
	}

	unsigned int EventManager::Add(LPHANDLER evt, EventType type)
	{
		EventItem::Ptr node(new EventItem());
		unsigned int retVal = node->Id = NextId();
		node->handler = evt;
		node->function = nullptr;
		node->Type = type;

		// Add node to event list
		_eventAdd.push_back(std::move(node));

		return retVal;
	}

	unsigned int EventManager::Add(std::function<void(EventType, LPEVENTARGS)> function, EventType type)
	{
		EventItem::Ptr node(new EventItem());
		unsigned int retVal = node->Id = NextId();
		node->handler = nullptr;
		node->function = function;
		node->Type = type;

		// Add node to event list
		_eventAdd.push_back(std::move(node));

		return retVal;
	}

	unsigned int EventManager::Add(LPTIMEHANDLER evt, TimeType TType, int interval)
	{
		TimedEvent::Ptr node(new TimedEvent());
		unsigned int retVal = node->Id = NextId();
		node->function = nullptr;
		node->handler = evt;
		node->TType = TType;
		node->time = interval;

		// Add node to timed list
		_timedAdd.push_back(std::move(node));

		return retVal;
	}

	unsigned int EventManager::Add(std::function<void(TimeType)> function, TimeType TType, int interval)
	{
		TimedEvent::Ptr node(new TimedEvent());
		unsigned int retVal = node->Id = NextId();
		node->handler = nullptr;
		node->function = function;
		node->TType = TType;
		node->time = interval;

		// Add node to timed list
		_timedAdd.push_back(std::move(node));

		return retVal;
	}

	bool EventManager::Remove(unsigned int id)
	{
		bool beenFound = false;
		// Search through the map for event id
		for (auto &it = _eventList.begin(); it != _eventList.end(); ++it)
		{
			// Search through each list for event id
			for (auto e = it->second.begin(); e != it->second.end(); ++e)
			{
				if ((*e)->Id == id)
				{
					it->second.erase(e);
					beenFound = true;
					break;
				}
			}
			if (beenFound) break;
		}
			
		return beenFound;
	}

	bool EventManager::RemoveTimed(unsigned int Id)
	{
		bool beenFound = false;
		for (auto it = _timedList.begin(); it != _timedList.end(); ++it)
		{
			for (auto e = it->second.begin(); e != it->second.end(); ++e)
			{
				if ((*e)->Id == Id)
				{
					it->second.erase(e);
					beenFound = true;
				}
			}
		}

		return beenFound;
	}

	bool EventManager::RemoveTimed(LPTIMEDEVENT e)
	{
		bool beenRemoved = false;
		// Search for item in timed event list
		for (auto it = _timedList.begin(); it != _timedList.end(); ++it)
		{
			for (auto et = it->second.begin(); et != it->second.end(); ++et)
			{
				if ((*et)->Id == e->Id)
				{
					it->second.erase(et);
					beenRemoved = true;
					_evtCount--;
					break;
				}
			}
			if (beenRemoved) break;
		}
		// Find event in list and then remove it
		return beenRemoved;
	}

	void EventManager::HandleEvent(EventType type, LPEVENTARGS e)
	{
		for (auto it = _eventList[type].begin(); it != _eventList[type].end(); it++)
		{
			// Link to what the iterator is point to in the list
			EventItem *item = (*it).get();

			// Check if there is a defined class handler for this event
			if (item->handler != nullptr)
			{
				item->handler->HandleEvent(type, e);
			}// Endif handler is not null
			if (item->function != nullptr)
			{
				item->function(type, e);
			}
		}// End for each item in the list
	}

	void EventManager::HandleEvent(LPEVENTARGS e)
	{
		HandleEvent(e->Type, e);
		delete e;
	}

	void EventManager::HandleEvent(EventArgs::Ptr e)
	{
		HandleEvent(e->Type, e.get());
	}

	unsigned int EventManager::NextId()
	{
		int nId = _nextEventId;
		_nextEventId = (_nextEventId + 1) % 25000;
		return nId;
	}

	void EventManager::Update(double deltaTime)
	{
		// Check if we have any events to add
		while (_eventAdd.size() > 0)
		{
			EventItem::Ptr node = std::move(_eventAdd.back());
			_eventAdd.pop_back();
			_eventList[node->Type].push_back(std::move(node));
			_evtCount++;
		}
		// Check if we have any timed events to add
		while (_timedAdd.size() > 0)
		{
			TimedEvent::Ptr node = std::move(_timedAdd.back());
			_timedAdd.pop_back();
			_timedList[node->TType].push_back(std::move(node));
			_evtCount++;
		}

		Update(deltaTime, TT_COUNT);
		Update(deltaTime, TT_INTERVAL);
		Update(deltaTime, TT_INTERVALCOUNT);
		Update(deltaTime, TT_ONCE);
	}

	void EventManager::Update(double deltaTime, TimeType TType)
	{
		static std::vector<LPTIMEDEVENT> delEvents;

		if (_timedList[TType].size() > 0)
		{
			for (auto it = _timedList[TType].begin(); it != _timedList[TType].end(); ++it)
			{
				// TODO: Not sure if I want a base on frames or seconds
				LPTIMEDEVENT n = static_cast<LPTIMEDEVENT>((*it).get());
				n->cnt++;
				if (n->cnt >= n->time)
				{
					// Check if there is a class handler
					if (n->handler != nullptr)
					{
						n->handler->HandleEvent(n->TType);
					}// Endif handler is not null
					if (n->function != nullptr)
					{
						n->function(n->TType);
					}

					// Clear timeout count
					n->cnt = 0;
					if (n->TType == TimeType::TT_ONCE)
					{
						delEvents.push_back(n);
					}
				}// Endif event time has lapsed check
			}// End for all interval events
		}// Endif list has at least one item in it
		
		// Check if there are events to remove from the list
		if (delEvents.size() > 0)
		{
			for (auto it = delEvents.begin(); it != delEvents.end(); ++it)
			{
				RemoveTimed(*it);
			}
			delEvents.clear();
		}// Endif delEvents have items in it
	}

	void EventManager::Clear()
	{
		// TODO: Need to iterate through all the lists and clear the events
	}

	void EventManager::Clear(TimeType TType)
	{
		_evtCount -= _timedList.size();
		_timedList[TType].clear();
	}

	void EventManager::Clear(EventType type)
	{
		_evtCount -= _eventList[type].size();
		_eventList[type].clear();
	}

	unsigned int EventManager::EventCount()
	{
		return _evtCount;
	}

	unsigned int EventManager::EventCount(TimeType TType)
	{
		return _timedList[TType].size();
	}

	unsigned int EventManager::EventCount(EventType type)
	{
		return _eventList[type].size();
	}

} }// End namespace CPlusEngine::Events

