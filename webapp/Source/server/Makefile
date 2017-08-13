CC=g++
CFLAGS=-c -Wall -g -O0 -std=c++11
LDFLAGS=-L /usr/local/lib -lboost_system -lcrypto -lssl -lcpprest -lmysqlcppconn
SOURCES+= src/connector.cpp
SOURCES+= src/model.cpp
SOURCES+= src/portfolio.cpp
SOURCES+= src/stock.cpp
SOURCES+= src/trader.cpp
SOURCES+= src/transaction.cpp
SOURCES+= src/response.cpp
SOURCES+= src/handler.cpp
SOURCES+= src/server.cpp
SOURCES+= src/main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=server

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

.cpp.o:
	$(CC) $(OPTS) $(CFLAGS) $< -o $@

clean:
	rm $(OBJECTS) $(EXECUTABLE)
