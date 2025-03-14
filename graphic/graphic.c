#include "raylib.h"
#include "graphic.h"
#include "cube.h"
#include "solver.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// Helper function to convert cube color enum to Raylib Color
Color GetFaceColor(int colorIndex) {
    switch(colorIndex) {
        case COLOR_WHITE:   return WHITE;
        case COLOR_YELLOW:  return YELLOW;
        case COLOR_ORANGE:  return ORANGE;
        case COLOR_RED:     return RED;
        case COLOR_GREEN:   return GREEN;
        case COLOR_BLUE:    return BLUE;
        default:            return GRAY;
    }
}

void drawCube(Cube* cube) {
    const int screenWidth = 800;
    const int screenHeight = 600;
    
    const int cellSize = 40;   
    const int padding = 10;    // Aumentato per aggiungere margine tra le facce
    
    const int startX = (screenWidth - (cellSize * SIZE * 4 + padding * 4)) / 2;
    const int startY = (screenHeight - (cellSize * SIZE * 3 + padding * 3)) / 2;
    
    Rectangle rectUp = { startX + cellSize * SIZE + padding, startY, cellSize * SIZE, cellSize * SIZE };
    Rectangle rectLeft = { startX, startY + cellSize * SIZE + padding, cellSize * SIZE, cellSize * SIZE };
    Rectangle rectFront = { startX + cellSize * SIZE + padding, startY + cellSize * SIZE + padding, cellSize * SIZE, cellSize * SIZE };
    Rectangle rectRight = { startX + (cellSize * SIZE + padding) * 2, startY + cellSize * SIZE + padding, cellSize * SIZE, cellSize * SIZE };
    Rectangle rectBack = { startX + (cellSize * SIZE + padding) * 3, startY + cellSize * SIZE + padding, cellSize * SIZE, cellSize * SIZE };
    Rectangle rectDown = { startX + cellSize * SIZE + padding, startY + (cellSize * SIZE + padding) * 2, cellSize * SIZE, cellSize * SIZE };
    
    InitWindow(screenWidth, screenHeight, "Rubik's Cube - Vista 2D");
    SetTargetFPS(60);
    
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(DARKGRAY);
        
        Rectangle faces[] = { rectUp, rectLeft, rectFront, rectRight, rectBack, rectDown };
        int faceColors[] = { FACE_UP, FACE_LEFT, FACE_FRONT, FACE_RIGHT, FACE_BACK, FACE_DOWN };
        const char* faceLabels[] = { "UP", "LEFT", "", "RIGHT", "BACK", "DOWN" };
        
        for (int f = 0; f < 6; f++) {
            for (int y = 0; y < SIZE; y++) {
                for (int x = 0; x < SIZE; x++) {
                    Color cellColor = GetFaceColor(cube->color[faceColors[f]][y][x]);
                    DrawRectangle(faces[f].x + x * cellSize, faces[f].y + y * cellSize, cellSize - 2, cellSize - 2, cellColor);
                }
            }
            DrawRectangleLinesEx(faces[f], 2, WHITE);
            
            int textWidth = MeasureText(faceLabels[f], 20);
            if (f == 5) {
                DrawText(faceLabels[f], faces[f].x + (faces[f].width - textWidth) / 2, faces[f].y + faces[f].height + 5, 20, WHITE);
            } else {
                DrawText(faceLabels[f], faces[f].x + (faces[f].width - textWidth) / 2, faces[f].y - 25, 20, WHITE);
            }
        }
        
        DrawText("Rubik's Cube - Vista 2D", 10, 10, 20, WHITE);
        DrawFPS(10, 40);
        EndDrawing();
    }
    CloseWindow();
}
