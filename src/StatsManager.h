#pragma once

#include <string>
#include <map>

class StatsManager
{
public:
    static StatsManager& GetInstance()
    {
        static StatsManager    instance; // Guaranteed to be destroyed.
        // Instantiated on first use.
        return instance;
    }

public:
    StatsManager();

    void StartRecord(std::string recordName);

    void EndRecord(std::string recordName);

private:
    std::map<std::string, float> records;

    bool printResults = false;

};

