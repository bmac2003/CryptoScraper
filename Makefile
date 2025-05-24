CC = gcc
CFLAGS = -Wall
DFLAGS = $(CFLAGS) -g
LDFLAGS =

SOURCES = scraper.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = scraper
HEADERS = $(wildcard *.h)

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

debug: $(OBJECTS)
	$(CC) $(DFLAGS) $(OBJECTS) -o $(EXECUTABLE) $(LDFLAGS)

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

.PHONY: all clean
