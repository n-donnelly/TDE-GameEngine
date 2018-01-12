#include "TDE_Engine.h"
#include <sstream>

namespace TDE
{
	TDE_Engine::TDE_Engine(void)
	{
		Init();
	}


	TDE_Engine::~TDE_Engine(void)
	{
		Shutdown();
	}

	void TDE_Engine::Init(void)
	{
		texMgr = TextureManager();
		fontMgr = FontManager();
		audioMgr = AudioManager();
		inputMgr = InputManager();
		animMgr = AnimationManager(&texMgr);
		graphics = TDEGraphics(&texMgr, &animMgr, &fontMgr);
	}

	void TDE_Engine::Run(RootWidget* root, float updates)
	{
		float timeStep = 1000.f/60.f;
		float timeLast, timeCurrent, timeDelta, timeAccumulated, lastFPSCheck, currentFPS = 0.f;
		lastFPSCheck = timeCurrent = (float)SDL_GetTicks();
		timeAccumulated = 0;
		bool run = true;

		while(run)
		{
			timeLast = timeCurrent;
			timeCurrent = (float)SDL_GetTicks();
			timeDelta = timeCurrent - timeLast;
			timeAccumulated += timeDelta;
			while(timeAccumulated >= timeStep)
			{
				root->Update();
				timeAccumulated -= timeStep;
			}
			graphics.InitDraw();
			root->Draw(&graphics);
			if(timeCurrent - lastFPSCheck > 1000.f)
			{
				currentFPS = 1.f/timeDelta;
				lastFPSCheck = timeCurrent;
			}
			graphics.DrawString(Convert(currentFPS*1000), 10, 10);
			graphics.EndDraw();
			run = root->GetRunStatus();
		}
	}

	void TDE_Engine::Shutdown()
	{
		graphics.Shutdown();
		audioMgr.FreeAllSounds();
	}

	TDEGraphics* TDE_Engine::GetGraphics()
	{
		return &graphics;
	}

	TextureManager* TDE_Engine::GetTextureManager()
	{
		return &texMgr;
	}

	FontManager* TDE_Engine::GetFontManager()
	{
		return &fontMgr;
	}

	AudioManager* TDE_Engine::GetAudioManager()
	{
		return &audioMgr;
	}

	InputManager* TDE_Engine::GetInputManager()
	{
		return &inputMgr;
	}

	AnimationManager* TDE_Engine::GetAnimationManager()
	{
		return &animMgr;
	}

	std::string TDE_Engine::Convert (float number)
	{
		std::ostringstream buff;
		buff<<number;
		return buff.str();
    }
}