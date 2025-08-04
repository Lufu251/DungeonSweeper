#include <raylib.h>

#include <scene_manager.hpp>

int main(void){
    // Initialization -------------------------------------------------------------------
    // Screen dimensions
    const int screenWidth = 800;
    const int screenHeight = 800;
    
    //SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetConfigFlags(FLAG_WINDOW_HIGHDPI); // Enable High DPI scaling

    InitWindow(screenWidth, screenHeight, "Dungeon Sweeper");
    SetExitKey(KEY_NULL);
    SetTargetFPS(60);

    SceneManager scene;
    scene.SetScene(SceneType::MENU); // Start scene

    // RunScene -------------------------------------------------------------------------
    while (!WindowShouldClose()){
        scene.Run();

        if(scene.requestClose){
            CloseWindow(); // Close window and OpenGL context
        }
    }

    return 0;
}