#include "StatsManager.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "TimeManager.h"

#include <iostream>

StatsManager::StatsManager()
{

}

void StatsManager::StartRecord(std::string recordName)
{
	auto foundRecord = records.find(recordName);
	if (foundRecord != records.end())
	{
		std::cout << "Cannot register record " + recordName + " it's already registered" << std::endl;
		return;
	}

	records.insert({recordName, (float)TimeManager::GetInstance().GetTime()});
}

void StatsManager::EndRecord(std::string recordName)
{
	if (records.find(recordName) == records.end())
	{
		std::cout << "Cannot end record " + recordName + " it's not registered" << std::endl;
		return;
	}

	float diff = (float)TimeManager::GetInstance().GetTime() - records.find(recordName)->second;
	if (printResults)
	{
		std::cout << recordName + " took " << (diff * 1000) << "ms" << std::endl;
	}

	records.erase(recordName);
}