#include "stdafx.h"
#include "Photon.h"
#include "LightGate.h"
#include "Resources.h"

using namespace TDE;

Photon::Photon(float x, float y, float w, float h, float speed)
{
	mPos = Pointf(x, y);
	mColor = TDEColor(255,255,255);
	mImage = QUAYS_PHOTON;
	mWidth = w;
	mHeight = h;
	mSpeed = speed;
	mIsInGate = false;
	mContactGate = NULL;
	mLock = NULL;
	mHasRegisteredAnim = false;
}

Photon::Photon()
{
	mPos = Pointf(0.f, 0.f);
	mColor = TDEColor(255,255,255);
	mWidth = 0.f;
	mHeight = 0.f;
	mSpeed = 0.f;
	mIsInGate = false;
	mContactGate = NULL;
	mLock = NULL;
}

Photon::~Photon(void)
{
}

void Photon::InitResources(TDEGraphics* g)
{
	
}

void Photon::Draw(TDEGraphics* g)
{
	if(mImage)
	{
		g->ColorizeImages(true);
		if(mIsInGate)
		{
			float mGateX = mContactGate->GetPos().x;
			if(mGateX > mPos.x)
			{
				g->SetColor(mTransColor);
				float srcW = (mGateX-mPos.x)/mWidth;
				g->DrawImage(mImage, 
							Rect(mPos.x, mPos.y, mGateX-mPos.x, mHeight), 
							Rect(0,0,srcW*mImage->GetWidth(), mImage->GetHeight()));

				g->SetColor(mColor);
				g->DrawImage(mImage, 
							Rect(mGateX, mPos.y, mWidth-(mGateX-mPos.x), mHeight),
							Rect(srcW*mImage->GetWidth(),0,mImage->GetWidth()-(srcW*mImage->GetWidth()),mImage->GetHeight()));
				
				return;
			}
			mIsInGate = false;
		}
		g->SetColor(mColor);
		g->DrawImage(mImage, Rect(mPos.x, mPos.y, mWidth, mHeight));
		g->ColorizeImages(false);
		return;
	}

	if(mIsInGate)
	{
		float mGateX = mContactGate->GetPos().x;
		if(mGateX > mPos.x)
		{
			g->SetColor(mTransColor);
			g->FillRect(mPos.x, mPos.y, mGateX,mPos.y+mHeight);
			g->SetColor(mColor);
			g->FillRect(mGateX, mPos.y, mPos.x+mWidth, mPos.y+mHeight);
			return;
		}
		mIsInGate = false;
	}
	g->SetColor(mColor);
	g->FillRect(mPos.x,mPos.y,mPos.x+mWidth,mPos.y+mHeight);
}

void Photon::Move(Pointf newPos)
{
	mPos = newPos;
}

void Photon::SetSpeed(float newSpeed)
{
	mSpeed = newSpeed;
}

float Photon::GetSpeed()
{
	return mSpeed;
}

void Photon::ApplyColor(TDEColor newCol)
{
	//Perhaps mix when I figure out what works best
	mColor = newCol;
}

TDEColor Photon::GetColor()
{
	return mColor;
}

bool Photon::InGateContact(LightGate* gate)
{
	if(!(gate->HasContactedPhoton()))
	{
		mTransColor = mColor;
		mColor = gate->GetColor();
	}
	mContactGate = gate;
	mIsInGate = true;

	return true;
}

Pointf Photon::GetPos()
{
	return mPos;
}

float Photon::GetWidth()
{
	return mWidth;
}

float Photon::GetHeight()
{
	return mHeight;
}