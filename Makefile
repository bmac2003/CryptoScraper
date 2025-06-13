CC = gcc
CFLAGS = -Wall -Wextra -I./include
DFLAGS = $(CFLAGS) -g
LDFLAGS = -lcurl

SRC_DIR = src
INC_DIR = include
BUILD_DIR = build
TEST_DIR = tests

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))
TARGET = scraper

TEST_SRCS = $(patsubst $(SRC_DIR)/%.c,$(TEST_DIR)/%.test.c,$(SRCS))
TEST_OBJS = $(patsubst $(TEST_DIR)/%.test.c,$(BUILD_DIR)/%.test.o,$(TEST_SRCS))
TEST_TARGETS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%_test,$(SRCS))

all: $(BUILD_DIR) $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

run:
	./$(TARGET)

# Test Framework
$(BUILD_DIR)/%_test: $(BUILD_DIR)/%.o $(patsubst $(SRC_DIR)/%.c,$(TEST_DIR)/%.test.c,$(patsubst $(BUILD_DIR)/%_test, $(SRC_DIR)/%.c,$@))
	$(CC) $(CFLAGS) -I$(TEST_DIR) $^ -o $@ $(LDFLAGS)

test_%: $(BUILD_DIR)/%_test
	@$^

# debug: $(OBJECTS)
# 	$(CC) $(DFLAGS) $(OBJECTS) -o $(EXECUTABLE) $(LDFLAGS)

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: all clean
