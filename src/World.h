#pragma once

#include "Cloth.h"

class World
{
public:
	Cloth * cloth;
	float time;

	glm::dvec3 wind = 10. * glm::dvec3(1, 0, -0.3);
	float GRAVITY = 9.81f;

	World();
	void update(double dt);
	virtual ~World();
};

