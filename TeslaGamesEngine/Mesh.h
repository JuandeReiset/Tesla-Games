#pragma once

/*
 * Class representing a mesh. Used by Model to load an obj
 */
class Mesh
{
public:
	Mesh();
	// Takes an array of vertices and indices to create an OpenGL mesh
	void CreateMesh(float *vertices, unsigned int *indices, unsigned int numOfVertices, unsigned int numOfIndices);
	// Clears the mesh and frees the memory
	void ClearMesh();
	~Mesh();

private:
	/* Uncomment after getting OpenGL working
	GLuint VAO, VBO, IBO;
	GLsizei indexCount;
	*/
};

