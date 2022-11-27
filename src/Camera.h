#ifndef CAMERA_H_
#define CAMERA_H_

#include <glm/detail/type_vec3.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float3.hpp>

class Camera
{
public:
	float SPEED = 0.001f;
	bool renderWireframe = true;
	glm::vec3 pos = glm::vec3(0,0,0);
	glm::vec3 vel = glm::vec3(0,0,0);
	glm::mat4 Projection;
	glm::mat4 View;

	double yaw = 0, pitch = 0, roll = 0;

	Camera(float, int, int, float, float, glm::vec3, glm::vec3);
	void accelerate(glm::vec3 acc);
	void update();

	virtual ~Camera();
};

#endif
