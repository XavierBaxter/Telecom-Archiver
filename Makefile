CC := gcc
CFLAGS ?= -Wall -Wextra -std=c99

ifeq ($(OS),Windows_NT)
TARGET := telecom-archive.exe
else
TARGET := telecom-archive
endif

SOURCES := main.c migration.c archive.c linked_list.c analytics.c
OBJECTS := $(SOURCES:.c=.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

%.o: %.c telecom_a2.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
ifeq ($(OS),Windows_NT)
	-del /Q $(OBJECTS) $(TARGET) logs.bin 2>NUL
else
	$(RM) $(OBJECTS) $(TARGET) logs.bin
endif

