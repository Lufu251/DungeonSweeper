#include <raylib.h>

#include <scene_manager.hpp>

int main(void){
    // Initialization -------------------------------------------------------------------
    // Screen dimensions
    const int screenWidth = 800;
    const int screenHeight = 800;
    //SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "Raylib Template");
    SetExitKey(KEY_NULL);
    SetTargetFPS(60);

    SceneManager scene;

    // RunScene -------------------------------------------------------------------------
    while (!WindowShouldClose()){
        scene.Run();

        if(scene.shouldClose){
            CloseWindow(); // Close window and OpenGL context
        }
    }

    

    return 0;
}