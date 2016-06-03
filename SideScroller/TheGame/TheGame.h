#ifndef H_THEGAME
#define H_THEGAME

#include "../stdafx.h"
#include <PlusEngine/Controller/KeyboardController.h>

namespace DemoGame
{

	class TheGame : public CPlusEngine::Events::IHandler
	{
	public:
		typedef CPlusEngine::CoreEngine CoreEngine;
		typedef CPlusEngine::Context Context;
		typedef CPlusEngine::Scene Scene;
		typedef CPlusEngine::Entity::Entity Entity;
		typedef CPlusEngine::Entity::Component::Render::TextureRender Render;
		typedef CPlusEngine::Entity::Component::Updaters::UpdateCmp Updater;
		typedef CPlusEngine::Error::EngineError EngineError;
		typedef CPlusEngine::Events::EventManager EventManager;
		typedef CPlusEngine::Events::EventType EventType;
		typedef CPlusEngine::Input::KeyState KeyState;
		typedef CPlusEngine::Graphics::SdlGfx SdlGfx;
		typedef CPlusEngine::Graphics::GfxColor GfxColor;
		typedef CPlusEngine::Graphics::GfxTexture Texture;
		typedef CPlusEngine::Input::SdlInput SdlInput;
		typedef CPlusEngine::Objects::Cameras::Camera Camera;
		typedef CPlusEngine::Controller::KeyboardController Keyboard;
		typedef Keyboard::Ptr KeyboardPtr;
		typedef CPlusEngine::Factories::EntityFactory EntityFactory;


	private:
		CoreEngine::Ptr _engine;
		bool _isReady;

		iVector2D _center;
		iVector2D _mousePos;

		Camera::SPtr _camera;
		Updater* _me;
		KeyboardPtr _ctrl;

		EntityFactory::Ptr _eFactory;

		Texture* _demo;

		GfxColor _clr;

	public:
#pragma region Ctors

		TheGame();
		~TheGame();

		void Init();

#pragma endregion

#pragma region Game Methods

		bool IsReady();

		int Run();

		void LoadScene(unsigned int idx);

		void DrawGrid();

#pragma endregion

#pragma region IHandler Methods

		virtual void HandleEvent(void *obj, CPlusEngine::Events::EventType type, CPlusEngine::Events::EventArgs *e);
		virtual void HandleKeyEvent(void *obj, CPlusEngine::Events::EventKeyArgs *e);
		virtual void HandleMouseEvent(void *obj, CPlusEngine::Events::EventMouseArgs *e);

#pragma endregion



	};

}// End namespace TheGame

#endif



