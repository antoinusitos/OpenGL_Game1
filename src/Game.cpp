#include "Game.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"
#include "Entity.h"
#include "LevelManager.h"
#include "MusicManager.h"
#include "ResourceLoader.h"
#include "Shader.h"
#include "WorldManager.h"

#include <iostream>

Game::Game()
{

}

void Game::Run()
{
	MusicManager::GetInstance();

	MusicManager::GetInstance().PlaySound("Sounds/Background.wav");

	// build and compile our shader zprogram
	// ------------------------------------
	ourShader = new Shader("src/3.3.coordinate_system.vs", "src/3.3.coordinate_system.fs");

	LevelManager::GetInstance().LoadLevel();

	camera = new Camera(glm::vec3(0.0f, 0.0f, 0.0f));

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

		camera->Tick(deltaTime);

		// input
		// -----
		processInput(window);

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// configure global opengl state
		// -----------------------------
		glEnable(GL_DEPTH_TEST);

		// activate shader
		ourShader->use();

		// create transformations
		// view = camera position
		ourShader->setMat4("view", camera->GetViewMatrix());
		// projection = Camera info (fov, near, far)
		glm::mat4 projection = glm::perspective(glm::radians(camera->Fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		ourShader->setMat4("projection", projection);

		WorldManager::GetInstance().Render(ourShader, camera);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	for (Entity* singleEntity : WorldManager::GetInstance().GetEntities())
	{
		singleEntity->Free();
	}

	delete ourShader;

	ResourceLoader::GetInstance().Free();

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
}

void Game::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}
void Game::processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera->ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera->ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera->ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera->ProcessKeyboard(RIGHT, deltaTime);
}
void Game::mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	if (!useOrbit)
	{
		return;
	}

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

	camera->ProcessMouseMovement(xoffset, yoffset);
}
void Game::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera->ProcessMouseScroll(static_cast<float>(yoffset));
}