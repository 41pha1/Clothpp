#pragma once

#include "Renderable.h"
#include <unordered_set>

class World;

class Cloth : public Renderable
{
public:
	World* world;

	int width, height;
	double stiffness;
	double mass;
	double distance;
	double friction;

	std::unordered_set<int> fixpoints;

	glm::dvec3** positions;
	glm::dvec3** normal_vectors;
	glm::dvec3** oldPositions;
	glm::dvec3** forces;

	Cloth(World * world, int width, int height, float stiffness = 400, float mass = 0.002, float friction = 0.005);
	void update(double dt);
	void mesh();
	void calculateNormals();
	void remesh();
	virtual ~Cloth();
};

