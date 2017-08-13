#include "../include/labeledinput.h"

LabeledInputWidget::LabeledInputWidget(std::string label_text, Wt::WContainerWidget *container):Wt::WContainerWidget(container) {
	label = new Wt::WLabel(label_text, this);
    lineedit = new Wt::WLineEdit(this);
}
