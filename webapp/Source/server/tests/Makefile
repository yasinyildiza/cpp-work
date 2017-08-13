CC=g++
CFLAGS=-c -Wall -g -O0 -std=c++11
LDFLAGS=-L /usr/local/lib -lboost_system -lcrypto -lssl -lcpprest -lmysqlcppconn -lboost_unit_test_framework
SOURCES+= test_model.cpp
SOURCES+= test_portfolio.cpp
SOURCES+= test_transaction.cpp
SOURCES+= test_stock.cpp
SOURCES+= test_trader.cpp
SOURCES+= test_response.cpp
SOURCES+= ../src/connector.cpp
SOURCES+= ../src/model.cpp
SOURCES+= ../src/portfolio.cpp
SOURCES+= ../src/stock.cpp
SOURCES+= ../src/trader.cpp
SOURCES+= ../src/transaction.cpp
SOURCES+= ../src/response.cpp
SOURCES+= ../src/handler.cpp
SOURCES+= ../src/server.cpp
SOURCES+= main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=runtest

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

.cpp.o:
	$(CC) $(OPTS) $(CFLAGS) $< -o $@

clean:
	rm $(OBJECTS) $(EXECUTABLE)
