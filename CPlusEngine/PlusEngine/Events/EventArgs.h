#ifndef H_EVENTARGS
#define H_EVENTARGS

#define LPEVENTARGS CPlusEngine::Events::EventArgs*

#include "EventType.h"
#include <memory>

namespace CPlusEngine{ namespace Events
{

	class EventArgs
	{
	public:
		typedef std::unique_ptr<EventArgs> Ptr;
		typedef std::shared_ptr<EventArgs> SPtr;

	public:
		unsigned int Id;
		EventType Type;
		void *object;

		EventArgs(unsigned int eId, EventType inType, void* obj);
		virtual ~EventArgs();
	};

} }


#endif