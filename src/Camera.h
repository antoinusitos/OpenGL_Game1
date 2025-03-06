#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "MusicManager.h"

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float FOV = 45.0f;
const float FOVMIN = 1.0f;
const float FOVMAX = 90.0f;

const int xMin = -1;
const int xMax = 1;
const int zMin = -10;
const int zMax = 0;

bool canMove = true;
const float timeToMove = 0.15f;
float currentTime = 0.0f;

class Camera
{
public:
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    float Yaw;
    float Pitch;

    float MovementSpeed;
    float MouseSensitivity;
    float Fov;

    // constructor with vectors
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Fov(FOV)
    {
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    // constructor with scalar values
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Fov(FOV)
    {
        Position = glm::vec3(posX, posY, posZ);
        WorldUp = glm::vec3(upX, upY, upZ);
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    void Tick(float deltaTime)
    {
        updateCameraVectors();

        if (!canMove)
        {
            currentTime += deltaTime;
            if (currentTime >= timeToMove)
            {
                canMove = true;
                currentTime = 0.0f;
            }
        }
    }

    // returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 GetViewMatrix()
    {
        return glm::lookAt(Position, Position + Front, Up);
    }

    // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void ProcessKeyboard(Camera_Movement direction, float deltaTime)
    {
        if (!canMove)
        {
            return;
        }

        glm::vec3 movement = glm::vec3(0.0f);

        if (direction == FORWARD)
        {
            movement += Front;
        }
        if (direction == BACKWARD)
        {
            movement -= Front;
        }
        if (direction == LEFT)
        {
            ProcessMouseMovement(-90, 0);
            canMove = false;
            return;
            movement -= Right;
        }
        if (direction == RIGHT)
        {
            ProcessMouseMovement(90, 0);
            canMove = false;
            return;
            movement += Right;
        }

        movement.x = round(movement.x);
        movement.z = round(movement.z);

        if (AllowToMove(movement))
        {
            MusicManager::GetInstance().PlaySound("Sounds/Footstep.wav");
            Position += movement;
            canMove = false;
            Position.y = 0;
        }
    }

    bool AllowToMove(glm::vec3 newPos)
    {
        glm::vec3 finalPos = Position + newPos;
        if (newPos.x > 0.0f)
        {
            return finalPos.x <= xMax;
        }
        else if (newPos.x < 0.0f)
        {
            return finalPos.x >= xMin;
        }
        else if (newPos.z < 0.0f)
        {
            return finalPos.z >= zMin;
        }
        else if (newPos.z > 0.0f)
        {
            return finalPos.z <= zMax;
        }
    }

    // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
    {
        //xoffset *= MouseSensitivity;
        //yoffset *= MouseSensitivity;

        Yaw += xoffset;
        Pitch += yoffset;

        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (constrainPitch)
        {
            if (Pitch > 89.0f)
                Pitch = 89.0f;
            if (Pitch < -89.0f)
                Pitch = -89.0f;
        }

        // update Front, Right and Up Vectors using the updated Euler angles
        updateCameraVectors();
    }

    // processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void ProcessMouseScroll(float yoffset)
    {
        Fov -= (float)yoffset;
        if (Fov < FOVMIN)
            Fov = FOVMIN;
        if (Fov > FOVMAX)
            Fov = FOVMAX;
    }

private:
    // calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors()
    {
        // calculate the new Front vector
        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Front = glm::normalize(front);
        // also re-calculate the Right and Up vector
        Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        Up = glm::normalize(glm::cross(Right, Front));
    }
};
#endif