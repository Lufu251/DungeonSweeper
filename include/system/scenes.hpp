#pragma once

#include <raylib.h>
#include <lfgl.hpp>

#include <asset_manager.hpp>

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

    void Enter() override;

    void Update() override;

    void Draw() override;

    void Exit() override;
};

struct PlayScene  :  public Scene{
    // Member variables specific to the PlayScene
    bool showDebug = true;
    lfgl::Button menuButton;

    AssetManager assets;

    // Declare RenderTexture2D objects
    RenderTexture2D gameRenderTexture;
    RenderTexture2D debugRenderTexture;
    RenderTexture2D guiRenderTexture;

    void Enter() override;

    void Update() override;

    void Draw() override;

    void Exit() override;
};