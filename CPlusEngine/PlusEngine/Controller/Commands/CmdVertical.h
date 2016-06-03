#ifndef H_CMDVERTICAL
#define H_CMDVERTICAL

#include "ICommand.h"

namespace CPlusEngine{ namespace Controller{ namespace Commands
{

	class CmdVertical : public ICommand
	{
	private:
		unsigned int _code;
		float _speed;

	public:
		CmdVertical(unsigned int code, float speed);
		~CmdVertical();

#pragma region ICommand Methods

		virtual void SetCode(unsigned int code);
		virtual unsigned int Code();
		virtual void RunCommand(UpdaterRealPtr updater);
		virtual void StopCommand(UpdaterRealPtr updater);
		virtual void SetSpeed(float speed);

#pragma endregion
	};

} } }// End namespace CPlusEngine::Controller::Commands

#endif