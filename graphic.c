#include "raylib.h"
#include "graphic.h"
#include "cube.h"
#include <stdio.h>
#include <math.h>

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
    const int screenWidth = 1200;
    const int screenHeight = 800;
    const float cubeSize = 1.0f;
    const float gap = 0.1f;
    const float fullSize = SIZE * (cubeSize + gap);
    const float startPos = -fullSize/2 + cubeSize/2;
    
    // Initialize window and camera
    InitWindow(screenWidth, screenHeight, "Rubik's Cube with 2D View");
    
    // Define camera to look at our 3D model
    Camera camera = { 0 };
    camera.position = (Vector3){ 6.0f, 6.0f, 6.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;
    
    // Variables for mouse camera control
    Vector2 previousMousePosition = { 0.0f, 0.0f };
    bool isMouseDragging = false;
    float cameraDistance = sqrtf(powf(camera.position.x, 2) + 
                               powf(camera.position.y, 2) + 
                               powf(camera.position.z, 2));
    float cameraAngleY = 0.8f;  // Initial horizontal angle in radians
    float cameraAngleX = 0.6f;  // Initial vertical angle in radians
    float mouseSensitivity = 0.003f;
    float zoomSensitivity = 0.5f;
    
    // 2D view properties
    const int cellSize = 38;   // Size of each small square in the 2D view
    const int padding = 26;    // Padding between faces
    
    // Position for the 2D view (bottom left corner) - MODIFIED
    const int startX = padding;
    const int startY = screenHeight - padding - cellSize * SIZE*3;
    
    Rectangle rectUp = {
        startX + cellSize * SIZE, 
        startY, 
        cellSize * SIZE, 
        cellSize * SIZE
    };
    
    Rectangle rectLeft = {
        startX, 
        startY + cellSize * SIZE, 
        cellSize * SIZE, 
        cellSize * SIZE
    };
    
    Rectangle rectFront = {
        startX + cellSize * SIZE, 
        startY + cellSize * SIZE, 
        cellSize * SIZE, 
        cellSize * SIZE
    };
    
    Rectangle rectRight = {
        startX + cellSize * SIZE * 2, 
        startY + cellSize * SIZE, 
        cellSize * SIZE, 
        cellSize * SIZE
    };
    
    Rectangle rectBack = {
        startX + cellSize * SIZE * 3, 
        startY + cellSize * SIZE, 
        cellSize * SIZE, 
        cellSize * SIZE
    };
    
    Rectangle rectDown = {
        startX + cellSize * SIZE, 
        startY + cellSize * SIZE * 2, 
        cellSize * SIZE, 
        cellSize * SIZE
    };
    
    SetTargetFPS(60);
    
    // Print debug info
    printf("Cube state verification:\n");
    for (int i = 0; i < NUM_FACES; i++) {
        printf("Face %d: ", i);
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < SIZE; k++) {
                printf("%d ", cube->color[i][j][k]);
            }
        }
        printf("\n");
    }
    
    // Main game loop
    while (!WindowShouldClose()) {
        // Mouse wheel zoom
        float wheelMove = GetMouseWheelMove();
        if (wheelMove != 0) {
            cameraDistance -= wheelMove * zoomSensitivity;
            if (cameraDistance < 3.0f) cameraDistance = 3.0f;  // Minimum zoom limit
            if (cameraDistance > 20.0f) cameraDistance = 20.0f;  // Maximum zoom limit
        }
        
        // Mouse drag for rotation
        Vector2 currentMousePosition = GetMousePosition();
        
        // Start dragging on left mouse button press
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            previousMousePosition = currentMousePosition;
            isMouseDragging = true;
        }
        
        // End dragging on mouse button release
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            isMouseDragging = false;
        }
        
        // Calculate rotation during dragging
        if (isMouseDragging) {
            Vector2 mouseDelta = { 
                currentMousePosition.x - previousMousePosition.x,
                currentMousePosition.y - previousMousePosition.y 
            };
            
            cameraAngleY -= mouseDelta.x * mouseSensitivity;
            cameraAngleX -= mouseDelta.y * mouseSensitivity;
            
            // Limit vertical angle to avoid strange rotations
            if (cameraAngleX < -1.5f) cameraAngleX = -1.5f;
            if (cameraAngleX > 1.5f) cameraAngleX = 1.5f;
            
            previousMousePosition = currentMousePosition;
        }
        
        // Update camera position based on angles
        camera.position.x = cosf(cameraAngleY) * cosf(cameraAngleX) * cameraDistance;
        camera.position.y = sinf(cameraAngleX) * cameraDistance;
        camera.position.z = sinf(cameraAngleY) * cosf(cameraAngleX) * cameraDistance;
        
        // Keep existing keyboard controls for flexibility
        if (IsKeyDown(KEY_RIGHT)) camera.position.x += 0.1f;
        if (IsKeyDown(KEY_LEFT)) camera.position.x -= 0.1f;
        if (IsKeyDown(KEY_UP)) camera.position.z -= 0.1f;
        if (IsKeyDown(KEY_DOWN)) camera.position.z += 0.1f;
        if (IsKeyDown(KEY_PAGE_UP)) camera.position.y += 0.1f;
        if (IsKeyDown(KEY_PAGE_DOWN)) camera.position.y -= 0.1f;
        
        // Orbital mode only with right mouse button (as backup)
        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
            UpdateCamera(&camera, CAMERA_ORBITAL);
        }
        
        BeginDrawing();
            ClearBackground(BLACK);
            
            // Full screen for 3D view, 2D view will be overlaid in bottom left
            BeginMode3D(camera);
                
                // Draw coordinate grid for reference
                DrawGrid(10, 1.0f);
                
                // Draw coordinate axes for reference
                DrawLine3D((Vector3){0,0,0}, (Vector3){5,0,0}, RED);
                DrawLine3D((Vector3){0,0,0}, (Vector3){0,5,0}, GREEN);
                DrawLine3D((Vector3){0,0,0}, (Vector3){0,0,5}, BLUE);
                
                // Draw a reference point at the origin
                DrawSphere((Vector3){0,0,0}, 0.1f, YELLOW);
                
                // Draw each small cube that makes up the Rubik's cube
                for (int i = 0; i < SIZE; i++) {
                    for (int j = 0; j < SIZE; j++) {
                        for (int k = 0; k < SIZE; k++) {
                            Vector3 position = {
                                startPos + i * (cubeSize + gap),
                                startPos + j * (cubeSize + gap),
                                startPos + k * (cubeSize + gap)
                            };
                            
                            // Draw the cube with the corresponding color
                            
                        }
                    }
                }
                
            EndMode3D();
            
            // Draw 2D view overlay in bottom left corner
            // Background for 2D view
            DrawRectangle(
                startX - padding, 
                startY - padding, 
                cellSize * SIZE * 4 + padding * 2, 
                cellSize * SIZE * 3 + padding * 2, 
                ColorAlpha(DARKGRAY, 0.8f)
            );
            
            // Draw title for 2D view
            DrawText("2D Cube Layout", startX, startY - padding - 30, 20, WHITE);
            
            // Draw legend
            DrawText("UP", rectUp.x + rectUp.width/3, rectUp.y - 25, 20, WHITE);
            DrawText("LEFT", rectLeft.x + rectLeft.width/4, rectLeft.y - 25, 20, WHITE);
            //DrawText("FRONT", rectFront.x + rectFront.width/4, rectFront.y - 25, 20, WHITE);
            DrawText("RIGHT", rectRight.x + rectRight.width/4, rectRight.y - 25, 20, WHITE);
            DrawText("BACK", rectBack.x + rectBack.width/4, rectBack.y - 25, 20, WHITE);
            DrawText("DOWN", rectDown.x + rectDown.width/4, rectDown.y + rectDown.height + 5, 20, WHITE);
            
            // Draw 2D representation of all six faces
            
            // Draw UP face
            for (int y = 0; y < SIZE; y++) {
                for (int x = 0; x < SIZE; x++) {
                    Color cellColor = GetFaceColor(cube->color[FACE_UP][y][x]);
                    DrawRectangle(
                        rectUp.x + x * cellSize, 
                        rectUp.y + y * cellSize, 
                        cellSize - 2, cellSize - 2, 
                        cellColor
                    );
                }
            }
            
            // Draw LEFT face
            for (int y = 0; y < SIZE; y++) {
                for (int x = 0; x < SIZE; x++) {
                    Color cellColor = GetFaceColor(cube->color[FACE_LEFT][y][x]);
                    DrawRectangle(
                        rectLeft.x + x * cellSize, 
                        rectLeft.y + y * cellSize, 
                        cellSize - 2, cellSize - 2, 
                        cellColor
                    );
                }
            }
            
            // Draw FRONT face
            for (int y = 0; y < SIZE; y++) {
                for (int x = 0; x < SIZE; x++) {
                    Color cellColor = GetFaceColor(cube->color[FACE_FRONT][y][x]);
                    DrawRectangle(
                        rectFront.x + x * cellSize, 
                        rectFront.y + y * cellSize, 
                        cellSize - 2, cellSize - 2, 
                        cellColor
                    );
                }
            }
            
            // Draw RIGHT face
            for (int y = 0; y < SIZE; y++) {
                for (int x = 0; x < SIZE; x++) {
                    Color cellColor = GetFaceColor(cube->color[FACE_RIGHT][y][x]);
                    DrawRectangle(
                        rectRight.x + x * cellSize, 
                        rectRight.y + y * cellSize, 
                        cellSize - 2, cellSize - 2, 
                        cellColor
                    );
                }
            }
            
            // Draw BACK face 
            for (int y = 0; y < SIZE; y++) {
                for (int x = 0; x < SIZE; x++) {
                    Color cellColor = GetFaceColor(cube->color[FACE_BACK][y][x]);
                    DrawRectangle(
                        rectBack.x + x * cellSize, 
                        rectBack.y + y * cellSize, 
                        cellSize - 2, cellSize - 2, 
                        cellColor
                    );
                }
            }
            
            // Draw DOWN face
            for (int y = 0; y < SIZE; y++) {
                for (int x = 0; x < SIZE; x++) {
                    Color cellColor = GetFaceColor(cube->color[FACE_DOWN][y][x]);
                    DrawRectangle(
                        rectDown.x + x * cellSize, 
                        rectDown.y + y * cellSize, 
                        cellSize - 2, cellSize - 2, 
                        cellColor
                    );
                }
            }
            
            // Draw face outlines for better visibility
            DrawRectangleLinesEx(rectUp, 2, WHITE);
            DrawRectangleLinesEx(rectLeft, 2, WHITE);
            DrawRectangleLinesEx(rectFront, 2, WHITE);
            DrawRectangleLinesEx(rectRight, 2, WHITE);
            DrawRectangleLinesEx(rectBack, 2, WHITE);
            DrawRectangleLinesEx(rectDown, 2, WHITE);
            
            // Draw instructions
            DrawText("Tasto sinistro: Ruota la visuale", 10, 10, 20, WHITE);
            DrawText("Rotella: Zoom avanti/indietro", 10, 40, 20, WHITE);
            DrawText("Tasto destro: Modalità orbitale alternativa", 10, 70, 20, WHITE);
            DrawText("Frecce/PgUp/PgDn: Muovi camera", 10, 100, 20, WHITE);
            
            // Display camera position
            DrawText(TextFormat("Camera: X=%.1f Y=%.1f Z=%.1f", 
                     camera.position.x, camera.position.y, camera.position.z), 
                     10, 130, 20, WHITE);
            
            DrawFPS(10, 160);
            
        EndDrawing();
    }
    
    CloseWindow();
}
