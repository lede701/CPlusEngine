#include "EngineError.h"
#include <sstream>

namespace CPlusEngine{ namespace Error
{

	EngineError::EngineError(unsigned int errNo, const std::string &errMsg)
	{
		_errNo = errNo;
		_errMsg = errMsg;
	}


	EngineError::~EngineError()
	{
	}

	unsigned int EngineError::GetErrNo()
	{
		return _errNo;
	}

	std::string EngineError::GetErrMsg()
	{
		return _errMsg;
	}

	std::string EngineError::ToString()
	{
		std::ostringstream out;
		out << "[" << _errNo << "] " << _errMsg;
		return out.str();
	}

} }// End namespace CPlusEngine::Error

