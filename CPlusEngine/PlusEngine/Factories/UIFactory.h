#ifndef H_UIFACTORY
#define H_UIFACTORY

#include <memory>
#include <stack>
#include <functional>

#include "../UI/ui.h"
#include "../Context.h"
#include "../Graphics/GfxTexture.h"
#include "../Error/EngineError.h"
#include "../Events/EventType.h"
#include "EntityFactory.h"

namespace CPlusEngine{ namespace Factories
{

	class UIFactory
	{
	public:
		typedef std::unique_ptr<UIFactory> Ptr;
		typedef std::shared_ptr<UIFactory> SPtr;

		typedef CPlusEngine::Context Context;
		typedef CPlusEngine::Graphics::GfxTexture GfxTexture;
		typedef CPlusEngine::Graphics::GfxColor GfxColor;

		typedef CPlusEngine::Error::EngineError EngineError;

		// UI Items
		typedef CPlusEngine::UI::Panel Panel;
		typedef CPlusEngine::UI::Button Button;
		typedef CPlusEngine::UI::Label Label;
		typedef CPlusEngine::UI::UIAlign UIAlign;

		typedef CPlusEngine::Events::EventType EventType;

	private:
		bool _isReady;

		Context::SPtr _ctx;
		EntityFactory::SPtr _factory;

		std::stack<EngineError::Ptr> _errStack;

	public:
#pragma region Ctors

		UIFactory(Context::SPtr ctx, EntityFactory::SPtr factory);
		~UIFactory();

		void Init();

#pragma endregion

#pragma region Status Methods

		bool IsReady();

		EngineError::Ptr LastError();

#pragma endregion

#pragma region UI Methods

		Panel::Ptr CreatePanel();
		Panel::Ptr CreatePanel(std::string bkgFile);
		Panel::Ptr CreatePanel(GfxTexture::SPtr background);

		Button::Ptr CreateButton();
		Button::Ptr CreateButton(std::string spriteFile);
		Button::Ptr CreateButton(std::string spriteFile, iRect2D normal, iRect2D over, iRect2D active, std::function<void()> action);
		Button::Ptr CreateButton(std::string spriteFile, std::string text, iRect2D normal, iRect2D over, iRect2D active, std::function<void()> action);

#pragma endregion

	};

} }// End namespace CPlusEngine::UI


#endif