#ifndef QUOTE_H
#define QUOTE_H

#include <string>

#include <Wt/WApplication>
#include <Wt/WContainerWidget>
#include <Wt/WBreak>
#include <Wt/WLabel>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WTable>

#include "labeledinput.h"
#include "tablepage.h"

class QuoteWidget : public TablePageWidget {
private:
public:
	LabeledInputWidget *stockcode;
    Wt::WPushButton *button_submit;

    QuoteWidget(Wt::WContainerWidget *container);

    void add_row(std::string stockcode, std::string lastsaleprice);
    void add_header();
};

#endif /* QUOTE_H */
