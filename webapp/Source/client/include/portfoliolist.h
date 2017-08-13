#ifndef PORTFOLIOLIST_H
#define PORTFOLIOLIST_H

#include <string>

#include <Wt/WApplication>
#include <Wt/WContainerWidget>
#include <Wt/WBreak>
#include <Wt/WLabel>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WTable>

#include "tablepage.h"

class PortfoliolistWidget : public TablePageWidget {
private:
public:
    PortfoliolistWidget(Wt::WContainerWidget *container);

    void add_row(std::string stockcode, std::string quantity, std::string totalcost);
    void add_header();
};

#endif /* PORTFOLIOLIST_H */
