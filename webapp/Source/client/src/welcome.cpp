#include "../include/welcome.h"

WelcomeWidget::WelcomeWidget(Wt::WContainerWidget *container):PageWidget("", container) {
    label = new Wt::WLabel("", this);
}

void WelcomeWidget::update(std::string username) {
	std::string text = "Welcome, ";
	text.append(username);
	text.append("!");
	label->setText(text);
}
