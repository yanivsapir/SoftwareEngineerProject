#include <windows.h>
#include <iostream>
#include "IControl.h"
#include "ConsoleEventsHandler.h"

#define BYTES_TO_READ 128

using namespace std;

HANDLE hStdin;
INPUT_RECORD irInBuf[128];
DWORD cNumRead;
IControl * form;

ConsoleEventsHandler::ConsoleEventsHandler(IControl * _form)
{
	hStdin = GetStdHandle(STD_INPUT_HANDLE);
	setForm(_form);
}

ConsoleEventsHandler::ConsoleEventsHandler()
{
	hStdin = GetStdHandle(STD_INPUT_HANDLE);
}

ConsoleEventsHandler::~ConsoleEventsHandler()
{
}


void ConsoleEventsHandler::setForm(IControl * _form)
{
	form = _form;
}

void ConsoleEventsHandler::listenToEvents() {

	while (true)
	{
		if (!ReadConsoleInput(
			hStdin,      // input buffer handle
			irInBuf,     // buffer to read into
			BYTES_TO_READ,         // size of read buffer
			&cNumRead)) // number of records read
			exit(-1);

		// Dispatch the events to the appropriate handler.
		for (int i = 0; i < cNumRead; i++)
		{
			if(irInBuf[i].EventType == MOUSE_EVENT || irInBuf[i].EventType == KEY_EVENT)
				form->handleEvent(&irInBuf[i]);
		}
	}
}