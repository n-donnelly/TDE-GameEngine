#ifndef QUAYS_GAME_H
#define QUAYS_GAME_H

#include "ParentWidget.h"
#include "Photon.h"
#include "NPObject.h"
#include "TDERandomGen.h"
#include "LevelReader.h"

using namespace TDE;

class QuaysGame : public ParentWidget
{
public:
	enum GameState{
		PLAYING,
		PAUSED,
		FINISHED_WIN,
		FINISHED_LOSS
	};

	QuaysGame(int x, int y, int w, int h, ParentWidget* parent);
	QuaysGame();
	~QuaysGame(void);

	void Play();
	void Stop();
	void Update();
	void Draw(TDEGraphics* g);

	void KeyDown(TDE_Key k);
	void KeyUp(TDE_Key k);
	GameState GetState();

	void PushObject(NPObject obj);
	void PushGate(LightGate g);
	void PushLock(Lock lock);

private:
	void DrawBG(TDEGraphics* g);

	RandomGen				mRandom;
	unsigned int			mSeedUsed;
	std::vector<NPObject*>	mObstacleVec;
	Lock*					mLock;
	int						mNumObjects;
	GameState				mState;
	LevelReader				mLevelReader;

	float		mSpeed;
	bool		mPaused;
	bool		mFinished;

	TDEImage*	mBackground;
	float		mBGx, mBGy;
	bool		wKeyDown, sKeyDown;
	Pointf      mPhotonPos;
	Photon		mPhoton;
	bool		mPhotonHitDoor;
};

#endif