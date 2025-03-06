#include "MusicManager.h"

#include <iostream>

MusicManager::MusicManager()
{
	result = ma_engine_init(NULL, &engine);
	if (result != MA_SUCCESS)
	{
		std::cout << "Failed to initialize Mini Audio Engine" << std::endl;
	}

	initialized = true;
}

void MusicManager::PlaySound(const char* soundPath)
{
	if (!initialized)
	{
		return;
	}

	ma_engine_play_sound(&engine, soundPath, NULL);
}