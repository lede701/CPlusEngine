#ifndef H_UIBUTTON
#define H_UIBUTTON

#include <memory>
#include <map>
#include <functional>
#include "../Entity/Entity.h"
#include "../Entity/Components/Render/TextureRender.h"
#include "../Events/IHandler.h"
#include "../Graphics/GfxTexture.h"
#include "ButtonStates.h"

namespace CPlusEngine{ namespace UI
{

	class Button : public CPlusEngine::Entity::Entity, public CPlusEngine::Events::IHandler
	{
	public:
		typedef std::unique_ptr<Button> Ptr;
		typedef std::shared_ptr<Button> SPtr;

		typedef CPlusEngine::Graphics::GfxTexture Texture;
		typedef CPlusEngine::Entity::ComponentType ComponentType;
		typedef CPlusEngine::Entity::Component::Render::TextureRender TextureRender;

		// Event classes
		typedef CPlusEngine::Events::EventArgs EventArgs;
		typedef CPlusEngine::Events::EventType EventType;
		typedef CPlusEngine::Input::KeyState KeyState;

	private:
		bool _isReady;

		// Structure to hold button data information
		struct btnData{
			Texture::SPtr texture;
			iRect2D rect;
		};

		std::map<ButtonStates, btnData> _buttonData;

		ButtonStates _currState;
		ButtonStates _lastDrawnState;

		std::function<void()> _action;

	public:
#pragma region Ctors

		Button(unsigned int id);
		~Button();

		void Init();

#pragma endregion

#pragma region Button Setup Methods

		void Set(ButtonStates state, Texture::SPtr texture, iRect2D rect);
		void Set(ButtonStates state);

		void SetNormal(Texture::SPtr normal);
		void SetNormal(iRect2D rect);
		void SetOver(Texture::SPtr over);
		void SetOver(iRect2D rect);
		void SetActive(Texture::SPtr active);
		void SetActive(iRect2D rect);

		virtual iVector2D Size();

		virtual void Reset();

#pragma endregion

#pragma region Button State Methods

		bool IsHit(iVector2D rect);

#pragma endregion

#pragma region Component Overides

		virtual void Draw(CPlusEngine::Context::SPtr context);

#pragma endregion

#pragma region Event Handler

		virtual void HandleEvent(EventType type, EventArgs *e);

		// Button Action mutator method
		virtual void SetAction(std::function<void()> action);

		virtual void NullAction();

#pragma endregion


	};

} }// End namespace CPlusEngine::UI



#endif