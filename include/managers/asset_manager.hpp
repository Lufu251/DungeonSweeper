#pragma once

#include <raylib.h>
#include <string>
#include <map>
#include <filesystem>
#include <iostream>

class AssetManager{
    public:
    AssetManager(){}
    ~AssetManager(){
        UnloadAllAssets();
    }

    void SetAssetsPath(std::string folderName){
        size_t searchDepth = 4; // Limit on how many parent directories should be searched
        std::filesystem::path currentPath = GetWorkingDirectory();

        TraceLog(LOG_INFO, ("AssetManager: Searching " + folderName + " directory").c_str());

        for (size_t i = 0; i < searchDepth; i++){

            // Check if directory is in the currentPath
            if (std::filesystem::exists(currentPath / folderName) && std::filesystem::is_directory(currentPath / folderName)) {
                assetPath = currentPath; // Directory found
                break; // Break for loop
            }

            currentPath = currentPath.parent_path(); // Move up one level
        }

        // Check if directory has been found
        if(assetPath == ""){
            TraceLog(LOG_WARNING, ("AssetManager: Failed to find directory " + folderName).c_str());
        }
        else{
            TraceLog(LOG_INFO, ("AssetManager: Path found " + assetPath).c_str());
        }
    }

    void LoadTexture(const std::string& name, const std::string& fileName) {
        Texture2D texture = ::LoadTexture(fileName.c_str());

        // Check if loading was successfull
        if (IsTextureValid(texture)) {
            textures[name] = texture;
        } else {
            TraceLog(LOG_WARNING, ("AssetManager: Failed to load texture " + fileName).c_str());
        }
    }

    void LoadSound(const std::string& name, const std::string& fileName) {
        Sound sound = ::LoadSound(fileName.c_str());

        // Check if loading was successfull
        if (IsSoundValid(sound)) {
            sounds[name] = sound;
        } else {
            TraceLog(LOG_WARNING, ("AssetManager: Failed to load sound " + fileName).c_str());
        }
    }

    void LoadFont(const std::string& name, const std::string& fileName) {
        Font font = ::LoadFont(fileName.c_str());
        
        // Check if loading was successfull
        if (IsFontValid(font)) {
            fonts[name] = font;
        } else {
            TraceLog(LOG_WARNING, ("AssetManager: Failed to load font " + fileName).c_str());
        }
    }

    Texture2D& GetTexture(const std::string& name) {
        if (IsTextureValid(textures.at(name))) {
            return textures[name];
        } else {
            std::cerr << "AssetManager: Failed to find texture " << name << std::endl;
            return textures[name];
        }
    }

    Sound& GetSound(const std::string& name) {
        if (IsSoundValid(sounds.at(name))) {
            return sounds[name];
        } else {
            std::cerr << "AssetManager: Failed to find sound " << name  << std::endl;
            return sounds[name];
        }
    }

    Font& GetFont(const std::string& name) {
        if (IsFontValid(fonts.at(name))) {
            return fonts[name];
        } else {
            std::cerr << "AssetManager: Failed to find font" << name << std::endl;
            return fonts[name];
        }
    }

    void UnloadAllAssets() {
        for (auto const& [name, texture] : this->textures) {
            ::UnloadTexture(texture);
        }
        this->textures.clear();

        for (auto const& [name, sound] : this->sounds) {
            ::UnloadSound(sound);
        }
        this->sounds.clear();

        for (auto const& [name, font] : this->fonts) {
            ::UnloadFont(font);
        }
        this->fonts.clear();

        TraceLog(LOG_INFO, "All assets unloaded.");
    }

    private:
    // Path to the asset folder
    std::string assetPath;

    // --- Asset Storage ---
    std::map<std::string, Texture2D> textures;
    std::map<std::string, Sound> sounds;
    std::map<std::string, Font> fonts;
};