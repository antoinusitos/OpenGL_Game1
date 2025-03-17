#include "WorldManager.h"

#include "Camera.h"
#include "Entity.h"
#include "Shader.h"

#include <iostream>
#include <string>

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

void WorldManager::EditModeAddCell(Entity* newEntity)
{
	int x = (int)newEntity->position.x;
	int z = (int)newEntity->position.z;
	if (cells.find(std::to_string(x) + "." + std::to_string(z)) != cells.end())
	{
		std::cout << "WARNING : already a cell at:" << x << " | " << z << std::endl;
		return;
	}

	AddCell(x, z, newEntity);
	if (x > xMax)
	{
		xMax = x;
	}
	if (z > zMax)
	{
		zMax = z;
	}
}

void WorldManager::EditModeRemoveCell(Entity* entity)
{
	int x = (int)entity->position.x;
	int z = (int)entity->position.z;
	cells.erase(std::to_string(x) + "." + std::to_string(z));
	entities.remove(entity);
	delete entity;
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
	cells.insert({ std::to_string(x) + "." + std::to_string(z), newEntity});
	newEntity->entityName = "Cell" + std::to_string(z * xMax + x);
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

	auto foundCell = cells.find(std::to_string(x) + "." + std::to_string(z));
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

void WorldManager::RemoveEntity(Entity* entity)
{
	Entity* cell = GetEntityAt(entity->position.x, entity->position.z);
	if (cell)
	{
		cell->child = nullptr;
	}
	entities.remove(entity);
	delete entity;
}

const std::map<std::string, Entity*> WorldManager::GetCells() const
{
	return cells;
}