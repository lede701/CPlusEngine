#ifndef H_GFXTEXTURE
#define H_GFXTEXTURE

#include <memory>

namespace CPlusEngine{ namespace Graphics
{
	class GfxTexture
	{
	public:
		typedef std::unique_ptr<GfxTexture> Ptr;
		typedef std::shared_ptr<GfxTexture> SPtr;
		typedef GfxTexture* RealPtr;

	public:
		void *texture;
		int Id;

		GfxTexture();
		GfxTexture(int idx, void *inTexture);

		~GfxTexture();
	};

} }// End namespace CPlusEngine::GRaphics


#endif