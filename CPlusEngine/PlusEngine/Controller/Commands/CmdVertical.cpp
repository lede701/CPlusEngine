#include "CmdVertical.h"

namespace CPlusEngine{ namespace Controller{ namespace Commands
{

	CmdVertical::CmdVertical(unsigned int code, float speed)
	{
		_code = code;
		_speed = speed;
	}

	CmdVertical::~CmdVertical()
	{
	}

#pragma region ICommand Methods

	void CmdVertical::SetCode(unsigned int code)
	{
		_code = code;
	}

	unsigned int CmdVertical::Code()
	{
		return _code;
	}

	void CmdVertical::RunCommand(UpdaterRealPtr updater)
	{
		updater->Velocity(updater->Velocity().x, _speed);
	}

	void CmdVertical::StopCommand(UpdaterRealPtr updater)
	{
		updater->Velocity(updater->Velocity().x, 0.f);
	}

	void CmdVertical::SetSpeed(float speed)
	{
		_speed = speed;
	}

#pragma endregion

} } }// End namespace CPlusEngine::Controller::Commands

