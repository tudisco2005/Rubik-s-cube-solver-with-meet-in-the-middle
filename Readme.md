# Very inefficient Meet in the middle for solving 3x3 Rubik's Cube

A C implementation of a Rubik's cube solver using a bidirectional search algorithm ("meet in the middle"). This solver finds a sequence of moves to solve a scrambled 3x3 Rubik's cube.



## Features

- 3x3 Rubik's cube representation with standard color scheme
- Support for all basic cube rotations (F, B, U, D, L, R) and their variations
- Scrambling functionality with random or predefined sequences
- Bidirectional search algorithm for finding solutions
- Pretty-printed cube state visualization with colors

## Installation

### Compatibility
- Windows
- Ubuntu 22.04 (need changes to the **makefile**)

### Requirements

- GCC compiler
- Make

### Building

- for windows, do not change anything

- makefile for linux with only textui
```makefile
# Compiler settings
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g -lc
LDFLAGS = -lGL -lm -lpthread -ldl -lrt -lX11

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
$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c $(SRC_DIR)/cube.h
$(OBJ_DIR)/cube.o: $(SRC_DIR)/cube.c $(SRC_DIR)/cube.h $(SRC_DIR)/utils.h

.PHONY: all directories clean run
```

- for linux with raylib graphic, move files from graphic/ into parent folder, change the makefile
>need raylib installed on the system

```makefile
# Compiler settings
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g -lc
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
```

#### Complie and run
```bash
# Clone the repository
git clone [repository-url]
cd cube_solver

# Compile the project
make

# Run the solver
make run
```
 

## Usage

The solver can be used by modifying the `main.c` file to define your scramble sequence:

```c
// Example usage in main.c
Cube *cube = initCube();
char scramble_config[] = "L R u F B R";  // Define your scramble sequence
scrambleCube(cube, scramble_config);
printCube(cube);

Cube *end = initCube();
char* solution = meetInTheMiddle(cube, end, 7);      // Find solution with max depth 7
printf("\nSolution: %s\n", solution);

scrambleCube(cube, solution);  // Apply solution to verify correctness
printCube(cube);
```

### Raylib graphics example usage
```c
// ...
#include "graphic.h"

int main() {
    // ...
    drawCube(cube)
    // ...
}

```

## Move Notation

- Uppercase letters (F, B, U, D, L, R) represent clockwise rotations of the respective face
- Lowercase letters (f, b, u, d, l, r) represent counter-clockwise rotations
- Number 2 suffix (F2, B2, etc.) represents double rotations (180°)

### Example

For a scramble "L R F B U D", the solver will find a sequence of moves to return to a solved state.

## How It Works

The solver implements a bidirectional search algorithm ("meet in the middle"):

1. Start two searches simultaneously: one from the scrambled state and one from the solved state
2. Expand both search frontiers until a common state is found
3. When a match is found, combine the forward path and reversed backward path to get the solution

This approach is significantly more efficient than a unidirectional search, as it effectively reduces the maximum search depth.

## Code Structure

- **cube.h/cube.c**: Defines the cube structure and rotation operations
- **solver.h/solver.c**: Implements the bidirectional search algorithm
- **utils.h/utils.c**: Utility functions for array manipulation and string operations
- **main.c**: Demo program showing how to use the solver

## Limitations

- The solver becomes memory-intensive for solutions requiring many moves
- Performance degrades significantly at higher search depths
- No optimizations for move sequence minimization

## Future Improvements

- Implement move sequence optimization
- Add pattern databases for more efficient heuristics
- Improve memory efficiency of the search algorithm
- Add support for different cube sizes

## License

MIT license

