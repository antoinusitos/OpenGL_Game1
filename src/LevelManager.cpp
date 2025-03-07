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

//Type:x,y,z:scale:texture
//Cube:0.0f,-1.50f,0.0f:1.0f:dirt
void LevelManager::LoadLevel()
{
	std::ifstream file("LVL2.txt");
	std::string str;
	std::cout << "Loading LVL.txt...:" << std::endl;

	//TEST

	int sizeX = 40;
	int sizeZ = 40;
	
	int minX = 999999;
	int maxX = -999999;
	int minZ = 999999;
	int maxZ = -999999;

	std::string texture = "grass";
	for (int i = 0; i < sizeX; i++)
	{
		for (int j = 0; j < sizeZ; j++)
		{
			WorldManager::GetInstance().AddShape(new Cube(glm::vec3(i - (sizeX / 2), -1.5f, -j), texture.c_str()));
			//std::cout << "Loaded :" << (i * sizeZ + j) << "/" << (sizeX * sizeZ) << std::endl;

			if (i - (sizeX / 2) < minX)
			{
				minX = i - (sizeX / 2);
			}
			else if (i - (sizeX / 2) > maxX)
			{
				maxX = i - (sizeX / 2);
			}
			if (-j < minZ)
			{
				minZ = -j;
			}
			else if (-j > maxX)
			{
				maxZ = -j;
			}
		}
	}

	WorldManager::GetInstance().xMin = minX;
	WorldManager::GetInstance().xMax = maxX;
	WorldManager::GetInstance().zMin = minZ;
	WorldManager::GetInstance().zMax = maxZ;

	//TEST

	return;

	while (std::getline(file, str))
	{
		if (str.find("//") != std::string::npos || str.empty())
		{
			continue;
		}

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

		std::string scale = str.substr(0, str.find(delimiter));;

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
			newShape = new Plane(glm::vec3(x, y, z), texture.c_str(), true, true, std::stof(scale));
		}

		WorldManager::GetInstance().AddShape(newShape);
	}
}