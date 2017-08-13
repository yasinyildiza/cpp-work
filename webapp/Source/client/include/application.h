#ifndef APPLICATION_H
#define APPLICATION_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <map>
#include <exception>

#include <Wt/WApplication>
#include <Wt/WBreak>
#include <Wt/WContainerWidget>
#include <Wt/WLabel>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WText>
#include <Wt/WMessageBox>
#include <Wt/Http/Client>
#include <Wt/Json/Object>
#include <Wt/Json/Array>
#include <Wt/Json/Value>
#include <Wt/Json/Parser>
#include <Wt/WOverlayLoadingIndicator>

#include "page.h"
#include "menu.h"
#include "signin.h"
#include "welcome.h"
#include "quote.h"
#include "transactions.h"
#include "portfoliolist.h"
#include "action.h"

class StockExchangeApplication : public Wt::WApplication {
private:
    PageWidget *active_widget;

    std::string username;
    std::string password;
    bool signedin;

    MenuWidget *menu_widget;
    SigninWidget *signin_widget;
    WelcomeWidget *welcome_widget;
    QuoteWidget *quote_widget;
    TransactionsWidget *transactions_widget;
    PortfoliolistWidget *portfoliolist_widget;
    ActionWidget *buy_widget;
    ActionWidget *sell_widget;

    Wt::WOverlayLoadingIndicator *loading_indicator;

    void set_active_widget(PageWidget *widget);

    bool is_signedin();

    void activate_signin();
    void activate_welcome();
    void activate_quote();
    void activate_transactions();
    void activate_portfoliolist();
    void activate_buy();
    void activate_sell();

    void show_alert(std::string category, std::string message);
    void show_error(std::string message);
    void show_warning(std::string message);
    void show_info(std::string message);

    std::string init_url(std::string path);

    Wt::Http::Client *create_client();
    void send(bool flag);
    void send_get(Wt::Http::Client *client, std::string url);
    void send_post(Wt::Http::Client *client, std::string url);
    void send_put(Wt::Http::Client *client, std::string url);
    void send_deleteRequest(Wt::Http::Client *client, std::string url);
    Wt::Json::Value recv(boost::system::error_code err, const Wt::Http::Message& response);

    void send_signin();
    void handle_signin(boost::system::error_code err, const Wt::Http::Message& response);

    void send_signup();
    void handle_signup(boost::system::error_code err, const Wt::Http::Message& response);

    void send_quote();
    void handle_quote(boost::system::error_code err, const Wt::Http::Message& response);

    void send_transactions();
    void handle_transactions(boost::system::error_code err, const Wt::Http::Message& response);

    void send_portfoliolist();
    void handle_portfoliolist(boost::system::error_code err, const Wt::Http::Message& response);

    bool validate_action_parameters(std::string stockcode, std::string quantity, std::string price);
    void send_action(std::string action_path, ActionWidget *widget);
    void handle_action(boost::system::error_code err, const Wt::Http::Message& response);
    void send_buy();
    void send_sell();

public:
    StockExchangeApplication(const Wt::WEnvironment& env);

};

#endif /* APPLICATION_H */
