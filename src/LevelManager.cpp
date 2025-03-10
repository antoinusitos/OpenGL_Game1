#include "LevelManager.h"

#include "Entity.h"
#include "Shapes/Cube.h"
#include "Shapes/Plane.h"
#include "WorldManager.h"

#include <iostream>
#include <fstream>
#include <string>

LevelManager::LevelManager()
{

}

//Type:x,y,z:scale:texture
//Cube:0.0f,-1.50f,0.0f:1.0f:dirt
void LevelManager::LoadLevel(const char* levelName)
{
	std::ifstream file(levelName);
	std::string str;
	std::cout << "Loading " << levelName << " ..." << std::endl;

	while (std::getline(file, str))
	{
		if (str.find("//") != std::string::npos || str.empty())
		{
			continue;
		}

		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;
		float rotX = 0.0f;
		float rotY = 0.0f;
		float rotZ = 0.0f;

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
		token = str.substr(0, str.find(delimiter));

		std::string rot = token;
		std::string rotDelimiter = ",";
		for (int i = 0; i < 3; i++)
		{
			std::string rotSingle = rot.substr(0, str.find(rotDelimiter));
			if (i == 0)
			{
				rotX = std::stof(rotSingle);
			}
			else if (i == 1)
			{
				rotY = std::stof(rotSingle);
			}
			else if (i == 2)
			{
				rotZ = std::stof(rotSingle);
			}
			rot.erase(0, rot.find(rotDelimiter) + rotDelimiter.length());
		}

		str.erase(0, str.find(delimiter) + delimiter.length());

		std::string scale = str.substr(0, str.find(delimiter));;

		str.erase(0, str.find(delimiter) + delimiter.length());

		Entity* entity = new Entity(glm::vec3(x, y, z));
		entity->rotation = glm::vec3(rotX, rotY, rotZ);

		Shape* newShape = nullptr;
		if (type == "Cube")
		{
			std::string texture = str;
			newShape = new Cube(texture.c_str());
		}
		else if (type == "Plane")
		{
			std::string texture = str;
			newShape = new Plane(texture.c_str(), true, false, std::stof(scale));
		}
		else if (type == "Billboard")
		{
			std::string texture = str;
			newShape = new Plane(texture.c_str(), true, true, std::stof(scale));
		}

		entity->shape = newShape;
		WorldManager::GetInstance().AddEntity(entity);
	}
}