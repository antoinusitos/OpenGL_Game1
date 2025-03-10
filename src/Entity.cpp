#include "Entity.h"

#include "Camera.h"
#include "Shader.h"
#include "Shapes/Shape.h"

Entity::Entity(glm::vec3 positionIn)
{
	position = positionIn;
}

void Entity::Render(Shader* ourShader, Camera* camera)
{
	if (shape)
	{
		shape->Render(ourShader, camera, position, rotation);
	}
}

void Entity::Free()
{
	if (shape)
	{
		shape->Free();
	}
}