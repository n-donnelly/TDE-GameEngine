#include "stdafx.h"
#include "QuaysGame.h"
#include "LightGate.h"
#include "Lock.h"
#include "Resources.h"

QuaysGame::QuaysGame(int x, int y, int w, int h, ParentWidget* parent)
	: ParentWidget(x,y,w,h,parent)
{
	mSpeed = 7.f;
	mBackground = QUAYS_BACKGROUND;
	mBGx = (float)mWidth;
	mBGy = 0.f;
	mPaused = true;
	wKeyDown = false;
	sKeyDown = false;
	mPhotonPos = Pointf(0.1f*w, h/2.f);
	mPhoton = Photon(mPhotonPos.x, mPhotonPos.y, 96.f, 36.f,12.f);
	mPhoton.ApplyColor(TDEColor(255,255,255));
	mFinished = false;
	mRandom = RandomGen();
	mState = GameState::PAUSED;
	mLock = NULL;
	mNumObjects = 0;
	mLevelReader = LevelReader(5);
	mObstacleVec.clear();
	mPhotonHitDoor = false;
}

QuaysGame::QuaysGame()
	: ParentWidget(0,0,0,0,NULL)
{
	mSpeed = 0.f;
	mBackground = NULL;
	mBGx = 0;
	mBGy = 0.f;
	mPaused = true;
	wKeyDown = false;
	sKeyDown = false;
	mPhotonPos = Pointf(0.f, 0.f);
	mPhoton = Photon(mPhotonPos.x, mPhotonPos.y, 5.f, 5.f,2.5f);
	mPhoton.ApplyColor(TDEColor(0,0,255));
	mFinished = false;
	mRandom = RandomGen();
	mState = GameState::PAUSED;
	mLock = NULL;
	mNumObjects = 0;
	mLevelReader = LevelReader();
	mObstacleVec.clear();
	mPhotonHitDoor = false;
}

void QuaysGame::Play()
{
	mState = GameState::PLAYING;
	mPaused = false;
	mKeyboard = GetKeyboard();
	if(mKeyboard)
		mKeyboard->Subscribe(this);
	ListenForKeyboard();
	mLevelReader.ReadLevel("test", this);
}

void QuaysGame::Stop()
{
	mPaused = true;
	mKeyboard = NULL;
}

QuaysGame::~QuaysGame(void)
{
}

void QuaysGame::Update()
{
	if(!mPaused && !mFinished)
	{
		if(mLock)
		{
			if(mLock->IsInContact(mPhoton))
			{
				mLock->OnPhotonCollision(&mPhoton);
			}
			if(mLock->GetPos().x > -mLock->GetDoorWidth())
				mLock->Update(mSpeed);
			else
			{
				if(mLock->IsUnlocked())
					mState = QuaysGame::FINISHED_WIN;
				else mState = QuaysGame::FINISHED_LOSS;
			}
			
			if(mLock->GetPos().x < mPhoton.GetPos().x)
				mPhotonHitDoor = true;
		}
		mBGx -= mSpeed;
		if(mBGx <= 0)
		{
			mBGx = (float)mWidth;
			if(!mLock)
				mLevelReader.GetNextScreen(mHeight, mWidth);
		}

		if(mPhotonHitDoor)
			return;

		if(wKeyDown)
			mPhotonPos.y = max(0.f, mPhotonPos.y-mPhoton.GetSpeed());
		if(sKeyDown)
			mPhotonPos.y = min((float)mHeight, mPhotonPos.y+mPhoton.GetSpeed());
		if(mPhotonPos.y != mPhoton.GetPos().y)
			mPhoton.Move(mPhotonPos);

		if(mObstacleVec.size() <= 0)
			return;
		int size = mObstacleVec.size();
		for(int i = 0; i < size; i++)
		{
			mObstacleVec[i]->Update(mSpeed);
		}

		bool found = false;
		std::vector<NPObject*>::iterator it = mObstacleVec.begin();
		int i = 0;
		while(!found && i < size)
		{
			if((*it)->GetPos().x > mPhotonPos.x + mPhoton.GetWidth())
				found = true;
			if((*it)->IsInContact(mPhoton))
			{
				(*it)->OnPhotonCollision(&mPhoton);
			}
			if((*it)->GetPos().x < -(*it)->GetWidth())
			{
				delete (*it);
				(*it) = NULL;
				it = mObstacleVec.erase(it);
				size =  mObstacleVec.size();
				if(size == 0)
					found = true;
				else it = mObstacleVec.begin();
			}
			else{
				it++;
				i++;
			}
		}

	}
}

void QuaysGame::Draw(TDEGraphics* g)
{
	DrawBG(g);
	for(int i = 0; i < mObstacleVec.size(); i++)
	{
		mObstacleVec[i]->Draw(g);
	}
	if(mLock)
		mLock->Draw(g);
	if(mPhotonHitDoor)
		return;

	mSpeed += 0.005f;
	mPhoton.Draw(g);
}

void QuaysGame::DrawBG(TDEGraphics* g)
{
	if(mBackground)
	{
		g->DrawImage(mBackground,
			Rect(0,0,(int)(mBGx),mHeight), 
			Rect((mWidth - mBGx)/mWidth * mBackground->GetWidth(), 0, (mBGx/mWidth)*mBackground->GetWidth(), mBackground->GetHeight()));
		g->DrawImage(mBackground,
			Rect((int)mBGx, 0, (int)(mWidth-mBGx), mHeight),
			Rect(0,0,(mWidth - mBGx)/mWidth * mBackground->GetWidth(),mBackground->GetHeight()));
	}
	else
	{
		g->SetColor(255,0,0);
		g->FillRect(0,0,(int)(mBGx),mHeight);
		g->SetColor(0,255,0);
		g->FillRect((int)mBGx, 0, (int)(mWidth-mBGx), mHeight);
	}
}

void QuaysGame::KeyDown(TDE_Key k)
{
	switch(k)
	{
	case KEY_SPACE:
		if(mPaused)
			mState = GameState::PAUSED;
		else
			mState = GameState::PLAYING;
		mPaused = !mPaused;
		break;
	case KEY_w:
	case KEY_UP:
		wKeyDown = true;
		break;
	case KEY_s:
	case KEY_DOWN:
		sKeyDown = true;
		break;
	default:
		break;
	}
}

void QuaysGame::KeyUp(TDE_Key k)
{
	switch(k)
	{
	case KEY_ESCAPE:
		break;
	case KEY_w:
	case KEY_UP:
		wKeyDown = false;
		break;
	case KEY_s:
	case KEY_DOWN:
		sKeyDown = false;
		break;
	default:
		break;
	}
}

QuaysGame::GameState QuaysGame::GetState()
{
	return mState;
}

void QuaysGame::PushObject(NPObject obj)
{
	mObstacleVec.push_back(new NPObject(obj));
	mNumObjects++;
}

void QuaysGame::PushGate(LightGate g)
{
	mObstacleVec.push_back(new LightGate(g));
	mNumObjects++;
}

void QuaysGame::PushLock(Lock lock)
{
	mLock = new Lock(lock);
}