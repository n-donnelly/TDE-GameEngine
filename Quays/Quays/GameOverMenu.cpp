#include "stdafx.h"
#include "GameOverMenu.h"


GameOverMenu::GameOverMenu(int x, int y, int w, int h, ParentWidget* parent, std::string status)
	: ParentWidget(x,y,w,h,parent)
{
	mState = GameOverState::WAITING;
	mPlayBtn = new QuaysButton(600, 600, 100, 50, this);
	mExitBtn = new QuaysButton(600, 700, 100, 50, this);

	mPlayID = 0;
	mExitID = 1;

	mPlayBtn->setID(mPlayID);
	mExitBtn->setID(mExitID);

	mPlayBtn->ListenForMouse();
	mExitBtn->ListenForMouse();

	AddChild(mPlayBtn);
	AddChild(mExitBtn);

	mStatus = status;
}

GameOverMenu::GameOverMenu(void)
	: ParentWidget(0,0,0,0,NULL)
{
	mState = GameOverState::WAITING;
	mPlayBtn = new QuaysButton();
	mExitBtn = new QuaysButton();
	mPlayID = -1;
	mExitID = -1;
	mMouse = NULL;
}


GameOverMenu::~GameOverMenu(void)
{
}

void GameOverMenu::Draw(TDE::TDEGraphics* g)
{
	g->SetColor(255,255,255);
	g->FillRect(mX, mY, mWidth, mHeight);
	g->DrawString("Game Over Menu PlaceHolder", 550, 400);
	g->DrawString(mStatus, 550, 400+g->GetFontHeight()+10, TDE::TDEColor(255,0,0));
	ParentWidget::Draw(g);
}

void GameOverMenu::OnBtnClick(int btnID)
{
	
}

void GameOverMenu::OnBtnRelease(int btnID)
{
	if(btnID == mPlayID)
		mState = GameOverState::WANT_PLAY;
	else if(btnID == mExitID)
		mState = GameOverState::WANT_EXIT;
	mPlayBtn->IgnoreMouse();
	mExitBtn->IgnoreMouse();
}

GameOverMenu::GameOverState GameOverMenu::GetState()
{
	return mState;
}
