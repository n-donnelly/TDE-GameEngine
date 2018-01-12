#include "DebugRoot.h"
#include "AIDecorator.h"
#include "BorderDecorator.h"
#include "InvertControlDecorator.h"

#define MIN(a, b) (a > b ? b : a)
#define MAX(a,b) (a > b ? a: b)

DebugRoot::DebugRoot(TDEGraphics* graphic)
	: RootWidget()
{
	g = graphic;

	//Initialise the graphics object with a width, height and window title
	g->InitGraphics(_WIDTH, _HEIGHT, "Testing Widgets and Input");

	//Creates a window, false indicates that it should not be full screen
	g->CreateWin(false);

	//Retrieves the keyboard from the input manager
	mKeyboard = GetKeyboard();
	mMouse = GetMouse();

	//Subscribes to the keyboard subject
	mKeyboard->Subscribe(this);
	mMouse->Subscribe(this);

	//Initialises the position and size of the blocks
	mX = 40;
	mY = 40;
	blockWidth = 50;
	blockHeight = 50;
	wKeyDown = aKeyDown = dKeyDown = sKeyDown = false;

	//Creates a new TSW
	mTSW = new TestSquareWidget(0,0,_WIDTH, _HEIGHT, this);

	//Wraps it in a basic WidgetDecorator
	mDecoratedWidget = new WidgetDecorator(mTSW);

	//Subscribes it to the keyboard presses
	mDecoratedWidget->ListenForKeyboard();
	am = AudioManager();
	am.Init();
	am.LoadMusicFile("supremacy", "C:\\Users\\Neil\\Desktop\\Supremacy.ogg");
	am.PlayMusic("supremacy", 0);
	am.LoadSoundFile("yay", "C:\\Users\\Neil\\Desktop\\bloop_x.wav");

	g->LoadAnim("Braid", "C:\\Users\\Neil\\Pictures\\SpriteSheets\\BraidSheet.png", 131, 148, 1024, 1024, 27);
	braid = g->GetAnim("Braid");
	braid->Play(700, 0, -1);
	bX = 0;
	bAngle = 0.f;
	bY = _HEIGHT/2 - braid->GetCellHeight()/2;

	g->LoadTDEImage("test.jpeg", "test");

	ran = RandomGen();
	ran.Randomize();

	result = "";
	//Adds it as a child so it will be drawn and updated when this widget is
	AddChild(mDecoratedWidget);
	black = TDEColor(0,0,0);
	white = TDEColor(255,255,255);
	col = white;
	bg = TDEColor(0, 0, 255);
	braidCol = TDEColor(255,0,0);

	for(int i = 0; i < 6; i++)
	{
		RandomShape[i][0] = 0.f;
		RandomShape[i][1] = 0.f;
	}
}


DebugRoot::~DebugRoot()
{
}


void DebugRoot::Update()
{
	//Calls the function of its base class to update the children
	RootWidget::Update();
	braid->Update();
	//Updates position of block
	if(wKeyDown)
	{
		mY = mY > 0 ? mY-3 : mY;
		bAngle += 2.5f;
	}
	if(sKeyDown)
	{
		mY = mY + blockHeight < _HEIGHT ? mY+3 : mY;
		bAngle -= 2.5f;
	}
	if(aKeyDown)
		mX = mX > 0 ? mX-3 : mX;
	if(dKeyDown)
	{
		if(braid->isPaused())
			braid->Resume();
		mX = mX + blockHeight < _WIDTH ? mX+3 : mX;
		bX = bX < _WIDTH ? bX + 3 : 0;
	}
	else if(!(braid->isPaused()))
	{
		braid->Pause();
	}
}

