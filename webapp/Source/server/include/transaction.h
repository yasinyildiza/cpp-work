#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "constants.h"
#include "model.h"

class Transaction : public Model {
private:
public:
	enum class Action {
		sell,
		buy
	};

	enum class Status {
		pending,
		executed
	};

	std::string username;
	std::string stockcode;
	int quantity;
	long datetime;
	int action;
	int status;

	Transaction();
	~Transaction();

	static std::vector<Transaction> filter_by_username(std::string username_);
	static bool create(std::string username_, std::string stockcode_, int quantity_, long datetime_, int action_, int status);
	bool update();
	web::json::value to_json();
};

#endif /* TRANSACTION_H */
