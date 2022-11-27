#include "ClothShader.h"

ClothShader::ClothShader()
{
	ProgramID = LoadShaders(vertexShaderFile, fragmentShaderFile);
}

ClothShader::~ClothShader()
{

}

