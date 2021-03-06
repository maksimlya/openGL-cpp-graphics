#include "Camera.h"

Camera::Camera()
{
	if (is_file_exist("camOpt.mysetting"))
	{
		ifstream loadFile("camOpt.mysetting");
		std::string load[6];
		for (int i = 0; i < 6; i++)
			std::getline(loadFile, load[i]);
	
		this->position.x = std::stof(load[0]);
		this->position.y = std::stof(load[1]);
		this->position.z = std::stof(load[2]);
		this->yaw = std::stof(load[3]);
		this->pitch = std::stof(load[4]);
		this->roll = std::stof(load[5]);
		this->speed = 2;
	}


	else
	{
		this->pitch = 0;
		this->roll = 0;
		this->yaw = 0;
		this->speed = 2;
		this->position.y = 5;
	}
}

glm::vec3 Camera::getPosition()
{
	return this->position;
}

float Camera::getPitch()
{
	return this->pitch;
}

float Camera::getYaw()
{
	return this->yaw;
}

float Camera::getRoll()
{
	return this->roll;
}

void Camera::move(DisplayManager display)
{
	if (glfwGetKey(display.getWindow(), GLFW_KEY_W) == GLFW_PRESS)
	{	
		position.z += -(float)cos(glm::radians(yaw)) * speed;
		position.x += (float)sin(glm::radians(yaw)) * speed;
	}

	if (glfwGetKey(display.getWindow(), GLFW_KEY_D) == GLFW_PRESS)
	{
		position.z += (float)sin(glm::radians(yaw)) * speed;
		position.x += (float)cos(glm::radians(yaw)) * speed;
	}

	if (glfwGetKey(display.getWindow(), GLFW_KEY_A) == GLFW_PRESS)
	{
		position.z -= (float)sin(glm::radians(yaw)) * speed;
		position.x -= (float)cos(glm::radians(yaw)) * speed;
	}

	if (glfwGetKey(display.getWindow(), GLFW_KEY_S) == GLFW_PRESS)
	{
		position.z -= -(float)cos(glm::radians(yaw)) * speed;
		position.x -= (float)sin(glm::radians(yaw)) * speed;
	}
	if (glfwGetKey(display.getWindow(), GLFW_KEY_Q) == GLFW_PRESS)
	{
		this->yaw -= 1;
	}
	if (glfwGetKey(display.getWindow(), GLFW_KEY_E) == GLFW_PRESS)
	{
		this->yaw += 1;
	}
	if (glfwGetKey(display.getWindow(), GLFW_KEY_R) == GLFW_PRESS)
	{
		this->pitch -= 0.5;
	}
	if (glfwGetKey(display.getWindow(), GLFW_KEY_F) == GLFW_PRESS)
	{
		this->pitch += 0.5;
	}
	if (glfwGetKey(display.getWindow(), GLFW_KEY_1) == GLFW_PRESS)
	{
		this->roll -= 0.5;
	}
	if (glfwGetKey(display.getWindow(), GLFW_KEY_2) == GLFW_PRESS)
	{
		this->roll += 0.5;
	}
	if (glfwGetKey(display.getWindow(), GLFW_KEY_Z) == GLFW_PRESS)
	{
		this->position.y -= 1;
	}
	if (glfwGetKey(display.getWindow(), GLFW_KEY_X) == GLFW_PRESS)
	{
		this->position.y += 1;
	}
}

bool is_file_exist(const char * fileName)
{
	std::ifstream infile(fileName);
	return infile.good();
}

void saveCamera(Camera camera)
{
	std::ofstream saveFile("camOpt.mysetting");
	saveFile << camera.getPosition().x << "\n" << camera.getPosition().y << "\n" << camera.getPosition().z << "\n" << (int)camera.getYaw() % 360 << "\n" << (int)camera.getPitch() % 360 << "\n" << (int)camera.getRoll() % 360;
}