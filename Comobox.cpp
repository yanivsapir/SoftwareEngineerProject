#include "Comobox.h"
#include <iostream>

using namespace std;

Comobox::Comobox(int height, int width, vector<string> _entries) : Panel(height, width)
{
	entries = _entries;
	setBorderType(BorderType::None);
	setWidth(width);
	chosenValuePanel = new Panel(3, width);
	chosenValuePanel->setBorderType(BorderType::None);
	chosenValueLabel = new Label(width - 3);
	chosenValueLabel->setBorderType(BorderType::Double);
	chosenValueLabel->setText("choose one option");
	openCloseChoisesPanelButton = new Button(1);
	openCloseChoisesPanelButton->setBorderType(BorderType::Double);
	openCloseChoisesPanelButton->addMouseListener(getOpenCloseButtonMouseListener());
	openCloseChoisesPanelButton->setText("+");
	
	
	choisesPanel = new Panel(height - 2, width);
	Button * btn;
	int i = 0;
	MouseListener * chooseOptionButtonMouseListener = getChooseOptionButtonMouseListener();
	for (string entry : _entries)
	{
		btn = new Button(width - 2);
		btn->setText(entry);
		btn->addMouseListener(chooseOptionButtonMouseListener);
		choisesPanel->AddControl(btn, 1, (i++ * 3) + 1);
	}
	chosenOption = (Button *)choisesPanel->getControllers()[0];
	chosenValuePanel->AddControl(chosenValueLabel, 0, 0);
	chosenValuePanel->AddControl(openCloseChoisesPanelButton, width -1, 0);
	
	choisesPanel->setVisible(false);
	AddControl(chosenValuePanel, 0, 0);
	AddControl(choisesPanel, 0, 3);
}

MouseListener * Comobox::getOpenCloseButtonMouseListener()
{
	class openCloseButtonMouseListener : public MouseListener {
	public:
		void mousePressed(IControl * control, int x, int y, bool isLeft)
		{
			Panel * chosenValuePanel = (Panel *)control;
			Comobox * cmbx = (Comobox *)chosenValuePanel->getParentControl();
			Panel * choisesPanel = cmbx->getChoisesPanel();
			bool visible = cmbx->getChoisesPanel()->isVisible();
			choisesPanel->setVisible(!visible);
			cmbx->getChosenOption()->SetBackground(BackgroundColor::White);
			cmbx->getChosenOption()->SetForeground(ForegroundColor::Black);
			cmbx->getChosenOption()->draw();
			SetConsoleCursorPosition(cmbx->getCursorHandler(), { cmbx->getChosenOption()->getLocationX(), cmbx->getChosenOption()->getLocationY() });
		}
	};
	return new openCloseButtonMouseListener();
}

MouseListener * Comobox::getChooseOptionButtonMouseListener()
{
	class ChooseOptionButtonMouseListener : public MouseListener {
	public:
		void mousePressed(IControl * control, int x, int y, bool isLeft)
		{
			Panel * choisesPanel = (Panel *)control;
			COORD coord = choisesPanel->getConsoleCursorCoordinates();
			Comobox * comobox = (Comobox *)choisesPanel->getParentControl();
			Button * button = (Button *)choisesPanel->findRelevantController({ static_cast<short>(x) , static_cast<short>(y) });
			if (button->isVisible())
			{
				comobox->setChosenOption(button);
				comobox->getChosenValueLabel()->setText(button->getText());
				comobox->getChosenValueLabel()->draw();
				comobox->getChoisesPanel()->setVisible(false);
				button->draw();
				SetConsoleCursorPosition(choisesPanel->getCursorHandler(), coord);
			}
		}
	};
	return new ChooseOptionButtonMouseListener();
}

Panel * Comobox::getChoisesPanel()
{
	return choisesPanel;
}

Label * Comobox::getChosenValueLabel()
{
	return chosenValueLabel;
}

Comobox::~Comobox()
{

}

void Comobox::operateKeyboardEvents(KEY_EVENT_RECORD ker)
{
	if (ker.bKeyDown)
	{
		Button * button;
		COORD cursorCoord = getConsoleCursorCoordinates();
		if (ker.wVirtualKeyCode == VK_UP || ker.wVirtualKeyCode == VK_DOWN)
		{
			short extension = ker.wVirtualKeyCode == VK_UP ? -3 : +3;
			short desiredMove = cursorCoord.Y + extension;
			bool legalMove =  desiredMove > choisesPanel->getLocationY() && desiredMove < choisesPanel->getLocationY() + choisesPanel->getHeight() - 1;
			if (legalMove)
			{
				button = (Button *)findRelevantController({ cursorCoord.X, cursorCoord.Y });
				button->SetBackground(backgroundColor);
				button->SetForeground(foregroundColor);
				button->draw();
				button = (Button *)choisesPanel->findRelevantController({ cursorCoord.X, cursorCoord.Y + extension });
				button->SetBackground(BackgroundColor::White);
				button->SetForeground(ForegroundColor::Black);
				button->draw();
				SetConsoleCursorPosition(cursorHandler, { cursorCoord.X, cursorCoord.Y + extension });
			}
		}
		else if (ker.wVirtualKeyCode == VK_RETURN || ker.wVirtualKeyCode == VK_SPACE)
		{
			button = (Button *)choisesPanel->findRelevantController({ cursorCoord.X, cursorCoord.Y });
			button->SetBackground(backgroundColor);
			button->SetForeground(foregroundColor);
			button->draw();
			button->onPressed();
			SetConsoleCursorPosition(cursorHandler, { cursorCoord.X, cursorCoord.Y });
		}
	}
}

Button * Comobox::getChosenOption()
{
	return chosenOption;
}

void Comobox::setChosenOption(Button * _chosenOption)
{
	chosenOption = _chosenOption;
}

void Comobox::operateMouseEvents(MOUSE_EVENT_RECORD mer)
{
	if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
	{
		chosenOption->SetBackground(backgroundColor);
		chosenOption->SetForeground(foregroundColor);
		coord = getMousePositionCoordinates(mer);
	}
}

void Comobox::setVisible(bool isVisible)
{
	Panel::setVisible(isVisible);
	choisesPanel->setVisible(false);
}