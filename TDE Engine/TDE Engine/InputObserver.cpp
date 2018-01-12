#include "InputObserver.h"

namespace TDE
{
	InputObserver::InputObserver(void)
	{
	}

	InputObserver::~InputObserver(void)
	{
	}

	InputSubject* InputObserver::getSubject()
	{
		return mSubject;
	}

	//Is empty as should be implemented by derived classes
	void InputObserver::Notify()
	{
		return;
	}

	MouseObserver::MouseObserver()
	{
		//Initialise the the mouse state
		mMouseState.leftClicked = false;
		mMouseState.rightClicked = false;
		mMouseState.x = 0;
		mMouseState.y = 0;
	}

	void MouseObserver::Notify(MouseState& m)
	{
		//Checks if there was any movement, if so then let everybody know
		if(m.x != mMouseState.x || m.y != mMouseState.y)
			MouseMoved(m);

		//Check which buttons are clicked then let everybody know
		if(m.leftClicked != mMouseState.leftClicked )
			m.leftClicked ? MouseClickDown(m) : MouseClickUp(m);			
		else if(m.rightClicked != mMouseState.rightClicked)
			m.rightClicked ? MouseClickDown(m) : MouseClickUp(m);

		mMouseState = m;
	}

	//These functions to be implemented by derived classes 
	void MouseObserver::MouseClickDown(MouseState &m)
	{
		return;
	}

	void MouseObserver::MouseClickUp(MouseState &m)
	{
		return;
	}

	void MouseObserver::MouseMoved(MouseState &m)
	{
		return;
	}

	void KeyObserver::Notify(SDL_KeyboardEvent* key)
	{
		//Checks whether the key has been pressed or released then call corresponding function
		if(key->state == SDL_PRESSED)
			KeyDown((TDE_Key)key->keysym.sym);
		else if(key->state == SDL_RELEASED)
			KeyUp((TDE_Key)key->keysym.sym);
	}

	void KeyObserver::KeyDown(TDE_Key key)
	{
		return;
	}

	void KeyObserver::KeyUp(TDE_Key key)
	{
		return;
	}
}