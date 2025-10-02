CXX = g++
CXXFLAGS = -Wall -std=c++17

BIN_DIR = bin
TARGET = $(BIN_DIR)/execute_me

SRC = $(shell find . -maxdepth 1 -name "*.cpp")
OBJ = $(patsubst ./%.cpp,$(BIN_DIR)/%.o,$(SRC))

LOGS_OBJ = ../LOGS/bin/logging.o

all: $(TARGET)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(TARGET): $(OBJ) $(LOGS_OBJ) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BIN_DIR)/%.o: %.cpp | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BIN_DIR)
