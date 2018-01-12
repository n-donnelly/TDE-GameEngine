#include "InputSubject.h"
#include "InputObserver.h"

namespace TDE
{
	InputSubject::InputSubject()
	{
	}


	InputSubject::~InputSubject()
	{
	}

	void InputSubject::Subscribe(InputObserver* inObs)
	{
		if(!inObs)
			return;

		for(int i = 0; i < subscribers.size(); i++)
		{
			if(subscribers[i] == inObs)
				return;
		}
		subscribers.push_back(inObs); //Put the observer on the subscribers list
	}

	//Removes an oberver from the list of subscribers
	void InputSubject::Unsubscribe(InputObserver* inObs)
	{
		//Leave function if the subscribers list is empty
		if(subscribers.empty())
			return;

		//Iterate through list until the pointer matches that of inObs,
		//If the pointers match then remove the observer from the list 
		for(int j = 0; j < (int)subscribers.size(); j++)
		{
			if(subscribers[j] == inObs)
			{
				subscribers.erase(subscribers.begin()+j);
				return;
			}
		}
	}

	int InputSubject::GetNumSubscribers()
	{
		return subscribers.size();
	}

	void InputSubject::Notify()
	{
		//Iterate through the subscribers and alert them to the new info
		for(std::vector<InputObserver*>::iterator it = subscribers.begin(); it < subscribers.end(); it++)
		{
			InputObserver& ob = **it;
			ob.Notify();
		}
	}

	MouseSubject::MouseSubject()
	{
		mCurrentMouseState.x = 0;
		mCurrentMouseState.y = 0;
		mCurrentMouseState.leftClicked = false;
		mCurrentMouseState.rightClicked = false;
		mCurrentMouseState.middleClicked = false;
	}

	MouseSubject::~MouseSubject()
	{
	}

	void MouseSubject::Notify(MouseState &m)
	{
		if(subscribers.size() == 0)
			return;
		for(int j = 0; j < (int)subscribers.size(); j++)
		{
			//Casts the observer to a mouse observer and notifies them with the changed mous state
			MouseObserver* mouseObs = dynamic_cast<MouseObserver*>(subscribers[j]);
			mouseObs->Notify(m);
		}
	}

	MouseState MouseSubject::getMouseState()
	{
		return mCurrentMouseState;
	}

	KeySubject::KeySubject()
	{
	}

	KeySubject::~KeySubject()
	{
	}

	void KeySubject::Notify(SDL_KeyboardEvent* key)
	{
		if(subscribers.size() == 0)
			return;
		for(int j = 0; j < (int)subscribers.size(); j++)
		{
			//Casts the observer to a keyboard observer and notifies them with the lastest keyboard event
			if(subscribers[j])
			{
				KeyObserver* keyObs = dynamic_cast<KeyObserver*>(subscribers[j]);
				keyObs->Notify(key);
			}
		}
	}
}