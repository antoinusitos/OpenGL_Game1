#pragma once

#include <map>

struct Texture2D
{
    unsigned char* data;
    int width;
    int height;
    int nrChannels;

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
	void GetTexture(const char* texture, int& inWidth, int& inHeight, int& inNrChannels);

    void Free();

private:

	std::map<const char*, Texture2D> textures;
};

