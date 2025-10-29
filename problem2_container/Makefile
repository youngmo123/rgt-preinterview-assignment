# Makefile for CircularBuffer project

CXX = g++
CXXFLAGS = -std=c++14 -Wall -Wextra -O2
TARGET = circular_buffer_test
SOURCES = main.cpp
HEADERS = CircularBuffer.h CircularBuffer.tpp

# Default target
all: $(TARGET)

# Build the executable
$(TARGET): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

# Clean build artifacts
clean:
	rm -f $(TARGET) $(TARGET).exe

# Run the program
run: $(TARGET)
	./$(TARGET)

# Windows-specific run target
run-win: $(TARGET)
	$(TARGET).exe

# Install dependencies (if needed)
install-deps:
	@echo "No external dependencies required"

# Help target
help:
	@echo "Available targets:"
	@echo "  all       - Build the project (default)"
	@echo "  clean     - Remove build artifacts"
	@echo "  run       - Build and run the program (Unix/Linux)"
	@echo "  run-win   - Build and run the program (Windows)"
	@echo "  help      - Show this help message"

.PHONY: all clean run run-win install-deps help
