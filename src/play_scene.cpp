#include <scenes.hpp>

#include <random>
#include <queue>
#include <array>

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
    guiRenderTexture = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());

    menuButton.setPosition({static_cast<float>(GetScreenWidth()) - 110, 10});
    menuButton.setSize({100, 30});

    // Generate board
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 99);
    

    size_t bombPercentage = 8;
    board = GameBoard(8,8);
    for(size_t x=0; x< board.grid.getX(); x++){
        for(size_t y=0; y< board.grid.getY(); y++){
            size_t randomInt = dist(gen);
            std::cout << "Random: " << randomInt << std::endl;
            if(randomInt < bombPercentage){
                std::cout << "Bomb" << std::endl;
                board.grid(x,y).mBomb = true;

            }
        }
    }
    board.CalculateNumbers();

    playCamera.target = {(board.grid.getX() * tileSize) /2,(board.grid.getY() * tileSize) /2};
    playCamera.offset = {static_cast<float>(GetScreenWidth()) /2, static_cast<float>(GetScreenHeight()) /2};
    playCamera.zoom = 1.5f;
    playCamera.rotation = 0.0f;
}

void PlayScene::Update() {
    menuButton.update(false, false);

    if(IsMouseButtonPressed(0)){
        Vector2 mousePosition = GetScreenToWorld2D(GetMousePosition(), playCamera);
        std::cout << "x:" << mousePosition.x << " y:" << mousePosition.y << std::endl;
        int xGrid = mousePosition.x / tileSize;
        int yGrid = mousePosition.y / tileSize;

        if(!board.grid.isOutOfBound(xGrid, yGrid)){
            // If Bomb
            if(board.grid(xGrid, yGrid).mBomb){
                gameOver = true;
            } else {
               uncoverTiles(xGrid, yGrid);
            }
        }
    }
}

void PlayScene::Draw() {
    // Draw to Textures ----------------------------------------------
    // ------------ Render to gameRenderTexture ------------
    BeginTextureMode(gameRenderTexture);
        ClearBackground(DARKBLUE);

        BeginMode2D(playCamera);

            // Render Board
            renderBoard();

        EndMode2D();
    EndTextureMode();

    // ------------ Render to guiRenderTexture ------------
    BeginTextureMode(guiRenderTexture);
        ClearBackground(BLANK);
        DrawText("Play", 20, 20, 20, YELLOW);

        DrawRectangleRec(menuButton.mRect, WHITE);
        DrawText("Menu", menuButton.mRect.x, menuButton.mRect.y, 20, BLACK);
    EndTextureMode();
    
    // ------------ Draw to Screen ------------
    BeginDrawing();
        ClearBackground(RAYWHITE); // Clear the main screen background

        // Draw game texture
        DrawTextureRec(gameRenderTexture.texture, { 0, 0, (float)gameRenderTexture.texture.width, (float)-gameRenderTexture.texture.height }, { 0, 0 }, WHITE);

        // Draw GUI texture (on top of everything)
        DrawTextureRec(guiRenderTexture.texture, { 0, 0, (float)guiRenderTexture.texture.width, (float)-guiRenderTexture.texture.height }, { 0, 0 }, WHITE);
        
        // Draw directly to screen

    EndDrawing();
}

void PlayScene::Exit() {
    TraceLog(LOG_INFO, "PlayScene: Exited");
    // Unload textures
    UnloadRenderTexture(gameRenderTexture);
    UnloadRenderTexture(guiRenderTexture);

    // Unload all Assets
    assets.UnloadAllAssets();
}

void PlayScene::renderBoard(){
    for(size_t x=0; x< board.grid.getX(); x++){
        for(size_t y=0; y< board.grid.getY(); y++){
            Tile& currentTile = board.grid(x,y);

            size_t lineOffset = 1;
            size_t textOffset = 8;

            if(currentTile.open){
                
                DrawRectangleV({x * tileSize, y * tileSize}, {tileSize, tileSize}, WHITE);
                DrawRectangleLinesEx({x * tileSize, y * tileSize -lineOffset, tileSize +lineOffset, tileSize +lineOffset}, lineOffset, BLACK);
                std::string text = std::to_string(board.grid(x,y).count);
                DrawText(text.c_str(), x * tileSize + textOffset, y * tileSize + textOffset, 14, BLACK);
            } else {
                DrawRectangleV({x * tileSize, y * tileSize}, {tileSize, tileSize}, GRAY);
                DrawRectangleLinesEx({x * tileSize, y * tileSize -lineOffset, tileSize +lineOffset, tileSize +lineOffset}, lineOffset, BLACK);
            }

            if(currentTile.mBomb){
                DrawRectangleV({x * tileSize, y * tileSize}, {tileSize, tileSize}, RED);
            }
            
        }
    }
}

void PlayScene::uncoverTiles(size_t x, size_t y){

    if(board.grid(x,y).count > 0){
        board.grid(x,y).open = true;
    }else {
        std::array<std::pair<int, int>, 4> directions = {{{0,-1}, {1,0}, {0,1}, {-1,0}}};
        std::queue<std::pair<size_t, size_t>> q;
        q.push({x,y});

        while (!q.empty()) {
            // Get and remove the first element
            std::pair<size_t, size_t> current = q.front();
            q.pop();

            // Open current tile
            board.grid(current.first, current.second).open = true;

            // Start cycle
            for (auto& direction : directions) {
                std::pair<int, int> nPos{current.first + direction.first, current.second + direction.second};

                if(board.grid.isOutOfBound(nPos.first, nPos.second)){
                    continue;
                }

                if(board.grid(nPos.first, nPos.second).open){
                    continue;
                }

                if(board.grid(nPos.first, nPos.second).count == 0){
                    q.push({nPos.first, nPos.second});
                }
            }
        }
    }
}

bool PlayScene::CheckVictory(){
    bool victory = true;
    for(size_t x=0; x< board.grid.getX(); x++){
        for(size_t y=0; y< board.grid.getY(); y++){
            if(board.grid(x,y).open == false && !board.grid(x,y).mBomb){
                victory = false;
            }
        }
    }
    return victory;
}