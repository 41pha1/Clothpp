#pragma once

#include "Cloth.h"
#include "ShaderProgram.h"

class ClothRenderer {
public:
	ClothRenderer();
	virtual ~ClothRenderer();
	void render(ShaderProgram* shader, Cloth* cloth);
};

