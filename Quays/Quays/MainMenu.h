#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "QuaysButton.h"

using namespace TDE;

class MainMenu : public ParentWidget
{
public:
	enum MainMenuState{
		WAITING,
		WANT_PLAY,
		WANT_EXIT
	};

	MainMenu(int x, int y, int w, int h, ParentWidget* parent);
	MainMenu(void);
	~MainMenu(void);

	void Draw(TDEGraphics* g);

	void OnBtnClick(int btnID);
	void OnBtnRelease(int btnID);

	MainMenuState GetState();

private:
	MouseSubject*		mMouse;
	MainMenuState		mState;
	int					mPlayID;
	int					mExitID;
	QuaysButton*		mPlayBtn;
	QuaysButton*		mExitBtn;

	TDE::TDEImage*		mBG;
};

#endif