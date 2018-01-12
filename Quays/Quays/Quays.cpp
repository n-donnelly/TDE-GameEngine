// Quays.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "QuaysRoot.h"

using namespace TDE;

int main(int argc, char** argv)
{
	TDE_Engine engine = TDE_Engine();
	TDEGraphics* g = engine.GetGraphics();
	g->InitGraphics(1600, 900, "Quays");
	g->CreateWin(false);
	QuaysRoot root = QuaysRoot(engine.GetInputManager(),g,engine.GetAudioManager());
	engine.Run(&root, 60);

	return 0;	
}