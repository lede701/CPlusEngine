#include "panel.h"

namespace CPlusEngine{ namespace UI
{

	Panel::Panel(unsigned int id, Texture::SPtr texture/* = nullptr*/, unsigned int layer/* = 5*/) : CPlusEngine::Entity::Entity(id, layer)
	{
		if (texture != nullptr)
		{
			// Panel has a background so we need to auto add a renderer
			PanelRender::Ptr render(new PanelRender());
			render->SetTexture(std::move(texture));
			// TODO: Need to add a way to access the renderer object
			Add(std::move(render));
		}
	}


	Panel::~Panel()
	{
	}

#pragma region Render Methods

	Panel::PanelRender::RealPtr Panel::Render()
	{
		// Need access to the entity components
		PanelRender::RealPtr render = nullptr;

		Entity::CmpData* cmps = Components();

		if ((*cmps)[ComponentType::CT_RENDER].size() > 0)
		{
			// Return the first render which maybe a bug!
			render = static_cast<PanelRender::RealPtr>((*cmps)[ComponentType::CT_RENDER].front().get());
		}

		return render;
	}

	std::stack<Panel::PanelRender::RealPtr> Panel::Renders()
	{
		// I really don't like this design but it is an evil I need for now
		std::stack<PanelRender::RealPtr> renders;
		/*
		if (Components()[ComponentType::CT_RENDER].size() > 0)
		{
		for (auto cmp = Components()[ComponentType::CT_RENDER].begin(); cmp != Components()[ComponentType::CT_RENDER].end(); ++cmp)
		{
		// This will get fugly!
		renders.push(static_cast<TextureRender::RealPtr>((*cmp).get()));
		}
		}
		//*/
		// What a waste of memory :(
		return renders;
	}

	void Panel::SetRect(iRect2DPtr rect)
	{
		if (Render() != nullptr)
		{
			Render()->SetRect(std::move(rect));
		}
	}

#pragma endregion

#pragma region Entity Overides

	void Panel::Draw(CPlusEngine::Context::SPtr ctx)
	{

		switch (_backSize)
		{
		case BackgroundSize::HV_Fit:
			{
				iVector2D screen = ctx->Graphics()->ScreenSize();
				Render()->SetBackSize(iVector2DPtr(new iVector2D(screen.x, screen.y)));
			}
			break;
		}

		// Call parent draw utility
		Entity::Draw(ctx);

	}

#pragma endregion

#pragma region Background Methods

	void Panel::SetBackground(BackgroundSize size)
	{
		_backSize = size;
	}

	void Panel::SetBackground(iRect2D rect)
	{
		_backRect = rect.ToFloat();
	}

	void Panel::SetBackground(fRect2D rect)
	{
		_backRect = rect;
	}

	void Panel::SetBackground(BackgroundSize size, iRect2D rect)
	{
		_backSize = size;
		_backRect = rect.ToFloat();
	}

#pragma endregion

#pragma region Event Methods

	void Panel::Reset()
	{

	}

#pragma endregion


} }// End namespace CPlusEngine::UI


