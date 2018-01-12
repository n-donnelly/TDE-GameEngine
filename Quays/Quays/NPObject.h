#ifndef NP_OBJECT_H
#define NP_OBJECT_H

#include "Photon.h"

class NPObject
{
public:
	NPObject(TDE::Pointf pos, float w, float h);
	~NPObject(void);

	virtual void Draw(TDE::TDEGraphics* g) {};
	virtual void Update(float speed) {};
	virtual void OnPhotonCollision(Photon* p) {};

	TDE::Pointf GetPos();
	float GetWidth();
	float GetHeight();
	bool IsInContact(Photon p);

protected:
	TDE::Pointf mPos;
	float		mWidth;
	float		mHeight;
};

#endif