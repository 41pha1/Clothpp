#include <glad/glad.h>
#include <string>

#ifndef SHADERPROGRAM_H_
#define SHADERPROGRAM_H_

class ShaderProgram
{
public:
	ShaderProgram();
	virtual ~ShaderProgram();
	GLuint LoadShaders(std::string vertFile, std::string fragFile);
	GLuint ProgramID;
};

#endif
