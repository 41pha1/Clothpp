#include "World.h"
#include "Cloth.h"

World::World()
{
	time = 0;
	cloth = new Cloth(this, 20, 20);
}

void World::update(double dt)
{
	time += dt;
	wind = 4. * glm::dvec3(1, 0.2, 0.3 * sin(time * 10));
	cloth->update(dt);
}

World::~World()
{
}
