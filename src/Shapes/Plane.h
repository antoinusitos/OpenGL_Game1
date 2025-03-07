#pragma once

#include "Shape.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

class Camera;
class Shader;

class Plane : public Shape
{
public:
	glm::vec3 position;

	unsigned int VBO, VAO, EBO;
	unsigned int texture1;

	bool flipped = false;
	bool billboarded = true;
	float scale = 1.0f;

	Plane(glm::vec3 positionIn, const char* texture, bool flip = false, bool billboard = true, float inScale = 1.0f);

	void Render(Shader* ourShader, Camera* camera) override;

	void Free() override;
};