#ifndef QUAYS_BTN_H
#define QUAYS_BTN_H

#include "ButtonWidget.h"

using namespace TDE;

class QuaysButton : public ButtonWidget
{
public:
	QuaysButton(int x, int y, int width, int height, ParentWidget* parent);
	QuaysButton(int x, int y, int width, int height, ParentWidget* parent, TDEImage* aUp, TDEImage* aDown);
	QuaysButton(void);
	~QuaysButton(void);

	void Draw(TDEGraphics* g);

private:

};

#endif