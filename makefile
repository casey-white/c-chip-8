# Compiler flags and options
# CC is the compiler
CC = gcc
# CFLAGS is compiler options, -Wall -Wextra are both warnings, -std=c99 is the standard being enforced
CFLAGS = -Wall -Wextra -std=c99
# SDL2 flags from shell
SDL2_CFLAGS = $(shell sdl2-config --cflags)
SDL2_LDFLAGS = $(shell sdl2-config --libs)

# Defines target and source files
# Name of the final executable
TARGET = chip8_emulator
# Lists the source files(.c files)
SRCS = main.c
# This line automatically generates a list of object files(.o files)
OBJS = $(SRCS:.c=.o)

# Build rules. This is the default rule.
all: $(TARGET)
# This rule states that $(TARGET) depends on $(OBJS)
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) $(SDL2_LDFLAGS)
# This is a pattern rule, meaning it applies to any .c file to generate its corresponding .o file.
%.o: %.c
	$(CC) $(CFLAGS) $(SDL2_CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)