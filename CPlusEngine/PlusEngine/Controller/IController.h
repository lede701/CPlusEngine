#ifndef H_ICONTROLLER
#define H_ICONTROLLER

#include <memory>
#include "../Input/IInput.h"
#include "Commands/ICommand.h"

namespace CPlusEngine{ namespace Controller
{

	class IController
	{
	public:
		typedef std::unique_ptr<IController> Ptr;
		typedef CPlusEngine::Input::IInput Input;
		typedef Input::SPtr InputSPtr;

		typedef Commands::ICommand Command;
		typedef Command::Ptr CommandPtr;
		typedef Command::RealPtr CommandRealPtr;

	public:
		IController();
		virtual ~IController();

		virtual void Init() = 0;


#pragma region Controller Utilities

		virtual void AutoKeyController() = 0;
		virtual void Clear() = 0;
		virtual unsigned int Id() = 0;
		virtual bool IsReady() = 0;

#pragma endregion

#pragma region Command Methods

		virtual void Add(CommandPtr cmd) = 0;
		virtual void Remove(CommandRealPtr cmd) = 0;

#pragma endregion

	};

} }// End namespace CPlusEngine::Controllers





#endif