#ifndef SHITOT_CONSOLEEVENTSHANDLER_H
#define SHITOT_CONSOLEEVENTSHANDLER_H
#pragma once
#include "IControl.h"

class ConsoleEventsHandler
{

private:
	IControl * form;
public:
	ConsoleEventsHandler();
	ConsoleEventsHandler(IControl * form);
	void setForm(IControl * form);
	~ConsoleEventsHandler();
	void listenToEvents();
};
#endif //SHITOT_CONSOLEEVENTSHANDLER_H
