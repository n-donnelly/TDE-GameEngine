/*
Basic decorator for a widget
*/
#ifndef WIDGET_DECOR_H
#define WIDGET_DECOR_H

#include "Widget.h"

namespace TDE
{
	class WidgetDecorator : public Widget
	{
	public:
		//Constructs decorator using the widget and the widget's details
		WidgetDecorator(Widget* widget) {mWidget = widget; 
							mParent = widget->GetParent();
							mNoParent = !(hasParent()); 
							mKeyListening = widget->IsListeningForKeys();
							mMouseListening = widget->IsListeningForMouse();};
		~WidgetDecorator(void) {};
		
		//All of these functions are inherited from widget and pass control to the widget its decorating
		//But allow derived classes to implement their own
		virtual void Update() { mWidget->Update();};
		virtual void Draw(TDEGraphics* g) { mWidget->Draw(g);};

		virtual void Hide() { mWidget->Hide();};
		virtual void Show() { mWidget->Show();};

		bool operator==(Widget w) {return &w == mWidget; };

		virtual void SetActive(bool isActive) { mWidget->SetActive(isActive);};
		bool IsActive() { return mWidget->IsActive();};
		bool IsShown() { return mWidget->IsShown();};

		bool ListenForMouse() { return mWidget->ListenForMouse();};
		bool ListenForKeyboard() { return mWidget->ListenForKeyboard();};

		void IgnoreKeyboard() { return mWidget->IgnoreKeyboard();};
		void IgnoreMouse() { return mWidget->IgnoreMouse();};

		bool IsListeningForKeys() { return mWidget->IsListeningForKeys(); };
		bool IsListeningForMouse() { return mWidget->IsListeningForMouse(); };

		virtual void KeyDown(TDE_Key k) { mWidget->KeyDown(k);};
		virtual void KeyUp(TDE_Key k) { mWidget->KeyUp(k);};
		virtual void MouseClickDown(MouseState &m) { mWidget->MouseClickDown(m);};
		virtual void MouseClickUp(MouseState &m) { mWidget->MouseClickUp(m);};
		virtual void MouseMoved(MouseState &m) { mWidget->MouseMoved(m);};

		ParentWidget* GetParent() { return mWidget->GetParent();};
		int GetID() { return mWidget->GetID();};
		void setID(int newID) { mWidget->setID(newID);};
		bool hasParent() { return mWidget->hasParent();};

		int GetX() { return mWidget->GetX();};
		int GetY() { return mWidget->GetY();};
		int GetWidth() { return mWidget->GetWidth();};
		int GetHeight() { return mWidget->GetWidth();};

	protected:
		//The decorated widget
		Widget*		mWidget;
	};
}
#endif