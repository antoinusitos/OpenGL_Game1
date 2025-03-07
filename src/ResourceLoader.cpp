#include "ResourceLoader.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "utilities/stb_image.h"

#include <iostream>

unsigned int ResourceLoader::GetTexture(const char* texture, int& inWidth, int& inHeight, int& inNrChannels)
{
	auto foundTexture = textures.find(texture);
	if (foundTexture != textures.end())
	{
		std::cout << "found Texture:" << texture << std::endl;
		inWidth = foundTexture->second.width;
		inHeight = foundTexture->second.height;
		inNrChannels = foundTexture->second.nrChannels;
		return foundTexture->second.id;
	}
	unsigned int texture1;

        glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	
	std::string tex = "Textures/" + std::string(texture) + ".png";
	unsigned char* data = stbi_load(tex.c_str(), &inWidth, &inHeight, &inNrChannels, 0);
	if (data)
	{
		std::cout << "LOADED Texture:" << texture << std::endl;
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, inWidth, inHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		textures.insert({ texture, Texture2D { data, inWidth, inHeight, inNrChannels, texture1 }});
		return texture1;
	}
	else
	{
		std::cout << "Failed to load texture:" << texture << std::endl;
		return texture1;
	}
}

void ResourceLoader::Free()
{
	for (auto it = textures.begin(); it != textures.end(); ++it)
	{
		stbi_image_free(it->second.data);
	}
}
