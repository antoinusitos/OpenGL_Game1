#include "WorldManager.h"

#include "Camera.h"
#include "Shader.h"
#include "Shapes/Shape.h"

#include <iostream>

WorldManager::WorldManager()
{

}

void WorldManager::AddShape(Shape* newShape)
{
	shapes.push_back(newShape);
}

const std::list<Shape*> WorldManager::GetShapes() const
{
	return shapes;
}

void WorldManager::Render(Shader* ourShader, Camera* camera)
{
	for (Shape* singleShape : WorldManager::GetInstance().GetShapes())
	{
		singleShape->Render(ourShader, camera);
	}
}