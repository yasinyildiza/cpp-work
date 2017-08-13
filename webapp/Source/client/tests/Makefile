CC=g++
CFLAGS=-c -Wall -g -O0 -std=c++11 -DBOOST_SIGNALS_NO_DEPRECATION_WARNING
LDFLAGS=-lwthttp -lwt -lboost_random -lboost_regex -lboost_signals -lboost_system -lboost_thread -lboost_filesystem -lboost_program_options -lboost_date_time
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
