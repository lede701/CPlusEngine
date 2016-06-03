#include "TheGame.h"

namespace DemoGame
{
#pragma region Ctors

	TheGame::TheGame()
	{
		_engine = nullptr;
		_isReady = false;
		_demo = nullptr;
		_clr = { 128, 128, 128, 80 };
	}


	TheGame::~TheGame()
	{
		_demo = nullptr;
	}

	void TheGame::Init()
	{
		_isReady = false;

		// Build context for game engine
		Context::SPtr ctx(new Context());
		ctx->Events(EventManager::SPtr(new EventManager()));
		ctx->Graphics(SdlGfx::Ptr(new SdlGfx(ctx->Events())));
		// TODO: When changing screen size destroy window and recreate it
		//ctx->Graphics()->SetSceneSize(1024, 536);
		ctx->Input(SdlInput::SPtr(new SdlInput()));

		_center.x = ctx->Graphics()->ScreenSize().x / 2u;
		_center.y = ctx->Graphics()->ScreenSize().y / 2u;

		_engine = CoreEngine::Ptr(new CoreEngine());
		_engine->Context(ctx);
		_engine->SetFps(60);
		_engine->Init();

		// Report errors
		EngineError::Ptr err = std::move(_engine->LastError());
		if (err != nullptr)
		{
			do
			{
				// TODO: Move this to an error logging system
				std::cerr << err->ToString() << std::endl;
				err = std::move(_engine->LastError());
			} while (err != nullptr);
			return;
		}

		// Build Factories
		_eFactory = EntityFactory::Ptr(new EntityFactory());
		_eFactory->Init();
		if (!_eFactory->IsReady())
		{
			// Report error!
			std::cerr << "Factory failed to initialize!" << std::endl;
			return;
		}

		// Add game event managment
		ctx->Events()->Add(static_cast<LPHANDLER>(this), nullptr, EventType::ET_KEYDOWN);
		ctx->Events()->Add(static_cast<LPHANDLER>(this), nullptr, EventType::ET_KEYUP);
		ctx->Events()->Add(static_cast<LPHANDLER>(this), nullptr, EventType::ET_MOUSE_MOVE);
		ctx->Events()->Add(static_cast<LPHANDLER>(this), nullptr, EventType::ET_MOUSE_CLICK);
		ctx->Events()->Add(static_cast<LPHANDLER>(this), nullptr, EventType::ET_ENDFRAME);

		// Load demo texture
		std::string file = ctx->Graphics()->LibPath() + "RockHeadSpriteSheet.png";

		_isReady = true;
	}

#pragma endregion

#pragma region Game Methods

	int TheGame::Run()
	{
		int retVal = -1;

		if (_isReady)
		{
			retVal = _engine->RunEngine();
		}

		return retVal;
	}

	bool TheGame::IsReady()
	{
		return _isReady;
	}

	void TheGame::LoadScene(unsigned int id)
	{
		using CPlusEngine::Entity::Component::Updaters::UpdateCmp;

		// Create a new scene
		_eFactory->CreateScene();

		Entity::Ptr entity = _eFactory->CreateEntity();
		// TODO: Move camera creation to the factory
		_camera = Camera::SPtr(new Camera(1));

		std::string file = _engine->Context()->Graphics()->LibPath() + "vase.png";
		// Add a render object to entity
		entity = _eFactory->CreateRender(std::move(entity), _engine->Context()->Graphics()->LoadImage(file), iRect2DPtr(new iRect2D(0, 0, 40, 40)));
		Updater::Ptr mover = _eFactory->CreateMover();
		mover->SetParent(entity.get());
		_me = mover.get();
		entity->Add(std::move(mover));

		// TODO: Change the real pointer to a shared pointer
		_ctrl = KeyboardPtr(new Keyboard(0, _me));
		// Link controller to the event system
		_engine->Context()->Events()->Add(static_cast<LPHANDLER>(_ctrl.get()), this, EventType::ET_KEYDOWN);
		_engine->Context()->Events()->Add(static_cast<LPHANDLER>(_ctrl.get()), this, EventType::ET_KEYUP);
		// Set initial entity position
		entity->Transform()->Position(500.f, 350.f);

		// Add entity to scene
		_eFactory->Add(std::move(entity));
		// Setup camera
		iVector2D screenSize = _engine->Context()->Graphics()->ScreenSize();
		_camera->SetViewSize(screenSize.x, screenSize.y);
		_eFactory->Scene()->Add(_camera);
		// Push scene on to the scene stack
		_engine->PushScene(_eFactory->Scene());

		if (!_engine->IsReady())
		{
			// An error occured and we need to report this!
			while (EngineError::Ptr err = std::move(_engine->LastError()))
			{
				std::cerr << err->ToString() << std::endl;
			}
		}
	}

