#include "UIFactory.h"

namespace CPlusEngine{ namespace Factories
{
#pragma region Ctors

	UIFactory::UIFactory(Context::SPtr ctx, EntityFactory::SPtr factory)
	{
		_ctx = ctx;
		_factory = factory;
	}


	UIFactory::~UIFactory()
	{
	}

	void UIFactory::Init()
	{
		_isReady = false;
		// Validate context object
		if (_ctx == nullptr)
		{
			// Report Error!
			_errStack.push(EngineError::Ptr(new EngineError(5050, "UI Factory has an invalid context.")));
			return;
		}

		// Validate factory object
		if (_factory == nullptr)
		{
			_errStack.push(EngineError::Ptr(new EngineError(5051, "UI Factory has an invalid Entity Factory.")));
			return;
		}

		// Validation is complete!
		_isReady = true;
	}

#pragma endregion

#pragma region Status Methods

	bool UIFactory::IsReady()
	{
		return _isReady;
	}

	UIFactory::EngineError::Ptr UIFactory::LastError()
	{
		EngineError::Ptr err = nullptr;
		if (_errStack.size() > 0)
		{
			// move error to new object
			err = std::move(_errStack.top());
			// Remove old item from stack so we don't get a fugly error
			_errStack.pop();
		}// Endif _errStack has items in structure

		return err;
	}

#pragma endregion

#pragma region UI Methods

	UIFactory::Panel::Ptr UIFactory::CreatePanel()
	{
		// Create panel with no background
		Panel::Ptr panel(new Panel(_factory->NextId()));
		return panel;
	}

	UIFactory::Panel::Ptr UIFactory::CreatePanel(std::string bkgFile)
	{
		// Create new panel and load image from file
		Panel::Ptr panel(new Panel(_factory->NextId(), _ctx->Graphics()->LoadImage(bkgFile)));
		return panel;
	}

	UIFactory::Panel::Ptr UIFactory::CreatePanel(GfxTexture::SPtr background)
	{
		// Create panel with new background
		Panel::Ptr panel(new Panel(_factory->NextId(), background));
		return panel;
	}

	UIFactory::Button::Ptr UIFactory::CreateButton()
	{
		// Create a new button. Duh...
		Button::Ptr btn(new Button(_factory->NextId()));
		btn->Init();
		// Connect button to events
		_ctx->Events()->Add(static_cast<LPHANDLER>(btn.get()), EventType::ET_MOUSE_MOVE);
		_ctx->Events()->Add(static_cast<LPHANDLER>(btn.get()), EventType::ET_MOUSE_CLICK);

		return btn;
	}

	UIFactory::Button::Ptr UIFactory::CreateButton(std::string spriteFile)
	{
		// Create a new button
		Button::Ptr btn(new Button(_factory->NextId()));
		btn->Init();
		// Connect button to events
		_ctx->Events()->Add(static_cast<LPHANDLER>(btn.get()), EventType::ET_MOUSE_MOVE);
		_ctx->Events()->Add(static_cast<LPHANDLER>(btn.get()), EventType::ET_MOUSE_CLICK);

		// Load texture
		GfxTexture::SPtr texture = _ctx->Graphics()->LoadImage(spriteFile);
		// Set texture for all button states
		btn->SetNormal(texture);
		btn->SetOver(texture);
		btn->SetActive(texture);

		return btn;
	}

	UIFactory::Button::Ptr UIFactory::CreateButton(std::string spriteFile, iRect2D normal, iRect2D over, iRect2D active, std::function<void()> action)
	{
		Button::Ptr btn = CreateButton(spriteFile);
		btn->SetNormal(normal);
		btn->SetOver(over);
		btn->SetActive(active);
		btn->SetAction(action);

		return btn;
	}

	UIFactory::Button::Ptr UIFactory::CreateButton(std::string spriteFile, std::string text, iRect2D normal, iRect2D over, iRect2D active, std::function<void()> action)
	{
		Button::Ptr btn = CreateButton(spriteFile);
		btn->SetNormal(normal);
		btn->SetOver(over);
		btn->SetActive(active);
		btn->SetAction(action);

		Label::Ptr label(new Label(_factory->NextId(), text));
		label->SetColor(GfxColor::White);
		label->SetAlign((int)UIAlign::HCENTER);
		label->SetFont("arial-plain.ttf", 28);
		btn->Add(std::move(label));
		
		return btn;
	}


#pragma endregion

} }// End namespace CPlusEngine::UI

