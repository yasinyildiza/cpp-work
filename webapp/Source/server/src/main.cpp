#include <iostream>
#include <cstdlib>
#include <exception>

#include "../include/connector.h"
#include "../include/server.h"

#ifdef _WIN32
int wmain(int argc, wchar_t *argv[])
#else
int main(int argc, char *argv[])
#endif
{
    if(argc < 5) {
        std::cout << "usage: ./server <db_ip> <db_port> <db_username> <db_password>" << std::endl;
        return -1;
    }

    std::string db_address, server_address, protocol, ip, port, username, password, name, path;

	db_address = "";
    server_address = "";

    protocol = "tcp";
    ip = argv[1]; // "127.0.0.1";
    port = argv[2]; // "3306";

    username = argv[3]; // "root";
    password = argv[4]; // "root";
    name = "StockExchange";

    db_address.append(protocol).append("://").append(ip).append(":").append(port);

    protocol = "http";
    ip = "0.0.0.0";
    port = "34568";
    path = "exchange";

    server_address.append(protocol).append("://").append(ip).append(":").append(port);

    web::http::uri_builder uri(server_address);
    uri.append_path(path);
    auto addr = uri.to_uri().to_string();

    std::unique_ptr<Connector> mysql_dealer = std::unique_ptr<Connector>(Connector::getInstance());
    std::unique_ptr<SimpleServer> http_dealer = std::unique_ptr<SimpleServer>(new SimpleServer(addr));

    try{
        mysql_dealer->connect(db_address, username, password, name);
    } catch(sql::SQLException &e) {
        std::cerr << "Unable to connect to MySQL" << std::endl;
        std::cerr << "Error Code: " << e.getErrorCode() << std::endl;
        std::cerr << "Error Description: " << e.what() << std::endl;
        std::cerr << "SQL State: " << e.getSQLState() << std::endl;
        exit(EXIT_FAILURE);
    }
    
    try {
        http_dealer->open().wait();
    } catch(std::exception &e) {
        std::cerr << "Unable to start Server" << std::endl;
        std::cerr << "Error Description: " << e.what() << std::endl;
        mysql_dealer->disconnect();
        exit(EXIT_FAILURE);
    }

    std::cout << "Press ENTER to exit." << std::endl;
    std::string line;
    std::getline(std::cin, line);

    http_dealer->close().wait();
    mysql_dealer->disconnect();

    return 0;
}
