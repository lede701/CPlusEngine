#ifndef H_EVENTERRORARGS
#define H_EVENTERRORARGS

#include "EventArgs.h"
#include "..\Error\EngineError.h"

namespace CPlusEngine{ namespace Events
{
	using CPlusEngine::Error::EngineError;

	class EventErrorArgs : public EventArgs
	{
	public:
		EngineError* Error;

		EventErrorArgs(unsigned int eId, EventType inType, void* obj, EngineError* err);
		~EventErrorArgs();
	};

} }// End namespace CPlusEngine::Events

#endif