	void TheGame::DrawGrid()
	{
		iVector2D screen = _engine->Context()->Graphics()->ScreenSize();
		iVector2D camPos = _camera->Position()->ToInt();

		int widthSpace = screen.x / 25;
		int heightSpace = screen.y / 20;

		// Set gride offset to fake drawing lines everywhere :D
		camPos.x = camPos.x % widthSpace;
		camPos.y = camPos.y % heightSpace;

		for (int i = 0; i < widthSpace; ++i)
		{
			fVector2DPtr st(new fVector2D(i*widthSpace - camPos.x, 0));
			fVector2DPtr en(new fVector2D(i*widthSpace - camPos.x, screen.y));
			_engine->Context()->Graphics()->DrawLine(std::move(st), std::move(en), 1.f, _clr);
		}
		for (int i = 0; i < heightSpace; ++i)
		{
			fVector2DPtr st(new fVector2D(0, i*heightSpace - camPos.y));
			fVector2DPtr en(new fVector2D(screen.x, i*heightSpace - camPos.y));
			_engine->Context()->Graphics()->DrawLine(std::move(st), std::move(en), 1.f, _clr);
		}
	}

#pragma endregion

#pragma region IHandler Methods

	void TheGame::HandleEvent(void *obj, CPlusEngine::Events::EventType type, CPlusEngine::Events::EventArgs *e)
	{
		switch (e->Type)
		{
		case EventType::ET_KEYUP:
		case EventType::ET_KEYDOWN:
			{
				auto ke = static_cast<CPlusEngine::Events::EventKeyArgs*>(e);
				HandleKeyEvent(obj, ke);
			}
			break;
		case EventType::ET_MOUSE_CLICK:
		case EventType::ET_MOUSE_MOVE:
			{
				auto me = static_cast<CPlusEngine::Events::EventMouseArgs*>(e);
				HandleMouseEvent(obj, me);
			}
			break;
		case EventType::ET_ENDFRAME:
			{
				fVector2DPtr st(new fVector2D(_center.x, _center.y));
				fVector2DPtr en(new fVector2D(_mousePos.x, _mousePos.y));
				GfxColor clr = GfxColor::Blue;
				clr.a = 80;
				_engine->Context()->Graphics()->DrawLine(std::move(st), std::move(en), 1.0f, clr);
				DrawGrid();
		}
			break;

		}
	
	}

	void TheGame::HandleKeyEvent(void *obj, CPlusEngine::Events::EventKeyArgs *e)
	{
		float camSpeed = 5.f;
		// TODO: Convert this into a controller
		// Never use something like this in production!!!!! This isn't just ugle it is fugly
		switch (e->Key)
		{
		case KC_LEFT:
			{
				if (e->State == KeyState::KT_JUSTPRESSED)
				{
					_camera->Velocity(camSpeed, _camera->Velocity().y);
				}
				else
				{
					_camera->Velocity(0.f, _camera->Velocity().y);
				}
			}
			break;
		case KC_RIGHT:
				if (e->State == KeyState::KT_JUSTPRESSED)
				{
					_camera->Velocity(-camSpeed, _camera->Velocity().y);
				}
				else
				{
					_camera->Velocity(0.f, _camera->Velocity().y);
				}
			break;
		case KC_DOWN:
				if (e->State == KeyState::KT_JUSTPRESSED)
				{
					_camera->Velocity(_camera->Velocity().x, -camSpeed);
				}
				else
				{
					_camera->Velocity(_camera->Velocity().x, 0.f);
				}
			break;
		case KC_UP:
				if (e->State == KeyState::KT_JUSTPRESSED)
				{
					_camera->Velocity(_camera->Velocity().x, camSpeed);
				}
				else
				{
					_camera->Velocity(_camera->Velocity().x, 0.f);
				}
			break;
		}

		// Fire once keys only
		if (e->State == KeyState::KT_JUSTRELEASED)
		{
			switch (e->Key)
			{
			case KC_F1:
				{
					std::cerr << "Game F1 needs to be handled." << std::endl;
				}
				break;
			case KC_MINUS:
				{
					_clr.a -= 10;
					std::cerr << _clr.ToString() << std::endl;
				}
				break;
			case KC_EQUAL:
				{
					_clr.a += 10;
					std::cerr << _clr.ToString() << std::endl;
				}
				break;
			default:
				{
					// Drop key event we don't have anything to do here
				}
				break;
			}
		}

	}

	void TheGame::HandleMouseEvent(void *obj, CPlusEngine::Events::EventMouseArgs *e)
	{
		if(e->Type == EventType::ET_MOUSE_CLICK)
		{
			// Mouse clicks are being recorded!!!!
			if (e->State == KeyState::KT_JUSTRELEASED)
			{
				iVector2D mPos(e->x, e->y);
				iVector2D wPos = mPos - _camera->Position()->ToInt();
				std::cerr << mPos.ToString() << ", " << wPos.ToString() << std::endl;
			}
		}
		if (e->Type == EventType::ET_MOUSE_MOVE)
		{
			_mousePos.x = e->x;
			_mousePos.y = e->y;
		}

	}


#pragma endregion

}// End namespace TheGame

