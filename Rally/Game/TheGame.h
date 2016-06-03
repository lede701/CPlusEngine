#ifndef H_THEGAME_RALLY
#define H_THEGAME_RALLY

#include "../stdafx.h"

namespace Rally
{

	class TheGame : public CPlusEngine::Events::IHandler
	{
	public:
		typedef CPlusEngine::CoreEngine CoreEngine;
		typedef CPlusEngine::Context Context;
		typedef CPlusEngine::Events::EventManager EventManager;
		typedef CPlusEngine::Graphics::SdlGfx SdlGfx;
		typedef CPlusEngine::Input::SdlInput SdlInput;
		typedef CPlusEngine::Scene Scene;
		typedef CPlusEngine::Entity::Entity Entity;
		typedef CPlusEngine::Objects::Cameras::Camera Camera;
		typedef CPlusEngine::Error::EngineError EngineError;

		// Graphics
		typedef CPlusEngine::Graphics::GfxColor GfxColor;

		// Factories
		typedef CPlusEngine::Factories::EntityFactory EntityFactory;
		typedef CPlusEngine::Factories::UIFactory UIFactory;

		// Event objects
		typedef CPlusEngine::Events::EventArgs EventArgs;
		typedef CPlusEngine::Events::EventType EventType;

		// User Interface Classes
		typedef CPlusEngine::UI::Panel Panel;
		typedef CPlusEngine::UI::Button Button;
		typedef CPlusEngine::UI::Label Label;

	private:
		CoreEngine::Ptr _engine;
		Context::SPtr _ctx;
		EntityFactory::SPtr _factory;
		UIFactory::Ptr _ui;

		std::stack<EngineError::Ptr> _errStack;
		
		bool _isReady;

		struct MenuItem
		{
			std::string text;
			std::function<void()> action;
		};

	public:
#pragma region Ctors

		TheGame();
		~TheGame();

		void Init();

#pragma endregion

#pragma region Game Scenes

		void MainMenu();
		void LoadLevel();

#pragma endregion

		bool IsReady();

		int Run();

#pragma region Error Utilities

		// Connect the error system for reporting purposes!
		EngineError::Ptr LastError();

		void ReportErrors();

#pragma endregion

#pragma region Event Methods

		virtual void HandleEvent(EventType type, EventArgs *e);

		virtual void NullEvent();
		virtual void Play();
		virtual void Continue();
		virtual void Quit();
		virtual void Settings();
		virtual void Host();
		virtual void Connect();
		virtual void Network();
		virtual void Credits();
		virtual void Back();

#pragma endregion

	};

}// End namespace Rally



#endif