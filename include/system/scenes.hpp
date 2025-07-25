#pragma once

#include <raylib.h>
#include <lfgl.hpp>
#include <game_objects.hpp>

#include <asset_manager.hpp>

enum class SceneType {
    NONE,
    MENU,
    PLAY,
    VICTORY
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
    lfgl::Button exitButton;

    void Enter() override;

    void Update() override;

    void Draw() override;

    void Exit() override;
};

struct PlayScene  :  public Scene{
    // Member variables specific to the PlayScene
    lfgl::Button menuButton;

    bool gameOver = false;

    AssetManager assets;

    Camera2D playCamera;

    // Game objects
    float tileSize = 24;
    GameBoard board;

    // Declare RenderTexture2D objects
    RenderTexture2D gameRenderTexture;
    RenderTexture2D guiRenderTexture;

    void Enter() override;

    void Update() override;

    void Draw() override;

    void Exit() override;

    void renderBoard();
    void uncoverTiles(size_t x, size_t y);
    bool CheckVictory();
};

struct VictoryScene : public Scene{
    // Member variables specific to the MenuScene
    lfgl::Button playagainButton;
    lfgl::Button exitButton;

    void Enter() override;

    void Update() override;

    void Draw() override;

    void Exit() override;
};