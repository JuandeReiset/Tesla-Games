#pragma once

#include <GL/glew.h>

class Shadow
{
public:
	Shadow();

	//Method for creating shadow with a given set of vertices and indices
	void createShadow(GLfloat* vertices, unsigned int* indices, unsigned int numOfVertices, unsigned int numOfIndices);
	//Method for showing shadows
	void renderShadow();
	//Method to clear memory being used HUD and free it
	void clearShadow();

	~Shadow();

private:
	GLuint VAO, VBO, IBO;
	GLsizei indexCount;
};

