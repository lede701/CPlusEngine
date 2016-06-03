#include "SplashScreen.h"

#include <chrono>
#include <thread>

namespace CPlusEngine{ namespace Graphics
{

#pragma region Ctors

	SplashScreen::SplashScreen(Context::SPtr context)
	{
		_timeDelay = 1.f;
		_alpha = 0;
		_isReady = false;
		_context = context;
	}

	SplashScreen::~SplashScreen()
	{
	}

	void SplashScreen::Init()
	{
		_isReady = false;
		if (_context == nullptr)
		{
			// Report invalid context
			_errList.push(EngineError::Ptr(new EngineError(10, "Invalid context provided to splash screen class")));
			return;
		}

		std::string splashFile = _context->Graphics()->LibPath() + "zscreditlogo_v1.png";

		_splash = _context->Graphics()->LoadImage(splashFile);
		if (_splash == nullptr)
		{
			// Report error
			_errList.push(EngineError::Ptr(new EngineError(11, "Can't find splash screen media!")));
			return;
		}

		_isReady = true;
	}

#pragma endregion

	bool SplashScreen::IsReady()
	{
		return _isReady;
	}

	SplashScreen::EngineError::Ptr SplashScreen::LastError()
	{
		EngineError::Ptr err = std::move(_errList.top());
		_errList.pop();
		return err;
	}

	bool SplashScreen::Show()
	{
		bool bRetVal = false;
		// Store the current background color so we can reset it when done
		GfxColor backColor = _context->Graphics()->BackgroundColor();
		_context->Graphics()->ClearColor(GfxColor::Black);

		unsigned int time = unsigned int(_timeDelay * 1000);
		unsigned int paused = 0;
		unsigned int pauseInterval = 10;

		// Setup the variable to track splash fade in
		float alpha = 0.f;
		float alphaStep = 0.02f;
		
		if (_splash != nullptr)
		{
			iRect2D src{ 0, 0, 1280, 691 };
			iVector2D sSize = _context->Graphics()->ScreenSize();
			iVector2D orgSize = sSize.Clone();

			if (src.w > orgSize.x)
			{
				float reduce = float(sSize.x) / float(src.w);
				sSize.x = int(src.w * reduce);
				sSize.y = int(src.h * reduce);
			}
			if (sSize.y > orgSize.y)
			{
				float reduce = float(sSize.y) / float(src.w);
				sSize.x = int(src.w * reduce);
				sSize.y = int(src.h * reduce);
			}
			iRect2D dst{ 0, 0, sSize.x, sSize.y };

			while (paused < time)
			{
				_context->Graphics()->SetAlpha(_splash, alpha);
				_context->Graphics()->StartFrame();
				// Draw splash screen
				_context->Graphics()->Draw(_splash, src, dst);
				_context->Graphics()->EndFrame();
				_context->Input()->Update(1.f);
				std::this_thread::sleep_for(std::chrono::milliseconds(pauseInterval));
				alpha += alphaStep;
				paused += pauseInterval;
			}

			// Fade-out splash screen
			while (alpha > 0.f)
			{
				_context->Graphics()->SetAlpha(_splash, alpha);
				_context->Graphics()->StartFrame();
				// Draw splash screen
				_context->Graphics()->Draw(_splash, src, dst);
				_context->Graphics()->EndFrame();
				alpha -= alphaStep;
				std::this_thread::sleep_for(std::chrono::milliseconds(pauseInterval));
			}

			std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}

		bRetVal = paused >= time;

		_context->Graphics()->ClearColor(backColor);

		return bRetVal;
	}



} }// End namespace CPlusEngine::Graphics
