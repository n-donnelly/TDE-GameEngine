#ifndef LIGHT_GATE_H
#define LIGHT_GATE_H

#include "NPObject.h"

class LightGate : public NPObject
{
public:
	LightGate(TDE::Pointf pos, float w, float h, TDE::TDEColor aCol);
	~LightGate(void);

	void Update(float speed);
	void Draw(TDE::TDEGraphics* g);
	void OnPhotonCollision(Photon* p);
	TDE::TDEColor GetColor();
	bool HasContactedPhoton();

	void SetColor(TDE::TDEColor aCol);
private:
	bool				mHadPhotonContact;
	bool				mAnimRegistered;
	TDE::TDEColor		mColor;
	TDE::TDE_Animation*	mAnim;
};

#endif