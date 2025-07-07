#include <scenes.hpp>

void MenuScene::Enter() {
    TraceLog(LOG_INFO, "MenuScene: Entered");

    playButton.setPosition({100, 100});
    playButton.setSize({200, 50});
}

void MenuScene::Update() {
    playButton.update(false, false);
}

void MenuScene::Draw() {
    BeginDrawing();
        ClearBackground(DARKGREEN); // Clear the main screen background
        DrawText("Menu", 20, 20, 20, YELLOW);

        DrawRectangleRec(playButton.mRect, WHITE);

    EndDrawing();
}

void MenuScene::Exit() {
    TraceLog(LOG_INFO, "MenuScene: Exited");
    // Clean up menu-specific resources if any
}