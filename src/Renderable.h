#pragma once

#include "VAO.h"
#include <glm/detail/type_mat4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glad/glad.h>

class Renderable
{
public:
	VAO * vao = 0;
	glm::mat4 model;
	glm::vec3 pos = glm::vec3(0,0,0);

	GLfloat* verts = 0;
	GLfloat* normals = 0;
	GLfloat* uvs = 0;
	GLuint* indices = 0;
	int vCount = 0, iCount = 0;

	virtual void mesh() = 0;
	void initRenderable();
	void updateVAO();

	virtual ~Renderable();
};

