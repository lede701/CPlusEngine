#ifndef H_SPLASHSCREEN
#define H_SPLASHSCREEN

#include <memory>
#include <stack>

#include "../Context.h"
#include "../Error/EngineError.h"
#include "../Graphics/GfxTexture.h"

namespace CPlusEngine{ namespace Graphics
{

	class SplashScreen
	{
	public:
		typedef std::unique_ptr<SplashScreen> Ptr;
		typedef CPlusEngine::Error::EngineError EngineError;
		typedef CPlusEngine::Context Context;
		typedef CPlusEngine::Graphics::GfxTexture Texture;


	private:
		float _timeDelay;
		bool _isReady;

		std::stack<EngineError::Ptr> _errList;

		Context::SPtr _context;
		Texture::SPtr _splash;

		unsigned char _alpha;

	public:
#pragma region Ctors

		SplashScreen(Context::SPtr context);
		~SplashScreen();

		void Init();

#pragma endregion

		bool IsReady();

		bool Show();

		EngineError::Ptr LastError();
	};

} }// End namespace CPlusEngine::Graphics

#endif