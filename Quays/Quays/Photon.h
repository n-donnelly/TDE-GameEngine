#ifndef PHOTON_H
#define PHOTON_H

#include "ColorDefines.h"

class LightGate;
class Lock;

class Photon
{
public:
	Photon(float x, float y, float w, float h, float speed);
	Photon();
	~Photon(void);

	void InitResources(TDE::TDEGraphics* g);
	void Draw(TDE::TDEGraphics* g);

	bool InGateContact(LightGate* gate);
	void Move(TDE::Pointf newPos);
	void ApplyColor(TDE::TDEColor col);
	TDE::TDEColor GetColor();
	TDE::Pointf GetPos();

	void SetSpeed(float newSpeed);
	float GetSpeed();
	float GetWidth();
	float GetHeight();

private:
	float				mSpeed;
	TDE::TDEColor		mColor, mTransColor;
	bool				mIsInGate;
	TDE::Pointf			mPos;
	TDE::TDEImage*		mImage;
	float				mWidth;
	float				mHeight;
	LightGate*			mContactGate;
	Lock*				mLock;
	bool				mHasRegisteredAnim;
};

#endif