/*
The basic widget class. The main point of interaction for the user
*/

#ifndef WIDGET_H
#define WIDGET_H

#include "TDEGraphics.h"
#include "Includes.h"
#include "InputSubject.h"
#include "InputObserver.h"

namespace TDE
{
	//Lets the widget know that a parent widget exists
	class ParentWidget;

	class Widget : public MouseObserver, public KeyObserver
	{
	public:
		Widget(int x, int y, int width, int height, ParentWidget* parent);
		Widget() {};
		~Widget();

		//Functions that will be implemented by derived classes
		virtual void Update();
		virtual void Draw(TDEGraphics* g);

		//Hides the widget from view
		virtual void Hide();
		//Reveales the widget
		virtual void Show();

		//Overriding the == operator to compare widgets
		//Uses their ID's for comparison
		//ID should be given by parent
		bool operator==(Widget w);

		//Sets activity
		virtual void SetActive(bool isActive);

		//Getters to check if the widget is active and being displayed
		bool IsActive();
		bool IsShown();

		//Subscribes the widget to listen for specific input
		bool ListenForMouse();
		bool ListenForKeyboard();

		//Unsubscribes the widget
		void IgnoreMouse();
		void IgnoreKeyboard();

		//Checks to see if the widget is listening to anything
		bool IsListeningForKeys() { return mKeyListening; };
		bool IsListeningForMouse() { return mMouseListening; };

		//Functions that should be implemented by derived classes to act upon input
		virtual void KeyDown(TDE_Key k);
		virtual void KeyUp(TDE_Key k);
		virtual void MouseClickDown(MouseState &m);
		virtual void MouseClickUp(MouseState &m);
		virtual void MouseMoved(MouseState &m);

		//Returns a pointer to its parent
		ParentWidget* GetParent();

		void SetParent(ParentWidget* p);

		//Various getters and setters
		int GetID();
		void setID(int newID);
		bool hasParent();

		int GetX();
		int GetY();
		int GetWidth();
		int GetHeight();

		void SetX(int x) {mX = x;};
		void SetY(int y) {mY = y;};
		void SetWidth(int w) {mWidth = w;};
		void SetHeight(int h) {mHeight = h;};

		//To be used by parent to see if mouse input can be used by a widget
		bool IsPointWithinBounds(Point p);

	protected:
		bool			mIsShown;
		bool			mIsActive;
		bool			mNoParent;
		MouseSubject*	mMouse;
		KeySubject*		mKeyboard;
		MouseState		mCurrentMouseState;
		ParentWidget*	mParent;
		int				mX, mY;
		int				mWidth, mHeight;
		int				mID, mParentID;

		bool			mKeyListening;
		bool			mMouseListening;
	};
}
#endif
