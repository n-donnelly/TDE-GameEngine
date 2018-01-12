#include "Widget.h"
#include "ParentWidget.h"

namespace TDE
{
	//Inits all the member variables
	Widget::Widget(int x, int y, int width, int height, ParentWidget* parent)
	{
		mX = x;
		mY = y;
		mWidth = width;
		mHeight = height;

		mParent = parent;
		mNoParent = mParent == NULL;

		mCurrentMouseState.x = 0;
		mCurrentMouseState.y = 0;
		mCurrentMouseState.leftClicked = false;
		mCurrentMouseState.rightClicked = false;
		mCurrentMouseState.middleClicked = false;

		mIsShown = true;
		mIsActive = true;

		mKeyListening = false;
		mMouseListening = false;

		mMouse = 0;
		mKeyboard = 0;

		mID = 0;
		mParentID = mParent == NULL ? -1 : mParent->mID;
	}


	Widget::~Widget()
	{
	}

	//Hides the widget
	void Widget::Hide()
	{
		mIsShown = false;
		mIsActive = false;
	}

	//Shows the widget
	void Widget::Show()
	{
		mIsShown = true;
		mIsActive = true;
	}

	//Compares the widget based on the ID
	bool Widget::operator==(Widget w)
	{
		if(w.GetID() != mID)
			return false;

		//Make sure they have the same parent also
		if(mParent == NULL || w.GetParent() == NULL)
			return false;

		return (mParent->GetID() == w.GetParent()->GetID());
	}

	void Widget::SetActive(bool isActive)
	{
		mIsActive = isActive;
	}

	bool Widget::IsActive()
	{
		return mIsActive;
	}

	bool Widget::IsShown()
	{
		return mIsShown;
	}

	//If the widget is not already listening, then subscribe it
	bool Widget::ListenForKeyboard()
	{
		if(mKeyListening)
			return true;
		if(!hasParent())
			return false;
		mKeyboard = mParent->GetKeyboard();
		if(!mKeyboard)
			return false;
		mKeyboard->Subscribe(this);
		mKeyListening = true;
		return true;
	}

	bool Widget::ListenForMouse()
	{
		if(mMouseListening)
			return true;
		if(!hasParent())
			return false;
		mMouse = mParent->GetMouse();
		if(!mMouse)
			return false;
		mMouse->Subscribe(this);
		mMouseListening = true;
		return true;
	}

	//If the widget is listening, then ignore it
	void Widget::IgnoreKeyboard()
	{
		if(!mKeyListening)
			return;
		mKeyboard->Unsubscribe(this);
		mKeyListening = false;
	}

	void Widget::IgnoreMouse()
	{
		if(!mMouseListening)
			return;
		mMouse->Unsubscribe(this);
		mMouseListening = false;
	}

	void Widget::MouseClickDown(MouseState& m)
	{
		mCurrentMouseState = m;
	}

	void Widget::MouseClickUp(MouseState& m)
	{
		mCurrentMouseState = m;
	}

	void Widget::Update()
	{
		return;
	}

	void Widget::Draw(TDEGraphics* g)
	{
		return;
	}

	void Widget::KeyDown(TDE_Key key)
	{
		return;
	}

	void Widget::KeyUp(TDE_Key key)
	{
		return;
	}

	void Widget::MouseMoved(MouseState &m)
	{
		return;
	}

	ParentWidget* Widget::GetParent()
	{
		return mParent;
	}

	void Widget::SetParent(ParentWidget* parent)
	{
		if(parent)
			mParent = parent;
	}

	int Widget::GetID()
	{
		return mID;
	}

	void Widget::setID(int newID)
	{
		mID = newID;
	}

	bool Widget::hasParent()
	{
		return !mNoParent;
	}

	int Widget::GetX()
	{
		return mX;
	}

	int Widget::GetY()
	{
		return mY;
	}

	int Widget::GetWidth()
	{
		return mWidth;
	}

	int Widget::GetHeight()
	{
		return mHeight;
	}

	bool Widget::IsPointWithinBounds(Point p)
	{
		return (p.x > mX && p.x < mX + mWidth && p.y > mY && p.y < mY + mHeight);
	}
}
