#include "WorldManager.h"

#include "Camera.h"
#include "Entity.h"
#include "Shader.h"

#include <iostream>

WorldManager::WorldManager()
{

}

void WorldManager::AddEntity(Entity* newEntity)
{
	entities.push_back(newEntity);
}

const std::list<Entity*> WorldManager::GetEntities() const
{
	return entities;
}

void WorldManager::Render(Shader* ourShader, Camera* camera)
{
	for (Entity* singleEntity: entities)
	{
		singleEntity->Render(ourShader, camera);
	}
}