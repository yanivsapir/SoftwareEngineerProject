#include <iostream>
#include "ConsoleEventsHandler.h"
#include <string>
#include <vector>
#include "CheckList.h"
#include "NumericBox.h"
#include "RadioBox.h"
#include "comobox.h"
#include "MessageBoxs.h"

using namespace std;

int main(void) {

	vector<string> strings = { "option A", "option B", "option C", "option D" };
	vector<string> stringsA = { "hey", "yinon", "whats", "up" };
	Panel panel(60, 75);
	panel.setLocationX(2);
	panel.setLocationY(2);

	Comobox comobox(15, 20, strings);
	comobox.SetBackground(BackgroundColor::Blue);
	
	CheckList checkList(15, 14 ,stringsA);
	checkList.SetBackground(BackgroundColor::Green);
	
	RadioBox radioBox(15, 14, stringsA);
	radioBox.SetBackground(BackgroundColor::Red);
	
	NumericBox nb(15, 1, 5);
	nb.SetBackground(BackgroundColor::Yellow);
	nb.SetForeground(ForegroundColor::Black);

	MessageBoxs mb(15,30);
	mb.SetBackground(BackgroundColor::Purple);

	TextBox tb(20);
	tb.SetBackground(BackgroundColor::Teal);
	tb.SetForeground(ForegroundColor::White);

	panel.AddControl(&checkList, 2, 2);
	panel.AddControl(&radioBox, 19, 2);
	panel.AddControl(&mb, 36, 2);
	panel.AddControl(&nb, 2, 20);
	panel.AddControl(&comobox, 20, 20);
	panel.AddControl(&tb, 43, 20);
	
	panel.setVisible(true);
	
	panel.setCursorVisiblity(true);
	ConsoleEventsHandler consoleEventsHandler(&panel);
	SetConsoleCursorPosition(comobox.getCursorHandler(), { comobox.getLocationX() + 2, comobox.getLocationY() + 1 });
	consoleEventsHandler.listenToEvents();
	return 0;
}