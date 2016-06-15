#ifndef SHITOT_NUMERIC_BOX_H
#define SHITOT_NUMERIC_BOX_H
#pragma once
#include "Panel.h"
#include "Button.h"
class NumericBox : public Panel
{

private:
	int count = 0;
	Button * plusButton;
	Button * minusButton;
	Label * countText;
	int min;
	int max;
public:
	NumericBox(int, int, int);
	int getMin();
	int getMax();
	int getCount();
	void incCount();
	void decCount();
	~NumericBox();
};
#endif //SHITOT_NUMERIC_BOX_H

