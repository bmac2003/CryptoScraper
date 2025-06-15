CC = gcc
CFLAGS = -Wall -Wextra -I./include
DFLAGS = $(CFLAGS) -g
LDFLAGS = -lcurl

SRC_DIR = src
INC_DIR = include
BUILD_DIR = build
TEST_DIR = tests

TARGET = CryptoScraper

all: $(BUILD_DIR) $(TARGET)

$(TARGET): $(BUILD_DIR)
	@cd $(BUILD_DIR); \
	cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..; \
	make

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

run:
	./$(BUILD_DIR)/$(TARGET)

test:
	@echo "Running all tests..."
	@cd $(BUILD_DIR); \
	ctest

test_%:
	@echo "Running tests for $*.c ..."
	@cd $(BUILD_DIR); \
	make run_$*_test

# debug: $(OBJECTS)
# 	$(CC) $(DFLAGS) $(OBJECTS) -o $(EXECUTABLE) $(LDFLAGS)

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: all clean
