TARGET = internet_time

CC = clang
CFLAGS = -O3 \
		 -fomit-frame-pointer \
         -fno-unwind-tables \
		 -fno-asynchronous-unwind-tables \
		 -DNDEBUG

SOURCES = main.c

OBJECTS = $(SOURCES:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean

