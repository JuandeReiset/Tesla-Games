#include "pch.h"
#include "Renderer.h"


/*
Renderer::Renderer()
{
	// window = Window();
	// camera = Camera();
}
*/

Renderer::Renderer(Window& w, Camera& c) : window(w), camera(c)
{
	window = w;
	camera = c;
}


void Renderer::DrawModel(Model m, Shader s, Material mat, glm::mat4 modelMatrix)
{
	// Take Model m
	// Load it's textures and shaders
	// Get view matrix from camera
	// Render to screen
}

Renderer::~Renderer()
{
}
