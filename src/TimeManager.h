#pragma once

class TimeManager
{
public:
    static TimeManager& GetInstance()
    {
        static TimeManager    instance; // Guaranteed to be destroyed.
        // Instantiated on first use.
        return instance;
    }

public:
    TimeManager();

    void Tick();

	const float GetTime() const;
	const float GetDeltaTime() const;

private:
    float deltaTime = 0;
    float lastFrame = 0;
    float currentFrame = 0;
};

