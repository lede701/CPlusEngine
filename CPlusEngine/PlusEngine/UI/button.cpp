#include "button.h"
#include <iostream>

#include "../Events/EventMouseArgs.h"

namespace CPlusEngine{ namespace UI
{
#pragma region Ctors

	Button::Button(unsigned int id) : CPlusEngine::Entity::Entity(id)
	{
		_currState = ButtonStates::BS_NORMAL;
		_lastDrawnState = ButtonStates::BS_NONE;
		_action = std::bind(&Button::NullAction, this);
	}


	Button::~Button()
	{
	}

	void Button::Init()
	{
		_isReady = false;

		// enums can be such a pain sometimes
		//Lazy code do not do this! :(
		_buttonData[_currState].texture = nullptr;
		_buttonData[_currState].rect = { 0, 0, 0, 0 };
		_buttonData[ButtonStates::BS_ACTIVE].texture = nullptr;
		_buttonData[ButtonStates::BS_ACTIVE].rect = { 0, 0, 0, 0 };
		_buttonData[ButtonStates::BS_OVER].texture = nullptr;
		_buttonData[ButtonStates::BS_OVER].rect = { 0, 0, 0, 0 };

		// Make sure we have a render for the button
		Add(TextureRender::Ptr(new TextureRender()));

		_isReady = true;
	}

#pragma endregion

#pragma region Button Setup Methods

	void Button::Set(ButtonStates state, Texture::SPtr texture, iRect2D rect)
	{
		switch (state)
		{
		case ButtonStates::BS_NORMAL:
			{
				SetNormal(std::move(texture));
				SetNormal(rect);
			}
			break;
		case ButtonStates::BS_OVER:
			{
				SetOver(std::move(texture));
				SetOver(rect);
			}
			break;
		case ButtonStates::BS_ACTIVE:
			{
				SetActive(std::move(texture));
				SetActive(rect);
			}
			break;
		}
	}

	void Button::Set(ButtonStates state)
	{
		_currState = state;
	}

	void Button::SetNormal(Texture::SPtr normal)
	{
		// Make sure normal is a valid object
		if (normal != nullptr)
		{
			_buttonData[ButtonStates::BS_NORMAL].texture = normal;
		}
	}

	void Button::SetNormal(iRect2D rect)
	{
		_buttonData[ButtonStates::BS_NORMAL].rect = rect;
	}

	void Button::SetOver(Texture::SPtr over)
	{
		// Make sure over is a valid object
		if (over != nullptr)
		{
			_buttonData[ButtonStates::BS_OVER].texture = over;
		}
	}

	void Button::SetOver(iRect2D rect)
	{
		_buttonData[ButtonStates::BS_OVER].rect = rect;
	}

	void Button::SetActive(Texture::SPtr active)
	{
		// Make sure active is a valid object
		if (active != nullptr)
		{
			_buttonData[ButtonStates::BS_ACTIVE].texture = active;
		}
	}

	void Button::SetActive(iRect2D rect)
	{
		_buttonData[ButtonStates::BS_ACTIVE].rect = rect;
	}

	iVector2D Button::Size()
	{
		iVector2D size(_buttonData[_currState].rect.w, _buttonData[_currState].rect.h);
		return size;
	}

	void Button::Reset()
	{
		// Reset button state
		_currState = ButtonStates::BS_NORMAL;
		_lastDrawnState = ButtonStates::BS_NONE;
	}


#pragma endregion

#pragma region Button State Methods

	bool Button::IsHit(iVector2D hit)
	{
		// Get current position of button
		iVector2D pos = Position()->ToInt();
		iRect2D src = _buttonData[_currState].rect;
		iRect2D collider(pos.x, pos.y, pos.x + src.w, pos.y + src.h);
		 
		return (hit.x >= collider.x && hit.y >= collider.y
			&& hit.x <= collider.w && hit.y <= collider.h);
	}

#pragma endregion

#pragma region Component Overides

	void Button::Draw(CPlusEngine::Context::SPtr context)
	{
		if (_currState != _lastDrawnState)
		{
			// Get current state graphic
			iRect2D src = _buttonData[_currState].rect;
			iVector2D pos = Position()->ToInt();
			// Need to feed dest to the render component
			if ((*Components())[ComponentType::CT_RENDER].size() > 0)
			{
				TextureRender* render = (TextureRender*)(*Components())[ComponentType::CT_RENDER].front().get();
				render->SetRect(iRect2DPtr(new iRect2D(src.x, src.y, src.w, src.h)));
				render->SetTexture(_buttonData[_currState].texture);
			}
			// Set the last drawn state to current state so we don't do this again
			_lastDrawnState = _currState;
		}// Endif _currState not equal _lastDrawnState

		// Pass drawing to entity
		Entity::Draw(context);
	}

#pragma endregion

#pragma region Event Handler

	void Button::HandleEvent(EventType type, EventArgs *e)
	{
		if (IsActive())
		{
			if (type == EventType::ET_MOUSE_MOVE || type == EventType::ET_MOUSE_CLICK)
			{
				auto me = static_cast<CPlusEngine::Events::EventMouseArgs*>(e);
				iVector2D hit(me->x, me->y);
				_currState = ButtonStates::BS_NORMAL;
				if (IsHit(hit))
				{
					switch (type)
					{
					case EventType::ET_MOUSE_MOVE:
						_currState = ButtonStates::BS_OVER;
						break;
					case EventType::ET_MOUSE_CLICK:
					{
						// Set current action to active after clicked.
						_currState = ButtonStates::BS_ACTIVE;
						// Check if the click has been released
						if (me->State == KeyState::KT_JUSTRELEASED)
						{
							// Call action for this button
							_action();
						}// Endif state has just been released
					}
					break;
					}// End switch type
				}// Endif was hit
			}// Endif EventType is mouse move or mouse click
		}// Endif is entity active
	}

	void Button::SetAction(std::function<void()> action)
	{
		_action = action;
	}

	void Button::NullAction()
	{
		// Do nothing...
		std::cerr << "No action for button." << std::endl;
	}

#pragma endregion

} }// End namespace CPlusEngine::UI

