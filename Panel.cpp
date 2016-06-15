#include "Panel.h"

void drawPanelUpperBorderLayer(Panel * panel);
void drawPanelMiddleBorderLayer(Panel * panel);
void drawPanelLowerBorderLayer(Panel * panel);
void drawBorder(Panel * panel);
bool isControllerRegion(COORD, IControl *);

Panel::Panel(int height, int width)
{
	setWidth(width);
	setHeight(height);
}

Panel::~Panel()
{

}

void Panel::AddControl(IControl * control, int locationX, int locationY)
{
	control->setLocationX(getLocationX() +  locationX);
	control->setLocationY(getLocationY() + locationY);
	control->setParentControl(this);
	controllers.push_back(control);
}


void Panel::draw()
{
	if (isVisible())
	{
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(cursorHandler, &csbi);
		SetConsoleTextAttribute(cursorHandler, static_cast<int>(foregroundColor) | static_cast<int>(backgroundColor));
		COORD coord = getConsoleCursorCoordinates();
		drawBorder(this);
		for (IControl * controller : controllers)
		{
			controller->draw();
		}
		SetConsoleCursorPosition(cursorHandler, coord);
		SetConsoleTextAttribute(cursorHandler, csbi.wAttributes);
	}
}

void Panel::operateKeyboardEvents(KEY_EVENT_RECORD ker)
{
	coord = getConsoleCursorCoordinates();
}

void Panel::operateMouseEvents(MOUSE_EVENT_RECORD mer)
{
	if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
	{
		coord = getMousePositionCoordinates(mer);
	}
}

IControl * Panel::findRelevantController(COORD coord)
{
	IControl * relevantController = NULL;
	for (IControl * controller : controllers)
	{
		if(isControllerRegion(coord, controller))
		{
			relevantController = controller;
			break;
		}
	}
	return relevantController;
}

bool isControllerRegion(COORD coord, IControl * controller)
{
	if (controller->getLocationX() - 1 <= coord.X && controller->getLocationX() + controller->getWidth() + 1 >= coord.X  &&
		controller->getLocationY() <= coord.Y && controller->getLocationY() + controller->getHeight() - 1>= coord.Y)
		return true;
	return false;
}

void Panel::handleEvent(INPUT_RECORD * irInBuf)
{
	coord = {};
	IControl::handleEvent(irInBuf);
	IControl * controller = findRelevantController(coord);
	if (controller != NULL)
		controller->handleEvent(irInBuf);
}

void Panel::setLocationX(short _locationX)
{
	for (IControl * controller : controllers)
	{
		controller->setLocationX(controller->getLocationX() - locationX);
		controller->setLocationX(controller->getLocationX() + _locationX);
	}
	locationX = _locationX;
}

void Panel::setLocationY(short _locationY)
{
	for (IControl * controller : controllers)
	{
		controller->setLocationY(controller->getLocationY() - locationY);
		controller->setLocationY(controller->getLocationY() + _locationY);
	}
	locationY = _locationY;
}

void drawBorder(Panel * panel)
{
	if (panel->getBorderType() != BorderType::None)
	{
		drawPanelUpperBorderLayer(panel);
		drawPanelMiddleBorderLayer(panel);
		drawPanelLowerBorderLayer(panel);
	}
	else
	{
		cout << endl;
		cout << endl;
		cout << endl;
	}
}

void drawPanelUpperBorderLayer(Panel * panel)
{
	BorderSignContainer borderSignContainer = panel->getBorderSigns()[panel->getBorderType()];
	SetConsoleCursorPosition(panel->getCursorHandler(), { panel->getLocationX(), panel->getLocationY() });
	cout << borderSignContainer.topLeftCorner;
	for (int i = 0; i < panel->getWidth(); i++) {
		cout << borderSignContainer.horizontalLine;
	}
	cout << borderSignContainer.topRightCorner << endl;
}

void drawPanelMiddleBorderLayer(Panel * panel)
{
	BorderSignContainer borderSignContainer = panel->getBorderSigns()[panel->getBorderType()];
	for (short i = 1; i < panel->getHeight(); i++)
	{
		SetConsoleCursorPosition(panel->getCursorHandler(), { panel->getLocationX(), panel->getLocationY() + i });
		cout << borderSignContainer.verticalLine;
		for (int j = 0; j < panel->getWidth(); j++)
		{
			cout << ' ';
		}
		cout << borderSignContainer.verticalLine << endl;
	}
}

void drawPanelLowerBorderLayer(Panel * panel)
{
	SetConsoleCursorPosition(panel->getCursorHandler(), { panel->getLocationX(), panel->getLocationY() + static_cast<short>(panel->getHeight()) });
	BorderSignContainer borderSignContainer = panel->getBorderSigns()[panel->getBorderType()];
	cout << borderSignContainer.bottomLeftCorner;
	for (int i = 0; i < panel->getWidth(); i++) {
		cout << borderSignContainer.horizontalLine;
	}
	cout << borderSignContainer.bottomRightCorner << endl;
}

void Panel::SetForeground(ForegroundColor color)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(cursorHandler, &csbi);
	foregroundColor = color;
	SetConsoleTextAttribute(cursorHandler, static_cast<int>(color) | static_cast<int>(backgroundColor));
	draw();
	SetConsoleTextAttribute(cursorHandler, csbi.wAttributes);
	for (IControl * controller : controllers)
		controller->SetForeground(color);
}

void Panel::SetBackground(BackgroundColor color)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(cursorHandler, &csbi);
	backgroundColor = color;
	SetConsoleTextAttribute(cursorHandler, static_cast<int>(foregroundColor) | static_cast<int>(color));
	draw();
	SetConsoleTextAttribute(cursorHandler, csbi.wAttributes);
	for (IControl * controller : controllers)
		controller->SetBackground(color);
}

vector<IControl *> Panel::getControllers()
{
	return controllers;
}

void Panel::setVisible(bool isVisible)
{
	IControl::setVisible(isVisible);
	for (IControl * control : controllers)
	{
		control->setVisible(isVisible);
	}
}