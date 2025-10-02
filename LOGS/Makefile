CXX = g++
CXXFLAGS = -Wall -std=c++17

BIN_DIR = bin
LIB = $(BIN_DIR)/liblogging.a

all: $(LIB)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(LIB): logging.o | $(BIN_DIR)
	ar rcs $(LIB) $(BIN_DIR)/logging.o

logging.o: logging.cpp logging.hpp | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -c logging.cpp -o $(BIN_DIR)/logging.o

clean:
	rm -rf $(BIN_DIR)
