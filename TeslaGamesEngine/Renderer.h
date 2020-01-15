#pragma once

#include "Transform.h"
#include "Window.h"
#include "Model.h"
#include "Camera.h"
#include "Light.h"

/*
 * Class responsible for all rendering in the game. Only rednering related class referenced by the game directly
 */
class Renderer
{
public:
	Renderer();

	// Draws a specific model to the window
	// TODO: This should instead be included in the Mesh/Model classes and they should have access to the renderer
	void DrawModel(Model m);

	~Renderer();

private: 
	Window window;
	Camera camera;
	// TODO: Change this to be vectors of different light types when added
	std::vector<Light> lights;
};

