#ifndef H_CMDHORIZONTAL
#define H_CMDHORIZONTAL

#include "ICommand.h"

namespace CPlusEngine{ namespace Controller{ namespace Commands
{

	class CmdHorizontal : public ICommand
	{
	private:
		unsigned int _code;
		float _speed;

	public:
		CmdHorizontal(unsigned int code, float speed);
		virtual ~CmdHorizontal();
#pragma region ICommand Methods

		virtual void SetCode(unsigned int code);
		virtual unsigned int Code();
		virtual void RunCommand(UpdaterRealPtr updater);
		virtual void StopCommand(UpdaterRealPtr updater);
		virtual void SetSpeed(float speed);

#pragma endregion

	};

} } }// End namespace CPlusEngine::Controllers::Commands


#endif