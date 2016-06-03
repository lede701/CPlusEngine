#ifndef H_PANEL
#define H_PANEL

#include <memory>
#include <stack>
#include "../Entity/Entity.h"
#include "../Graphics/GfxTexture.h"
#include "../Entity/Components/components.h"

namespace CPlusEngine{ namespace UI
{

	class Panel : public CPlusEngine::Entity::Entity
	{
	public:
		typedef std::unique_ptr<Panel> Ptr;
		typedef std::shared_ptr<Panel> SPtr;

		typedef CPlusEngine::Graphics::GfxTexture Texture;
		typedef CPlusEngine::Entity::Component::Render::PanelRender PanelRender;
		typedef CPlusEngine::Entity::ComponentType ComponentType;

		typedef std::map<ComponentType, std::vector<Entity::Ptr>> vComponents;

		enum class BackgroundSize
		{
			V_Fit,
			H_Fit,
			HV_Fit,
			Custom,
			Normal
		};

	private:

		fRect2D _backRect;
		BackgroundSize _backSize;

	public:
		Panel(unsigned int id, Texture::SPtr texture = nullptr, unsigned int layer = 5);
		~Panel();

#pragma region Entity Overides

		virtual void Draw(CPlusEngine::Context::SPtr context);

#pragma endregion
		
#pragma region Render Methods

		PanelRender::RealPtr Render();
		std::stack<PanelRender::RealPtr> Renders();

		void SetRect(iRect2DPtr rect);

#pragma endregion

#pragma region Background Methods

		void SetBackground(BackgroundSize size);
		void SetBackground(iRect2D rect);
		void SetBackground(fRect2D rect);
		void SetBackground(BackgroundSize size, iRect2D rect);

#pragma endregion

#pragma region Event Methods

		void Reset();

#pragma endregion
		
	};

} }// End namespace CPlusEngine::UI


#endif