#include "MasterRenderer.h"

#include <glad/glad.h>
#include <glm/detail/type_mat4x4.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/geometric.hpp>
#include <glm/trigonometric.hpp>
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Camera.h"
#include "World.h"
#include <iostream>

MasterRenderer::MasterRenderer(int width, int height)
{
	camera = new Camera(70, width, height, 0.01, 1000, glm::vec3(0.5,0.5,1), glm::vec3(-90,0,0));
	clothShader = new ClothShader();
	clothRenderer = new ClothRenderer();
}

MasterRenderer::~MasterRenderer()
{

}

void MasterRenderer::render(World * world)
{
	glClearColor(SKY_COLOR.x, SKY_COLOR.y, SKY_COLOR.z, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 4);


	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	//glEnable(GL_CULL_FACE);
	glEnable(GL_MULTISAMPLE);

	camera->update();
	if(camera->renderWireframe)
		glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glm::mat4 vp = camera->Projection * camera->View;
	GLuint ViewProjection = glGetUniformLocation(clothShader->ProgramID, "VP");
	glUniformMatrix4fv(ViewProjection, 1, GL_FALSE, &vp[0][0]);
	
	glUseProgram(clothShader->ProgramID);

	clothRenderer->render(clothShader, world->cloth);
}

