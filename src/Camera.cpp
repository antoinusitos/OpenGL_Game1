#include "Camera.h"

#include "MusicManager.h"

// constructor with vectors
Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Fov(FOV)
{
    Position = position;
    WorldUp = up;
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
}

// constructor with scalar values
Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Fov(FOV)
{
    Position = glm::vec3(posX, posY, posZ);
    WorldUp = glm::vec3(upX, upY, upZ);
    Yaw = yaw == 0 ? YAW : yaw;
    Pitch = pitch;
    updateCameraVectors();
}

void Camera::Tick(float deltaTime)
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
glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(Position, Position + Front, Up);
}

// processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
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

bool Camera::AllowToMove(glm::vec3 newPos)
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

    return false;
}

// processes input received from a mouse input system. Expects the offset value in both the x and y direction.
void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
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
void Camera::ProcessMouseScroll(float yoffset)
{
    Fov -= (float)yoffset;
    if (Fov < FOVMIN)
        Fov = FOVMIN;
    if (Fov > FOVMAX)
        Fov = FOVMAX;
}

// calculates the front vector from the Camera's (updated) Euler Angles
void Camera::updateCameraVectors()
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
