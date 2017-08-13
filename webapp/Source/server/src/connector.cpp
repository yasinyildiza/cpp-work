#include "../include/connector.h"

Connector* Connector::m_instance = new Connector();

Connector::Connector() {
	is_connected = false;
	m_driver = NULL;
	m_connection = NULL;
}

void Connector::connect(std::string address, std::string username, std::string password, std::string dbname) {
	if(is_connected) {
		return;
	}

	m_driver = get_driver_instance();
	m_connection = m_driver->connect(address, username, password);
	m_connection->setSchema(dbname);
	is_connected = true;
}

Connector::~Connector() {
	delete m_connection;
}

Connector* Connector::getInstance() {
	return m_instance;
}

sql::Statement* Connector::createStatement() {
	if(!m_instance->is_connected) {
		return NULL;
	}
	return m_instance->m_connection->createStatement();
}

sql::PreparedStatement* Connector::prepareStatement(std::string query) {
	if(!m_instance->is_connected) {
		return NULL;
	}
	return m_instance->m_connection->prepareStatement(query);
}

void Connector::disconnect() {
	if(!m_instance->is_connected) {
		return;
	}
	m_instance->is_connected = false;
	m_instance->m_connection->close();
}
