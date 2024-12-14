# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iinclude

# Source and build directories
SRCDIR = src
INCDIR = include
BUILDDIR = build

# List of source files
SRCS = $(wildcard $(SRCDIR)/*.c)

# List of object files (in the build directory)
OBJS = $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%.o, $(SRCS))

# Output executable
TARGET = prgm

# Default target to build the program
all: $(TARGET)

# Rule to link object files into the executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@

# Rule to compile source files into object files
$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(BUILDDIR)  # Ensure the build directory exists
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build directory and executable
clean:
	rm -rf $(BUILDDIR) $(TARGET)
