#include <glad/glad.h>
#include <GLFW/glfw3.h>
/*#define STB_IMAGE_IMPLEMENTATION
#include "utilities/stb_image.h"*/

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "utilities/shader_s.h"
#include "Camera.h"
#include "Cube.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

// settings
const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;

// timing
float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 1.0f));
float lastX = SCR_WIDTH / 2;
float lastY = SCR_HEIGHT / 2;
bool firstMouse = true;

int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Game1", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);

	// build and compile our shader zprogram
	// ------------------------------------
	Shader* ourShader = new Shader("src/3.3.coordinate_system.vs", "src/3.3.coordinate_system.fs");

	glm::vec3 cubePositions[] = {
	//dirt
		glm::vec3(0.0f,  -1.50f,  0.0f),
		glm::vec3(0.0f,  -1.50f,  -1.0f),
		glm::vec3(0.0f,  -1.50f,  -2.0f),
		glm::vec3(0.0f,  -1.50f,  -3.0f),
		glm::vec3(0.0f,  -1.50f,  -4.0f),
		glm::vec3(0.0f,  -1.50f,  -5.0f),
		glm::vec3(0.0f,  -1.50f,  -6.0f),
		glm::vec3(0.0f,  -1.50f,  -7.0f),
		glm::vec3(0.0f,  -1.50f,  -8.0f),
		glm::vec3(0.0f,  -1.50f,  -9.0f),
		glm::vec3(0.0f,  -1.50f,  -10.0f),
	};

	Cube* cubes[] = {
		//dirt
		new Cube(glm::vec3(0.0f,  -1.50f,  0.0f), "Textures/dirt.png"),
		new Cube(glm::vec3(0.0f,  -1.50f,  -1.0f), "Textures/dirt.png"),
		new Cube(glm::vec3(0.0f,  -1.50f,  -2.0f), "Textures/dirt.png"),
		new Cube(glm::vec3(0.0f,  -1.50f,  -3.0f), "Textures/dirt.png"),
		new Cube(glm::vec3(0.0f,  -1.50f,  -4.0f), "Textures/dirt.png"),
		new Cube(glm::vec3(0.0f,  -1.50f,  -5.0f), "Textures/dirt.png"),
		new Cube(glm::vec3(0.0f,  -1.50f,  -6.0f), "Textures/dirt.png"),
		new Cube(glm::vec3(0.0f,  -1.50f,  -7.0f), "Textures/dirt.png"),
		new Cube(glm::vec3(0.0f,  -1.50f,  -8.0f), "Textures/dirt.png"),
		new Cube(glm::vec3(0.0f,  -1.50f,  -9.0f), "Textures/dirt.png"),
		new Cube(glm::vec3(0.0f,  -1.50f,  -10.0f), "Textures/dirt.png"),

		//grass
		new Cube(glm::vec3(-1.0f,  -1.50f,  0.0f), "Textures/grass.png"),
		new Cube(glm::vec3(-1.0f,  -1.50f,  -1.0f), "Textures/grass.png"),
		new Cube(glm::vec3(-1.0f,  -1.50f,  -2.0f), "Textures/grass.png"),
		new Cube(glm::vec3(-1.0f,  -1.50f,  -3.0f), "Textures/grass.png"),
		new Cube(glm::vec3(-1.0f,  -1.50f,  -4.0f), "Textures/grass.png"),
		new Cube(glm::vec3(-1.0f,  -1.50f,  -5.0f), "Textures/grass.png"),
		new Cube(glm::vec3(-1.0f,  -1.50f,  -6.0f), "Textures/grass.png"),
		new Cube(glm::vec3(-1.0f,  -1.50f,  -7.0f), "Textures/grass.png"),
		new Cube(glm::vec3(-1.0f,  -1.50f,  -8.0f), "Textures/grass.png"),
		new Cube(glm::vec3(-1.0f,  -1.50f,  -9.0f), "Textures/grass.png"),
		new Cube(glm::vec3(-1.0f,  -1.50f,  -10.0f), "Textures/grass.png"),

		new Cube(glm::vec3(1.0f,  -1.50f,  0.0f), "Textures/grass.png"),
		new Cube(glm::vec3(1.0f,  -1.50f,  -1.0f), "Textures/grass.png"),
		new Cube(glm::vec3(1.0f,  -1.50f,  -2.0f), "Textures/grass.png"),
		new Cube(glm::vec3(1.0f,  -1.50f,  -3.0f), "Textures/grass.png"),
		new Cube(glm::vec3(1.0f,  -1.50f,  -4.0f), "Textures/grass.png"),
		new Cube(glm::vec3(1.0f,  -1.50f,  -5.0f), "Textures/grass.png"),
		new Cube(glm::vec3(1.0f,  -1.50f,  -6.0f), "Textures/grass.png"),
		new Cube(glm::vec3(1.0f,  -1.50f,  -7.0f), "Textures/grass.png"),
		new Cube(glm::vec3(1.0f,  -1.50f,  -8.0f), "Textures/grass.png"),
		new Cube(glm::vec3(1.0f,  -1.50f,  -9.0f), "Textures/grass.png"),
		new Cube(glm::vec3(1.0f,  -1.50f,  -10.0f), "Textures/grass.png"),
	};

	// tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
	// -------------------------------------------------------------------------------------------
	ourShader->use();
	ourShader->setInt("texture1", 0);

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// input
		// -----
		processInput(window);

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// activate shader
		ourShader->use();

		// create transformations
		// view = camera position
		ourShader->setMat4("view", camera.GetViewMatrix());
		// projection = Camera info (fov, near, far)
		glm::mat4 projection = glm::perspective(glm::radians(camera.Fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		ourShader->setMat4("projection", projection);

		for (unsigned int i = 0; i < sizeof(cubes) / sizeof(cubes[0]); i++)
		{
			cubes[i]->Render(ourShader);
		}

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	for (unsigned int i = 0; i < 10; i++)
	{
		cubes[i]->Free();
	}

	delete ourShader;

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}