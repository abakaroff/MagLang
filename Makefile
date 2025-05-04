CC = gcc
CFLAGS = -Wall -Wextra -std=c99
INCLUDES = -I./src

SRC_DIR = src
SOURCES = $(wildcard $(SRC_DIR)/*.c) \
           $(wildcard $(SRC_DIR)/lexer/*.c) \
           $(wildcard $(SRC_DIR)/parser/*.c) \
           $(wildcard $(SRC_DIR)/variables/*.c) \
           $(wildcard $(SRC_DIR)/executor/*.c)
OBJECTS = $(SOURCES:.c=.o)
TARGET = interpreter

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean