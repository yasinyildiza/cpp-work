#ifndef ACTION_H
#define ACTION_H

#include <string>

#include <Wt/WApplication>
#include <Wt/WContainerWidget>
#include <Wt/WBreak>
#include <Wt/WLabel>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>

#include "labeledinput.h"
#include "page.h"

class ActionWidget : public PageWidget {
private:
public:
	LabeledInputWidget *stockcode;
	LabeledInputWidget *quantity;
	LabeledInputWidget *price;
    Wt::WPushButton *button_submit;

    ActionWidget(std::string title_label, Wt::WContainerWidget *container);
};

#endif /* ACTION_H */
