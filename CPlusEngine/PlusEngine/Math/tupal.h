#ifndef H_TUPAL
#define H_TUPAL

#include <string>
#include <sstream>

namespace CPlusEngine{ namespace Math
{

	template<class T = float>
	struct tupal
	{
	public:
		T val;
		std::string tupalLabel;
		std::string tupalDesc;

		tupal operator=(T ival){ val = ival; return *this; };

		std::string ToString(){ std::ostringstream out; out << tupalLabel << ": " << val; return out.str(); };
	};

} }// End namespace CPlusEngine



#endif