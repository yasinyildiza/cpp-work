#include "../include/application.h"

StockExchangeApplication::StockExchangeApplication(const Wt::WEnvironment& env):Wt::WApplication(env) {
    signedin = false;
    setTitle("StockExchange");

    loading_indicator = new Wt::WOverlayLoadingIndicator();
    loading_indicator->setMessage("Please wait...");
    Wt::WApplication::instance()->setLoadingIndicator(loading_indicator);
    loading_indicator->hide();

    active_widget = NULL;

    menu_widget = new MenuWidget(root());
    menu_widget->quote_button->clicked().connect(this, &StockExchangeApplication::activate_quote);
    menu_widget->transactions_button->clicked().connect(this, &StockExchangeApplication::activate_transactions);
    menu_widget->portfoliolist_button->clicked().connect(this, &StockExchangeApplication::activate_portfoliolist);
    menu_widget->buy_button->clicked().connect(this, &StockExchangeApplication::activate_buy);
    menu_widget->sell_button->clicked().connect(this, &StockExchangeApplication::activate_sell);
    menu_widget->signout_button->clicked().connect(this, &StockExchangeApplication::activate_signin);

    signin_widget = new SigninWidget(root());
    signin_widget->button_signin->clicked().connect(this, &StockExchangeApplication::send_signin);
    signin_widget->button_signup->clicked().connect(this, &StockExchangeApplication::send_signup);
    signin_widget->username->lineedit->enterPressed().connect(this, &StockExchangeApplication::send_signin);
    signin_widget->password->lineedit->enterPressed().connect(this, &StockExchangeApplication::send_signin);

    welcome_widget = new WelcomeWidget(root());

    quote_widget = new QuoteWidget(root());
    quote_widget->button_submit->clicked().connect(this, &StockExchangeApplication::send_quote);

    transactions_widget = new TransactionsWidget(root());

    portfoliolist_widget = new PortfoliolistWidget(root());

    buy_widget = new ActionWidget("Buy", root());
    buy_widget->button_submit->clicked().connect(this, &StockExchangeApplication::send_buy);

    sell_widget = new ActionWidget("Sell", root());
    sell_widget->button_submit->clicked().connect(this, &StockExchangeApplication::send_sell);

    set_active_widget(signin_widget);
}

bool StockExchangeApplication::is_signedin() {
    if(signedin) {
        return true;
    }

    show_error("Must sign in first");
    return false;
}

void StockExchangeApplication::set_active_widget(PageWidget *widget) {
    //menu_widget->hide();
    signin_widget->hide();
    welcome_widget->hide();
    quote_widget->hide();
    transactions_widget->hide();
    portfoliolist_widget->hide();
    buy_widget->hide();
    sell_widget->hide();
    menu_widget->signout_button->show();

    active_widget = widget;
    active_widget->show();
}

void StockExchangeApplication::activate_signin() {
    username = "";
    password = "";
    signedin = false;
    welcome_widget->update(username);
    set_active_widget(signin_widget);
    menu_widget->signout_button->hide();
}

void StockExchangeApplication::activate_welcome() {
    if(!is_signedin()) {
        return;
    }
    welcome_widget->update(username);
    set_active_widget(welcome_widget);
}

void StockExchangeApplication::activate_quote() {
    if(!is_signedin()) {
        return;
    }
    set_active_widget(quote_widget);
}

void StockExchangeApplication::activate_transactions() {
    if(!is_signedin()) {
        return;
    }
    set_active_widget(transactions_widget);
    send_transactions();
}

void StockExchangeApplication::activate_portfoliolist() {
    if(!is_signedin()) {
        return;
    }
    set_active_widget(portfoliolist_widget);
    send_portfoliolist();
}

void StockExchangeApplication::activate_buy() {
    if(!is_signedin()) {
        return;
    }
    set_active_widget(buy_widget);
}

void StockExchangeApplication::activate_sell() {
    if(!is_signedin()) {
        return;
    }
    set_active_widget(sell_widget);
}

void StockExchangeApplication::show_alert(std::string category, std::string message) {
    Wt::WMessageBox::show(category, message, Wt::StandardButton::Ok);
    std::string log_text = "";
    log_text.append(category);
    log_text.append("::");
    log_text.append(message);
    Wt::log(log_text);
}

