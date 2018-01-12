#ifndef INPUT_SUB_H
#define INPUT_SUB_H

/*
The subjects for the observer pattern
*/
#include "Includes.h"
#include "InputKeys.h"
#include <vector>

namespace TDE
{
	//Informs the subjects that the observers exist and will be implemented later on
	class InputObserver;
	class MouseObserver;
	class KeyObserver;

	//Basic subject to be extended by the mouse and keyboard subjects
	class InputSubject
	{
	public:
		InputSubject();
		~InputSubject();

		//Subscribes the the observers with the subject
		void Subscribe(InputObserver* inObs);
		void Unsubscribe(InputObserver* inObs);
		int GetNumSubscribers();

		//Notifies all the subscribers
		virtual void Notify();

	protected:
		std::vector<InputObserver*> subscribers;
	};

	class MouseSubject : public InputSubject
	{
	public:
		MouseSubject();
		~MouseSubject();
		void Notify(MouseState &m); //Notfies the subscribers with the updated mouse state
		MouseState getMouseState(); //Allows subscribers to get the current state of the mouse

	private:
		//Current mouse state that will be passed to the observer
		MouseState mCurrentMouseState;
	};

	class KeySubject : public InputSubject
	{
	public:
		KeySubject();
		~KeySubject();
		void Notify(SDL_KeyboardEvent* key); //Notifies the subscribers with a new keyboard event
	};
}

#endif