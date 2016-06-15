#ifndef SHITOT_BUTTON_H
#define SHITOT_BUTTON_H
#include "Panel.h"
#include "Label.h"
#include "MouseListener.h"

#pragma once
class Button : public Label
{
private:
	MouseListener * mouseListener;
	Panel * panel;

public:
	Button(int width);
	void addMouseListener(MouseListener *);
	void setPanel(Panel *);
	void operateKeyboardEvents(KEY_EVENT_RECORD);
	void operateMouseEvents(MOUSE_EVENT_RECORD);
	void onPressed();
	~Button();
};

#endif //SHITOT_BUTTON_H