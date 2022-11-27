#ifndef VAO_H_
#define VAO_H_

#include <glad/glad.h>

class VAO
{
public:
	VAO(GLuint id);
	virtual ~VAO();
	GLuint vaoID = 0;
	GLuint vertexBuffer = 0;
	GLuint normalBuffer = 0;
	GLuint UVBuffer = 0;
	GLuint indexBuffer = 0;
	int vertCount = 0;
	int indexCount = 0;

	void enableVAO();
	void disableVAO();

	void setUVBuffer(GLuint u);
	void setIndexBuffer(GLuint i);
	void setNormalBuffer(GLuint n);
	void setVertexBuffer(GLuint v);
};

#endif /* VAO_H_ */
