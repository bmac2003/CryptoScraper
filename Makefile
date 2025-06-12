CC = gcc
CFLAGS = -Wall -Wextra -I./include
DFLAGS = $(CFLAGS) -g
LDFLAGS = -lcurl

SRC_DIR = src
INC_DIR = include
BUILD_DIR = build

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))
TARGET = scraper

all: $(BUILD_DIR) $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

run:
	./$(TARGET)

# debug: $(OBJECTS)
# 	$(CC) $(DFLAGS) $(OBJECTS) -o $(EXECUTABLE) $(LDFLAGS)

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: all clean
