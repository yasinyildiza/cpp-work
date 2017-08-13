#include "../include/portfolio.h"

Portfolio::Portfolio() {}
Portfolio::~Portfolio() {}

std::vector<Portfolio> Portfolio::filter_by_username(std::string username_) {
	sql::PreparedStatement *prepared_statement = Connector::prepareStatement("SELECT username, stockcode, quantity, totalcost FROM portfolio WHERE username=(?) ORDER BY stockcode");
	prepared_statement->setString(1, username_);

	sql::ResultSet *result = prepared_statement->executeQuery();
	int count = result->rowsCount();

	int counter = 0;
	std::vector<Portfolio> records(count);
	while(result->next()) {
		records[counter].exists(true);
		records[counter].username = result->getString(KEY_USERNAME);
		records[counter].stockcode = result->getString(KEY_STOCKCODE);
		records[counter].quantity = result->getInt(KEY_QUANTITY);
		records[counter].totalcost = result->getInt(KEY_TOTALCOST);

		counter++;
	}

	delete result;
	delete prepared_statement;

	return records;
}

std::vector<Portfolio> Portfolio::filter_by_stockcode(std::string stockcode_) {
	sql::PreparedStatement *prepared_statement = Connector::prepareStatement("SELECT username, stockcode, quantity, totalcost FROM portfolio WHERE stockcode=(?) ORDER BY username");
	prepared_statement->setString(1, stockcode_);

	sql::ResultSet *result = prepared_statement->executeQuery();
	int count = result->rowsCount();

	int counter = 0;
	std::vector<Portfolio> records(count);
	while(result->next()) {
		records[counter].exists(true);
		records[counter].username = result->getString(KEY_USERNAME);
		records[counter].stockcode = result->getString(KEY_STOCKCODE);
		records[counter].quantity = result->getInt(KEY_QUANTITY);
		records[counter].totalcost = result->getInt(KEY_TOTALCOST);

		counter++;
	}

	delete result;
	delete prepared_statement;

	return records;
}

void Portfolio::find_by_username_and_stockcode(std::string username_, std::string stockcode_, Portfolio &record) {
	sql::PreparedStatement *prepared_statement = Connector::prepareStatement("SELECT username, stockcode, quantity, totalcost FROM portfolio WHERE username=(?) AND stockcode=(?)");
	prepared_statement->setString(1, username_);
	prepared_statement->setString(2, stockcode_);

	sql::ResultSet *result = prepared_statement->executeQuery();
	if(result->next()) {
		record.exists(true);
		record.username = result->getString(KEY_USERNAME);
		record.stockcode = result->getString(KEY_STOCKCODE);
		record.quantity = result->getInt(KEY_QUANTITY);
		record.totalcost = result->getInt(KEY_TOTALCOST);
	}

	delete result;
	delete prepared_statement;
}

bool Portfolio::create(std::string username_, std::string stockcode_, int quantity_, int totalcost_) {
	sql::PreparedStatement *prepared_statement = Connector::prepareStatement("INSERT INTO portfolio(username, stockcode, quantity, totalcost) VALUES((?), (?), (?), (?))");
	prepared_statement->setString(1, username_);
	prepared_statement->setString(2, stockcode_);
	prepared_statement->setInt(3, quantity_);
	prepared_statement->setInt(4, totalcost_);
	prepared_statement->execute();

	delete prepared_statement;

	return true;
}

bool Portfolio::update() {
	sql::PreparedStatement *prepared_statement = Connector::prepareStatement("UPDATE portfolio SET quantity=(?), totalcost=(?) WHERE username=(?) AND stockcode=(?)");
	prepared_statement->setInt(1, quantity);
	prepared_statement->setInt(2, totalcost);
	prepared_statement->setString(3, username);
	prepared_statement->setString(4, stockcode);
	prepared_statement->execute();

	delete prepared_statement;

	return true;
}

web::json::value Portfolio::to_json() {
	web::json::value obj = web::json::value::object();
    obj[KEY_USERNAME] = web::json::value::string(username);
	obj[KEY_STOCKCODE] = web::json::value::string(stockcode);
	obj[KEY_QUANTITY] = web::json::value::number(quantity);
	obj[KEY_TOTALCOST] = web::json::value::number(totalcost);
	return obj;
}
