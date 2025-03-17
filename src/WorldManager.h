#pragma once

#include <list>
#include <map>
#include <string>

class Camera;
class Entity;
class Shader;

class WorldManager
{
public:
    static WorldManager& GetInstance()
    {
        static WorldManager    instance; // Guaranteed to be destroyed.
        // Instantiated on first use.
        return instance;
    }

public:
    WorldManager();

    void AddEntity(Entity* newEntity);

    void AddTempCell(Entity* newEntity);

    //EDIT MODE
    void EditModeAddCell(Entity* newEntity);
    void EditModeRemoveCell(Entity* entity);

    void FillCells();
    void AddCell(int x, int z, Entity* newEntity);

    const std::list<Entity*> GetEntities() const;

    //std::list<Entity*> GetCells() const;

    Entity* GetEntityAt(int x, int z) const;

    void Render(Shader* ourShader, Camera* camera);

    void RemoveEntity(Entity* entity);

    const std::map<std::string, Entity*> GetCells() const;

    int xMin = 0;
    int xMax = 6;
    int zMin = 0;
    int zMax = 10;

private:
    std::list<Entity*> entities;
    std::list<Entity*> tempCells;
    //std::list<Entity*> cells;
    std::map<std::string, Entity*> cells;

};

