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

    const int xMin = -3;
    const int xMax = 3;
    const int zMin = -10;
    const int zMax = 0;

private:
    std::list<Shape*> shapes;
};

