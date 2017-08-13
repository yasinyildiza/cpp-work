#include "../include/action.h"

ActionWidget::ActionWidget(std::string title_label, Wt::WContainerWidget *container):PageWidget(title_label, container) {
	stockcode =  new LabeledInputWidget("Stock Code: ", this);
	quantity =  new LabeledInputWidget("Quantity: ", this);
	price =  new LabeledInputWidget("Price: ", this);
    button_submit = new Wt::WPushButton("Submit", this);

    stockcode->lineedit->setFocus();
}
