#include "graphic.h"
#include "cube.h"
#include <stdio.h>

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
    const float cubeSize = 1.0f;     // LARGER CUBE SIZE
    const float gap = 0.1f;          // LARGER GAP
    const float fullSize = SIZE * (cubeSize + gap);
    const float startPos = -fullSize/2 + cubeSize/2;
    
    // Initialize window and camera
    InitWindow(screenWidth, screenHeight, "Rubik's Cube");
    
    // Define camera to look at our 3D model
    Camera camera = { 0 };
    camera.position = (Vector3){ 6.0f, 6.0f, 6.0f };  // MOVE CAMERA FURTHER BACK
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };    // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };        // Camera up vector
    camera.fovy = 45.0f;                              // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;           // Camera projection type
    
    SetTargetFPS(60);                                 // Set target frames-per-second
    
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
        // Process input - add manual camera controls for debugging
        if (IsKeyDown(KEY_RIGHT)) camera.position.x += 0.1f;
        if (IsKeyDown(KEY_LEFT)) camera.position.x -= 0.1f;
        if (IsKeyDown(KEY_UP)) camera.position.z -= 0.1f;
        if (IsKeyDown(KEY_DOWN)) camera.position.z += 0.1f;
        if (IsKeyDown(KEY_PAGE_UP)) camera.position.y += 0.1f;
        if (IsKeyDown(KEY_PAGE_DOWN)) camera.position.y -= 0.1f;
        
        // Update camera (only if right mouse button is being held)
        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
            UpdateCamera(&camera, CAMERA_ORBITAL);
        }
        
        BeginDrawing();
            ClearBackground(BLACK);  // CHANGE TO BLACK for maximum contrast
            
            BeginMode3D(camera);
                
                // Draw coordinate grid for reference
                DrawGrid(10, 1.0f);
                
                // Draw coordinate axes for reference - MAKE THEM LONGER
                DrawLine3D((Vector3){0,0,0}, (Vector3){5,0,0}, RED);
                DrawLine3D((Vector3){0,0,0}, (Vector3){0,5,0}, GREEN);
                DrawLine3D((Vector3){0,0,0}, (Vector3){0,0,5}, BLUE);
                
                // Draw a reference point at the origin
                DrawSphere((Vector3){0,0,0}, 0.1f, YELLOW);
                
                // Draw each small cube that makes up the Rubik's cube
                for (int x = 0; x < SIZE; x++) {
                    float xPos = startPos + x * (cubeSize + gap);
                    
                    for (int y = 0; y < SIZE; y++) {
                        float yPos = startPos + y * (cubeSize + gap);
                        
                        for (int z = 0; z < SIZE; z++) {
                            float zPos = startPos + z * (cubeSize + gap);
                            
                            // Draw ALL cubes for debugging (remove outer layer check)
                            // Later you can add back: if (x == 0 || x == SIZE-1 || y == 0 || y == SIZE-1 || z == 0 || z == SIZE-1)
                            
                            // Draw the small cube at position with wireframe for better visibility
                            DrawCubeWires((Vector3){xPos, yPos, zPos}, cubeSize, cubeSize, cubeSize, WHITE);
                            
                            // Draw colored faces based on the cube's state with more offset
                            // Front face (FACE_FRONT)
                            if (z == SIZE-1) {
                                Color faceColor = GetFaceColor(cube->color[FACE_FRONT][y][x]);
                                DrawCubeV((Vector3){xPos, yPos, zPos + cubeSize/2 * 0.8f}, 
                                          (Vector3){cubeSize * 0.9f, cubeSize * 0.9f, 0.05f}, 
                                          faceColor);
                            }
                            
                            // Back face (FACE_BACK)
                            if (z == 0) {
                                Color faceColor = GetFaceColor(cube->color[FACE_BACK][y][SIZE-1-x]);
                                DrawCubeV((Vector3){xPos, yPos, zPos - cubeSize/2 * 0.8f}, 
                                          (Vector3){cubeSize * 0.9f, cubeSize * 0.9f, 0.05f}, 
                                          faceColor);
                            }
                            
                            // Right face (FACE_RIGHT)
                            if (x == SIZE-1) {
                                Color faceColor = GetFaceColor(cube->color[FACE_RIGHT][y][SIZE-1-z]);
                                DrawCubeV((Vector3){xPos + cubeSize/2 * 0.8f, yPos, zPos}, 
                                          (Vector3){0.05f, cubeSize * 0.9f, cubeSize * 0.9f}, 
                                          faceColor);
                            }
                            
                            // Left face (FACE_LEFT)
                            if (x == 0) {
                                Color faceColor = GetFaceColor(cube->color[FACE_LEFT][y][z]);
                                DrawCubeV((Vector3){xPos - cubeSize/2 * 0.8f, yPos, zPos}, 
                                          (Vector3){0.05f, cubeSize * 0.9f, cubeSize * 0.9f}, 
                                          faceColor);
                            }
                            
                            // Top face (FACE_UP)
                            if (y == 0) {
                                Color faceColor = GetFaceColor(cube->color[FACE_UP][z][x]);
                                DrawCubeV((Vector3){xPos, yPos - cubeSize/2 * 0.8f, zPos}, 
                                          (Vector3){cubeSize * 0.9f, 0.05f, cubeSize * 0.9f}, 
                                          faceColor);
                            }
                            
                            // Bottom face (FACE_DOWN)
                            if (y == SIZE-1) {
                                Color faceColor = GetFaceColor(cube->color[FACE_DOWN][SIZE-1-z][x]);
                                DrawCubeV((Vector3){xPos, yPos + cubeSize/2 * 0.8f, zPos}, 
                                          (Vector3){cubeSize * 0.9f, 0.05f, cubeSize * 0.9f}, 
                                          faceColor);
                            }
                        }
                    }
                }
                
            EndMode3D();
            
            DrawText("Arrow keys to move camera position", 10, 10, 20, WHITE);
            DrawText("Right-click and drag to rotate view", 10, 40, 20, WHITE);
            DrawText("PgUp/PgDn to change camera height", 10, 70, 20, WHITE);
            
            // Display camera position
            DrawText(TextFormat("Camera: X=%.1f Y=%.1f Z=%.1f", 
                     camera.position.x, camera.position.y, camera.position.z), 
                     10, screenHeight - 30, 20, WHITE);
            
            DrawFPS(screenWidth - 100, 10);
            
        EndDrawing();
    }
    
    CloseWindow();  // Close window and OpenGL context
}