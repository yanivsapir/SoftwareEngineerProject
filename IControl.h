#ifndef SHITOT_ICONTROL_H
#define SHITOT_ICONTROL_H
#pragma once
#include <windows.h>
#include <iostream>
#include <map>
#include "BorderSignContainer.h"

using namespace std;

enum class BorderType { Single, Double, None };
enum class ForegroundColor {
	Red = FOREGROUND_INTENSITY | FOREGROUND_RED, Blue = FOREGROUND_INTENSITY | FOREGROUND_BLUE,
	Green = FOREGROUND_INTENSITY | FOREGROUND_GREEN, Purple = FOREGROUND_RED | FOREGROUND_BLUE,
	Teal = FOREGROUND_BLUE | FOREGROUND_GREEN,
	Yellow = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
	White = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
	Black = 0
};
enum class BackgroundColor { 
	Red = BACKGROUND_RED, Blue = BACKGROUND_BLUE, Green = BACKGROUND_GREEN, Purple = BACKGROUND_RED | BACKGROUND_BLUE,
	Teal = BACKGROUND_BLUE | BACKGROUND_GREEN, Yellow = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY,
	White = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE, Black = 0 
};

class IControl
{

private:
	IControl * parentControl;

protected:
	short locationX;
	short locationY;
	short width;
	short height;
	bool visible;
	BackgroundColor backgroundColor;
	ForegroundColor foregroundColor;
	HANDLE cursorHandler;
	HWND consoleWindow;
	BorderType borderType;
	map<BorderType, BorderSignContainer> borderSigns;

public:

	IControl();
	virtual void operateKeyboardEvents(KEY_EVENT_RECORD) = 0;
	virtual void operateMouseEvents(MOUSE_EVENT_RECORD) = 0;
	virtual void draw() = 0;
	virtual void handleEvent(INPUT_RECORD *);
	virtual void setVisible(bool);
	short getLocationX();
	short getLocationY();
	virtual void setLocationX(short);
	virtual void setLocationY(short);
	int getWidth();
	int getHeight();
	void setWidth(int);
	void setHeight(int);
	void setBorderType(BorderType);
	void setParentControl(IControl *);
	IControl * getParentControl();
	BorderType getBorderType();
	map<BorderType, BorderSignContainer> getBorderSigns();
	virtual void SetForeground(ForegroundColor color);
	virtual void SetBackground(BackgroundColor color);
	ForegroundColor GetForeground();
	BackgroundColor GetBackground();
	bool isVisible();
	
	void IControl::setCursorVisiblity(bool isVisible);
	HANDLE getCursorHandler();
	HWND getConsoleWindow();
	COORD getConsoleCursorCoordinates();
	COORD getMousePositionCoordinates(MOUSE_EVENT_RECORD);
};
#endif //SHITOT_ICONTROL_H
