# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -g

# Target executable
TARGET = lsh

# Buld directory
BUILD_DIR = build

# Source files
SRCS = main.c \
       loop.c \
       parser.c \
       executor.c \
       builtins.c \
       signals.c \
       redirection.c \
       utils.c

# Object files (generated automatically from SRCS)
OBJS = $(SRCS:%.c=$(BUILD_DIR)/%.o)

# Default target
all: $(TARGET)

# Build the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

# Compile .c to .o
$(BUILD_DIR)/%.o: %.c shell.h
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# Rebuild everything from scratch
rebuild: clean all
