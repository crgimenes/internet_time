TARGET = internet_time
VERSION = 2.0.0

CC = clang
CFLAGS = -std=c99 \
		 -Wall \
		 -Wextra \
		 -Wpedantic \
		 -O3 \
		 -fomit-frame-pointer \
         -fno-unwind-tables \
		 -fno-asynchronous-unwind-tables \
		 -DNDEBUG \
		 -DVERSION=\"$(VERSION)\"

# Debug flags
DEBUG_CFLAGS = -std=c99 -Wall -Wextra -Wpedantic -g -O0 -DDEBUG

SOURCES = main.c
OBJECTS = $(SOURCES:.c=.o)

# Installation paths
PREFIX ?= /usr/local
BINDIR = $(PREFIX)/bin
MANDIR = $(PREFIX)/share/man/man1

all: $(TARGET)

debug: CFLAGS = $(DEBUG_CFLAGS)
debug: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

install: $(TARGET)
	install -d $(BINDIR)
	install -m 755 $(TARGET) $(BINDIR)

uninstall:
	rm -f $(BINDIR)/$(TARGET)

clean:
	rm -f $(OBJECTS) $(TARGET)

test: $(TARGET)
	@echo "Testing basic functionality..."
	@./$(TARGET)
	@echo "Testing timezone offset..."
	@./$(TARGET) -t 2
	@echo "Testing local time..."
	@./$(TARGET) -l
	@echo "Testing beat conversion..."
	@./$(TARGET) -b 500
	@echo "Testing verbose mode..."
	@./$(TARGET) -v
	@echo "All tests passed!"

format:
	clang-format -i $(SOURCES)

.PHONY: all debug clean install uninstall test format

