#ifndef WELCOME_H
#define WELCOME_H

#include <Wt/WContainerWidget>
#include <Wt/WLabel>

#include "page.h"

class WelcomeWidget : public PageWidget {
private:
public:
    Wt::WLabel *label;

    WelcomeWidget(Wt::WContainerWidget *container);

    void update(std::string username);
};

#endif /* WELCOME_H */
