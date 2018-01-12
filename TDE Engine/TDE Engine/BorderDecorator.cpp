#include "BorderDecorator.h"

namespace TDE
{
	BorderDecorator::BorderDecorator(Widget* w, int thickness)
		: WidgetDecorator(w) //Uses the default decorator constructor
	{
		mThickness = thickness; //Sets the thickness
	}


	BorderDecorator::~BorderDecorator(void)
	{
	}

	void BorderDecorator::Draw(TDEGraphics *g)
	{
		WidgetDecorator::Draw(g);
		TDEColor col = g->GetColor(); //Gets the current color and saves it so it can be reset
		g->SetColor(0,0,255);
		for(int i = 1; i < mThickness; i++)
		{
			//Draws a rectangle around the edge, the rectangle gets smaller each time the for-loop iterates
			g->DrawRect(WidgetDecorator::mWidget->GetX()+(i-1), 
				WidgetDecorator::mWidget->GetY()+i,
				WidgetDecorator::mWidget->GetWidth()-(i*2),
				WidgetDecorator::mWidget->GetHeight()-(i*2));
		}
		g->SetColor(col);
	}

	//Sets the thickness
	void BorderDecorator::setThickness(int thickness)
	{
		mThickness = thickness;
	}
}