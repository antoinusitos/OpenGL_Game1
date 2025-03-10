#include "../Camera.h"
#include "../Shader.h"

class Shape
{
public:
	virtual void Render(Shader* ourShader, Camera* camera, glm::vec3 rotationIn)
	{

	}
	virtual void Free()
	{

	}
};