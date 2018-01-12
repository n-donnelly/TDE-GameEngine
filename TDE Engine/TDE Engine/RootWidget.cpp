#include "RootWidget.h"

namespace TDE
{
	RootWidget::RootWidget(InputManager* inputMgr, TDEGraphics* g, AudioManager* audio)
		: ParentWidget(0, 0, g->GetWidth(), g->GetHeight(), 0) //Creates a parent with default values
	{
		mInputMgr = inputMgr; //Inits a new input manager
		mGraphics = g;
		mAudio = audio;
		mWantRun = true;
	}

	RootWidget::RootWidget(void)
		: ParentWidget(0, 0, _WIDTH, _HEIGHT, 0) //Creates a parent with default values
	{
		mInputMgr = new InputManager(); //Inits a new input manager
		mWantRun = true;
	}

	RootWidget::~RootWidget(void)
	{
	}

	//Updates the input manager and calls the parent widget update function to update the children
	void RootWidget::Update()
	{
		mInputMgr->Update();
		mGraphics->UpdateAnims();
		ParentWidget::Update();
	}

	void RootWidget::Draw(TDEGraphics* g)
	{
		ParentWidget::Draw(g);
	}

	void RootWidget::AddChild(Widget* child)
	{
		ParentWidget::AddChild(child);
	}

	void RootWidget::RemoveChild(Widget* child)
	{
		ParentWidget::RemoveChild(child);
	}

	//Returns the Keyboard and mouse subject from the input manager
	KeySubject* RootWidget::GetKeyboard()
	{
		return mInputMgr->GetKeySubject();
	}

	MouseSubject* RootWidget::GetMouse()
	{
		return mInputMgr->GetMouseSubject();
	}

	bool RootWidget::GetRunStatus()
	{
		return mWantRun;
	}
}