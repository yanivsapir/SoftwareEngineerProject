#ifndef SHITOT_CLB_MOUSE_LISTENER_H
#define SHITOT_CLB_MOUSE_LISTENER_H
#include "MouseListener.h"
#pragma once
class CLBMouseListener : public MouseListener
{
public:
	CLBMouseListener();
	void mousePressed(IControl *, int, int, bool);
	~CLBMouseListener();
};

#endif //SHITOT_CLB_MOUSE_LISTENER_H