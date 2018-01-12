#include "stdafx.h"
#include "Lock.h"
#include "Resources.h"


Lock::Lock(TDE::Pointf pos, float dWidth, float cWidth, float h, TDE::TDEColor col)
	: NPObject(pos, dWidth, h)
{
	mColor = col;
	mDoor = QUAYS_DOOR;
	mContents = QUAYS_CONTENTS;
	mDoorWidth = dWidth;
	mContentsWidth = cWidth;
	mDoorPos = mPos;
	mIsUnlocked = false;
}

Lock::~Lock(void)
{
}

void Lock::Update(float speed)
{
	mPos.x -= speed;
	if(mIsUnlocked)
		mDoorPos.y -= speed*3;
}

void Lock::Draw(TDE::TDEGraphics* g)
{
	if(mDoor)
	{
		//Idea for door: draw rect behind with mColor. Then draw non-colorized image on top with alpha present along gaps
		g->ColorizeImages(true);
		g->ColorizeImages(false);
		g->DrawImage(mDoor, TDE::Rect(mPos.x, mDoorPos.y, mDoorWidth, mHeight));
		g->ColorizeImages(false);
	}
	else
	{
		g->SetColor(mColor);
		g->FillRect(mPos.x, mDoorPos.y, mPos.x+mDoorWidth, mHeight);
	}
	if(mContents)
	{
		g->DrawImage(mContents, TDE::Rect(mPos.x+mDoorWidth, mPos.y, mContentsWidth, mHeight));
	}
	else
	{
		g->SetColor(255,233,0);
		g->FillRect(mPos.x+mDoorWidth, mPos.y, mPos.x+mDoorWidth+mContentsWidth, mHeight);
		g->SetColor(RED);
		g->DrawString("GOLD VAULT!!!", mPos.x + mDoorWidth/2, mPos.y + 400);
	}
}

void Lock::OnPhotonCollision(Photon* p)
{
	TDE::TDEColor pCol = p->GetColor();
	if(mColor.m_iRed == pCol.m_iRed &&
		mColor.m_iGreen == pCol.m_iGreen &&
		mColor.m_iBlue == pCol.m_iBlue)
	{
		mIsUnlocked = true;
	}
	else
	{
		mIsUnlocked = false;
	}
}

TDE::TDEColor Lock::GetColor()
{
	return mColor;
}

void Lock::SetColor(TDE::TDEColor aCol)
{
	mColor = aCol;
}

float Lock::GetDoorWidth()
{
	return mDoorWidth;
}

bool Lock::IsUnlocked()
{
	return mIsUnlocked;
}