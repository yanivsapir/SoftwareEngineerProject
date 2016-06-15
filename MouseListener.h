#ifndef SHITOT_MOUSE_LISTENER_H
#define SHITOT_MOUSE_LISTENER_H
#pragma once
#include "IControl.h"
class MouseListener
{
public:
	virtual void mousePressed(IControl * control, int x, int y, bool isLeft) = 0;
};

#endif //SHITOT_MOUSE_LISTENER_H