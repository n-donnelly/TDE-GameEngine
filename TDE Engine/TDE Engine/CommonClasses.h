#ifndef COMMONCLASSES_H
#define COMMONCLASSES_H

namespace TDE
{
	struct Point
	{
		Point(void) {x = 0; y = 0;};
		Point(int x, int y) { this->x = x; this->y = y; };
		int x;
		int y;
	};

	struct Pointf
	{
		Pointf(void)  {x = 0.f; y = 0.f;};
		Pointf(float x, float y) { this->x = x; this->y = y; };
		float x;
		float y;
	};

	struct Rect
	{
		Rect(void) {x = 0; y = 0; width = 0; height = 0;};
		Rect(int aX, int aY, int w, int h) { x = aX; y = aY; width = w; height = h; };
		int x;
		int y;
		int width;
		int height;
	};

	struct Rectf
	{
		Rectf(void) {x = 0.f; y = 0.f; width = 0.f; height = 0.f;};
		Rectf(float aX, float aY, float aX2, float aY2) { x = aX; y = aY; width = aX2; height = aY2; };
		float x;
		float y;
		float width;
		float height;
	};

}

#endif