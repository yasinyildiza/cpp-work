#ifndef STOCK_H
#define STOCK_H

#include "constants.h"
#include "model.h"

class Stock : public Model {
private:

public:
	std::string stockcode;
	int lastsaleprice;

	Stock();
	~Stock();

	static void find_by_stockcode(std::string stockcode_, Stock &record);
	static bool create(std::string stockcode_, int lastsaleprice_);
	bool update();
	web::json::value to_json();
};

#endif /* STOCK_H */
