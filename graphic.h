#ifndef GRAPHIC_H
#define GRAPHIC_H

#include "raylib.h"
#include "cube.h"
#include "solver.h"

void drawCube(Cube* cube);
Color GetFaceColor(int colorIndex);

#endif // GRAPHIC_H