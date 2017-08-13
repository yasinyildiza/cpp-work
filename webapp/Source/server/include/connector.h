#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <iostream>
#include <string>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

class Connector {
private:
	static Connector *m_instance;

	sql::Driver *m_driver;
	sql::Connection *m_connection;

	bool is_connected;

	Connector();

public:
	~Connector();
	void connect(std::string address, std::string username, std::string password, std::string dbname);

	static Connector* getInstance();
	static sql::Statement* createStatement();
	static sql::PreparedStatement* prepareStatement(std::string query);
	static void disconnect();
};

#endif /* CONNECTOR_H */
