#include "GfxTexture.h"

namespace CPlusEngine{ namespace Graphics
{

	GfxTexture::GfxTexture()
	{
		Id = -1;
		texture = nullptr;
	}

	GfxTexture::GfxTexture(int idx, void *inTexture)
	{
		Id = idx;
		texture = inTexture;
	}

	GfxTexture::~GfxTexture()
	{
	}

} }// End namespace CPlusEngine::GRaphics