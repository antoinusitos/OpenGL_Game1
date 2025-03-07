#pragma once

#include "utilities/miniaudio.h"

class MusicManager
{
public:
    static MusicManager& GetInstance()
    {
        static MusicManager    instance; // Guaranteed to be destroyed.
        // Instantiated on first use.
        return instance;
    }

public:
    MusicManager();

	void PlaySound(const char* soundPath);

private:
    ma_result result;
    ma_engine engine;

    bool initialized = false;

    bool muted = true;
};

