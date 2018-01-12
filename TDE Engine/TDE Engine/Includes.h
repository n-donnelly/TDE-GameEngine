#ifndef INCLUDES_H
#define INCLUDES_H

#include <stdio.h>
#include <stdlib.h>
#include <string>
//#include <SDL.h>
#include <SDL_image.h>
#include <SDL_opengl.h>
#include <SDL_ttf.h>
#include <gl/GL.h>
#include <math.h>
#include <stack>
#include <vector>
#include "TDEColor.h"
#include "CommonClasses.h"

#define uint unsigned int
#define Uint8 unsigned __int8
#define Uint16 unsigned __int16
#define Uint32 unsigned __int32
#define Uint64 unsigned __int64

#define _WIDTH 800
#define _HEIGHT 600

struct MouseState
{
	int x, y;
	bool leftClicked;
	bool rightClicked;
	bool middleClicked;
};

#endif