void StockExchangeApplication::show_error(std::string message) {
    show_alert("Error", message);
}

void StockExchangeApplication::show_warning(std::string message) {
    show_alert("Warning", message);
}

void StockExchangeApplication::show_info(std::string message) {
    show_alert("Info", message);
}

std::string StockExchangeApplication::init_url(std::string path) {
    std::string url = "http://localhost:34568/exchange/";
    url.append(path);
    url.append("?username=");
    url.append(username);
    url.append("&password=");
    url.append(password);

    return url;
}

Wt::Http::Client *StockExchangeApplication::create_client() {
    Wt::Http::Client *client = new Wt::Http::Client(this);
    client->setTimeout(15);
    client->setMaximumResponseSize(10 * 1024);
    return client;
}

void StockExchangeApplication::send(bool flag) {
    loading_indicator->show();
    if(flag) {
        Wt::WApplication::instance()->deferRendering();
    } else {
        loading_indicator->hide();
        show_error("An error occured, please try again.");
    }
}

void StockExchangeApplication::send_get(Wt::Http::Client *client, std::string url) {
    send(client->get(url));
}

void StockExchangeApplication::send_post(Wt::Http::Client *client, std::string url) {
    send(client->post(url, Wt::Http::Message()));
}

void StockExchangeApplication::send_put(Wt::Http::Client *client, std::string url) {
    send(client->put(url, Wt::Http::Message()));
}

void StockExchangeApplication::send_deleteRequest(Wt::Http::Client *client, std::string url) {
    send(client->deleteRequest(url, Wt::Http::Message()));
}

Wt::Json::Value StockExchangeApplication::recv(boost::system::error_code err, const Wt::Http::Message& response) {
    loading_indicator->hide();
    Wt::WApplication::instance()->resumeRendering();
    if(!err && response.status() == 200) {
        Wt::log(response.body());

        Wt::Json::Object result;
        Wt::Json::parse(response.body(), result);
        bool success = result.get("success");
        if(success) {
            return result.get("payload");
        }

        Wt::Json::Object error = result.get("error");
        int code = error.get("code");
        std::string message = error.get("message");
        show_error(message.append(" (").append(std::to_string(code)).append(")"));
    } else {
        show_error("An error occured, please try again later.");
    }

    return Wt::Json::Value::Null;
}

void StockExchangeApplication::send_signin() {
    username = signin_widget->username->lineedit->text().narrow();
    password = signin_widget->password->lineedit->text().narrow();

    if(username == "") {
        show_error("username can't be blank");
        return;
    }

    if(password == "") {
        show_error("password can't be blank");
        return;
    }

    Wt::Http::Client *client = create_client();
    client->done().connect(boost::bind(&StockExchangeApplication::handle_signin, this, _1, _2));

    std::string url = init_url("login");
    send_post(client, url);
}

void StockExchangeApplication::handle_signin(boost::system::error_code err, const Wt::Http::Message& response)
{
    Wt::Json::Value p = recv(err, response);
    if(!p.isNull()) {
        signedin = true;
        activate_welcome();
    }
}

void StockExchangeApplication::send_signup() {
    username = signin_widget->username->lineedit->text().narrow();
    password = signin_widget->password->lineedit->text().narrow();

    if(username == "") {
        show_error("username can't be blank");
        return;
    }

    if(password == "") {
        show_error("password can't be blank");
        return;
    }

    Wt::Http::Client *client = create_client();
    client->done().connect(boost::bind(&StockExchangeApplication::handle_signup, this, _1, _2));

    std::string url = init_url("register");
    send_post(client, url);
}

void StockExchangeApplication::handle_signup(boost::system::error_code err, const Wt::Http::Message& response)
{
    Wt::Json::Value p = recv(err, response);
    if(!p.isNull()) {
        signedin = true;
        activate_welcome();
    }
}

void StockExchangeApplication::send_quote() {
    if(!is_signedin()) {
        return;
    }

    quote_widget->reset();

    std::string stockcode = quote_widget->stockcode->lineedit->text().narrow();

    if(stockcode == "") {
        show_error("stockcode can't be blank");
        return;
    }

    Wt::Http::Client *client = create_client();
    client->done().connect(boost::bind(&StockExchangeApplication::handle_quote, this, _1, _2));

    std::string url = init_url("quote");
    url.append("&stockcode=");
    url.append(stockcode);
    send_get(client, url);
}

