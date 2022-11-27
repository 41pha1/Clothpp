#include "VAO.h"



VAO::VAO(GLuint id)
{
	vaoID = id;
}

VAO::~VAO()
{
	glDeleteVertexArrays(1, &vaoID);
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &UVBuffer);
	glDeleteBuffers(1, &normalBuffer);
	glDeleteBuffers(1, &normalBuffer);
}

void VAO::enableVAO()
{
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, UVBuffer);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
}

void VAO::disableVAO()
{
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

void VAO::setUVBuffer(GLuint u)
{
	UVBuffer = u;
}

void VAO::setVertexBuffer(GLuint v)
{
	vertexBuffer = v;
}

void VAO::setNormalBuffer(GLuint n)
{
	normalBuffer = n;
}

void VAO::setIndexBuffer(GLuint i)
{
	indexBuffer = i;
}
