#include "RadioBox.h"

RadioBox::RadioBox(int height, int width, vector<string> strings) : CheckList(height, width, strings)
{
	MouseListener * ml = getButtonMouseListener();
	for (Button * button : buttons)
		button->addMouseListener(ml);
}

MouseListener * RadioBox::getButtonMouseListener()
{
	class RadioBoxButtonMouseListener : public MouseListener {
	public:
		void mousePressed(IControl * control, int x, int y, bool isLeft)
		{
			Panel * panel = (Panel *)control;
			RadioBox * rb = (RadioBox *)panel->getParentControl();
			Button * buttonToCheck = (Button *)panel->findRelevantController({ static_cast<short>(x) , static_cast<short>(y) });
			Button * buttonToUncheck = rb->GetButtonsByIndex()[rb->GetSelectedIndex()];
			buttonToUncheck->setText("[ ]");
			buttonToUncheck->draw();
			rb->SetSelectedIndex(rb->getButtonIndecies()[buttonToCheck->getLocationY() - rb->getLocationY()]);
			buttonToCheck->setText("[X]");
			panel->SetBackground(BackgroundColor::White);
			panel->SetForeground(ForegroundColor::Black);
			panel->draw();
		}
	};
	return new RadioBoxButtonMouseListener();
}

size_t RadioBox::GetSelectedIndex()
{
	return selectedIndex;
}

void RadioBox::SetSelectedIndex(size_t index)
{
	resultLabel->setText("[ " + to_string(index) + " ]");
	resultLabel->draw();
	selectedIndex = index;
}

RadioBox::~RadioBox()
{
}
