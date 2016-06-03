#include "KeyboardController.h"
#include "Commands/CmdHorizontal.h"
#include "Commands/CmdVertical.h"
#include "../Events/EventKeyArgs.h"
#include "../Input/KeyCodes.h"
#include "../Input/KeyState.h"

namespace CPlusEngine{ namespace Controller
{

#pragma region CTors

	KeyboardController::KeyboardController(unsigned int id, UpdaterRealPtr updater, bool AutoSetup/* = true*/)
	{
		_id = id;
		_input = nullptr;
		_isReady = false;
		_updater = updater;
		Clear();
		if (AutoSetup)
		{
			AutoKeyController();
		}
	}


	KeyboardController::~KeyboardController()
	{
		Clear();
	}

	void KeyboardController::Init()
	{
		_isReady = false;
		if (_input == nullptr)
		{
			// TODO: Need to report initialization error message
			return;
		}

		_isReady = true;
	}

#pragma endregion

#pragma region Controller Utilities

	void KeyboardController::AutoKeyController()
	{
		using Commands::CmdVertical;
		using Commands::CmdHorizontal;
		
		// Create vertical movement
		CmdVertical::Ptr cmd(new CmdVertical(0, -5.f));
		cmd->SetCode(KC_W);
		_cmdMap[cmd->Code()] = std::move(cmd);
		cmd = CmdVertical::Ptr(new CmdVertical(1, 5.f));
		cmd->SetCode(KC_S);
		_cmdMap[cmd->Code()] = std::move(cmd);

		// Create horizontal movement
		cmd = CmdHorizontal::Ptr(new CmdHorizontal(2, -5.f));
		cmd->SetCode(KC_A);
		_cmdMap[cmd->Code()] = std::move(cmd);
		cmd = CmdHorizontal::Ptr(new CmdHorizontal(2, 5.f));
		cmd->SetCode(KC_D);
		_cmdMap[cmd->Code()] = std::move(cmd);

	}

	void KeyboardController::Clear()
	{
		_cmdMap.clear();
	}

	unsigned int KeyboardController::Id()
	{
		return _id;
	}

	bool KeyboardController::IsReady()
	{
		return _isReady;
	}

#pragma endregion

#pragma region IHandler Methods

	void KeyboardController::HandleEvent(void *obj, EventType type, EventArgs *e)
	{
		using CPlusEngine::Input::KeyState;
		// Convert arguments to key argument
		auto ke = static_cast<CPlusEngine::Events::EventKeyArgs*>(e);
		// Check for valid input
		if (ke != nullptr && _cmdMap[ke->Key] != nullptr)
		{
			if (ke->State == KeyState::KT_JUSTPRESSED)
			{
				_cmdMap[ke->Key]->RunCommand(_updater);
			}
			else if (ke->State == KeyState::KT_JUSTRELEASED)
			{
				_cmdMap[ke->Key]->StopCommand(_updater);
			}
		}
	}

#pragma endregion

#pragma region Command Methods

	void KeyboardController::Add(CommandPtr cmd)
	{
		if (cmd != nullptr)
		{
			_cmdMap[cmd->Code()] = std::move(cmd);
		}
	}

	void KeyboardController::Remove(CommandRealPtr cmd)
	{
		// This will automagically delete after scope
		CommandPtr delCmd = std::move(_cmdMap[cmd->Code()]);
	}

#pragma endregion


} }// End namespace CPlusEngine::Controllers


