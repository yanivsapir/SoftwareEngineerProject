#include "Button.h"

Button::Button(int width) :Label(width)
{
}

void Button::addMouseListener(MouseListener * _mouseListener)
{
	mouseListener = _mouseListener;
}

void Button::setPanel(Panel * _panel)
{
	panel = _panel;
}

void Button::operateKeyboardEvents(KEY_EVENT_RECORD ker)
{

}

void Button::operateMouseEvents(MOUSE_EVENT_RECORD ker)
{
	switch (ker.dwEventFlags)
	{
	case 0:
		if (ker.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			onPressed();
		}
		break;
	default:
		break;
	}
	/*cout << "mouseEvent" << endl;*/
}

void Button::onPressed()
{
	mouseListener->mousePressed(getParentControl(), locationX, locationY, false);
}

Button::~Button()
{
}
