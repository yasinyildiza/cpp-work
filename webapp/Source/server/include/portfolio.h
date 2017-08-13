#ifndef PORTFOLIO_H
#define PORTFOLIO_H

#include "constants.h"
#include "model.h"

class Portfolio : public Model {
private:

public:
	std::string username;
	std::string stockcode;
	int quantity;
	int totalcost;

	Portfolio();
	~Portfolio();

	static std::vector<Portfolio> filter_by_username(std::string username_);
	static std::vector<Portfolio> filter_by_stockcode(std::string stockcode_);
	static void find_by_username_and_stockcode(std::string username_, std::string stockcode_, Portfolio &record);
	static bool create(std::string username_, std::string stockcode_, int quantity_, int totalcost_);
	bool update();
	web::json::value to_json();
};

#endif /* PORTFOLIO_H */
