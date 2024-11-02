# Compiler flags and options
# CC is the compiler
CC = gcc
# CFLAGS is compiler options, -Wall -Wextra are both warnings, -std=c99 is the standard being enforced
CFLAGS = -Wall -Wextra -std=c99 -Iinclude
# SDL2 flags from shell
SDL2_CFLAGS = $(shell sdl2-config --cflags)
SDL2_LDFLAGS = $(shell sdl2-config --libs)
# folder names for obj folder and src folder
OBJDIR = build
SRCDIR = src

# Lists the source files(.c files), wildcard is used to make files in the directory
SRCS = $(wildcard $(SRCDIR)/*.c)
# This line automatically generates a list of object files(.o files) 
# pathsubst is a function that replaces parts of text tthat match a pattern with replacement
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))
# Defines target and source files
# Name of the final executable
TARGET = $(OBJDIR)/chip8_emulator

# Build rules. This is the default rule.
all: $(TARGET)
# This rule states that $(TARGET) depends on $(OBJS)
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(SDL2_LDFLAGS) 
# This is a pattern rule, meaning it applies to any .c file to generate its corresponding .o file.
# % is the pattern rules representing a generic part of a filename
# * is used in file matching patterns to represent any sequence of characters within filenames.
# $@ and $^
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) $(SDL2_CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR)