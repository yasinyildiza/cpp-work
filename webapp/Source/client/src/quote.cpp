#include "../include/quote.h"

QuoteWidget::QuoteWidget(Wt::WContainerWidget *container):TablePageWidget("Quote", container) {
    stockcode = new LabeledInputWidget("Stock Code: ", this);
    button_submit = new Wt::WPushButton("Submit", this);
    addWidget(new Wt::WBreak());
}

void QuoteWidget::add_row(std::string stockcode, std::string lastsaleprice) {
    table->elementAt(row_counter, 0)->addWidget(new Wt::WText(stockcode));
    table->elementAt(row_counter++, 1)->addWidget(new Wt::WText(lastsaleprice));
}

void QuoteWidget::add_header() {
    add_row("Stock Code", "Last Sale Price");
 }
 