#include "label.h"

namespace CPlusEngine{ namespace UI
{

	Label::Label(unsigned int id, std::string text) : Entity(id)
	{
		_text = text;
		_color = GfxColor::Black;
		_background = GfxColor::Clear;
		// Set default fonr information
		SetFont("arial-plain.ttf", 24);
	}


	Label::~Label()
	{
	}

#pragma region Component Overides

	void Label::Draw(CPlusEngine::Context::SPtr context)
	{
		Entity::Draw(context);
		iVector2DPtr pos(new iVector2D(Position()->ToInt().x, Position()->ToInt().y));
		// Check if we need to calculate center of parent object
		if (Parent() != nullptr)
		{
			auto btn = dynamic_cast<Button*>(Parent());
			if (btn != nullptr)
			{
				// TODO: Add alignment settings to this calculation
				float x = (float)(btn->Size().x / 2);
				float y = (float)(btn->Size().y / 2);
				// Get x and y adjustements so text is in center of button
				x = x - (context->Graphics()->Measure(_text, _font.font, _font.point).x / 2);
				y = y - (context->Graphics()->Measure(_text, _font.font, _font.point).y / 2);
				Transform()->Position(x, y);
			}
		}
		context->Graphics()->DrawText(_text, _color, _font.font, _font.point, pos);
		// Need a way to know how we want to position the label first
	}

#pragma endregion

#pragma region Mutators

	void Label::SetColor(GfxColor clr)
	{
		_color = clr;
	}

	void Label::SetBackground(GfxColor clr)
	{
		_background = clr;
	}

	void Label::SetAlign(unsigned int align)
	{
		_align = align;
	}

	void Label::SetFont(std::string fontName, int pt)
	{
		_font.font = fontName;
		_font.point = pt;
	}

#pragma endregion

} }// End namespace CPlusEngine::UI

