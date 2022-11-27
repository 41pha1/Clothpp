#pragma once

#include "ShaderProgram.h"

class ClothShader : public ShaderProgram
{
public:
	ClothShader();
	const std::string vertexShaderFile = "src/shaders/vertexShader.glsl";
	const std::string fragmentShaderFile = "src/shaders/fragmentShader.glsl";
	virtual ~ClothShader();
};

