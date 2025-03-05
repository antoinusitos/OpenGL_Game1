#pragma once

#define STB_IMAGE_IMPLEMENTATION
#include "utilities/stb_image.h"

class Shape
{
public:
	virtual void Render(Shader* ourShader, Camera camera)
	{

	}
	virtual void Free()
	{

	}
};