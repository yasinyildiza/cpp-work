#include "../include/trader.h"

Trader::Trader() {}
Trader::~Trader() {}

void Trader::find_by_username(std::string username_, Trader &record) {
	sql::PreparedStatement *prepared_statement = Connector::prepareStatement("SELECT username, password, balancecash FROM trader WHERE username=(?)");
	prepared_statement->setString(1, username_);

	sql::ResultSet *result = prepared_statement->executeQuery();
	while(result->next()) {
		record.exists(true);
		record.username = result->getString(KEY_USERNAME);
		record.password = result->getString(KEY_PASSWORD);
		record.balancecash = result->getInt(KEY_BALANCECASH);
	}

	delete result;
	delete prepared_statement;
}

bool Trader::authenticate(std::string username_, std::string password_) {
	sql::PreparedStatement *prepared_statement = Connector::prepareStatement("SELECT username FROM trader WHERE username=(?) AND password=(?)");
	prepared_statement->setString(1, username_);
	prepared_statement->setString(2, password_);

	sql::ResultSet *result = prepared_statement->executeQuery();
	int count = result->rowsCount();

	delete result;
	delete prepared_statement;

	return count > 0;
}

bool Trader::create(std::string username_, std::string password_, int balancecash_) {
	sql::PreparedStatement *prepared_statement = Connector::prepareStatement("INSERT INTO trader(username, password, balancecash) VALUES((?), (?), (?))");
	prepared_statement->setString(1, username_);
	prepared_statement->setString(2, password_);
	prepared_statement->setInt(3, balancecash_);
	prepared_statement->execute();

	delete prepared_statement;

	return true;
}

bool Trader::update() {
	sql::PreparedStatement *prepared_statement = Connector::prepareStatement("UPDATE trader SET password=(?), balancecash=(?) WHERE username=(?)");
	prepared_statement->setString(1, password);
	prepared_statement->setInt(2, balancecash);
	prepared_statement->setString(3, username);
	prepared_statement->execute();

	delete prepared_statement;

	return true;
}

web::json::value Trader::to_json() {
	web::json::value obj = web::json::value::object();
    obj[KEY_USERNAME] = web::json::value::string(username);
	//obj[KEY_PASSWORD] = web::json::value::string(password);
	obj[KEY_BALANCECASH] = web::json::value::number(balancecash);
	return obj;
}
