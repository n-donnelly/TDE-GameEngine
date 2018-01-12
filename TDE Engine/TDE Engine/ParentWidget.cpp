#include "ParentWidget.h"

namespace TDE
{
	ParentWidget::ParentWidget(int x, int y, int width, int height, ParentWidget* parent)
		: Widget(x,y,width,height, parent)
	{
		mNumChildren = 0;
		mParent = parent;
	}


	ParentWidget::~ParentWidget(void)
	{
	}

	void ParentWidget::Update()
	{
		//Iterates though the list of children and updates each one
		if(!(mChildren.empty()))
		{
			for(list<TDE::Widget*>::iterator it = mChildren.begin(); it != mChildren.end(); it++)
			{
				(*it)->Update();
			}
		}
	}

	//Iterates through list of children and draws each
	void ParentWidget::Draw(TDEGraphics* g)
	{
		if(!(mChildren.empty()))
		{
			for(list<TDE::Widget*>::iterator it = mChildren.begin(); it != mChildren.end(); it++)
			{
				if((*it)->IsActive())
					(*it)->Draw(g);
			}
		}
	}

	//Hides all children
	void ParentWidget::Hide()
	{
		if(!(mChildren.empty()))
		{
			for(list<TDE::Widget*>::iterator it = mChildren.begin(); it != mChildren.end(); it++)
			{
				(*it)->Hide();
			}
		}
	}

	//Shows all children
	void ParentWidget::Show()
	{
		if(!(mChildren.empty()))
		{
			for(list<TDE::Widget*>::iterator it = mChildren.begin(); it != mChildren.end(); it++)
			{
				(*it)->Show();
			}
		}
	}

	//Adds child to list of children
	void ParentWidget::AddChild(Widget* child)
	{
		if(!child)
			return;

		for(list<TDE::Widget*>::iterator it = mChildren.begin(); it != mChildren.end(); it++)
		{
			if(child == (*it))
				return;
		}

		child->setID(mNumChildren);
		mChildren.push_back(child);
		mNumChildren++;
	}

	//Removes child from list of children using the pointer to compare
	void ParentWidget::RemoveChild(Widget* child)
	{
		if(!child)
			return;
		if(mChildren.empty())
			return;
		mChildren.remove(child);
		mNumChildren--;
	}

	KeySubject* ParentWidget::GetKeyboard()
	{
		return mNoParent ? NULL : mParent->GetKeyboard();
	}

	MouseSubject* ParentWidget::GetMouse()
	{
		return mNoParent ? NULL : mParent->GetMouse();
	}

	void ParentWidget::OnBtnClick(int btnID)
	{
		return;
	}

	void ParentWidget::OnBtnRelease(int btnID)
	{
		return;
	}
}