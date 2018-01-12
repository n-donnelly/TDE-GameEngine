#ifndef BUTTON_WIDGET_H
#define BUTTON_WIDGET_H

#include "Widget.h"

namespace TDE
{
	class ButtonWidget : public Widget
	{
	public:
		ButtonWidget(int x, int y, int width, int height, ParentWidget* parent);
		ButtonWidget(int x, int y, int width, int height, ParentWidget* parent, TDEImage* btnIm);
		ButtonWidget(int x, int y, int width, int height, ParentWidget* parent, TDEImage* aUp, TDEImage* aDown);
		ButtonWidget();
		~ButtonWidget(void);

		void SetUpImage(TDEImage* aUp);
		void SetDownImage(TDEImage* aDown);

		virtual void Draw(TDEGraphics* g);
		
		virtual void MouseClickDown(MouseState &m);
		virtual void MouseClickUp(MouseState &m);

		virtual void OnClick();
		virtual void OnRelease();
		bool IsBeingClicked();

	protected:
		bool beingClicked;
		TDEImage* mUp, *mDown;
	};
}
#endif