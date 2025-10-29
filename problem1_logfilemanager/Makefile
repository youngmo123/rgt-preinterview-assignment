# Makefile for LogFileManager project
CXX = g++
CXXFLAGS = -std=c++14 -Wall -Wextra -O2
TARGET = logmanager_test
SOURCES = main.cpp LogFileManager.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# Default target
all: $(TARGET)

# Build the executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files to object files
%.o: %.cpp LogFileManager.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -f $(OBJECTS) $(TARGET) *.log

# Clean only log files
clean-logs:
	rm -f *.log

# Run the program
run: $(TARGET)
	./$(TARGET)

# Build and run
test: $(TARGET)
	./$(TARGET)

.PHONY: all clean clean-logs run test
