#include "SdlInput.h"

namespace CPlusEngine{ namespace Input
{ 

	SdlInput::SdlInput()
	{
		_isReady = false;
		_anyKey = false;
		_events = nullptr;
	}


	SdlInput::~SdlInput()
	{
	}

	void SdlInput::Init()
	{
		_isReady = false;

		if (_events == nullptr)
		{
			// TODO: Add engine error system to class
			return;
		}

		for (int i = 0; i < MAXBUFFKEYS; i++)
		{
			_keyDown[i] = false;
			_pastDown[i] = false;
		}
		for (int i = 0; i < MAXMOUSEKEYS; i++)
		{
			_mouseDown[i] = false;
		}


		_isReady = true;
	}

	bool SdlInput::IsReady()
	{
		return _isReady;
	}

	int SdlInput::GetKey()
	{
		int retVal = -1;
		return retVal;
	}

	int SdlInput::PeekKey()
	{
		int retVal = -1;
		return retVal;
	}

	bool SdlInput::AnyKey()
	{
		return _anyKey;
	}

	KeyState SdlInput::GetState(int key)
	{
		KeyState state = KT_NORMAL;

		if (_pastDown[key] == false && _keyDown[key] == true)
		{
			state = KT_JUSTPRESSED;
		}
		else if (_pastDown[key] == true && _keyDown[key] == false)
		{
			state = KT_JUSTRELEASED;
		}
		else if (_pastDown[key] == true && _keyDown[key] == true)
		{
			state = KT_PRESSED;
		}

		return state;
	}

	KeyState SdlInput::GetMouseState(int key)
	{
		KeyState state = KT_NORMAL;

		if (_mousePast[key] == false && _mouseDown[key] == true)
		{
			state = KT_JUSTPRESSED;
		}
		else if (_mousePast[key] == true && _mouseDown[key] == false)
		{
			state = KT_JUSTRELEASED;
		}
		else if (_mousePast[key] == true && _mouseDown[key] == true)
		{
			state = KT_PRESSED;
		}

		return state;
	}

	void SdlInput::Update(double deltaTime)
	{
		// Move current key stat to past key state
		for (int i = 0; i < MAXBUFFKEYS; i++)
		{
			_pastDown[i] = _keyDown[i];
		}
		// Move mouse state
		for (int i = 0; i < MAXMOUSEKEYS; i++)
		{
			_mousePast[i] = _mouseDown[i];
		}

		_anyKey = false;
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_KEYDOWN:
			{
				int key = e.key.keysym.scancode;
				_keyDown[key] = true;
				_anyKey = true;
				ProcessKeyEvent(key);
			}
				break;
			case SDL_KEYUP:
			{
				int key = e.key.keysym.scancode;
				_keyDown[key] = false;
				ProcessKeyEvent(key);
			}
				break;
			case SDL_MOUSEBUTTONDOWN:
				_anyKey = true;
				switch (e.button.button)
				{
				case SDL_BUTTON_LEFT:
				{
					_mouseDown[MOUSE_BUTTON_LEFT] = true;
					ProcessMouseClick(MOUSE_BUTTON_LEFT);
				}
					break;
				case SDL_BUTTON_RIGHT:
				{
					_mouseDown[MOUSE_BUTTON_RIGHT] = true;
					ProcessMouseClick(MOUSE_BUTTON_RIGHT);
				}
					break;
				}
				break;
			case SDL_MOUSEBUTTONUP:
				switch (e.button.button)
				{
				case SDL_BUTTON_LEFT:
					_mouseDown[MOUSE_BUTTON_LEFT] = false;
					ProcessMouseClick(MOUSE_BUTTON_LEFT);
					break;
				case SDL_BUTTON_RIGHT:
					_mouseDown[MOUSE_BUTTON_RIGHT] = false;
					ProcessMouseClick(MOUSE_BUTTON_RIGHT);
					break;
				}
				break;
			case SDL_MOUSEMOTION:
				{
					ProcessMouseMove();
				}
				break;
			case SDL_QUIT:
			{
				EventArgs *e = new EventArgs(_events->NextId(), CPlusEngine::Events::ET_QUIT, this);
				_events->HandleEvent(e);
			}
				break;
			}
		}
	}

	void SdlInput::ProcessKeyEvent(int key)
	{
		// Process key event
		EventKeyArgs::Ptr evt = nullptr;
		// Need to detect the key state and send the proper event to the event manager
		KeyState state = GetState(key);
		switch (state)
		{
		case KeyState::KT_JUSTPRESSED:
		{
			evt = EventKeyArgs::Ptr(new EventKeyArgs(_events->NextId(), CPlusEngine::Events::ET_KEYDOWN, this, key, GetState(key)));
		}
			break;
		case KeyState::KT_JUSTRELEASED:
			evt = EventKeyArgs::Ptr(new EventKeyArgs(_events->NextId(), CPlusEngine::Events::ET_KEYUP, this, key, GetState(key)));
			break;
		default:
			evt = EventKeyArgs::Ptr(new EventKeyArgs(_events->NextId(), CPlusEngine::Events::ET_KEY, this, key, GetState(key)));
			break;
		}
		_events->HandleEvent(std::move(evt));
	}

	void SdlInput::ProcessMouseClick(int btn)
	{
		EventMouseArgs *evt = new EventMouseArgs(_events->NextId(), CPlusEngine::Events::ET_MOUSE_CLICK, this);
		switch (btn)
		{
		case MOUSE_BUTTON_LEFT:
			evt->Button = MouseButton::MB_LEFT;
			break;
		case MOUSE_BUTTON_RIGHT:
			evt->Button = MouseButton::MB_RIGHT;
			break;
		}

		SDL_GetMouseState(&evt->x, &evt->y);
		evt->State = GetMouseState(btn);
		_events->HandleEvent(evt);
	}

	void SdlInput::ProcessMouseMove()
	{
		EventMouseArgs *evt = new EventMouseArgs(_events->NextId(), CPlusEngine::Events::ET_MOUSE_MOVE, this);
		SDL_GetMouseState(&evt->x, &evt->y);
		evt->State = CPlusEngine::Events::KeyState::KT_NORMAL;
		evt->Button = MouseButton::MB_NONE;
		_events->HandleEvent(evt);
	}

	void SdlInput::SetEvents(CPlusEngine::Events::EventManager::SPtr em)
	{
		_events = em;
	}


} }// End namespace CPlusEngine::Input

