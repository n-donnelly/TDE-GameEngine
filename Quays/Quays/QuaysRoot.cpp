#include "stdafx.h"
#include "QuaysRoot.h"
#include "Resources.h"

using namespace TDE;

QuaysRoot::QuaysRoot(InputManager* inputMgr, TDEGraphics* g, AudioManager* audio)
	: RootWidget(inputMgr, g, audio)
{
	InitResources(g);

	mainMenu = new MainMenu(0,0,mWidth, mHeight, this);
	AddChild(mainMenu);
	mState = RootState::MAIN_MENU;

	game = QuaysGame(0,0,mWidth,mHeight, this);
	AddChild(&game);
	game.SetParent(this);
	game.SetActive(false);
	game.Hide();

	gameOver = NULL;
}


QuaysRoot::~QuaysRoot(void)
{
	delete mainMenu;
}

void QuaysRoot::Update()
{
	RootWidget::Update();
	switch(mState)
	{
	case MAIN_MENU:
		{
			MainMenu::MainMenuState menuState = mainMenu->GetState();
			if(menuState == MainMenu::MainMenuState::WANT_PLAY)
			{
				mainMenu->Hide();
				mainMenu->SetActive(false);
				mState = IN_GAME;
				game.Show();
				game.SetActive(true);
				game.Play();
			}
			else if(menuState == MainMenu::MainMenuState::WANT_EXIT)
			{
				mWantRun = false;
			}
			break;
		}
	case IN_GAME:
		{
			QuaysGame::GameState gameState = game.GetState();
			if(gameState == QuaysGame::GameState::FINISHED_LOSS)
			{
				mState = GAME_OVER;
				game.Hide();
				game.SetActive(false);
				game.Stop();
				gameOver = new GameOverMenu(0,0,mWidth,mHeight,this,"You Lost");
				gameOver->SetActive(true);
				gameOver->Show();
				AddChild(gameOver);
			}
			else if(gameState == QuaysGame::GameState::FINISHED_WIN)
			{
				mState = GAME_OVER;
				game.Hide();
				game.SetActive(false);
				game.Stop();
				gameOver = new GameOverMenu(0,0,mWidth,mHeight,this,"You Won");
				gameOver->SetActive(true);
				gameOver->Show();
				AddChild(gameOver);
			}
		}
		break;
	case PAUSED:
		break;
	case GAME_OVER:
		{
			GameOverMenu::GameOverState gameOverState = gameOver->GetState();
			if(gameOverState == MainMenu::MainMenuState::WANT_PLAY)
			{
				gameOver->Hide();
				gameOver->SetActive(false);
				mState = IN_GAME;
				game = QuaysGame(0,0,mWidth,mHeight, this);
				game.Show();
				game.SetActive(true);
				game.Play();
			}
			else if(gameOverState == GameOverMenu::GameOverState::WANT_EXIT)
			{
				mWantRun = false;
			}
		}
		break;
	default:
		break;
	}
}

void QuaysRoot::Draw(TDEGraphics* g)
{
	RootWidget::Draw(g);
}
