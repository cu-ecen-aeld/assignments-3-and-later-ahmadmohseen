# Makefile for writer application
# Supports both native and cross-compilation

# Check if CROSS_COMPILE is set, otherwise use native compiler
ifeq ($(CROSS_COMPILE),)
    CC = gcc
else
    CC = $(CROSS_COMPILE)gcc
endif

# Compiler flags
CFLAGS = -Wall -Werror -O2

# Target executable
TARGET = writer

# Source files
SRC = writer.c

# Default target
all: $(TARGET)

# Build the writer executable
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

# Clean build artifacts
clean:
	rm -f $(TARGET) *.o

.PHONY: all clean

