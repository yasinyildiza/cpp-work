#include "../include/stock.h"

Stock::Stock() {}
Stock::~Stock() {}

void Stock::find_by_stockcode(std::string stockcode_, Stock &record) {
	sql::PreparedStatement *prepared_statement = Connector::prepareStatement("SELECT stockcode, lastsaleprice FROM stock WHERE stockcode=(?)");
	prepared_statement->setString(1, stockcode_);

	sql::ResultSet *result = prepared_statement->executeQuery();
	while(result->next()) {
		record.exists(true);
		record.stockcode = result->getString(KEY_STOCKCODE);
		record.lastsaleprice = result->getInt(KEY_LASTSALEPRICE);
	}

	delete result;
	delete prepared_statement;
}

bool Stock::create(std::string stockcode_, int lastsaleprice_) {
	sql::PreparedStatement *prepared_statement = Connector::prepareStatement("INSERT INTO stock(stockcode, lastsaleprice) VALUES((?), (?))");
	prepared_statement->setString(1, stockcode_);
	prepared_statement->setInt(2, lastsaleprice_);
	prepared_statement->execute();

	delete prepared_statement;

	return true;
}

bool Stock::update() {
	sql::PreparedStatement *prepared_statement = Connector::prepareStatement("UPDATE stock SET lastsaleprice=(?) WHERE stockcode=(?)");
	prepared_statement->setInt(1, lastsaleprice);
	prepared_statement->setString(2, stockcode);
	prepared_statement->execute();

	delete prepared_statement;

	return true;
}

web::json::value Stock::to_json() {
	web::json::value obj = web::json::value::object();
	obj[KEY_STOCKCODE] = web::json::value::string(stockcode);
	obj[KEY_LASTSALEPRICE] = web::json::value::number(lastsaleprice);
	return obj;
}
