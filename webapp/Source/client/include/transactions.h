#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H

#include <string>

#include <Wt/WApplication>
#include <Wt/WContainerWidget>
#include <Wt/WBreak>
#include <Wt/WLabel>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WTable>

#include "tablepage.h"

class TransactionsWidget : public TablePageWidget {
private:
public:
    TransactionsWidget(Wt::WContainerWidget *container);

    void add_row(std::string stockcode, std::string quantity, std::string datetime, std::string action, std::string status);
    void add_header();
};

#endif /* TRANSACTIONS_H */
