#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

/*
#include <PlusEngine\Events\EventManager.h>
#include <PlusEngine\Events\ITimeHandler.h>
#include <PlusEngine\Events\IHandler.h>
#include <PlusEngine\Tests\EventObject.h>
#include <PlusEngine\Tests\TimedObject.h>

*/

namespace UnitEngine
{
	//void CallMe(void *obj, LPEVENTARGS e);
	//void TimeMe(void *obj);
	//void TimeOnce(void *obj);

	TEST_CLASS(unitEvents)
	{
	public:
		bool calledBack;
		bool timeBack;
		int timeOnce;
		
		TEST_METHOD(EventManager)
		{
			/*
			calledBack = false;
			timeBack = false;
			timeOnce = 0;
			
			// TODO: Need to figure out how to link my game world class to this test unit
			using CPlusEngine::Events::EventManager;
			using CPlusEngine::Events::EventArgs;

			EventManager manager;

			Assert::AreEqual(0u, manager.NextId(), L"Error next event id is not 1u", LINE_INFO());

			// Add event to manager
			manager.Add(&CallMe, this, CPlusEngine::Events::EventType::ET_TEST);
			Assert::IsFalse(calledBack, L"Callback is not set to false", LINE_INFO());
			Assert::AreEqual(2u, manager.NextId(), L"Error next event id is not 2u", LINE_INFO());

			// Test event callback
			LPEVENTARGS e = new EventArgs(manager.NextId(), CPlusEngine::Events::EventType::ET_TEST);
			manager.HandleEvent(e);
			Assert::IsTrue(calledBack, L"Callback failed for test", LINE_INFO());
			// Clean up my mess like my moma always said
			delete e;
			e = nullptr;

			// Test timed callback
			manager.Add(&TimeMe, this, CPlusEngine::Events::TimeType::TT_INTERVAL, 10);
			manager.Add(&TimeOnce, this, CPlusEngine::Events::TimeType::TT_ONCE, 2);
			Assert::AreEqual(3u, manager.EventCount(), L"The number of events is different then the expected 2", LINE_INFO());
			int cnt = 0;
			// Simulate the update process for the event manager
			while (!timeBack)
			{
				manager.Update(1.0f);
				if (cnt++ > 100) break;
			}
			// Validate that the simulation was successful on iterating the proper number of steps
			Assert::AreEqual(10, cnt, L"Counter didn't process 10 iterations before stopping", LINE_INFO());
			// Validate the once event only fired once
			Assert::AreEqual(1, timeOnce, L"Once event failed by running more than one time", LINE_INFO());

			// Make sure list got properly cleared
			manager.Clear(CPlusEngine::Events::TT_INTERVAL);
			Assert::AreEqual(0u, manager.EventCount(CPlusEngine::Events::TT_INTERVAL), L"Interval list didn't properly get cleared!", LINE_INFO());
			// Test the object version of the events
			auto t = new CPlusEngine::Tests::TimedObject();
			
			manager.Add(static_cast<LPTIMEHANDLER>(t), nullptr, CPlusEngine::Events::TT_ONCE, 5);
			// Simulate event manager again
			for (int i = 0; i < 10; i++)
			{
				manager.Update(1.0f);
			}
			Assert::AreEqual(1u, t->count, L"Once event ran more than once in object version", LINE_INFO());
			t->reset();
			manager.Add(static_cast<LPTIMEHANDLER>(t), nullptr, CPlusEngine::Events::TT_INTERVAL, 10);
			// Simulate event loop
			for (int i = 0; i < 100; ++i)
			{
				manager.Update(1.0f);
			}
			Assert::AreEqual(10u, t->count, L"Event didn't run 10 times!", LINE_INFO());
			delete t;
			t = nullptr;
			// Cleanup the event manager
			manager.Clear(CPlusEngine::Events::TT_INTERVAL);

			// Test simple events in handler objects
			auto obj = new CPlusEngine::Tests::EventObject();
			manager.Add(static_cast<LPHANDLER>(obj), nullptr, CPlusEngine::Events::ET_NONE);		
			// Make sure the obj count is properly set
			Assert::AreEqual(0u, obj->count, L"Event didn't define default count to 0", LINE_INFO());
			e = new CPlusEngine::Events::EventArgs(manager.NextId(), CPlusEngine::Events::ET_NONE);
			manager.HandleEvent(e);
			Assert::AreEqual(1u, obj->count, L"Event didn't get processed so count is not 1", LINE_INFO());

			// Clean up my mess so I can have desert
			delete obj;
			delete e;
			e = nullptr;
			obj = nullptr;
			*/
		}
		

	};

	/*
	
	void CallMe(void *obj, LPEVENTARGS e)
	{
		unitEvents *unit = static_cast<unitEvents*>(obj);
		unit->calledBack = true;
	}

	void TimeMe(void *obj)
	{
		unitEvents *unit = static_cast<unitEvents*>(obj);
		if (unit != nullptr)
		{
			unit->timeBack = true;
		}
	}

	void TimeOnce(void *obj)
	{
		unitEvents *unit = static_cast<unitEvents*>(obj);
		if (unit != nullptr)
		{
			++unit->timeOnce;
		}
	}

	*/

}