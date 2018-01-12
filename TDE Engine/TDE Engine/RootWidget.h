/*
The root widget is the root of the widget tree, it extends the parent but has no parent itself
*/

#ifndef ROOTWIDGET_H
#define ROOTWIDGET_H

#include "ParentWidget.h"
#include "InputManager.h"

namespace TDE
{
	class RootWidget : public ParentWidget
	{
	public:
		RootWidget(InputManager* inputMan, TDEGraphics* g, AudioManager* audio);
		RootWidget(void);
		~RootWidget();

		virtual void Update();
		virtual void Draw(TDEGraphics* g);

		virtual void AddChild(Widget* child);
		virtual void RemoveChild(Widget* child);

		//Will return the keyboard and mouse subject from the member input manager
		KeySubject* GetKeyboard();
		MouseSubject* GetMouse();

		TDEGraphics* GetGraphics() {return mGraphics;};
		AudioManager* GetAudio() {return mAudio;};

		bool GetRunStatus();

	protected:
		//Contains the input manager for the other widgets
		InputManager*	mInputMgr;
		TDEGraphics*	mGraphics;
		AudioManager*	mAudio;
		bool			mWantRun;
	};
}

#endif