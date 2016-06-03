#ifndef H_TIMETYPE
#define H_TIMETYPE

namespace CPlusEngine{ namespace Events
{

	enum TimeType
	{
		TT_NONE,
		TT_COUNT,
		TT_INTERVAL,
		TT_INTERVALCOUNT,
		TT_ONCE
	};

} }// End namespace CPlusEngine::Events

#endif