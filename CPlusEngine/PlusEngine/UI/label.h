#ifndef H_LABEL
#define H_LABEL

#include <memory>
#include <map>
#include <string>
#include "UIAlign.h"
#include "UIFont.h"
#include "button.h"
#include "../Entity/Entity.h"
#include "../Entity/Components/Render/TextureRender.h"
#include "../Events/IHandler.h"
#include "../Graphics/GfxColor.h"

namespace CPlusEngine{ namespace UI
{

	class Label : public CPlusEngine::Entity::Entity
	{
	public:
		typedef std::unique_ptr<Label> Ptr;
		typedef std::shared_ptr<Label> SPtr;

		typedef CPlusEngine::Graphics::GfxColor GfxColor;

	private:
		std::string _text;

		GfxColor _color;
		GfxColor _background;

		unsigned int _align;

		UIFont _font;

	public:
#pragma region Ctors

		Label(unsigned int id, std::string text);
		~Label();

#pragma endregion

#pragma region Mutators

		void SetColor(GfxColor clr);
		void SetBackground(GfxColor clr);

		void SetAlign(unsigned int align);
		void SetFont(std::string fontName, int pt);

#pragma endregion

#pragma region Component Overides

		virtual void Draw(CPlusEngine::Context::SPtr context);

#pragma endregion

	};

} }// End namespace CPlusEngine::UI



#endif