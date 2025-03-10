#pragma once

#include <map>

struct Texture2D
{
    unsigned char* data;
    int width;
    int height;
    int nrChannels;
    unsigned int id;
};

struct ShapeInfo
{
    unsigned int VBO;
    unsigned int VAO;
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
    unsigned int GetTexture(const char* texture);

    const bool HasShape(const char* shape) const;
    void RegisterShape(const char* shape, unsigned int vao, unsigned int vbo);
    unsigned int GetShape(const char* shape) const;

    void Free();

private:

    std::map<const char*, Texture2D> textures;
    std::map<const char*, ShapeInfo> shapes;
};

