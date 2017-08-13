CC=g++
CFLAGS=-c -Wall -g -O0 -std=c++11
LDFLAGS=-L /usr/local/lib -lboost_system -lcrypto -lssl -lcpprest
SOURCES+= test_client.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=test_client

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

.cpp.o:
	$(CC) $(OPTS) $(CFLAGS) $< -o $@

clean:
	rm $(OBJECTS) $(EXECUTABLE)
