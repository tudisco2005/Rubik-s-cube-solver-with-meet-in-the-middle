# Makefile for Cube Solver

# Compiler settings
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# Directories
SRC_DIR = .
BIN_DIR = bin
OBJ_DIR = $(BIN_DIR)/obj

# Source files and objects
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

# Executable name
EXEC = $(BIN_DIR)/cube_solver

# Main rule
all: directories $(EXEC)

# Rule to create directories
directories:
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(OBJ_DIR)

# Rule to link objects into executable
$(EXEC): $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# Rule to compile source files to objects
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -rf $(BIN_DIR)

# Run rule
run: all
	$(EXEC)

# Additional dependencies
$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c $(SRC_DIR)/cube.h $(SRC_DIR)/graphic.h
$(OBJ_DIR)/cube.o: $(SRC_DIR)/cube.c $(SRC_DIR)/cube.h $(SRC_DIR)/utils.h
$(OBJ_DIR)/graphic.o: $(SRC_DIR)/graphic.c $(SRC_DIR)/graphic.h $(SRC_DIR)/cube.h

.PHONY: all directories clean run