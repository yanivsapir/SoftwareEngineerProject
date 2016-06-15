#include "IControl.h"

IControl::IControl() {
	cursorHandler = GetStdHandle(STD_OUTPUT_HANDLE);
	consoleWindow = GetConsoleWindow();
	borderSigns[BorderType::None] = {' ',' ',' ',' ',' ',' '};
	borderSigns[BorderType::Single] = { '\xBF','\xDA','\xC4','\xB3','\xD9','\xC0' };
	borderSigns[BorderType::Double] = { '\xBB','\xC9','\xCD','\xBA','\xBC','\xC8' };
	backgroundColor = BackgroundColor::Black;
	foregroundColor = ForegroundColor::White;
	visible = false;
}

short IControl::getLocationX() {
	return locationX;
}

short IControl::getLocationY() {
	return locationY;
}

void IControl::setLocationX(short _locationX) {
	locationX = _locationX;
}

void IControl::setLocationY(short _locationY) {
	locationY = _locationY;
}

int IControl::getWidth() {
	return width;
}

int IControl::getHeight() {
	return height;
}

void IControl::setWidth(int _width) {
	width = _width;
}

void IControl::setHeight(int _height) {
	height = _height;
}

HANDLE IControl::getCursorHandler()
{
	return cursorHandler;
}

HWND IControl::getConsoleWindow()
{
	return consoleWindow;
}

void IControl::setBorderType(BorderType _borderType)
{
	borderType = _borderType;
}

void IControl::setParentControl(IControl * _parentControl)
{
	parentControl = _parentControl;
}

IControl * IControl::getParentControl()
{
	return parentControl;
}

map<BorderType, BorderSignContainer> IControl::getBorderSigns()
{
	return borderSigns;
}

BorderType IControl::getBorderType()
{
	return borderType;
}

COORD IControl::getConsoleCursorCoordinates()
{
	COORD coord;
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	GetConsoleScreenBufferInfo(cursorHandler, &consoleInfo);
	coord.X = consoleInfo.dwCursorPosition.X;
	coord.Y = consoleInfo.dwCursorPosition.Y;
	return coord;
}

COORD IControl::getMousePositionCoordinates(MOUSE_EVENT_RECORD ker)
{
	return { ker.dwMousePosition.X, ker.dwMousePosition.Y };
}

void IControl::handleEvent(INPUT_RECORD * irInBuf)
{
	if (irInBuf->EventType == KEY_EVENT)
	{
		operateKeyboardEvents(irInBuf->Event.KeyEvent);
	}
	else if (irInBuf->EventType == MOUSE_EVENT)
	{
		if (irInBuf->Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			operateMouseEvents(irInBuf->Event.MouseEvent);
		}
	}
}

void IControl::setVisible(bool isVisible)
{
	COORD coord = getConsoleCursorCoordinates();
	SetConsoleCursorPosition(getCursorHandler(), { getLocationX(), getLocationY() });
	if (isVisible == false)
	{
		this->visible = false;
		for (int i = 0; i <= height + 1; i++)
		{
			for (int j = 0; j <= width + 2; j++)
			{
				cout << ' ';
			}
			SetConsoleCursorPosition(getCursorHandler(), { getLocationX(), getLocationY() + static_cast<short>(i) });
		}
	}
	else
	{
		this->visible = true;
		draw();
	}
	SetConsoleCursorPosition(getCursorHandler(), coord);
}

void IControl::setCursorVisiblity(bool isVisible)
{
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(cursorHandler, &cursorInfo);
	cursorInfo.bVisible = isVisible;
	SetConsoleCursorInfo(cursorHandler, &cursorInfo);
}

void IControl::SetForeground(ForegroundColor color)
{
	foregroundColor = color;
}

void IControl::SetBackground(BackgroundColor color)
{
	backgroundColor = color;
}

ForegroundColor IControl::GetForeground()
{
	return foregroundColor;
}

BackgroundColor IControl::GetBackground()
{
	return backgroundColor;
}

bool IControl::isVisible()
{
	return this->visible;
}
