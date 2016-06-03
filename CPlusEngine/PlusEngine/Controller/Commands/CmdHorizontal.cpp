#include "CmdHorizontal.h"

namespace CPlusEngine{ namespace Controller{ namespace Commands
{

	CmdHorizontal::CmdHorizontal(unsigned int code, float speed)
	{
		_code = code;
		_speed = speed;
	}


	CmdHorizontal::~CmdHorizontal()
	{
	}

#pragma region ICommand Methods

	void CmdHorizontal::SetCode(unsigned int code)
	{
		_code = code;
	}

	unsigned int CmdHorizontal::Code()
	{
		return _code;
	}

	void CmdHorizontal::RunCommand(UpdaterRealPtr updater)
	{
		updater->Velocity(_speed, updater->Velocity().y);
	}

	void CmdHorizontal::StopCommand(UpdaterRealPtr updater)
	{
		updater->Velocity(0.f, updater->Velocity().y);
	}

	void CmdHorizontal::SetSpeed(float speed)
	{
		_speed = speed;
	}

#pragma endregion

} } }// End namespace CPlusEngine::Controllers::Commands

