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

void WorldManager::AddTempCell(Entity* newEntity)
{
	tempCells.push_back(newEntity);
}

void WorldManager::FillCells()
{
	for (Entity* e : tempCells)
	{
		AddCell(e->position.x, e->position.z, e);
	}
}

void WorldManager::AddCell(int x, int z, Entity* newEntity)
{
	cells.insert({ x * zMax + z, newEntity});
}

const std::list<Entity*> WorldManager::GetEntities() const
{
	return entities;
}

Entity* WorldManager::GetEntityAt(int x, int z) const
{
	if (x < 0 || z < 0 || x > xMax || z > zMax)
	{
		return nullptr;
	}

	auto foundCell = cells.find(x * zMax + z);
	if (foundCell != cells.end())
	{
		return foundCell->second;
	}
	return nullptr;
}

void WorldManager::Render(Shader* ourShader, Camera* camera)
{
	for (Entity* singleEntity: entities)
	{
		singleEntity->Render(ourShader, camera);
	}
}