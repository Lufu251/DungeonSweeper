#include <scenes.hpp>

void VictoryScene::Enter() {
    TraceLog(LOG_INFO, "VictoryScene: Entered");

    playagainButton.setPosition({300, 250});
    playagainButton.setSize({200, 50});

    exitButton.setPosition({300, 450});
    exitButton.setSize({200, 50});
}

void VictoryScene::Update() {
    playagainButton.update(false, false);
    exitButton.update(false, false);
}

void VictoryScene::Draw() {
    BeginDrawing();
        ClearBackground(DARKGREEN); // Clear the main screen background
        DrawText("Victory", 20, 20, 20, YELLOW);

        DrawRectangleRec(exitButton.mRect, WHITE);
        DrawText("Exit", exitButton.mRect.x, exitButton.mRect.y, 20, BLACK);


        DrawRectangleRec(playagainButton.mRect, WHITE);
        DrawText("Play Again", playagainButton.mRect.x, playagainButton.mRect.y, 20, BLACK);

    EndDrawing();
}

void VictoryScene::Exit() {
    TraceLog(LOG_INFO, "VictoryScene: Exited");
    // Clean up menu-specific resources if any
}