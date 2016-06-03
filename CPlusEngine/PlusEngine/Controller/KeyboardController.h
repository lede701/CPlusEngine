#ifndef H_KEYBOARDCONTROLLER
#define H_KEYBOARDCONTROLLER

#include <memory>
#include <map>
#include "IController.h"
#include "../Events/IHandler.h"
#include "../Entity/Components/Updaters/UpdateCmp.h"

namespace CPlusEngine{ namespace Controller
{

	class KeyboardController : public IController, public CPlusEngine::Events::IHandler
	{
	public:
		typedef std::unique_ptr<KeyboardController> Ptr;
		typedef std::shared_ptr<KeyboardController> SPtr;
		typedef KeyboardController* RealPtr;

		typedef CPlusEngine::Events::EventType EventType;
		typedef CPlusEngine::Events::EventArgs EventArgs;

		typedef CPlusEngine::Entity::Component::Updaters::UpdateCmp* UpdaterRealPtr;

	private:
		Input::SPtr _input;
		bool _isReady;
		
		std::map<unsigned int, CommandPtr> _cmdMap;

		UpdaterRealPtr _updater;

		unsigned int _id;

	public:
#pragma region Ctors

		KeyboardController(unsigned int id, UpdaterRealPtr updater, bool AutoSetup = true);
		virtual ~KeyboardController();

		virtual void Init();

#pragma endregion

#pragma region IHandler Methods

		virtual void HandleEvent(void *obj, EventType type, EventArgs *e);

#pragma endregion

#pragma region Controller Utilities

		virtual void AutoKeyController();
		virtual void Clear();
		virtual unsigned int Id();
		virtual bool IsReady();

#pragma endregion


#pragma region Command Methods

		virtual void Add(CommandPtr cmd);
		virtual void Remove(CommandRealPtr cmd);

#pragma endregion

	};

} }// End namespace CPlusEngine::Controllers


#endif