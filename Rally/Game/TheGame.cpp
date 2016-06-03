#include "TheGame.h"

namespace Rally
{

	TheGame::TheGame()
	{
		_isReady = false;
		_ctx = nullptr;
		_engine = nullptr;
		_factory = nullptr;
	}


	TheGame::~TheGame()
	{
	}

	void TheGame::Init()
	{
		_isReady = false;

		// Create game context for engine
		_ctx = Context::SPtr(new Context());
		if (_ctx == nullptr)
		{
			_errStack.push(EngineError::Ptr(new EngineError(6000, "Context was not able to instantiate.")));
			return;
		}

		_ctx->Events(EventManager::SPtr(new EventManager));
		_ctx->Graphics(SdlGfx::Ptr(new SdlGfx(_ctx->Events())));
		_ctx->Input(SdlInput::SPtr(new SdlInput()));

		_engine = std::unique_ptr<CoreEngine>(new CoreEngine());
		if (_engine == nullptr)
		{
			// Report engine failed to 
			_errStack.push(EngineError::Ptr(new EngineError(6001, "CoreEngine was not able to instantiate.")));
			return;
		}

		_engine->Context(_ctx);
		_engine->SetFps(60);
		_ctx->Graphics()->SetSceneSize(1024, 576);
		_engine->Init();

		if (!_engine->IsReady())
		{
			_errStack.push(EngineError::Ptr(new EngineError(6002, "CoreEngine failed to initialize.")));
			// Get error messages from the core engine for reporting
			for (auto err = _engine->LastError(); err != nullptr; err = _engine->LastError())
			{
				// Move error to my error stack...
				_errStack.push(std::move(err));
			}
			return;
		}

		// Create Entity Factory
		_factory = EntityFactory::SPtr(new EntityFactory());
		if (_factory == nullptr)
		{
			// Report instantion error
			_errStack.push(EngineError::Ptr(new EngineError(6003, "EntityFactory was not able to instantiate.")));
			return;
		}

		_factory->Init();
		// Check if factory successfully initialized
		if (!_factory->IsReady())
		{
			// Report EntityFactory error
			_errStack.push(EngineError::Ptr(new EngineError(6004, "EntityFactory failed to initialize.")));
			for (auto err = _factory->LastError(); err != nullptr; err = _factory->LastError())
			{
				_errStack.push(std::move(err));
			}
			
		}

		// Create UI Factory
		_ui = UIFactory::Ptr(new UIFactory(_ctx, _factory));
		if (_ui == nullptr)
		{
			// Report instantion error
			_errStack.push(EngineError::Ptr(new EngineError(6005, "UI Factory was not able to instantiate.")));
			return;
		}
		_ui->Init();
		if (!_ui->IsReady())
		{
			// Report EntityFactory error
			_errStack.push(EngineError::Ptr(new EngineError(6006, "UI yFactory failed to initialize.")));
			for (auto err = _factory->LastError(); err != nullptr; err = _factory->LastError())
			{
				_errStack.push(std::move(err));
			}
		}

		// Tie game into error events
		_ctx->Events()->Add(static_cast<LPHANDLER>(this), EventType::ET_ERROR);
		// Added this event so we can draw text to the screen.
		_ctx->Events()->Add(static_cast<LPHANDLER>(this), EventType::ET_ENDFRAME);

		// We are good so run the game!
		_isReady = true;
	}

	

	bool TheGame::IsReady()
	{
		return _isReady;
	}

	int TheGame::Run()
	{
		int retVal = -1;

		if (_isReady)
		{
			retVal = _engine->RunEngine();
		}

		return retVal;
	}

