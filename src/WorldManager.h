#pragma once

#include <list>

class Camera;
class Shader;
class Shape;

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

    void AddShape(Shape* newShape);

    const std::list<Shape*> GetShapes() const;

    void Render(Shader* ourShader, Camera* camera);

    int xMin = -3;
    int xMax = 3;
    int zMin = -10;
    int zMax = 0;

private:
    std::list<Shape*> shapes;
};

