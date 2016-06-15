#ifndef SHITOT_MESSAGE_BOXS_H
#define SHITOT_MESSAGE_BOXS_H
#pragma once
#include "Panel.h"
#include "Label.h"
#include "Button.h"
class MessageBoxs : public Panel
{
private:
	string text;
	string title;
	Label * textLabel;
	Label * titleLabel;
	Button * OKButton;
	Button * cancelButton;
	string value;

public:
	
	MessageBoxs(int,int);
	void SetText(string);
	void SetTitle(string);
	string getValue();
	void setValue(string);
	~MessageBoxs();
};
#endif //SHITOT_MESSAGE_BOXS_H
