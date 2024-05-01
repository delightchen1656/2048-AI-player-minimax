CXX = g++
CXXFLAGS = -Wall -g
TARGET = start

OBJS = main.o gameboard.o ai1.o ai2.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

main.o: main.cpp gameboard.h
	$(CXX) $(CXXFLAGS) -c main.cpp

gameboard.o: gameboard.cpp gameboard.h ai1.h ai2.h
	$(CXX) $(CXXFLAGS) -c gameboard.cpp

ai1.o: ai1.cpp ai1.h gameboard.h
	$(CXX) $(CXXFLAGS) -c ai1.cpp

ai2.o: ai2.cpp ai2.h gameboard.h
	$(CXX) $(CXXFLAGS) -c ai2.cpp

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
