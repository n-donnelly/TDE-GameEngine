/*
The input manager is in control of collecting the input from SDL and supplying it to 
the subjects in the observer pattern to notify their subscribers of the change
*/

#ifndef INPUT_MGR_H
#define INPUT_MGR_H

#include <vector>
#include "Includes.h"
#include "InputSubject.h"

namespace TDE
{
	class InputManager
	{
	public:
		InputManager();
		~InputManager();

		//Input manager checks for any new input
		bool Update();

		//Returns a pointer to the subjects in the observer pattern
		//Used by the observers to subscribe
		MouseSubject* GetMouseSubject();
		KeySubject* GetKeySubject();

	private:
		//The subjects for the input
		MouseSubject	mMouseSubject;
		KeySubject		mKeySubject;

		//Mouse State is a struct containing the latest info on the mouse
		//i.e. positition and state of the buttons
		MouseState		mMouseState;
	};
}

#endif