	void TheGame::MainMenu()
	{
		MenuItem btns[5];
		int idx = 0;
		btns[idx].text = "Play";
		btns[idx++].action = std::bind(&TheGame::Play, this);

		btns[idx].text = "Continue";
		btns[idx++].action = std::bind(&TheGame::Continue, this);

		btns[idx].text = "Network";
		btns[idx++].action = std::bind(&TheGame::Network, this);

		btns[idx].text = "Credits";
		btns[idx++].action = std::bind(&TheGame::Credits, this);

		btns[idx].text = "Exit";
		btns[idx++].action = std::bind(&TheGame::Quit, this);

		// Create a main menu scene
		_factory->CreateScene();
		// Load menu items background
		std::string bkgFile = _ctx->Graphics()->LibPath() + "rally.png";
		Camera::SPtr cam(new Camera(1));
		_factory->Scene()->Add(std::move(cam));
		 
		// Create menu panel
		Panel::Ptr menu = _ui->CreatePanel(bkgFile);
		menu->SetRect(iRect2DPtr(new iRect2D(0, 0, 1920, 1080)));
		menu->SetBackground(Panel::BackgroundSize::HV_Fit);
		// Add a button, okay there is a lot more to this!
		std::string btnFile = _ctx->Graphics()->LibPath() + "btnBkg.png";
		iRect2D norm(0, 0, 256, 40);
		iRect2D over(0, 40, 256, 40);
		iRect2D actv(0, 80, 256, 40);
		int buttonXCenter = norm.w / 2;
		float buttonY = 250.f;
		iVector2D screen = _ctx->Graphics()->ScreenSize();

		for (int i = 0; i < idx; ++i)
		{
			Button::Ptr btn = _ui->CreateButton(btnFile, btns[i].text, norm, over, actv, btns[i].action);
			btn->Transform()->Position((screen.x / 2 - buttonXCenter), buttonY);
			buttonY += 50;
			menu->Add(std::move(btn));
		}

		// Add panel to scene
		_factory->Add(std::move(menu));
		
		_engine->PushScene(_factory->Scene());
	}

	TheGame::EngineError::Ptr TheGame::LastError()
	{
		EngineError::Ptr err = nullptr;
		if (_errStack.size() > 0)
		{
			// Move top error to pointer
			err = std::move(_errStack.top());
			_errStack.pop();
		}

		// Return err object if there was one found
		return err;
	}

	void TheGame::ReportErrors()
	{
		// Report all error messages in the stack
		while (_errStack.size() > 0)
		{
			std::cerr << _errStack.top()->ToString() << std::endl;
			_errStack.pop();
		}
		// Report all engine errors
		for (auto err = _engine->LastError(); err != nullptr; err = _engine->LastError())
		{
			std::cerr << err->ToString() << std::endl;
		}
	}

#pragma region Event Methods

	void TheGame::HandleEvent(EventType type, EventArgs *e)
	{
		switch (type)
		{
		case EventType::ET_ERROR:
			_engine->Quit();
			ReportErrors();
#ifdef _DEBUG
			// Yes I know this is only a windows thing and will make this not compliant with other OS's!
			system("PAUSE");
#endif
			break;
		case EventType::ET_ENDFRAME:
			break;
		}
	}

	void TheGame::NullEvent()
	{
		// Nothing to do!
	}

	void TheGame::Play()
	{
		std::cerr << "You pressed play!" << std::endl;
	}

	void TheGame::Continue()
	{

	}

	void TheGame::Quit()
	{
		_engine->Quit();
	}

	void TheGame::Settings()
	{

	}

	void TheGame::Host()
	{

	}

	void TheGame::Connect()
	{

	}

