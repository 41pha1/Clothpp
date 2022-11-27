#include "Cloth.h"
#include <iostream>
#include <chrono>
#include "World.h"

Cloth::Cloth(World * world, int w, int h, float s, float m, float f)
{
	this->world = world;

	friction = f;
	width = w;
	height = h;
	stiffness = s;
	mass = m;
	distance = 1.f / width;

	fixpoints = std::unordered_set<int>();
	//fixpoints.insert(height);
	//fixpoints.insert((width + 1) * (height + 1) - 1);

	positions = new glm::dvec3 * [width + 1];
	normal_vectors = new glm::dvec3 * [width + 1];
	oldPositions = new glm::dvec3 * [width + 1];
	forces = new glm::dvec3 * [width + 1];

	for (int x = 0; x <= width; x++)
	{
		positions[x] = new glm::dvec3[height + 1];
		normal_vectors[x] = new glm::dvec3[height + 1];
		oldPositions[x] = new glm::dvec3[height + 1];
		forces[x] = new glm::dvec3[height + 1];

		for (int y = 0; y <= height; y++)
		{
			float dx = x * distance;
			float dy = y * distance;
			positions[x][y] = glm::vec3(dx, dy, 0);
			normal_vectors[x][y] = glm::vec3(dx, dy, 0);
			oldPositions[x][y] = positions[x][y];
			forces[x][y] = glm::vec3(0, 0, 0);
		}
	}
	initRenderable();
}

void Cloth::calculateNormals()
{
	for (int x = 0; x <= width; x++)
	{
		for (int y = 0; y <= height; y++)
		{
			normal_vectors[x][y] = glm::dvec3(0, 0, 0);
		}
	}
	for (int i = 0; i < iCount; i += 3)
	{
		glm::vec3 a = positions[indices[i+0] / (height + 1)][indices[i+0] % (height + 1)];
		glm::vec3 b = positions[indices[i+1] / (height + 1)][indices[i+1] % (height + 1)];
		glm::vec3 c = positions[indices[i+2] / (height + 1)][indices[i+2] % (height + 1)];

		glm::vec3 ab = b - a;
		glm::vec3 ac = c - a;
		glm::vec3 normal = glm::normalize(glm::cross(ab, ac));

		for (int j = 0; j < 3; j++)
		{
			normal_vectors[indices[i+j] / (height +1)][indices[i+j] % (height + 1)] += normal;
		}
	}
	for (int x = 0; x <= width; x++)
	{
		for (int y = 0; y <= height; y++)
		{
			normal_vectors[x][y] = glm::normalize(normal_vectors[x][y]);
		}
	}
}

void Cloth::update(double dt)
{
	//float t = sin(world->time * 15);
	//double s = sin(t);
	//double c = cos(t);
	//for(int i = 0; i <= width; i++)
	//{
	//	positions[i][height] = glm::vec3((i*distance - 0.5) * c + 0.5, 1, (i * distance - 0.5) * s);
	//}
	for (int i = 0; i <= height; i++)
		positions[0][i] = glm::vec3(0, i * distance, 0);

	float structure = 1;
	float sheer = 0.2;
	float flexion = 1.5;
	int fd = 2;
 
	static const int dx[]{ 1, 0, -1, 0, 1, 1, -1, -1, -fd, 0, fd, 0 };
	static const int dy[]{ 0, 1, 0, -1, 1, -1, 1, -1, 0, fd, 0, -fd };
	static const float initial[]{ 1, 1, 1, 1, 1.414, 1.414, 1.414, 1.414, 2, 2, 2, 2 };
	static const float influence[]{ structure, structure, structure, structure, sheer, sheer, sheer, sheer, flexion, flexion, flexion, flexion };

	for (int x = 0; x <= width; x++)
	{
		for (int y = 0; y <= height; y++)
		{
			for(int n = 0; n < 12; n++)
			{
				int nx = x + dx[n];
				int ny = y + dy[n];

				if (nx<0 || ny < 0 || nx > width || ny > height)
					continue;

				glm::dvec3 dir = (positions[nx][ny] - positions[x][y]);

				double d = glm::length(dir);
				double dd = d - (distance * initial[n]);
				double f = dd * (stiffness * influence[n]);

				glm::dvec3 spring_force = f * dir / d;
				glm::dvec3 gravity = world->GRAVITY * glm::vec3(0, -mass, 0);
				glm::dvec3 velocity = (positions[x][y] - oldPositions[x][y]) / dt;

				float viscous = glm::dot(normal_vectors[x][y], world->wind - velocity);
				glm::dvec3 viscous_force = 0.2 *  viscous * normal_vectors[x][y];

				glm::dvec3 damping_force = -0.01 * velocity;

				forces[x][y] += gravity + spring_force + viscous_force + damping_force;
			}

		}
	}
	for (int x = 0; x <= width; x++)
	{
		for (int y = 0; y <= height; y++)
		{
			if (fixpoints.find(x * (height + 1) + y) != fixpoints.end())
				continue;

			glm::dvec3 a = forces[x][y] / mass;

			glm::dvec3 temp = positions[x][y];
			positions[x][y] = (2. - friction) * positions[x][y]  - (1. - friction) *  oldPositions[x][y] + a * dt * dt;
			oldPositions[x][y] = temp;

			forces[x][y] = glm::dvec3(0, 0, 0);
		}
	}

	calculateNormals();
	remesh();
	updateVAO();
}

void Cloth::remesh()
{
	int index = 0;

	for (int x = 0; x <= width; x++)
	{
		for (int y = 0; y <= height; y++)
		{
			glm::vec3 point = positions[x][y];
			glm::vec3 normal = normal_vectors[x][y];

			normals[index] = normal.x;
			verts[index++] = point.x;
			normals[index] = normal.y;
			verts[index++] = point.y;
			normals[index] = normal.z;
			verts[index++] = point.z;
		}
	}
}

void Cloth::mesh()
{
	vCount = (width+1) * (height+1);
	iCount = width * height * 6;

	verts = new GLfloat[vCount * 3];
	normals = new GLfloat[vCount * 3];
	uvs = new GLfloat[vCount * 2];
	indices = new GLuint[iCount];
	
	int uIndex = 0;

	for(int x = 0; x <= width; x++)
	{
		for (int y = 0; y <= height; y++)
		{
			glm::vec3 point = positions[x][y];
			uvs[uIndex++] = point.x;
			uvs[uIndex++] = point.y;
		}
	}

	int index = 0;

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			indices[index++] = x + y * (width + 1);
			indices[index++] = x + (y + 1) * (width + 1);
			indices[index++] = (x + 1) + (y + 1) * (width + 1);
			indices[index++] = (x + 1) + y * (width + 1);
			indices[index++] = x + y * (width + 1);
			indices[index++] = (x + 1) + (y + 1) * (width + 1);
		}
	}

	remesh();
}

Cloth::~Cloth()
{
	for (int x = 0; x <= width; x++)
	{
		delete[] positions[x];
		delete[] normal_vectors[x];
		delete[] oldPositions[x];
		delete[] forces[x];
	}
	delete[] positions;
	delete[] normal_vectors;
	delete[] oldPositions;
	delete[] forces;
}
