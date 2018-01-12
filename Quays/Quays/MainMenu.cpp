#include "stdafx.h"
#include "MainMenu.h"
#include "Resources.h"

MainMenu::MainMenu(int x, int y, int w, int h, ParentWidget* parent)
	: ParentWidget(x, y, w, h, parent)
{
	mState = MainMenuState::WAITING;
	mPlayBtn = new QuaysButton(mWidth/2 - 100, 600, 200, 100, this);
	mExitBtn = new QuaysButton(mWidth/2 - 100, 750, 200, 100, this);

	mPlayBtn->SetUpImage(QUAYS_PLAY_BTN);
	mPlayBtn->SetDownImage(QUAYS_PLAY_BTN_PRESSED);

	mExitBtn->SetUpImage(QUAYS_EXIT_BTN);
	mExitBtn->SetDownImage(QUAYS_EXIT_BTN_PRESSED);

	mPlayID = 0;
	mExitID = 1;

	mPlayBtn->setID(mPlayID);
	mExitBtn->setID(mExitID);

	mPlayBtn->ListenForMouse();
	mExitBtn->ListenForMouse();

	AddChild(mPlayBtn);
	AddChild(mExitBtn);

	mBG = QUAYS_MENU_BG;
}

MainMenu::MainMenu(void)
	: ParentWidget(0,0,0,0,NULL)
{
	mState = MainMenuState::WAITING;
	mPlayBtn = new QuaysButton();
	mExitBtn = new QuaysButton();
	mPlayID = -1;
	mExitID = -1;
	mMouse = NULL;
}


MainMenu::~MainMenu(void)
{
	delete mPlayBtn;
	delete mExitBtn;
}

void MainMenu::Draw(TDEGraphics* g)
{
	g->DrawImage(mBG, Rect(0,0,mWidth,mHeight));
	ParentWidget::Draw(g);
}

void MainMenu::OnBtnClick(int btnID)
{
	
}

void MainMenu::OnBtnRelease(int btnID)
{
	if(btnID == mPlayID)
		mState = MainMenuState::WANT_PLAY;
	else if(btnID == mExitID)
		mState = MainMenuState::WANT_EXIT;
	mPlayBtn->IgnoreMouse();
	mExitBtn->IgnoreMouse();
}

MainMenu::MainMenuState MainMenu::GetState()
{
	return mState;
}