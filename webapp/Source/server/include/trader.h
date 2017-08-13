#ifndef TRADER_H
#define TRADER_H

#include "constants.h"
#include "model.h"

class Trader : public Model {
private:

public:
	std::string username;
	std::string password;
	int balancecash;

	Trader();
	~Trader();

	static void find_by_username(std::string username_, Trader &record);
	static bool authenticate(std::string username_, std::string password_);
	static bool create(std::string username_, std::string password_, int balancecash_);
	bool update();
	web::json::value to_json();
};

#endif /* TRADER_H */
