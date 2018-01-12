#include "stdafx.h"
#include "LightGate.h"
#include "Resources.h"


LightGate::LightGate(TDE::Pointf pos, float w, float h, TDE::TDEColor aCol)
	: NPObject(pos, w, h)
{
	mAnim = new TDE::TDE_Animation(QUAYS_GATE_ANIM);
	mColor = aCol;
	mAnimRegistered = false; //Register in Resources when animation is inserted
	mHadPhotonContact = false;
}

LightGate::~LightGate(void)
{

}

void LightGate::Update(float speed)
{
	mPos.x -= speed;
}

void LightGate::Draw(TDE::TDEGraphics* g)
{
	g->SetColor(mColor);
	if(!mAnimRegistered)
	{
		g->GetAnimMgr()->RegisterAnim(mAnim);
		mAnim->Play(500, 0, -1);
		mAnimRegistered = true;
	}
	g->ColorizeImages(true);
	g->DrawAnimation(mAnim, TDE::Rect(mPos.x, mPos.y, mWidth, mHeight));
	g->ColorizeImages(false);
	
	if(mPos.x <= -mWidth/2)
		g->GetAnimMgr()->DeregisterAnim(mAnim);
	//g->FillRect(mPos.x, mPos.y, mPos.x + mWidth, mPos.y+mHeight);
}

void LightGate::OnPhotonCollision(Photon* p)
{
	p->InGateContact(this);
	mHadPhotonContact = true;
}

void LightGate::SetColor(TDE::TDEColor col)
{
	mColor = col;
}

TDE::TDEColor LightGate::GetColor()
{
	return mColor;
}

bool LightGate::HasContactedPhoton()
{
	return mHadPhotonContact;
}