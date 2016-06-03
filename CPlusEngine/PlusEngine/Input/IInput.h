#ifndef H_IINPUT
#define H_IINPUT

#include <memory>

#include "KeyState.h"
#include "../Events/EventManager.h"

namespace CPlusEngine{ namespace Input
{ 
	class IInput
	{
	public:
		typedef std::unique_ptr<IInput> Ptr;
		typedef std::shared_ptr<IInput> SPtr;
		typedef IInput* RealPtr;

	public:
		IInput();
		virtual ~IInput();

		virtual void Init() = 0;
		virtual bool IsReady() = 0;

		virtual int GetKey() = 0;
		virtual int PeekKey() = 0;
		virtual bool AnyKey() = 0;

		virtual void SetEvents(CPlusEngine::Events::EventManager::SPtr em) = 0;

		KeyState GetState(int key);

		virtual void Update(double deltaTime) = 0;
	};

} }// End namespace CPlusEngine::Input



#endif