void StockExchangeApplication::handle_quote(boost::system::error_code err, const Wt::Http::Message& response)
{
    Wt::Json::Value p = recv(err, response);
    if(!p.isNull()) {
        Wt::Json::Object& payload = p;
        std::string stockcode = payload.get("stockcode");
        int lastsaleprice = payload.get("lastsaleprice");
        quote_widget->add_row(stockcode, std::to_string(lastsaleprice));
    }
}

void StockExchangeApplication::send_transactions() {
    if(!is_signedin()) {
        return;
    }

    transactions_widget->reset();

    Wt::Http::Client *client = create_client();
    client->done().connect(boost::bind(&StockExchangeApplication::handle_transactions, this, _1, _2));

    std::string url = init_url("transactions");
    send_get(client, url);
}

void StockExchangeApplication::handle_transactions(boost::system::error_code err, const Wt::Http::Message& response)
{
    Wt::Json::Value p = recv(err, response);
    if(!p.isNull()) {
        Wt::Json::Object& payload = p;
        Wt::Json::Value r = payload.get("records");
        Wt::Json::Array& records = r;
        
        for(auto i=records.begin(); i!=records.end(); i++) {
            Wt::Json::Object& record = *i;
            std::string stockcode = record.get("stockcode");
            int quantity = record.get("quantity");
            int datetime = record.get("datetime");
            int action = record.get("action");
            int status = record.get("status");

            transactions_widget->add_row(stockcode, std::to_string(quantity), std::to_string(datetime), action == 0 ? "Sell" : "Buy", status == 0 ? "Pending" : "Executed");
        }
    }
}

void StockExchangeApplication::send_portfoliolist() {
    if(!is_signedin()) {
        return;
    }

    portfoliolist_widget->reset();

    Wt::Http::Client *client = create_client();
    client->done().connect(boost::bind(&StockExchangeApplication::handle_portfoliolist, this, _1, _2));

    std::string url = init_url("portfoliolist");
    send_get(client, url);
}

void StockExchangeApplication::handle_portfoliolist(boost::system::error_code err, const Wt::Http::Message& response)
{
    Wt::Json::Value p = recv(err, response);
    if(!p.isNull()) {
        Wt::Json::Object& payload = p;
        Wt::Json::Value r = payload.get("records");
        Wt::Json::Array& records = r;
        
        for(auto i=records.begin(); i!=records.end(); i++) {
            Wt::Json::Object& record = *i;

            std::string stockcode = record.get("stockcode");
            int quantity = record.get("quantity");
            int totalcost = record.get("totalcost");

            portfoliolist_widget->add_row(stockcode, std::to_string(quantity), std::to_string(totalcost));
        }
    }
}

bool StockExchangeApplication::validate_action_parameters(std::string stockcode, std::string quantity, std::string price) {
    try {
        stoi(quantity);
    } catch(std::exception& e) {
        show_error("Quantity must be an integer");
        return false;
    }

    try {
        stoi(quantity);
    } catch(std::exception& e) {
        show_error("Price must be an integer");
        return false;
    }

    return true;
}

void StockExchangeApplication::send_action(std::string action_path, ActionWidget *widget) {
    if(!is_signedin()) {
        return;
    }

    std::string stockcode = widget->stockcode->lineedit->text().narrow();
    std::string quantity = widget->quantity->lineedit->text().narrow();
    std::string price = widget->price->lineedit->text().narrow();

    if(!validate_action_parameters(stockcode, quantity, price)) {
        return;
    }

    Wt::Http::Client *client = create_client();
    client->done().connect(boost::bind(&StockExchangeApplication::handle_action, this, _1, _2));

    std::string url = init_url(action_path);
    url.append("&stockcode=");
    url.append(stockcode);
    url.append("&quantity=");
    url.append(quantity);
    url.append("&price=");
    url.append(price);
    send_put(client, url);
}

void StockExchangeApplication::handle_action(boost::system::error_code err, const Wt::Http::Message& response)
{
    Wt::Json::Value p = recv(err, response);
    if(!p.isNull()) {
        show_info("Success!");
        activate_transactions();
    }
}

void StockExchangeApplication::send_buy() {
    send_action("buy", buy_widget);
}

void StockExchangeApplication::send_sell() {
    send_action("sell", sell_widget);
}
