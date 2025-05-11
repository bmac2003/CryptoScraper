CC = gcc
CFLAGS = -Wall
DFLAGS = $(CFLAGS) -g
LDFLAGS =
SOURCE = scraper.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = myprogram

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

debug %.o: %.c
	$(CC) $(DFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

.PHONY: all clean
