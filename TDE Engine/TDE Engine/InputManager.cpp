#include "InputManager.h"

namespace TDE
{
	InputManager::InputManager()
	{
		//Creates objects for the mouse and keyboard subjects
		mMouseSubject = MouseSubject();
		mKeySubject = KeySubject();

		//Initialises the mouse state 
		mMouseState.x = 0;
		mMouseState.y = 0;
		mMouseState.leftClicked = false;
		mMouseState.rightClicked = false;
		mMouseState.middleClicked = false;
	}

	InputManager::~InputManager()
	{
	}

	bool InputManager::Update()
	{
		//Polls the SDL event handler and for each key press it detected decides what to do with it
		SDL_Event aEvent;
		while(SDL_PollEvent(&aEvent))
		{
			switch(aEvent.type)
			{
				//For any key press or release, let the keyboard subject know
			case SDL_KEYUP:
			case SDL_KEYDOWN:
				mKeySubject.Notify(&aEvent.key);
				break;
				//Updates the mouse state with the new position and notifies the Mouse subject
			case SDL_MOUSEMOTION:
				mMouseState.x = aEvent.motion.x;
				mMouseState.y = aEvent.motion.y;
				mMouseSubject.Notify(mMouseState);
				break;
				//If a button is pressed, record what buttons are pressed and notify the mouse subject
			case SDL_MOUSEBUTTONUP: 
			case SDL_MOUSEBUTTONDOWN:
				switch(aEvent.button.button)
				{
				case SDL_BUTTON_LEFT:
					mMouseState.leftClicked = aEvent.button.state == SDL_PRESSED ? true : false;
					break;
				case SDL_BUTTON_RIGHT:
					mMouseState.rightClicked = aEvent.button.state == SDL_PRESSED ? true : false;
					break;
				case SDL_BUTTON_MIDDLE:
					mMouseState.middleClicked = aEvent.button.state == SDL_PRESSED ? true : false;
					break;
				default:
					break;
				}
				mMouseSubject.Notify(mMouseState);
				break;
				//Detects if the window is being closed, if so print it to the output (for what its worth) and shut down
			case SDL_QUIT:
				printf("Quitting\n");
				exit(1);
				return true;
				break;
			default:
				break;
			}
		}
		return false;
	}

	MouseSubject* InputManager::GetMouseSubject()
	{
		return &mMouseSubject;
	}

	KeySubject* InputManager::GetKeySubject()
	{
		return &mKeySubject;
	}
}