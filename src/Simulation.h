#ifndef SIMULATION_H_
#define SIMULATION_H_

#include <glm/ext/vector_float3.hpp>
#include <map>
#include <string>
#include <vector>
#include <mutex>
#include "World.h"

class Simulation
{
public:
	World* world;

	Simulation(World*);

	virtual ~Simulation();
	void update(double dt);
};

#endif
