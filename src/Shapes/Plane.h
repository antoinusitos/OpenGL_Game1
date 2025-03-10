#pragma once

#include "Shape.h"

class Camera;
class Shader;

class Plane : public Shape
{
public:
	unsigned int VBO, VAO, EBO;
	unsigned int texture1;

	bool flipped = false;
	bool billboarded = true;
	float scale = 1.0f;

	Plane(const char* texture, bool flip = false, bool billboard = true, float inScale = 1.0f);

	void Render(Shader* ourShader, Camera* camera, glm::vec3 positionIn, glm::vec3 rotationIn) override;

	void Free() override;
};