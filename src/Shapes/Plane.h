#pragma once

#include "Shape.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../ResourceLoader.h"

#include <iostream>

class Plane : public Shape
{
public:
	glm::vec3 position;

	unsigned int VBO, VAO, EBO;
	unsigned int texture1;

	float flipped = false;
	bool billboarded = true;
	float scale = 1.0f;

	Plane(glm::vec3 positionIn, const char* texture, bool flip = false, bool billboard = true, float inScale = 1.0f)
	{
		// set up vertex data (and buffer(s)) and configure vertex attributes
		// ------------------------------------------------------------------
		float vertices[] = {
			// positions          // texture coords
			 0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
			 0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
			-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
			-0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left 
		};
		unsigned int indices[] = {  // note that we start from 0!
			0, 1, 3,  // first Triangle
			1, 2, 3   // second Triangle
		};

		position = positionIn;
		flipped = flip;
		scale = inScale;

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		// texture coord attribute
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		// texture 1
		// ---------
		glGenTextures(1, &texture1);
		glBindTexture(GL_TEXTURE_2D, texture1);
		// set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_FILL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_FILL);
		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// load image, create texture and generate mipmaps
		int width, height, nrChannels;
		stbi_set_flip_vertically_on_load(flipped); // tell stb_image.h to flip loaded texture's on the y-axis.
		ResourceLoader::GetInstance().GetTexture(texture, width, height, nrChannels);
	}

	void Render(Shader* ourShader, Camera camera)
	{
		// bind textures on corresponding texture units
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, position);
		glm::vec3 forward = camera.Position - position;
		model = glm::inverse(glm::lookAt(position, camera.Position, glm::vec3(0.0f, 1.0f, 0.0f)));
		model = glm::scale(model, glm::vec3(scale));
		ourShader->setMat4("model", model);

		// render container
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

	void Free()
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	}
};