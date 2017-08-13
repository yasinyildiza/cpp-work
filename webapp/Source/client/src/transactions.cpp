#include "../include/transactions.h"

TransactionsWidget::TransactionsWidget(Wt::WContainerWidget *container):TablePageWidget("Transactions", container) {
}

void TransactionsWidget::add_row(std::string stockcode, std::string quantity, std::string datetime, std::string action, std::string status) {
	table->elementAt(row_counter, 0)->addWidget(new Wt::WText(stockcode));
	table->elementAt(row_counter, 1)->addWidget(new Wt::WText(quantity));
	table->elementAt(row_counter, 2)->addWidget(new Wt::WText(datetime));
	table->elementAt(row_counter, 3)->addWidget(new Wt::WText(action));
	table->elementAt(row_counter++, 4)->addWidget(new Wt::WText(status));
}

void TransactionsWidget::add_header() {
    add_row("Stock Code", "Quantity", "Datetime", "Action", "Status");
 }
 