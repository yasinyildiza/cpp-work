CC=g++
CFLAGS=-c -Wall -g -O0 -std=c++11 -DBOOST_SIGNALS_NO_DEPRECATION_WARNING
LDFLAGS=-lwthttp -lwt -lboost_random -lboost_regex -lboost_signals -lboost_system -lboost_thread -lboost_filesystem -lboost_program_options -lboost_date_time
SOURCES+= src/labeledinput.cpp
SOURCES+= src/page.cpp
SOURCES+= src/tablepage.cpp
SOURCES+= src/menu.cpp
SOURCES+= src/signin.cpp
SOURCES+= src/welcome.cpp
SOURCES+= src/quote.cpp
SOURCES+= src/transactions.cpp
SOURCES+= src/portfoliolist.cpp
SOURCES+= src/action.cpp
SOURCES+= src/application.cpp
SOURCES+= src/main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=client

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

.cpp.o:
	$(CC) $(OPTS) $(CFLAGS) $< -o $@

clean:
	rm $(OBJECTS) $(EXECUTABLE)
