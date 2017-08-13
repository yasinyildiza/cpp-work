#ifndef MENU_H
#define MENU_H

#include <Wt/WContainerWidget>
#include <Wt/WBreak>
#include <Wt/WPushButton>

#include "page.h"

class MenuWidget : public PageWidget {
private:
public:
    Wt::WPushButton *quote_button;
    Wt::WPushButton *transactions_button;
    Wt::WPushButton *portfoliolist_button;
    Wt::WPushButton *buy_button;
    Wt::WPushButton *sell_button;
    Wt::WPushButton *signout_button;
    
    MenuWidget(Wt::WContainerWidget *container);
};

#endif /* MENU_H */
