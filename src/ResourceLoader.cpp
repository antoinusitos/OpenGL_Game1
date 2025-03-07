#include "ResourceLoader.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "utilities/stb_image.h"

#include <iostream>

void ResourceLoader::GetTexture(const char* texture, int& inWidth, int& inHeight, int& inNrChannels)
{
	auto foundTexture = textures.find(texture);
	if (foundTexture != textures.end())
	{
		inWidth = foundTexture->second.width;
		inHeight = foundTexture->second.height;
		inNrChannels = foundTexture->second.nrChannels;
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, inWidth, inHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, foundTexture->second.data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	unsigned char* data = stbi_load(texture, &inWidth, &inHeight, &inNrChannels, 0);
	if (data)
	{
		textures.insert({ texture, Texture2D { data, inWidth, inHeight, inNrChannels }});
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, inWidth, inHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture:" << texture << std::endl;
	}
}

void ResourceLoader::Free()
{
	for (auto it = textures.begin(); it != textures.end(); ++it)
	{
		stbi_image_free(it->second.data);
	}
}