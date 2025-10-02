# Server Makefile

CXX = g++
CXXFLAGS = -Wall -std=c++17

BIN_DIR = bin
TARGET = $(BIN_DIR)/execute_me

# Source files
SRC = server.cpp commandcenter.cpp logging.cpp

# Object files in bin directory
OBJ = $(patsubst %.cpp,$(BIN_DIR)/%.o,$(notdir $(SRC)))

all: $(BIN_DIR) $(TARGET)

# Create bin directory if it does not exist
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Compile each .cpp into bin/*.o
$(BIN_DIR)/%.o: %.cpp | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Link all object files into target
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Clean
clean:
	rm -rf $(BIN_DIR)/*.o $(TARGET)
