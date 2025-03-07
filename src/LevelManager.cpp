#include "LevelManager.h"

#include "Shapes/Cube.h"
#include "Shapes/Plane.h"
#include "WorldManager.h"

#include <iostream>
#include <fstream>
#include <string>

LevelManager::LevelManager()
{

}

void LevelManager::LoadLevel()
{
	std::ifstream file("LVL.txt");
	std::string str;
	std::cout << "Loading LVL.txt...:" << std::endl;
	while (std::getline(file, str))
	{
		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;

		std::string delimiter = ":";
		std::string token = str.substr(0, str.find(delimiter));
		std::string type = token;
		str.erase(0, str.find(delimiter) + delimiter.length());
		token = str.substr(0, str.find(delimiter));
		std::string pos = token;
		std::string posDelimiter = ",";
		for (int i = 0; i < 3; i++)
		{
			std::string posSingle = pos.substr(0, str.find(posDelimiter));
			if (i == 0)
			{
				x = std::stof(posSingle);
			}
			else if (i == 1)
			{
				y = std::stof(posSingle);
			}
			else if (i == 2)
			{
				z = std::stof(posSingle);
			}
			pos.erase(0, pos.find(posDelimiter) + posDelimiter.length());
		}

		str.erase(0, str.find(delimiter) + delimiter.length());

		Shape* newShape = nullptr;
		if (type == "Cube")
		{
			std::string texture = "Textures/" + str + ".png";
			newShape = new Cube(glm::vec3(x, y, z), texture.c_str());
		}
		else if (type == "Plane")
		{
			std::string texture = "Textures/" + str + ".png";
			newShape = new Plane(glm::vec3(0.0f, -0.5f, -8.0f), texture.c_str(), true);
		}

		WorldManager::GetInstance().AddShape(newShape);
	}
}