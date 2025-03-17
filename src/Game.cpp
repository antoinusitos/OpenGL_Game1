#include "Game.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"
#include "CombatManager.h"
#include "Entity.h"
#include "LevelManager.h"
#include "MusicManager.h"
#include "PlayerManager.h"
#include "ResourceLoader.h"
#include "Shader.h"
#include "Shapes/Cube.h"
#include "StatsManager.h"
#include "TextRendererManager.h"
#include "TimeManager.h"
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

	LevelManager::GetInstance().LoadLevel("LVL.txt", "LVL_PROPS.txt", true);

	camera = new Camera(glm::vec3(3.0f, -0.25f, 0.0f));
	camera->Yaw = 90;

	if (useOrbit)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	// tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
	// -------------------------------------------------------------------------------------------
	ourShader->use();
	ourShader->setInt("texture1", 0);

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		TimeManager::GetInstance().Tick();
		float deltaTime = TimeManager::GetInstance().GetDeltaTime();
		//StatsManager::GetInstance().StartRecord("Frame");
		//std::cout << "FPS " << (1 / deltaTime) << std::endl;

		//StatsManager::GetInstance().StartRecord("CombatManager::Tick");
		CombatManager::GetInstance().Tick(deltaTime);
		//StatsManager::GetInstance().EndRecord("CombatManager::Tick");

		//StatsManager::GetInstance().StartRecord("Camera::Tick");
		camera->Tick(deltaTime);
		//StatsManager::GetInstance().EndRecord("Camera::Tick");

		// input
		// -----
		//StatsManager::GetInstance().StartRecord("ProcessInput");
		processInput(window);
		//StatsManager::GetInstance().EndRecord("ProcessInput");

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
		//StatsManager::GetInstance().StartRecord("ShaderView");
		ourShader->setMat4("view", camera->GetViewMatrix());
		//StatsManager::GetInstance().EndRecord("ShaderView");
		// projection = Camera info (fov, near, far)
		//StatsManager::GetInstance().StartRecord("Projection");
		glm::mat4 projection = glm::perspective(glm::radians(camera->Fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		ourShader->setMat4("projection", projection);
		//StatsManager::GetInstance().EndRecord("Projection");

		//StatsManager::GetInstance().StartRecord("WorldRender");
		WorldManager::GetInstance().Render(ourShader, camera);
		//StatsManager::GetInstance().EndRecord("WorldRender");

		PlayerManager::GetInstance().Tick(deltaTime);

		//StatsManager::GetInstance().StartRecord("TextRender");

		if (editMode)
		{
			TextRendererManager::GetInstance().RenderText("Texture:" + editorTextures[textureIndex], 0, 48, 0.5f, glm::vec3(0,0,1));
		}


		TextRendererManager::GetInstance().RenderTexts();
		//StatsManager::GetInstance().EndRecord("TextRender");

		//StatsManager::GetInstance().StartRecord("SwapBuffers");
		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
		//StatsManager::GetInstance().EndRecord("SwapBuffers");

		//StatsManager::GetInstance().EndRecord("Frame");
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
	float deltaTime = TimeManager::GetInstance().GetDeltaTime();

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

	if (editMode)
	{
		if (!hasClicked && glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		{
			hasClicked = true;
			glm::vec3 cameraFront = camera->Front;
			glm::vec3 cameraPos = camera->Position + cameraFront;
			cameraPos.x = round(cameraPos.x);
			cameraPos.z = round(cameraPos.z);

			Entity* entity = new Entity(glm::vec3(cameraPos.x, -1.5f, cameraPos.z));
			entity->entityName = "EditCube";
			entity->shape = new Cube(editorTextures[textureIndex].c_str());
			WorldManager::GetInstance().AddEntity(entity);
			WorldManager::GetInstance().EditModeAddCell(entity);
		}
		else if (hasClicked && glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
		{
			hasClicked = false;
		}
		else if (!hasRightClicked && glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
		{
			hasRightClicked = true;
			glm::vec3 cameraFront = camera->Front;
			glm::vec3 cameraPos = camera->Position + cameraFront;
			cameraPos.x = round(cameraPos.x);
			cameraPos.z = round(cameraPos.z);

			Entity* e = WorldManager::GetInstance().GetEntityAt(cameraPos.x, cameraPos.z);
			if (e)
			{
				WorldManager::GetInstance().EditModeRemoveCell(e);
			}
		}
		else if (hasRightClicked && glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
		{
			hasRightClicked = false;
		}

		if (!hasTextureClicked && glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
		{
			hasTextureClicked = true;
			textureIndex++;
			if (textureIndex >= sizeof(editorTextures) / sizeof(editorTextures[0]))
			{
				textureIndex = 0;
			}
		}
		else if (hasTextureClicked && glfwGetKey(window, GLFW_KEY_T) == GLFW_RELEASE)
		{
			hasTextureClicked = false;
		}

		if (!hasSaved && glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		{
			hasSaved = true;
			LevelManager::GetInstance().EditorSaveLevel();
		}
		else if (hasSaved && glfwGetKey(window, GLFW_KEY_S) == GLFW_RELEASE)
		{
			hasSaved = false;
		}
	}
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