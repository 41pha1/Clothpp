#include "Camera.h"

#include <glm/ext/matrix_transform.hpp>
#include <glm/geometric.hpp>
#include <glm/trigonometric.hpp>
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <cmath>

Camera::Camera(float FOV, int width, int height, float NEAR_, float FAR_, glm::vec3 pos, glm::vec3 rot)
{
	this->pos = pos;
	yaw = rot.x;
	pitch = rot.y;
	roll = rot.z;
	View = glm::lookAt(pos, glm::vec3(0,0,0), glm::vec3(0,1,0));
	Projection = glm::perspective(glm::radians(FOV),  width / (float) height, NEAR_, FAR_);
}

void Camera::accelerate(glm::vec3 acc)
{
	vel += acc;
}

Camera::~Camera()
{

}

void Camera::update()
{
	pos += vel;
	vel *= 0.91f;

	glm::vec3 direction;
	direction.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	direction.y = sin(glm::radians(pitch));
	direction.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
	direction = glm::normalize(direction);

	View = glm::lookAt(pos, pos+direction, glm::vec3(0, 1, 0));
}