void DebugRoot::Draw()
{
	//Initialises drawing for it and its children
	g->InitDraw();
	g->SetColor(white);
	g->FillRect(0,0,_WIDTH,_HEIGHT); //Fills the background
	RootWidget::Draw(g); //Draws the children
	g->SetColor(0,255,0);
	g->FillRect(mX, mY, blockWidth, blockHeight); //Draws the block
	g->ColorizeImages(false);
	g->SetColor(braidCol);
	if(bX < _WIDTH && bX + braid->GetCellWidth() > _WIDTH)
	{
		int xOffset = (bX + braid->GetCellWidth() - _WIDTH);
		Rect dest1 = Rect(bX, bY, braid->GetCellWidth() - xOffset, braid->GetCellHeight());
		Rect dest2 = Rect(0, bY, xOffset, braid->GetCellHeight());

		Rect src1(0, 0, braid->GetCellWidth() - xOffset, braid->GetCellHeight());
		Rect src2(braid->GetCellWidth() - xOffset, 0, xOffset, braid->GetCellHeight());

		g->DrawAnimation(braid, dest1, src1);
		g->DrawRect(dest1);
		g->DrawRect(dest2);
		g->DrawAnimation(braid, dest2, src2);
	}
	else g->DrawAnimation(braid, bX, bY);
	
	g->FillRect(Rect(0, bY + braid->GetCellHeight() - 4, _WIDTH, 50));

	g->SetColor(0,0,0);	
	g->DrawShape(RandomShape, SHAPE_POINTS, TDEColor(255, 255, 0));
	g->ColorizeImages(false);
	g->SetColor(255,255,255);
	g->DrawString(result, 20, 20, TDEColor(0,0,0));

	g->EndDraw(); //Clears the buffer and updates the screen
}

void DebugRoot::KeyDown(TDE_Key k)
{
	//Called by the keyboard subject with a n ew keypress
	switch (k)
	{
	case KEY_SPACE:
		am.PlaySound("yay", 0);
		bX = 0;
		bAngle = 0;
		braid->Reset();
		break;
	case KEY_w:
		wKeyDown = true;
		break;
	case KEY_s:
		sKeyDown = true;
		break;
	case KEY_a:
		aKeyDown = true;
		break;
	case KEY_d:
		dKeyDown = true;
		break;
	case KEY_RETURN:
		result = std::to_string(ran.GetSeed());
		GenRandomShape();
		break;
	case KEY_1: //Inverts the control of the TSW by adding a new Decorator
		RemoveChild(mDecoratedWidget); //Get rid of the current Decorator as it's being changed
		mDecoratedWidget->IgnoreKeyboard(); //Tell the old decorator to ignore the keyboard
		mDecoratedWidget = new InvertControlDecorator(mTSW); //Add a new decorator to mTSW
		mDecoratedWidget->ListenForKeyboard(); //Subscribe the new widget to the keyboard
		AddChild(mDecoratedWidget); //Adds the new child
		break;
	case KEY_2: //We don't subscibe as the decorator will generate its own key presses
		RemoveChild(mDecoratedWidget);
		mDecoratedWidget->IgnoreKeyboard();
		mDecoratedWidget = new AIDecorator(mTSW);
		AddChild(mDecoratedWidget);
		break;
	case KEY_3: //Resets the widget to the basic decorator that doesn't do anything
		RemoveChild(mDecoratedWidget);
		mDecoratedWidget->IgnoreKeyboard();
		mDecoratedWidget = new WidgetDecorator(mTSW);
		mDecoratedWidget->ListenForKeyboard();
		AddChild(mDecoratedWidget);
		break;
	default:
		break;
	}
}

void DebugRoot::KeyUp(TDE_Key k)
{
	//Releases the key presses
	switch (k)
	{
	case KEY_SPACE:
		col = white;
		break;
	case KEY_w:
		wKeyDown = false;
		break;
	case KEY_s:
		sKeyDown = false;
		break;
	case KEY_a:
		aKeyDown = false;
		break;
	case KEY_d:
		dKeyDown = false;
		break;
	default:
		break;
	}
}

void DebugRoot::MouseMoved(MouseState &m)
{
	bg = TDEColor(MIN(255, m.y/2),0, MAX(0, 255 - m.y/2));
	braidCol = TDEColor(MAX(0, 255 - m.y/2), 0, MIN(255, m.y/2)); 
}

void DebugRoot::GenRandomShape()
{
	for(int i = 0; i < SHAPE_POINTS; i++)
	{
		RandomShape[i][0] = ran.Random(_WIDTH/2);
		RandomShape[i][1] = ran.Random(_HEIGHT/2);
	}
}