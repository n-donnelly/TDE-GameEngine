/*
Contains the Keyboard observer, the Mouse observer and the base class 'InputObserver' from which the others are derived
*/

#ifndef INPUT_OBS_H
#define INPUT_OBS_H

#include "InputSubject.h"

namespace TDE
{
	//Basic InputObserver
	class InputObserver
	{
	private:
		//Pointer to the observers subject
		InputSubject* mSubject;

	public:
		InputObserver();
		~InputObserver();
		virtual void Notify(); //Virtual notify function that the derived classes must implement

	protected:
		InputSubject* getSubject(); //Returns the input subject associated with observer

	};

	//The observer for the mouse input
	//The base class is virtual as quite often a widget will inherit from both
	class MouseObserver : public virtual InputObserver
	{
	private:
		//The mouse subject associated with the observer
		MouseSubject* mMouseSubject;
		//The current mouse state
		MouseState mMouseState;

		//Used by the observer to save the value of the provided mouse state in the member mouse state
		void CopyMouseState(MouseState* m);

	public:
		MouseObserver();

		//Called by the subject with a new, updated mouse state
		void Notify(MouseState& m);

		//Virtual functions to be implemented by the derived classes to be informed of the event
		virtual void MouseMoved(MouseState& m);
		virtual void MouseClickDown(MouseState& m);
		virtual void MouseClickUp(MouseState& m);
	};

	class KeyObserver : public virtual InputObserver
	{
	private:
		KeySubject* mKeySubject;
	public:
		//Called by the subject with a new keyboard event
		void Notify(SDL_KeyboardEvent* key);

		//Virtual functions to be implemented by derived classes to be informed of the event
		//Allows the derived class to operate on the event setn to them
		virtual void KeyDown(TDE_Key key);
		virtual void KeyUp(TDE_Key key);
	};
}

#endif