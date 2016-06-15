#ifndef SHITOT_RADIO_BOX_LIST_H
#define SHITOT_RADIO_BOX_LIST_H
#include "CheckList.h"
#pragma once
class RadioBox : public CheckList
{

private:
	size_t selectedIndex;

public:
	RadioBox(int, int, vector<string>);
	MouseListener * getButtonMouseListener();
	size_t GetSelectedIndex();
	void SetSelectedIndex(size_t index);
	~RadioBox();
};
#endif //SHITOT_RADIO_BOX_LIST_H