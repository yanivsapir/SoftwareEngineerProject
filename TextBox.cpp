#include "TextBox.h"

void drawTextBoxFirstLine(TextBox * textBox);
void drawTextBoxSecondLine(string text, TextBox * textBox);
void drawTextBoxThirdLine(TextBox * textBox);

TextBox::TextBox(int width)
{
	setWidth(width);
	setHeight(3);
}

void TextBox::setText(string value)
{
	text = value;
}

void TextBox::draw() 
{	
	if (isVisible())
	{
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(cursorHandler, &csbi);
		SetConsoleTextAttribute(cursorHandler, static_cast<int>(foregroundColor) | static_cast<int>(backgroundColor));
		COORD coord = getConsoleCursorCoordinates();
		if (this->getBorderType() != BorderType::None)
			drawTextBoxFirstLine(this);
		else
		{
			cout << endl;
		}
		drawTextBoxSecondLine(text, this);
		if (this->getBorderType() != BorderType::None)
			drawTextBoxThirdLine(this);
		else
		{
			cout << endl;
		}
		SetConsoleCursorPosition(cursorHandler, coord);
		SetConsoleTextAttribute(cursorHandler, csbi.wAttributes);
	}
}

void drawTextBoxFirstLine(TextBox * textBox)
{
	BorderSignContainer borderSignContainer = textBox->getBorderSigns()[textBox->getBorderType()];
	SetConsoleCursorPosition(textBox->getCursorHandler(), { textBox->getLocationX(), textBox->getLocationY() });
	cout << borderSignContainer.topLeftCorner;
	for (int i = 0; i < textBox->getWidth(); i++) {
		cout << borderSignContainer.horizontalLine;
	}
	cout << borderSignContainer.topRightCorner;
}

void drawTextBoxSecondLine(string text, TextBox * textBox)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(textBox->getCursorHandler(), &csbi);
	SetConsoleTextAttribute(textBox->getCursorHandler(), static_cast<int>(textBox->GetForeground()) | static_cast<int>(textBox->GetBackground()));
	SetConsoleCursorPosition(textBox->getCursorHandler(), { textBox->getLocationX(), textBox->getLocationY() + 1 });
	BorderSignContainer borderSignContainer = textBox->getBorderSigns()[textBox->getBorderType()];
	if (textBox->getBorderType() != BorderType::None)
	{
		cout << borderSignContainer.verticalLine;
	}
	cout << text;
	for (int i = 0; i < textBox->getWidth() - text.length(); i++) {
		cout << ' ';
	}
	if (textBox->getBorderType() != BorderType::None)
	{
		cout << borderSignContainer.verticalLine << endl;
	}
	SetConsoleTextAttribute(textBox->getCursorHandler(), csbi.wAttributes);
}

void drawTextBoxThirdLine(TextBox * textBox)
{
	SetConsoleCursorPosition(textBox->getCursorHandler(), { textBox->getLocationX(), textBox->getLocationY() + 2 });
	BorderSignContainer borderSignContainer = textBox->getBorderSigns()[textBox->getBorderType()];
	cout << borderSignContainer.bottomLeftCorner;
	for (int i = 0; i < textBox->getWidth(); i++) {
		cout << borderSignContainer.horizontalLine;
	}
	cout << borderSignContainer.bottomRightCorner;

}

TextBox::~TextBox()
{

}

