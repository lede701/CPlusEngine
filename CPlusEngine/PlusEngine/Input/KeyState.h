#ifndef H_KEYSTATES
#define H_KEYSTATES

namespace CPlusEngine{ namespace Input
{
	enum KeyState
	{
		KT_NORMAL,
		KT_JUSTPRESSED,
		KT_JUSTRELEASED,
		KT_PRESSED
	};

	struct KeyData
	{
	public:
		KeyState State;
		int frameCount;
	};


} }// End namespace CPlusEngine::Input

#endif