/*
This parent widget extends from the Widget class but includes behaviour to update all the children
*/
#ifndef PARENTWIDGET_H
#define PARENTWIDGET_H

#include "AudioManager.h"
#include "Widget.h"
#include <list>

namespace TDE
{
	class ParentWidget : public Widget
	{
	public:
		ParentWidget(int x, int y, int width, int height, ParentWidget* parent);
		~ParentWidget(void);

		//Extends these functions as it will call each childs version of the function as well
		virtual void Update();
		virtual void Draw(TDEGraphics* g);

		virtual void Hide();
		virtual void Show();

		//Adds and removes widgets from the parent's list of children
		virtual void AddChild(Widget* child);
		virtual void RemoveChild(Widget* child);

		//Returns a keyboard and mouse subject to the child
		//Each parent will check its parent until the subject is gotten from the root widget
		virtual KeySubject* GetKeyboard();
		virtual MouseSubject* GetMouse();

		virtual TDEGraphics* GetGraphics() {return mParent->GetGraphics();};
		virtual AudioManager* GetAudioManager() {return mParent->GetAudioManager();};

		virtual void OnBtnClick(int btnID);
		virtual void OnBtnRelease(int btnID);

	protected:
		//List of child widgets, the parent and the number of children
		list<Widget*>	mChildren;
		ParentWidget*		mParent;
		int					mNumChildren;
	};
}

#endif