#include <glm/detail/type_vec3.hpp>
#include <cstdlib>
#include <iostream>
#include <utility>

#include "Simulation.h"
#include "Camera.h"

Simulation::Simulation(World * world)
{
	this->world = world;
}

Simulation::~Simulation()
{

}

void Simulation::update(double dt)
{
	world->update(dt);
}
