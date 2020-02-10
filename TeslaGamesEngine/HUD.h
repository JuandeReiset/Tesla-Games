#pragma once

#include <GL\glew.h>

/*
*Class representing HUD.
*/

class HUD
{
public:
	HUD();

	//Method for creating an HUD with a given set of vertices and indices
	void createHUD(GLfloat* vertices, unsigned int* indices, unsigned int numOfVertices, unsigned int numOfIndices);
	//Method for showing HUD on the window
	void renderHUD();
	//Method to clearn memory being used HUD and freeing it
	void clearHUD();

	~HUD();

private:
	GLuint VAO, VBO, IBO;
	GLsizei indexCount;
};

