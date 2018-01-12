/*
The parent widget used to control the Test Square Widget
It has it's own square that will always be controlled the same way
*/

#ifndef DEBUG_ROOT
#define DEBUG_ROOT

#define SHAPE_POINTS 8

#include "RootWidget.h"
#include "TestSquareWidget.h"
#include "AudioManager.h"
#include "TDERandomGen.h"
#include <string>

using namespace TDE;

class DebugRoot : public RootWidget
{
public:
	//This is the root widget so it keeps the Graphics object that all the children will use to draw
	DebugRoot(TDE::TDEGraphics* graphic);
	~DebugRoot(void);

	void Update();
	void Draw();

	//Extends the KeyDown and KeyUp function to control what happens when a key press is detected
	void KeyDown(TDE_Key k);
	void KeyUp(TDE_Key k);

	void MouseMoved(MouseState& m);
	void GenRandomShape();

private:
	TDE::TDEGraphics*	g;
	Widget* mTSW; //The basic TestSquareWidget
	Widget*	mDecoratedWidget; //The decorator that wraps mTSW to add behaviour
	
	//Position of blocks
	int mX;
	int mY;

	//Size of block
	int blockWidth;
	int blockHeight;

	//Boolean to keep track of what keys are currently being pressed
	bool wKeyDown, sKeyDown, aKeyDown, dKeyDown;

	AudioManager am;
	TDE_Animation* braid;
	int bX, bY;
	float bAngle;

	//The current colors to use
	TDEColor black, white;
	TDEColor col, bg, braidCol;

	float RandomShape[SHAPE_POINTS][2];

	std::string result;
	RandomGen ran;
};

#endif