#pragma once

class Shader;

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <map>
#include <string>

/// Holds all state information relevant to a character as loaded using FreeType
struct Character {
    unsigned int TextureID; // ID handle of the glyph texture
    glm::ivec2   Size;      // Size of glyph
    glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
    unsigned int Advance;   // Horizontal offset to advance to next glyph
};

class TextRendererManager
{
public:
    static TextRendererManager& GetInstance()
    {
        static TextRendererManager    instance; // Guaranteed to be destroyed.
        // Instantiated on first use.
        return instance;
    }

public:
    TextRendererManager();

    void RenderText(std::string text, float x, float y, float scale, glm::vec3 color);

    std::map<GLchar, Character> Characters;

    Shader* shader;

    unsigned int texture;

private:
    unsigned int VAO, VBO;
};

