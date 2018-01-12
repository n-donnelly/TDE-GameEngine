#include "stdafx.h"
#include "QuaysButton.h"

QuaysButton::QuaysButton(int x, int y, int width, int height, ParentWidget* parent)
	: ButtonWidget(x,y,width,height,parent)
{
}

QuaysButton::QuaysButton(int x, int y, int width, int height, ParentWidget* parent, TDEImage* aUp, TDEImage* aDown)
	: ButtonWidget(x,y,width,height,parent, aUp, aDown)
{
}

QuaysButton::QuaysButton(void)
{
}


QuaysButton::~QuaysButton(void)
{
}

void QuaysButton::Draw(TDEGraphics* g)
{
	if(!beingClicked)
	{
		if(mUp)
			g->DrawImage(mUp, Rect(mX, mY, mWidth, mHeight));
		else
		{
			g->SetColor(0,255,0);
			g->FillRect(mX,mY,mWidth,mHeight);
		}
	}
	else
	{
		if(mDown)
			g->DrawImage(mDown, Rect(mX, mY, mWidth, mHeight));
		else
		{
			g->SetColor(0,0,255);
			g->FillRect(mX,mY,mWidth,mHeight);
		}
	}

}
