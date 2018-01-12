/*
This deorator draws a blue border around the edge of the widget
*/
#ifndef BORDER_DECOR_H
#define BORDER_DECOR_H

#include "WidgetDecorator.h"

namespace TDE
{
	class BorderDecorator : public WidgetDecorator
 	{
	public:
		//Needs the widget to be decorated and a thickness for the border
		BorderDecorator(Widget* w, int thickness);
		~BorderDecorator(void);
		void Draw(TDEGraphics* g);
		void setThickness(int thickness); //Allows something to change the width of the border

	private:
		int		mThickness;
	};
}
#endif