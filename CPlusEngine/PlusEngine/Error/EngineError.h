#ifndef H_ENGINEERROR
#define H_ENGINEERROR

#include <string>
#include <memory>

namespace CPlusEngine{ namespace Error
{

	class EngineError
	{
	public:
		typedef std::unique_ptr<EngineError> Ptr;
	private:
		std::string _errMsg;
		unsigned int _errNo;
	public:
		EngineError(unsigned int errNo, const std::string &errMsg);

		~EngineError();

		virtual unsigned int GetErrNo();
		virtual std::string GetErrMsg();

		virtual std::string ToString();
	};

} }// End namespace CPlusEngine::Error


#endif