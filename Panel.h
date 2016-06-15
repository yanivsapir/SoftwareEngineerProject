#ifndef SHITOT_PANEL_H
#define SHITOT_PANEL_H
#pragma once
#include "IControl.h"
#include <vector>
#include <iostream>
#include <string>

using namespace std;

class Panel : public IControl
{
private:
	vector<IControl *> controllers;
protected:
	COORD coord;

public:
	Panel(int height, int width);
	void AddControl(IControl * control, int locationX, int locationY);
	void operateKeyboardEvents(KEY_EVENT_RECORD);
	void operateMouseEvents(MOUSE_EVENT_RECORD);
	void handleEvent(INPUT_RECORD *);
	void setVisible(bool);
	void SetForeground(ForegroundColor color);
	void SetBackground(BackgroundColor color);
	void setLocationX(short);
	void setLocationY(short);
	vector<IControl *> getControllers();
	IControl * findRelevantController(COORD);
	void draw();
	~Panel();
};

#endif //SHITOT_PANEL_H
