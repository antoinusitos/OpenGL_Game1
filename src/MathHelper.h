#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <iostream>

float static DotProduct(glm::vec3 a, glm::vec3 b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

glm::vec3 Normalize(glm::vec3 a)
{
    float length = sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
    return glm::vec3(a.x / length, a.y / length, a.z / length);
}