#ifndef LOCK_H
#define LOCK_H

#include "NPObject.h"

class Lock : public NPObject
{
public:
	Lock(TDE::Pointf pos, float dWidth, float cWidth, float h, TDE::TDEColor mCol);
	~Lock(void);

	void Update(float speed);
	void Draw(TDE::TDEGraphics* g);
	void OnPhotonCollision(Photon* p);
	TDE::TDEColor GetColor();
	float GetDoorWidth();

	void SetColor(TDE::TDEColor aCol);
	bool IsUnlocked();

private:
	bool				mHadPhotonContact;
	TDE::TDEColor		mColor;
	TDE::TDEImage		*mDoor, *mContents;
	float				mDoorWidth, mContentsWidth;
	bool				mIsUnlocked;
	TDE::Pointf			mDoorPos;
};

#endif