void TextBox::operateKeyboardEvents(KEY_EVENT_RECORD ker)
{
	if (ker.bKeyDown)
	{
		COORD coord = getConsoleCursorCoordinates();
		if (ker.wVirtualKeyCode == 13)
		{
			coord = getConsoleCursorCoordinates();
			SetConsoleCursorPosition(cursorHandler, { locationX + 1, locationY + 4 });
			for (int i = 0; i < width; i++)
				cout << " ";
			cout << endl;
			SetConsoleCursorPosition(cursorHandler, { locationX + 1, locationY + 4 });
			cout << getText();
			SetConsoleCursorPosition(cursorHandler, coord);
		}
		else if (ker.wVirtualKeyCode == '\b' && coord.X >= locationX + 1)
		{
			CONSOLE_SCREEN_BUFFER_INFO csbi;
			GetConsoleScreenBufferInfo(cursorHandler, &csbi);
			SetConsoleTextAttribute(cursorHandler, static_cast<int>(foregroundColor) | static_cast<int>(backgroundColor));
			if (coord.X - 1 - locationX == text.length())
			{	
				printf("%c", ker.uChar);
				char print = coord.X == locationX + 1 ? borderSigns[borderType].verticalLine : ' ';
				cout << print;
				text = text.substr(0, text.size() - 1);
				coord = { coord.X == locationX + 1 ? coord.X : coord.X - 1, coord.Y };
				SetConsoleCursorPosition(cursorHandler, coord);
			}
			else
			{
				printf("%c", ker.uChar);
				char print = coord.X == locationX + 1 ? borderSigns[borderType].verticalLine : ' ';
				cout << print;
				text = text.substr(0, coord.X - 2 - locationX) + text.substr(coord.X - 1 - locationX, text.length() - 1);
				drawTextBoxSecondLine(text, this);
				coord = { coord.X == locationX + 1 ? coord.X : coord.X - 1, coord.Y };
				SetConsoleCursorPosition(cursorHandler, coord);
			}
			SetConsoleTextAttribute(cursorHandler, csbi.wAttributes);
		}

		else if (ker.wVirtualKeyCode == VK_DELETE && coord.X <= locationX + text.length())
		{
			CONSOLE_SCREEN_BUFFER_INFO csbi;
			GetConsoleScreenBufferInfo(cursorHandler, &csbi);
			SetConsoleTextAttribute(cursorHandler, static_cast<int>(foregroundColor) | static_cast<int>(backgroundColor));
			if (coord.X == locationX + 1 && text.length() != 0)
			{
				text = text.substr(1, text.length());
				for (int i = 0; i < width; i++)
					cout << " ";
				SetConsoleCursorPosition(cursorHandler, { locationX + 1 , locationY + 1 });
				cout << text;
				SetConsoleCursorPosition(cursorHandler, { locationX + 1 , locationY + 1 });
			}
			else
			{
				text = text.substr(0, coord.X - 1 - locationX) + text.substr(coord.X - locationX, text.length() - 1);
				drawTextBoxSecondLine(text, this);
				SetConsoleCursorPosition(cursorHandler, { coord.X, locationY + 1});
			}
			SetConsoleTextAttribute(cursorHandler, csbi.wAttributes);
		}
		
		else if (ker.wVirtualKeyCode == VK_LEFT)
		{
			if (coord.X > locationX + 1)
			{
				COORD c = { coord.X - 1, coord.Y };
				SetConsoleCursorPosition(cursorHandler, c);
			}
		}

		else if (ker.wVirtualKeyCode == VK_RIGHT)
		{
			if (coord.X < locationX + text.length() + 1)
			{
				COORD c = { coord.X + 1, coord.Y };
				SetConsoleCursorPosition(cursorHandler, c);
			}
		}

		else if (coord.X > locationX && coord.X <= locationX + width)
		{
			if (coord.X - locationX > text.length() && ker.wVirtualKeyCode != VK_DELETE)
			{
				text += ker.uChar.UnicodeChar;
				CONSOLE_SCREEN_BUFFER_INFO csbi;
				GetConsoleScreenBufferInfo(cursorHandler, &csbi);
				SetConsoleTextAttribute(cursorHandler, static_cast<int>(foregroundColor) | static_cast<int>(backgroundColor));
				printf("%c", ker.uChar);
				SetConsoleTextAttribute(cursorHandler, csbi.wAttributes);
			}
			else if (text.length() != width && ker.wVirtualKeyCode != VK_DELETE)
			{
				string end = text.substr(coord.X - 1 - locationX, text.length() - 1);
				text[coord.X - locationX - 1] = ker.uChar.UnicodeChar;
				text = text.substr(0, coord.X - locationX);
				text += end;
				text += ker.uChar.UnicodeChar;
				CONSOLE_SCREEN_BUFFER_INFO csbi;
				GetConsoleScreenBufferInfo(cursorHandler, &csbi);
				SetConsoleTextAttribute(cursorHandler, static_cast<int>(foregroundColor) | static_cast<int>(backgroundColor));
				drawTextBoxSecondLine(text, this);
				SetConsoleCursorPosition(cursorHandler, { coord.X + 1, coord.Y });
				SetConsoleTextAttribute(cursorHandler, csbi.wAttributes);
			}
		}
	}
}

void TextBox::operateMouseEvents(MOUSE_EVENT_RECORD ker)
{
	switch (ker.dwEventFlags)
	{
		case 0:	
			if (ker.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
			{
				if ((ker.dwMousePosition.Y == locationY + 1) && (ker.dwMousePosition.X - 1 >= locationX && ker.dwMousePosition.X <= locationX + text.length() + 1))
				{
					coord = getMousePositionCoordinates(ker);
					SetConsoleCursorPosition(cursorHandler, coord);
				}
			}
			break;
		default:
			break;
	}
}

string TextBox::getText()
{
	return text;
}
