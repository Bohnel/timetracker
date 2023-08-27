CXX = g++
CXXFLAGS = -std=c++11 -Wall
TARGET = timetracker
SOURCES = timetracker.cpp

$(TARGET): $(SOURCES)
	$(CXX) $(CSSFLAGS) -o $(TARGET) $(SOURCES)
