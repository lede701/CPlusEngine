#ifndef H_CTRLCOMMAND
#define H_CTRLCOMMAND

#include <memory>
#include "../../Entity/Components/Updaters/UpdateCmp.h"

namespace CPlusEngine{ namespace Controller{ namespace Commands
{

	class ICommand
	{
	public:
		typedef std::unique_ptr<ICommand> Ptr;
		typedef ICommand* RealPtr;
		typedef CPlusEngine::Entity::Component::Updaters::UpdateCmp* UpdaterRealPtr;

	public:
		ICommand();
		~ICommand();

		virtual void SetCode(unsigned int code) = 0;
		virtual unsigned int Code() = 0;
		virtual void RunCommand(UpdaterRealPtr updater) = 0;
		virtual void StopCommand(UpdaterRealPtr updater) = 0;
		virtual void SetSpeed(float speed) = 0;
	};

} } }// End namespace CPlusEngine::Controllers::Commands


#endif