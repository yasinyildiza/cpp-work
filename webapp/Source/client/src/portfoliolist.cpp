#include "../include/portfoliolist.h"

PortfoliolistWidget::PortfoliolistWidget(Wt::WContainerWidget *container):TablePageWidget("Portfolio List", container) {
}

void PortfoliolistWidget::add_row(std::string stockcode, std::string quantity, std::string totalcost) {
	table->elementAt(row_counter, 0)->addWidget(new Wt::WText(stockcode));
	table->elementAt(row_counter, 1)->addWidget(new Wt::WText(quantity));
	table->elementAt(row_counter++, 2)->addWidget(new Wt::WText(totalcost));
}

void PortfoliolistWidget::add_header() {
	add_row("Stock Code", "Quantity", "Total Cost");
}
