#pragma once

#include <raylib.h>
#include <lfgl.hpp>

enum class SceneType {
    NONE,
    MENU,
    PLAY
};

struct Scene {
    virtual ~Scene() = default;

    // Called once when the scene becomes active
    virtual void Enter() = 0;

    // Called every frame to update scene logic
    virtual void Update() = 0;

    // Called every frame to draw scene elements
    virtual void Draw() = 0;

    // Called once when the scene is no longer active (e.g., transitioning to another scene)
    virtual void Exit() = 0;

};

struct MenuScene : public Scene{
    // Member variables specific to the MenuScene
    lfgl::Button playButton;

    void Enter() override {
        TraceLog(LOG_INFO, "MenuScene: Entered");

        playButton.setPosition({100, 100});
        playButton.setSize({200, 50});
    }

    void Update() override {
        playButton.update(false, false);
    }

    void Draw() override {
        BeginDrawing();
            ClearBackground(DARKGREEN); // Clear the main screen background
            DrawText("Menu", 20, 20, 20, YELLOW);

            DrawRectangleRec(playButton.mRect, WHITE);

        EndDrawing();
    }

    void Exit() override {
        TraceLog(LOG_INFO, "MenuScene: Exited");
        // Clean up menu-specific resources if any
    }
};

struct PlayScene  :  public Scene{
    // Member variables specific to the PlayScene
    bool showDebug = true;

    // Declare RenderTexture2D objects
    RenderTexture2D gameRenderTexture;
    RenderTexture2D debugRenderTexture;
    RenderTexture2D guiRenderTexture;

    void Enter() override {
        TraceLog(LOG_INFO, "PlayScene: Entered");
        // Initialize RenderTexture2D objects
        // Make sure they have the same dimensions as your screen or desired render area
        gameRenderTexture = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
        debugRenderTexture = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
        guiRenderTexture = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
    }

    void Update() override {
        if (IsKeyPressed(KEY_D)) showDebug = !showDebug;
    }

    void Draw() override {
        // Draw to Textures ----------------------------------------------
        // Render to gameRenderTexture
        BeginTextureMode(gameRenderTexture);
            ClearBackground(DARKBLUE);
            

        EndTextureMode();

        // Render to debugRenderTexture
        BeginTextureMode(debugRenderTexture);
            ClearBackground(BLANK);
            if (showDebug)
            {
                // Draw debug elements
                DrawFPS(GetScreenWidth() - 100, 10);
            }
        EndTextureMode();

        // Render to guiRenderTexture
        BeginTextureMode(guiRenderTexture);
            ClearBackground(BLANK);
            DrawText("Play", 20, 20, 20, YELLOW);

        EndTextureMode();
        
        // Draw to Screen ----------------------------------------------
        BeginDrawing();
            ClearBackground(RAYWHITE); // Clear the main screen background

            // Draw game texture
            DrawTextureRec(gameRenderTexture.texture, { 0, 0, (float)gameRenderTexture.texture.width, (float)-gameRenderTexture.texture.height }, { 0, 0 }, WHITE);

            // Draw debug texture (on top of game)
            DrawTextureRec(debugRenderTexture.texture, { 0, 0, (float)debugRenderTexture.texture.width, (float)-debugRenderTexture.texture.height }, { 0, 0 }, WHITE);

            // Draw GUI texture (on top of everything)
            DrawTextureRec(guiRenderTexture.texture, { 0, 0, (float)guiRenderTexture.texture.width, (float)-guiRenderTexture.texture.height }, { 0, 0 }, WHITE);
            
            // Draw directly to screen

        EndDrawing();
    }

    void Exit() override {
        TraceLog(LOG_INFO, "PlayScene: Exited");
        // Unload textures
        UnloadRenderTexture(gameRenderTexture);
        UnloadRenderTexture(debugRenderTexture);
        UnloadRenderTexture(guiRenderTexture);
    }
};