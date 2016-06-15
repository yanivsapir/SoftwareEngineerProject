#include "MessageBoxs.h"

MessageBoxs::MessageBoxs(int height, int width) : Panel(height, width)
{

	Label * titleLabel = new Label(width);
	titleLabel->setText("here title");
	titleLabel->setBorderType(BorderType::Double);
	Label * textLabel = new Label(width - 2);
	textLabel->setText("here text");
	textLabel->setBorderType(BorderType::Single);

	class RejectApproveMouseListener : public MouseListener {
	public:
		void mousePressed(IControl * control, int x, int y, bool isLeft)
		{
			MessageBoxs * mb = (MessageBoxs *)control;
			Button * button = (Button *)mb->findRelevantController({ static_cast<short>(x) , static_cast<short>(y) });
			mb->setValue(button->getText());
			mb->setVisible(false);
		}
	};

	RejectApproveMouseListener * raml = new RejectApproveMouseListener();
	Button * OKButton = new Button((width / 2) - 2);
	OKButton->setText("OK");
	OKButton->addMouseListener(raml);
	Button * cancelButton = new Button((width / 2) - 2);
	cancelButton->setText("Cancel");
	cancelButton->addMouseListener(raml);

	AddControl(titleLabel, 0, 0);
	AddControl(textLabel, 1, 3);
	AddControl(OKButton, 1, height - 3);
	AddControl(cancelButton, (width / 2) + 1, height - 3);
}

void MessageBoxs::SetText(string _text)
{

}

void MessageBoxs::SetTitle(string _title)
{

}

string MessageBoxs::getValue()
{
	return value;
}

void MessageBoxs::setValue(string _value)
{
	value = _value;
}

MessageBoxs::~MessageBoxs()
{
}
