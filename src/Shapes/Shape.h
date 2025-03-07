#pragma once

class Camera;
class Shader;

class Shape
{
public:
	virtual void Render(Shader* ourShader, Camera* camera)
	{

	}
	virtual void Free()
	{

	}
};