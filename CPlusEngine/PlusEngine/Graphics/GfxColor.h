#ifndef H_GFXCOLOR
#define H_GFXCOLOR

#include <memory>
#include <string>

namespace CPlusEngine{ namespace Graphics
{

	struct GfxColor
	{
	public:
		typedef std::unique_ptr<GfxColor> Ptr;
		typedef std::shared_ptr<GfxColor> SPtr;
		typedef unsigned char uint8;

	public:
		GfxColor();
		GfxColor(uint8 r, uint8 g, uint8 b);
		GfxColor(uint8 r, uint8 g, uint8 b, uint8 a);

		std::string ToString();

		uint8 r;
		uint8 g;
		uint8 b;
		uint8 a;

		const static GfxColor White;
		const static GfxColor Red;
		const static GfxColor Green;
		const static GfxColor Blue;
		const static GfxColor Black;
		const static GfxColor Grey;
		const static GfxColor DkGrey;
		const static GfxColor Yellow;
		const static GfxColor Clear;
	};

} }// End namespace CPlusEngine::Graphics


#endif