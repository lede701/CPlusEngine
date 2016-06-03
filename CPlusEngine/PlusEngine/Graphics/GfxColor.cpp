#include "GfxColor.h"

#include <sstream>

namespace CPlusEngine{ namespace Graphics
{
	GfxColor::GfxColor()
	{
		r = 0;
		g = 0;
		b = 0;
		a = 0xff;
	}

	GfxColor::GfxColor(uint8 ir, uint8 ig, uint8 ib)
	{
		r = ir;
		g = ig;
		b = ib;
		a = 0xff;
	}

	GfxColor::GfxColor(uint8 ir, uint8 ig, uint8 ib, uint8 ia)
	{
		r = ir;
		g = ig;
		b = ib;
		a = ia;
	}

	std::string GfxColor::ToString()
	{
		std::ostringstream out;
		out << "R: " << r << " G: " << g << "B: " << b << " A:" << a;
		return out.str();
	}

	const GfxColor GfxColor::White(0xff, 0xff, 0xff);
	const GfxColor GfxColor::Red(0xff, 0x00, 0x00);
	const GfxColor GfxColor::Green(0x00, 0xff, 0x00);
	const GfxColor GfxColor::Blue(0x00, 0x00, 0xff);
	const GfxColor GfxColor::Black(0,0,0);
	const GfxColor GfxColor::Grey(128, 128, 128);
	const GfxColor GfxColor::DkGrey(64, 64, 64);
	const GfxColor GfxColor::Yellow(255, 255, 0);
	const GfxColor GfxColor::Clear(0, 0, 0, 0);

} }// End namespace CPlusEngine::Graphics