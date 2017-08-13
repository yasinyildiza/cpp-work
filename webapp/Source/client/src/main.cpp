#include <Wt/WApplication>
#include "../include/application.h"

Wt::WApplication *createApplication(const Wt::WEnvironment& env) {
    return new StockExchangeApplication(env);
}

int main(int argc, char **argv) {
    Wt::WRun(argc, argv, &createApplication);
    return 0;
}
