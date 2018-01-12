#ifndef MOUSE_SUB_H
#define MOUSE_SUB_H

#include "InputSubject.h"

namespace TDE
{
	class MouseSubject : public InputSubject
	{
	public:
		MouseSubject(void);
		~MouseSubject(void);

	private:
		MouseState mCurrentMouseState;
	};

}
#endif