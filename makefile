# Compiler flags and options
# CC is the compiler
CC = gcc
# CFLAGS is compiler options, -Wall -Wextra are both warnings, -std=c99 is the standard being enforced
CFLAGS = -Wall -Wextra -std=c99 -Iinclude
# Additional flags for gdb
DEBUG_FLAGS = -g
# SDL2 flags from shell
SDL2_CFLAGS = $(shell sdl2-config --cflags)
SDL2_LDFLAGS = $(shell sdl2-config --libs)
# folder names for obj folder and src folder
OBJDIR = build
SRCDIR = src
TESTDIR = test
# Unity source
UNITY_SRC = $(TESTDIR)/unity.c
UNITY_OBJ = $(OBJDIR)/unity.o
# Lists the source files(.c files), wildcard is used to make files in the directory
SRCS = $(wildcard $(SRCDIR)/*.c)
# This line automatically generates a list of object files(.o files) 
# pathsubst is a function that replaces parts of text tthat match a pattern with replacement
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))
# Defines target and source files
# Name of the final executable
TARGET = $(OBJDIR)/chip8_emulator

TEST_CPU_DEPEND = test/test_cpu.c test/unity.c src/cpu.c src/memory.c
TEST_CPU_OUT = test_cpu.out

TEST_MEMORY_DEPEND = test/test_memory.c test/unity.c src/cpu.c src/memory.c
TEST_MEMORY_OUT = test_memory.out

TEST_KEYPAD_DEPEND = test/test_keypad.c test/unity.c src/keypad.c
TEST_KEYPAD_OUT = test_keypad.out

.PHONY: test_memory.out

test_cpu: $(TEST_CPU_OUT)

$(TEST_CPU_OUT): $(TEST_CPU_DEPEND)
	$(CC) -Iinclude $^ -o $(TEST_CPU_OUT)

test_memory: $(TEST_MEMORY_OUT)

$(TEST_MEMORY_OUT): $(TEST_MEMORY_DEPEND)
	$(CC) -Iinclude $^ -o $(TEST_MEMORY_OUT)

test_keypad: $(TEST_KEYPAD_OUT)

$(TEST_KEYPAD_OUT): $(TEST_KEYPAD_DEPEND)
	$(CC) -Iinclude $^ $(SDL2_LDFLAGS) -o $(TEST_KEYPAD_OUT)

# %.out: test/%.c test/unity.c $(SRCS)
# 	$(CC) -Iinclude $^ -o $@

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

$(OBJDIR)/%.o: $(TESTDIR)/test_%.c
	$(CC) $(CFLAGS) $(SDL2_CFLAGS) -c $< -o $@

$(UNITY_OBJ): $(UNITY_SRC)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

debug: CFLAGS += $(DEBUG_FLAGS)
debug: clean $(TARGET)

clean:
	rm -rf $(OBJDIR)
