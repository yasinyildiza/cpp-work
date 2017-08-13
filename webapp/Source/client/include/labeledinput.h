#ifndef LABELEDINPUT_H
#define LABELEDINPUT_H

#include <string>

#include <Wt/WApplication>
#include <Wt/WContainerWidget>
#include <Wt/WBreak>
#include <Wt/WLabel>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>

class LabeledInputWidget : public Wt::WContainerWidget {
private:
public:
    Wt::WLabel *label;
    Wt::WLineEdit *lineedit;
    LabeledInputWidget(std::string label_text, Wt::WContainerWidget *container);
};

#endif /* LABELEDINPUT_H */
