#include "NumericBox.h"

NumericBox::NumericBox(int width, int _min, int _max) : Panel(2, width)
{
	max = _max;
	min = _min;
	class PlusButtonML : public MouseListener {
	public:
		void mousePressed(IControl * control, int x, int y, bool isLeft)
		{
			NumericBox * mb = (NumericBox *)control;
			if (mb->getCount() + 1 <= mb->getMax())
			{
				mb->incCount();
				mb->countText->setText(to_string(mb->getCount()));
				mb->countText->draw();
			}
		}
	};

	class MinusButtonML : public MouseListener {
	public:
		void mousePressed(IControl * control, int x, int y, bool isLeft)
		{
			NumericBox * mb = (NumericBox *)control;
			if (mb->getCount() - 1 >= mb->getMin())
			{
				mb->decCount();
				mb->countText->setText(to_string(mb->getCount()));
				mb->countText->draw();
			}
		}
	};
	PlusButtonML * plusButtonML = new PlusButtonML();
	MinusButtonML * minusButtonML = new MinusButtonML();
	plusButton = new Button(3);
	plusButton->setText(" + ");
	plusButton->addMouseListener(plusButtonML);
	plusButton->setBorderType(BorderType::Single);
	minusButton = new Button(3);
	minusButton->setText(" - ");
	minusButton->addMouseListener(minusButtonML);
	minusButton->setBorderType(BorderType::Single);
	countText = new Label(width - 10);
	countText->setText(to_string(getCount()));
	countText->setBorderType(BorderType::None);

	AddControl(minusButton, 0, 0);
	AddControl(countText, 6, 0);
	AddControl(plusButton, width - 3, 0);

	
}

int NumericBox::getCount()
{
	return count;
}

void NumericBox::incCount()
{
	count++;
}
void NumericBox::decCount()
{
	count--;
}

int NumericBox::getMin()
{
	return min;
}

int NumericBox::getMax()
{
	return max;
}

NumericBox::~NumericBox()
{
}
