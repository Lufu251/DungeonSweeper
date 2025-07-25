#pragma once

#include <raylib.h>
#include <memory>
#include <map>

#include <scenes.hpp>

class SceneManager {
    public:
    SceneManager() : currentSceneType(SceneType::NONE) {
        // Pre-create scenes or create on demand
        scenes[SceneType::MENU] = std::make_unique<MenuScene>();
        scenes[SceneType::PLAY] = std::make_unique<PlayScene>();
        scenes[SceneType::VICTORY] = std::make_unique<VictoryScene>();

        SetScene(SceneType::PLAY); // Start scene
    }

    ~SceneManager() {
        if (currentScene) {
            currentScene->Exit(); // Ensure the current scene exits properly
        }
    }

    void SetScene(SceneType newSceneType) {
        if (currentSceneType == newSceneType) {
            TraceLog(LOG_ERROR, "SceneManager: Attempted to set to the same scene type!");
            return; // Already in this scene
        }

        if (currentScene) {
            currentScene->Exit(); // Exit the old scene
        }

        currentSceneType = newSceneType;
        currentScene = scenes[newSceneType].get(); // Get raw pointer from unique_ptr

        if (currentScene) {
            currentScene->Enter(); // Enter the new scene
        } else {
            TraceLog(LOG_ERROR, "SceneManager: Attempted to set to a non-existent scene type!");
        }
    }

    void Run() {
        // Scene update
        if (currentScene) {
            currentScene->Update();
        }

        // Scene drawing
        if (currentScene) {
            currentScene->Draw();
        }

        // Scene switching
        SceneTransitionLogic();
    }

    private:
    SceneType currentSceneType;
    Scene* currentScene; // Raw pointer to the currently active scene
    std::map<SceneType, std::unique_ptr<Scene>> scenes; // Owns the scene objects

    // Manage scene transitions based on scene's internal state
    // Scene switching logic
    void SceneTransitionLogic(){
        switch (currentSceneType) {
            case SceneType::NONE : {
            } break;

            case SceneType::MENU : {
                MenuScene* menu = static_cast<MenuScene*>(currentScene);
                if (menu->playButton.mIsPressed) {
                    SetScene(SceneType::PLAY);
                }

                if(menu->exitButton.mIsPressed){
                    CloseWindow();
                }

            } break;

            case SceneType::PLAY: {
                PlayScene* play = static_cast<PlayScene*>(currentScene);
                // If ESC is pressed in PlayScene, go back to MenuScene
                if (play->menuButton.mIsPressed) {
                    SetScene(SceneType::MENU);
                }

                if (play->gameOver) {
                    SetScene(SceneType::MENU);
                }

                if(play->CheckVictory()){
                    SetScene(SceneType::VICTORY);
                }
            } break;

            case SceneType::VICTORY : {
                VictoryScene* menu = static_cast<VictoryScene*>(currentScene);
                if (menu->playagainButton.mIsPressed) {
                    SetScene(SceneType::PLAY);
                }

                if(menu->exitButton.mIsPressed){
                    CloseWindow();
                }

            } break;
        }
    }
};