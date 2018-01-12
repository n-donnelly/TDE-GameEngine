#include "ButtonWidget.h"
#include "ParentWidget.h"

namespace TDE
{
	ButtonWidget::ButtonWidget(int x, int y, int width, int height, ParentWidget* parent)
		: Widget(x, y, width, height, parent)
	{
		beingClicked = false;
		mUp = NULL;
		mDown = NULL;
	}

	ButtonWidget::ButtonWidget(int x, int y, int width, int height, ParentWidget* parent, TDEImage* btnIm)
		: Widget(x, y, width, height, parent)
	{
		beingClicked = false;
		mUp = mDown = btnIm;
	}

	ButtonWidget::ButtonWidget(int x, int y, int width, int height, ParentWidget* parent, TDEImage* aUp, TDEImage* aDown)
		: Widget(x, y, width, height, parent)
	{
		beingClicked = false;
		mUp = aUp;
		mDown = aDown;
	}

	ButtonWidget::ButtonWidget()
		: Widget()
	{
		beingClicked = false;
		mUp = NULL;
		mDown = NULL;
	}

	ButtonWidget::~ButtonWidget(void)
	{
	}

	void ButtonWidget::SetUpImage(TDEImage* aUp)
	{
		mUp = aUp;
	}

	void ButtonWidget::SetDownImage(TDEImage* aDown)
	{
		mDown = aDown;
	}

	void ButtonWidget::Draw(TDEGraphics* g)
	{
		if(mUp)
		{
			g->PushState();
			g->SetClipRect(mX, mY, mWidth, mHeight);

			if(beingClicked && mDown)
				g->DrawImage(mDown, 0,0);
			else
				g->DrawImage(mUp, 0, 0);

			g->PopState();
		}
	}

	void ButtonWidget::MouseClickDown(MouseState &m)
	{
		if(m.x > mX && m.x < mX + mWidth && m.y > mY && m.y < mY + mHeight)
		{
			beingClicked = true;
			OnClick();
		}
	}

	void ButtonWidget::MouseClickUp(MouseState &m)
	{
		if(m.x > mX && m.x < mX + mWidth && m.y > mY && m.y < mY + mHeight)
		{
			beingClicked = false;
			OnRelease();
		}
	}

	void ButtonWidget::OnClick()
	{
		if(mParent)
			mParent->OnBtnClick(mID);
		return;
	}

	void ButtonWidget::OnRelease()
	{
		if(mParent)
			mParent->OnBtnRelease(mID);
		return;
	}

	bool ButtonWidget::IsBeingClicked()
	{
		return beingClicked;
	}
}