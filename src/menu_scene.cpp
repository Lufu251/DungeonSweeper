#include <scenes.hpp>

void MenuScene::Enter() {
    TraceLog(LOG_INFO, "MenuScene: Entered");

    playButton.setPosition({300, 250});
    playButton.setSize({200, 50});

    exitButton.setPosition({300, 450});
    exitButton.setSize({200, 50});
}

void MenuScene::Update() {
    playButton.update(false, false);
    exitButton.update(false, false);
}

void MenuScene::Draw() {
    BeginDrawing();
        ClearBackground(DARKGREEN); // Clear the main screen background
        DrawText("Menu", 20, 20, 20, YELLOW);

        DrawRectangleRec(exitButton.mRect, WHITE);
        DrawText("Exit", exitButton.mRect.x, exitButton.mRect.y, 20, BLACK);

        DrawRectangleRec(playButton.mRect, WHITE);
        DrawText("Play", playButton.mRect.x, playButton.mRect.y, 20, BLACK);

    EndDrawing();
}

void MenuScene::Exit() {
    TraceLog(LOG_INFO, "MenuScene: Exited");
    // Clean up menu-specific resources if any
}