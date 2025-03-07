#pragma once

#include <map>

struct Texture2D
{
    unsigned char* data;
    int width;
    int height;
    int nrChannels;
    unsigned int* id;
};

class ResourceLoader
{
public:
    static ResourceLoader& GetInstance()
    {
        static ResourceLoader    instance; // Guaranteed to be destroyed.
        // Instantiated on first use.
        return instance;
    }

public:
    unsigned int* GetTexture(const char* texture, int& inWidth, int& inHeight, int& inNrChannels);

    void Free();

private:

	std::map<const char*, Texture2D> textures;
};

