#include "ClothRenderer.h"

#include <glad/glad.h>
#include <iostream>

#include "Cloth.h"
#include "ShaderProgram.h"
#include "VAO.h"

ClothRenderer::ClothRenderer()
{
}

ClothRenderer::~ClothRenderer()
{
}

void ClothRenderer::render(ShaderProgram* shader, Cloth * cloth)
{
	GLuint ModelMatrix = glGetUniformLocation(shader->ProgramID, "MODEL");
	glUniformMatrix4fv(ModelMatrix, 1, GL_FALSE, &cloth->model[0][0]);

	cloth->vao->enableVAO();
	glDrawElements(GL_TRIANGLES, cloth->vao->indexCount, GL_UNSIGNED_INT, (void*)0);
	cloth->vao->disableVAO();
}
