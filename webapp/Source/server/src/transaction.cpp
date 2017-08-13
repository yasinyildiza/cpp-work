#include "../include/transaction.h"

Transaction::Transaction() {}
Transaction::~Transaction() {}

std::vector<Transaction> Transaction::filter_by_username(std::string username_) {
	sql::PreparedStatement *prepared_statement = Connector::prepareStatement("SELECT username, stockcode, quantity, datetime, action, status FROM transaction WHERE username=(?) ORDER BY datetime DESC");
	prepared_statement->setString(1, username_);

	sql::ResultSet *result = prepared_statement->executeQuery();
	int count = result->rowsCount();

	int counter = 0;
	std::vector<Transaction> records(count);

	while(result->next()) {
		records[counter].exists(true);
		records[counter].username = result->getString(KEY_USERNAME);
		records[counter].stockcode = result->getString(KEY_STOCKCODE);
		records[counter].quantity = result->getInt(KEY_QUANTITY);
		records[counter].datetime = result->getInt(KEY_DATETIME);
		records[counter].action = result->getInt(KEY_ACTION);
		records[counter].status = result->getInt(KEY_STATUS);

		counter++;
	}

	delete result;
	delete prepared_statement;

	return records;
}

bool Transaction::create(std::string username_, std::string stockcode_, int quantity_, long datetime_, int action_, int status_) {
	sql::PreparedStatement *prepared_statement = Connector::prepareStatement("INSERT INTO transaction(username, stockcode, quantity, datetime, action, status) VALUES((?), (?), (?), (?), (?), (?))");
	prepared_statement->setString(1, username_);
	prepared_statement->setString(2, stockcode_);
	prepared_statement->setInt(3, quantity_);
	prepared_statement->setInt(4, datetime_);
	prepared_statement->setInt(5, action_);
	prepared_statement->setInt(6, status_);
	prepared_statement->execute();

	delete prepared_statement;

	return true;
}

bool Transaction::update() {
	return false;
}

web::json::value Transaction::to_json() {
	web::json::value obj = web::json::value::object();
    obj[KEY_USERNAME] = web::json::value::string(username);
	obj[KEY_STOCKCODE] = web::json::value::string(stockcode);
	obj[KEY_QUANTITY] = web::json::value::number(quantity);
	obj[KEY_DATETIME] = web::json::value::number(datetime);
	obj[KEY_ACTION] = web::json::value::number(action);
	obj[KEY_STATUS] = web::json::value::number(status);
	return obj;
}
