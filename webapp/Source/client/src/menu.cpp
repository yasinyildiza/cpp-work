#include "../include/menu.h"

MenuWidget::MenuWidget(Wt::WContainerWidget *container):PageWidget("StockExchange", container) {
    quote_button = new Wt::WPushButton("Quote", this);
    transactions_button = new Wt::WPushButton("Transactions", this);
    portfoliolist_button = new Wt::WPushButton("Portfolio List", this);
    buy_button = new Wt::WPushButton("Buy", this);
    sell_button = new Wt::WPushButton("Sell", this);
    signout_button = new Wt::WPushButton("Sign out", this);
}
