#ifndef QUAYS_ROOT_H
#define QUAYS_ROOT_H

#include "QuaysGame.h"
#include "MainMenu.h"
#include "GameOverMenu.h"

using namespace TDE;

class QuaysRoot : public RootWidget
{
public:
	QuaysRoot(InputManager* inputMgr,  TDEGraphics* g, AudioManager* audio);
	~QuaysRoot(void);

	void Update();
	void Draw(TDEGraphics* g);

private:
	enum RootState{
		MAIN_MENU,
		IN_GAME,
		PAUSED,
		GAME_OVER
	};
	QuaysGame game;
	MainMenu* mainMenu;
	GameOverMenu* gameOver;

	RootState mState;
};

#endif