#ifndef SHITOT_TEXTBOX_H
#define SHITOT_TEXTBOX_H
#pragma once
#include "IControl.h"
#include <iostream>
#include <string>

using namespace std;

class TextBox : public IControl
{

private:
	string text;
	COORD coord;
	short inputRowIndex;
public:
	TextBox(int width);
	~TextBox();
	void setText(string value);
	void draw();
	void operateKeyboardEvents(KEY_EVENT_RECORD);
	void operateMouseEvents(MOUSE_EVENT_RECORD);
	string getText();

};
#endif //SHITOT_TEXTBOX_H
