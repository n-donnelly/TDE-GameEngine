#ifndef TDE_ENGINE_H
#define TDE_ENGINE_H

#include "AudioManager.h"
#include "RootWidget.h"

namespace TDE
{
	class TDE_Engine
	{
	public:
		TDE_Engine(void);
		~TDE_Engine(void);

		void Init();
		void Run(RootWidget* root, float updates);
		void Shutdown();

		TDEGraphics* GetGraphics();
		AnimationManager* GetAnimationManager();
		TextureManager*	GetTextureManager();
		AudioManager* GetAudioManager();
		FontManager* GetFontManager();
		InputManager* GetInputManager();
		std::string Convert (float number);

	private:
		TDEGraphics			graphics;
		AnimationManager	animMgr;
		TextureManager		texMgr;
		AudioManager		audioMgr;
		FontManager			fontMgr;
		InputManager		inputMgr;
	};
}

#endif