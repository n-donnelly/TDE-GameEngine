#ifndef GAME_OVER_H
#define GAME_OVER_H

#include "QuaysButton.h"

using namespace TDE;

class GameOverMenu : public ParentWidget
{
public:
	enum GameOverState{
		WAITING,
		WANT_PLAY,
		WANT_EXIT
	};

	GameOverMenu(int x, int y, int w, int h, ParentWidget* parent, std::string status);
	GameOverMenu(void);
	~GameOverMenu(void);

	void Draw(TDEGraphics* g);

	void OnBtnClick(int btnID);
	void OnBtnRelease(int btnID);

	GameOverState GetState();

private:
	MouseSubject*		mMouse;
	GameOverState		mState;
	int					mPlayID;
	int					mExitID;
	QuaysButton*		mPlayBtn;
	QuaysButton*		mExitBtn;
	std::string			mStatus;
};

#endif