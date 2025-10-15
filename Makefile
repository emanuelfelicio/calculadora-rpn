CC = gcc
CFLAGS = -I./src -Wall -Wextra -std=c11
SRC = src/pol.c
LIB_OBJS =
BIN_DIR = bin
TEST_DIR = tests

.PHONY: all build test clean

all: build

# Build the command-line program (executable in bin/)
build: $(BIN_DIR)/pol

$(BIN_DIR)/pol: $(SRC) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $(SRC)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Build and run tests. Define UNIT_TEST to exclude main() from pol.c
test: $(TEST_DIR)/test
	./$(TEST_DIR)/test

$(TEST_DIR)/test: $(TEST_DIR)/test.c $(SRC)
	$(CC) $(CFLAGS) -DUNIT_TEST -o $@ $(TEST_DIR)/test.c $(SRC)

clean:
	rm -f $(BIN_DIR)/pol $(TEST_DIR)/test
