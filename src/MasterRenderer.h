#ifndef MASTERRENDERER_H_
#define MASTERRENDERER_H_

#include "ClothRenderer.h"
#include "ClothShader.h"
#include "Camera.h"
#include "World.h"

class MasterRenderer {
public:
	glm::vec3 SKY_COLOR = glm::vec3(0.1f, 0.1f, 0.1f);
	ClothRenderer * clothRenderer;
	ClothShader* clothShader;
	
	MasterRenderer(int width, int height);
	virtual ~MasterRenderer();
	void render(World * world);
	Camera * camera;
};

#endif
