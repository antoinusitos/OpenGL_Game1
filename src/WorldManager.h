#pragma once

#include <list>

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

    const std::list<Entity*> GetEntities() const;

    void Render(Shader* ourShader, Camera* camera);

    int xMin = -3;
    int xMax = 3;
    int zMin = -10;
    int zMax = 0;

private:
    std::list<Entity*> entities;
};

