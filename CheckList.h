#ifndef SHITOT_CHECK_LIST_H
#define SHITOT_CHECK_LIST_H
#include "Panel.h"
#include "Button.h"

#pragma once
class CheckList : public Panel
{
private:
	vector<size_t> selectedIndices;
	vector<string> entries;
	map<int, int> buttonIndecies;

protected:
	map<size_t,Button *> buttonsByIndex;
	vector<Button *> buttons;
	Label * resultLabel;

public:
	CheckList(int, int, vector<string>);
	void operateKeyboardEvents(KEY_EVENT_RECORD);
	void operateMouseEvents(MOUSE_EVENT_RECORD);
	vector<size_t> GetSelectedIndices();
	void SelectIndex(size_t index);
	void DeselectIndex(size_t index);
	vector<string> getEntries();
	map<int, int> getButtonIndecies();
	map<size_t, Button *> GetButtonsByIndex();
	virtual MouseListener * CheckList::getButtonMouseListener();
	Label * getResultLabel();
	~CheckList();
};

#endif //SHITOT_CHECK_LIST_H
