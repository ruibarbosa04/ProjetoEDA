# Compiler to use
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -g

# Find all .c files in the current directory
SOURCES = $(wildcard *.c)

# Generate object file names from source files
OBJECTS = $(SOURCES:.c=.o)

# Header files
HEADERS = $(wildcard *.h)

# Executable name
TARGET = programa

# Main rule
all: $(TARGET)

# Linking rule
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

# Compilation rule - automatically includes all headers
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -f $(OBJECTS) $(TARGET)

# Phony targets
.PHONY: all clean