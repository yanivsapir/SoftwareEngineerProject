#include "CheckList.h"
#include <algorithm>

string getVectorText(vector<size_t> indecies);
CheckList::CheckList(int height, int width, vector<string> strings) : Panel(height, width)
{
	int distanceBetweenButtonAndLable = 4;
	setHeight(height > ((strings.size() + 1) * 3) - 1 ? height : ((strings.size() + 1) * 3) - 1);
	entries = strings;
	Button * button = NULL;
	Label * label;
	Label * spaceLabel;
	Panel * panel;
	MouseListener * ml = getButtonMouseListener();
	int i = 0;
	for (string str : strings)
	{
		panel = new Panel(3,width);
		panel->setBorderType(BorderType::None);
		spaceLabel = new Label(distanceBetweenButtonAndLable);
		spaceLabel->setBorderType(BorderType::None);
		label = new Label(width - distanceBetweenButtonAndLable);
		label->setText(str);
		label->setBorderType(BorderType::None);
		button = new Button(3);
		button->setText("[ ]");
		button->setBorderType(BorderType::None);
		button->addMouseListener(ml);
		buttonsByIndex[i]= (button);
		AddControl(panel , 1, i * 3);
		panel->AddControl(button, 0, 0);
		panel->AddControl(spaceLabel, distanceBetweenButtonAndLable - 1, 0);
		panel->AddControl(label, distanceBetweenButtonAndLable, 0);
		buttons.push_back(button);
		buttonIndecies[button->getLocationY()] = i++;
	}
	resultLabel = new Label(width);
	resultLabel->setText("[ ]");
	resultLabel->SetBackground(backgroundColor);
	resultLabel->SetForeground(foregroundColor);
	this->AddControl(resultLabel, 0, this->height - 2);
}

vector<size_t> CheckList::GetSelectedIndices()
{
	return selectedIndices;
}

void CheckList::SelectIndex(size_t index)
{
	selectedIndices.push_back(index);
	sort(selectedIndices.begin(), selectedIndices.end());
}

void CheckList::DeselectIndex(size_t index)
{
	std::vector<size_t>::iterator it;
	it = find(selectedIndices.begin(), selectedIndices.end(), index);
	selectedIndices.erase(it);
}

vector<string> CheckList::getEntries()
{
	return entries;
}

map<int, int> CheckList::getButtonIndecies()
{
	return buttonIndecies;
}

Label * CheckList::getResultLabel()
{
	return resultLabel;
}

MouseListener * CheckList::getButtonMouseListener()
{
	class CheckListButtonMouseListener : public MouseListener {
	public:
		void mousePressed(IControl * control, int x, int y, bool isLeft)
		{
			Panel * panel = (Panel *)control;
			CheckList * cl = (CheckList *)panel->getParentControl();
			Button * button = (Button *)panel->findRelevantController({ static_cast<short>(x) , static_cast<short>(y) });
			string text = button->getText().compare("[X]") == 0 ? "[ ]" : "[X]";
			if (button->getText().compare("[X]") == 0)
			{
				cl->DeselectIndex(cl->getButtonIndecies()[button->getLocationY() - cl->getLocationY()]);
			}	
			else
			{
				cl->SelectIndex(cl->getButtonIndecies()[button->getLocationY() - cl->getLocationY()]);
			}
			cl->getResultLabel()->setText(getVectorText(cl->GetSelectedIndices()));
			cl->getResultLabel()->draw();
			button->setText(text);
			panel->SetBackground(BackgroundColor::White);
			panel->SetForeground(ForegroundColor::Black);
			panel->draw();
		}
	};
	return new CheckListButtonMouseListener();
}

void CheckList::operateKeyboardEvents(KEY_EVENT_RECORD ker)
{
	if (ker.bKeyDown)
	{
		Panel * panel;
		COORD cursorCoord = getConsoleCursorCoordinates();
		if (ker.wVirtualKeyCode == VK_UP || ker.wVirtualKeyCode == VK_DOWN)
		{
			short extension = ker.wVirtualKeyCode == VK_UP ? -3 : +3;
			if (buttonIndecies.find(cursorCoord.Y - locationY - 1 + extension) != buttonIndecies.end())
			{
				panel = (Panel *)findRelevantController({ cursorCoord.X, cursorCoord.Y });
				panel->SetBackground(BackgroundColor::White);
				panel->SetForeground(ForegroundColor::Black);
				panel->draw();
				SetConsoleCursorPosition(cursorHandler, { cursorCoord.X, cursorCoord.Y + extension });
				panel->SetBackground(backgroundColor);
				panel->SetForeground(foregroundColor);
				panel->draw();
				panel = (Panel *)findRelevantController({ cursorCoord.X, cursorCoord.Y + extension });
				panel->SetBackground(BackgroundColor::White);
				panel->SetForeground(ForegroundColor::Black);
				panel->draw();
			}
		}
		else if (ker.wVirtualKeyCode == VK_RETURN || ker.wVirtualKeyCode == VK_SPACE)
		{
			panel = (Panel *)findRelevantController({ cursorCoord.X, cursorCoord.Y });
			Button * button = (Button *)panel->findRelevantController({ cursorCoord.X, cursorCoord.Y });
			button->onPressed();
			SetConsoleCursorPosition(cursorHandler, { cursorCoord.X, cursorCoord.Y });
		}
	}
}

void CheckList::operateMouseEvents(MOUSE_EVENT_RECORD mer)
{
	Panel * panel;
	if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
	{
		COORD cursorCoord = getConsoleCursorCoordinates();
		panel = (Panel *)findRelevantController({ cursorCoord.X, cursorCoord.Y });
		if (panel != NULL)
		{
			panel->SetBackground(backgroundColor);
			panel->SetForeground(foregroundColor);
			panel->draw();
		}
		coord = getMousePositionCoordinates(mer);
		SetConsoleCursorPosition(cursorHandler, coord);
	}
}

map<size_t, Button *> CheckList::GetButtonsByIndex()
{
	return buttonsByIndex;
}

string getVectorText(vector<size_t> indecies)
{
	string stringToReturn;
	int i = 0;
	for (size_t index : indecies)
	{
		stringToReturn = stringToReturn + (i++ == 0 ? to_string(index) : ", " + to_string(index));
	}
	return "[ " + stringToReturn + " ]";
}

CheckList::~CheckList()
{
}
