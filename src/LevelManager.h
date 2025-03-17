#pragma once

#include <string>

class LevelManager
{
public:
    static LevelManager& GetInstance()
    {
        static LevelManager    instance; // Guaranteed to be destroyed.
        // Instantiated on first use.
        return instance;
    }

public:
    LevelManager();

	void LoadLevel(const char* levelName, const char* levelPropsName, bool loadingLands = true);

    void EditorSaveLevel();

private:
    std::string lastOpenedLevel;
};

