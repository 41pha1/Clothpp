#include "Renderable.h"
#include "VAOLoader.h"
#include <iostream>

void Renderable::initRenderable()
{
	model = glm::mat4(1.0f);
	model = glm::translate(model, pos);

	mesh();

	vao = VAOLoader::loadToVAO(verts, normals, uvs, indices, vCount, (vCount * 2) / 3, iCount);
}

void Renderable::updateVAO()
{
	VAOLoader::updateVertexBuffer(vao, verts, vCount);
	VAOLoader::updateNormalBuffer(vao, normals, vCount);
}

Renderable::~Renderable()
{
	delete[] verts;
	delete[] normals;
	delete[] uvs;
	delete[] indices;
}