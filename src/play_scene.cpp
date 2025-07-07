#include <scenes.hpp>

void PlayScene::Enter() {
    TraceLog(LOG_INFO, "PlayScene: Entered");

    // AssetManager
    assets.SetAssetsPath("assets");
    assets.LoadTexture("test_texture", "textures/test.psng");
    assets.LoadSound("test_texture", "textures/test.psng");
    assets.LoadFont("test_texture", "textures/test.psng");

    // Initialize RenderTexture2D objects
    // Make sure they have the same dimensions as your screen or desired render area
    gameRenderTexture = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
    debugRenderTexture = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
    guiRenderTexture = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());

    menuButton.setPosition({100, 100});
    menuButton.setSize({200, 50});
}

void PlayScene::Update() {
    if (IsKeyPressed(KEY_D)) showDebug = !showDebug;
    menuButton.update(false, false);
}

void PlayScene::Draw() {
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

        DrawRectangleRec(menuButton.mRect, WHITE);
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

void PlayScene::Exit() {
    TraceLog(LOG_INFO, "PlayScene: Exited");
    // Unload textures
    UnloadRenderTexture(gameRenderTexture);
    UnloadRenderTexture(debugRenderTexture);
    UnloadRenderTexture(guiRenderTexture);

    // Unload all Assets
    assets.UnloadAllAssets();
}