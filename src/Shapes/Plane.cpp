#include "Plane.h"

#include <glm/gtc/matrix_transform.hpp>

#include "Shape.h"
#include "../Camera.h"
#include "../Shader.h"
#include "../ResourceLoader.h"
#include "Utilities/stb_image.h"

#include <iostream>

Plane::Plane(const char* texture, bool flip, bool billboard , float inScale)
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

	textureName = texture;

	flipped = flip;
	scale = inScale;
	billboarded = billboard;

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
	stbi_set_flip_vertically_on_load(flipped); // tell stb_image.h to flip loaded texture's on the y-axis.
	texture1 = ResourceLoader::GetInstance().GetTexture(texture);
}

void Plane::Render(Shader* ourShader, Camera* camera, glm::vec3 positionIn, glm::vec3 rotationIn)
{
	// bind textures on corresponding texture units
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, positionIn);
	if (billboarded)
	{
		model = glm::inverse(glm::lookAt(positionIn, camera->Position, glm::vec3(0.0f, 1.0f, 0.0f)));
	}
	model = glm::rotate(model, glm::radians(rotationIn.x), glm::vec3(1.0, 0.0, 0.0));
	model = glm::rotate(model, glm::radians(rotationIn.y), glm::vec3(0.0, 1.0, 0.0));
	model = glm::rotate(model, glm::radians(rotationIn.z), glm::vec3(0.0, 0.0, 1.0));

	model = glm::scale(model, glm::vec3(scale));
	ourShader->setMat4("model", model);

	// render container
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Plane::Free()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}
