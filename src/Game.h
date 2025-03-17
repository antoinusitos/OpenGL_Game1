#pragma once

#include <string>

class Camera;
class Shader;

struct GLFWwindow;

class Game
{
public:
    Game();

	void Run();

	GLFWwindow* window = nullptr;

	// settings
	const unsigned int SCR_WIDTH = 1920;
	const unsigned int SCR_HEIGHT = 1080;

	void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	void processInput(GLFWwindow* window);
	void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

private:
	// camera
	Camera* camera;
	float lastX = SCR_WIDTH / 2;
	float lastY = SCR_HEIGHT / 2;
	bool firstMouse = true;
	const bool useOrbit = true;

	Shader* ourShader;

	//EDITOR
	const bool editMode = true;
	bool hasClicked = false;
	bool hasRightClicked = false;
	bool hasTextureClicked = false;
	bool hasSaved = false;
	std::string editorTextures[2] = { "grass", "dirt" };
	int textureIndex = 0;
};

