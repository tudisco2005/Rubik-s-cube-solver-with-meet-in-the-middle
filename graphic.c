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
    const int screenWidth = 800;
    const int screenHeight = 600;
    const float cubeSize = 1.0f;
    const float gap = 0.1f;
    const float fullSize = SIZE * (cubeSize + gap);
    const float startPos = -fullSize/2 + cubeSize/2;
    
    // Initialize window and camera
    InitWindow(screenWidth, screenHeight, "Rubik's Cube");
    
    // Define camera to look at our 3D model
    Camera camera = { 0 };
    camera.position = (Vector3){ 6.0f, 6.0f, 6.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;
    
    // Variabili per il controllo della camera con il mouse
    Vector2 previousMousePosition = { 0.0f, 0.0f };
    bool isMouseDragging = false;
    float cameraDistance = sqrtf(powf(camera.position.x, 2) + 
                               powf(camera.position.y, 2) + 
                               powf(camera.position.z, 2));
    float cameraAngleY = 0.8f;  // Angolo iniziale orizzontale in radianti
    float cameraAngleX = 0.6f;  // Angolo iniziale verticale in radianti
    float mouseSensitivity = 0.003f;
    float zoomSensitivity = 0.5f;
    
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
        // Gestione zoom con rotella del mouse
        float wheelMove = GetMouseWheelMove();
        if (wheelMove != 0) {
            cameraDistance -= wheelMove * zoomSensitivity;
            if (cameraDistance < 3.0f) cameraDistance = 3.0f;  // Limite minimo per lo zoom
            if (cameraDistance > 20.0f) cameraDistance = 20.0f;  // Limite massimo per lo zoom
        }
        
        // Gestione rotazione con trascinamento del mouse
        Vector2 currentMousePosition = GetMousePosition();
        
        // Inizia il trascinamento quando si preme il tasto sinistro del mouse
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            previousMousePosition = currentMousePosition;
            isMouseDragging = true;
        }
        
        // Termina il trascinamento quando si rilascia il tasto del mouse
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            isMouseDragging = false;
        }
        
        // Calcola la rotazione durante il trascinamento
        if (isMouseDragging) {
            Vector2 mouseDelta = { 
                currentMousePosition.x - previousMousePosition.x,
                currentMousePosition.y - previousMousePosition.y 
            };
            
            cameraAngleY -= mouseDelta.x * mouseSensitivity;
            cameraAngleX -= mouseDelta.y * mouseSensitivity;
            
            // Limita l'angolo verticale per evitare rotazioni strane
            if (cameraAngleX < -1.5f) cameraAngleX = -1.5f;
            if (cameraAngleX > 1.5f) cameraAngleX = 1.5f;
            
            previousMousePosition = currentMousePosition;
        }
        
        // Aggiorna la posizione della camera basata sugli angoli
        camera.position.x = cosf(cameraAngleY) * cosf(cameraAngleX) * cameraDistance;
        camera.position.y = sinf(cameraAngleX) * cameraDistance;
        camera.position.z = sinf(cameraAngleY) * cosf(cameraAngleX) * cameraDistance;
        
        // Mantieni anche i controlli di tastiera esistenti per maggiore flessibilità
        if (IsKeyDown(KEY_RIGHT)) camera.position.x += 0.1f;
        if (IsKeyDown(KEY_LEFT)) camera.position.x -= 0.1f;
        if (IsKeyDown(KEY_UP)) camera.position.z -= 0.1f;
        if (IsKeyDown(KEY_DOWN)) camera.position.z += 0.1f;
        if (IsKeyDown(KEY_PAGE_UP)) camera.position.y += 0.1f;
        if (IsKeyDown(KEY_PAGE_DOWN)) camera.position.y -= 0.1f;
        
        // Modalità orbitale solo con il tasto destro del mouse (come backup)
        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
            UpdateCamera(&camera, CAMERA_ORBITAL);
        }
        
        BeginDrawing();
            ClearBackground(BLACK);
            
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
                for (int x = 0; x < SIZE; x++) {
                    float xPos = startPos + x * (cubeSize + gap);
                    
                    for (int y = 0; y < SIZE; y++) {
                        float yPos = startPos + y * (cubeSize + gap);
                        
                        for (int z = 0; z < SIZE; z++) {
                            float zPos = startPos + z * (cubeSize + gap);
                            
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
            
            // Aggiornamento istruzioni
            DrawText("Tasto sinistro: Ruota la visuale", 10, 10, 20, WHITE);
            DrawText("Rotella: Zoom avanti/indietro", 10, 40, 20, WHITE);
            DrawText("Tasto destro: Modalità orbitale alternativa", 10, 70, 20, WHITE);
            DrawText("Frecce/PgUp/PgDn: Muovi camera", 10, 100, 20, WHITE);
            
            // Display camera position
            DrawText(TextFormat("Camera: X=%.1f Y=%.1f Z=%.1f", 
                     camera.position.x, camera.position.y, camera.position.z), 
                     10, screenHeight - 30, 20, WHITE);
            
            DrawFPS(screenWidth - 100, 10);
            
        EndDrawing();
    }
    
    CloseWindow();
}