	void TheGame::Network()
	{
		_engine->CurrentScene()->SetActive(false);
		// First we need a new scene
		_factory->CreateScene();
		std::string bkgFile = _ctx->Graphics()->LibPath() + "rally.png";
		Panel::Ptr net = _ui->CreatePanel(bkgFile);
		net->SetBackground(Panel::BackgroundSize::HV_Fit);

		Panel::Ptr menu = _ui->CreatePanel();
		iVector2D screen = _ctx->Graphics()->ScreenSize();
		// Set menu screen size
		net->SetRect(iRect2DPtr(new iRect2D(0, 0, 1920, 1080)));
		// Add default camera
		Camera::SPtr cam(new Camera(1));
		_factory->Scene()->Add(std::move(cam));
		_factory->Scene()->SetBlocking(true);


		// Create button data structures
		iRect2D norm(0, 0, 256, 40);
		iRect2D over(0, 40, 256, 40);
		iRect2D actv(0, 80, 256, 40);
		std::string btnFile = _ctx->Graphics()->LibPath() + "btnBkg.png";
		int buttonXCenter = norm.w / 2;
		menu->Transform()->Position((screen.x / 2) - buttonXCenter, 300);

		Button::Ptr host = _ui->CreateButton(btnFile, "Host", norm, over, actv, std::bind(&TheGame::NullEvent, this));
		host->Transform()->Position(0.f, 0.f);
		menu->Add(std::move(host));

		Button::Ptr join = _ui->CreateButton(btnFile, "Join", norm, over, actv, std::bind(&TheGame::NullEvent, this));
		join->Transform()->Position(0.f, 50.f);
		menu->Add(std::move(join));

		// Create back menu button
		Button::Ptr back = _ui->CreateButton(btnFile, "Back", norm, over, actv, std::bind(&TheGame::Back, this));
		back->Transform()->Position(0.f, 150.f);
		menu->Add(std::move(back));

		// Add back button to menu
		net->Add(std::move(menu));
		_factory->Add(std::move(net));


		// Add scene to the stack!
		_engine->PushScene(_factory->Scene());
	}

	void TheGame::Back()
	{
		// TODO: Remove events from scene when we remove them from the stack
		// Remove current scene from stack
		_engine->CurrentScene()->SetActive(false);
		_engine->PopScene();
		_engine->CurrentScene()->SetActive(true);
	}

	void TheGame::Credits()
	{
		_engine->CurrentScene()->SetActive(false);
		_factory->CreateScene();
		std::string bkgFile = _ctx->Graphics()->LibPath() + "rally.png";
		std::string btnFile = _ctx->Graphics()->LibPath() + "btnBkg.png";
		iVector2D size = _ctx->Graphics()->ScreenSize();

		Panel::Ptr screen = _ui->CreatePanel(bkgFile);
		screen->SetBackground(Panel::BackgroundSize::HV_Fit);
		screen->SetRect(iRect2DPtr(new iRect2D(0, 0, 1920, 1080)));

		Panel::Ptr menu = _ui->CreatePanel();
		
		iRect2D norm(0, 0, 256, 40);
		iRect2D over(0, 40, 256, 40);
		iRect2D actv(0, 80, 256, 40);
		int buttonXCenter = norm.w / 2;

		menu->Transform()->Position((float)(size.x / 2) - buttonXCenter, 300.f); 

		Button::Ptr back = _ui->CreateButton(btnFile, "Back", norm, over, actv, std::bind(&TheGame::Back, this));
		back->Transform()->Position(0.f, 150.f);
		menu->Add(std::move(back));

		screen->Add(std::move(menu));

		Panel::Ptr credits = _ui->CreatePanel();
		credits->Transform()->Position((float)(size.x / 2) - buttonXCenter, 300.f);

		// Add credits to me for all the hard work I have done
		Label::Ptr me(new Label(_factory->NextId(), "Engine Programmer:"));
		me->Transform()->Position(-80.f, 0.f);
		me->SetColor(GfxColor::Yellow);
		credits->Add(std::move(me));

		Label::Ptr name(new Label(_factory->NextId(), "Leland Ede"));
		name->Transform()->Position(200.f, 0.f);
		name->SetColor(GfxColor::White);
		credits->Add(std::move(name));

		screen->Add(std::move(credits));
				

		_factory->Add(std::move(screen));

		Camera::SPtr cam(new Camera(1));
		_factory->Scene()->Add(std::move(cam));
		_factory->Scene()->SetBlocking(true);

		_engine->PushScene(_factory->Scene());

	}

#pragma endregion

}// End namespace Rally


