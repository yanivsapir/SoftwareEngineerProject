#ifndef SHITOT_LABEL_H
#define SHITOT_LABEL_H
#pragma once
#include "TextBox.h"
#include <iostream>

using namespace std;

class Label : public TextBox
{
private:
	string text;
public:
	Label(int width);
	~Label();
	void operateKeyboardEvents(KEY_EVENT_RECORD);
	void operateMouseEvents(MOUSE_EVENT_RECORD);
};
#endif //SHITOT_LABEL_H