#pragma once

#include <GL\glew.h>

/*
 * Class representing a mesh. Used by Model to load an obj
 */
class Mesh
{
public:
	Mesh();
	// Method for creating a mesh with a given set of vertices and indices
	void CreateMesh(GLfloat *vertices, unsigned int *indices, unsigned int numOfVertices, unsigned int numOfIndices);
	// Method for showing the mesh on the window
	void RenderMesh();
	// Method to clear memory being used mesh and freeing it
	void ClearMesh();

	~Mesh();

private:
	GLuint VAO, VBO, IBO;
	GLsizei indexCount;
};


