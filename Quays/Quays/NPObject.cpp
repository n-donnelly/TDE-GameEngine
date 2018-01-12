#include "stdafx.h"
#include "NPObject.h"

NPObject::NPObject(TDE::Pointf pos, float w, float h)
{
	mPos = pos;
	mWidth = w;
	mHeight = h;
}

NPObject::~NPObject()
{
}

TDE::Pointf NPObject::GetPos() 
{
	return mPos;
}

float NPObject::GetWidth() 
{
	return mWidth;
}

float NPObject::GetHeight()
{
	return mHeight;
}

bool NPObject::IsInContact(Photon p)
{
	TDE::Pointf pPos = p.GetPos();
	return (mPos.x < (pPos.x + p.GetWidth()) &&
		(mPos.x+mWidth) > pPos.x &&
		mPos.y < (pPos.y + p.GetHeight()) &&
		(mPos.y + mHeight) > pPos.y);
}