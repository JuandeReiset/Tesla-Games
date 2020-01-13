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
	void DrawModel(Model m);

	~Renderer();

private: 
	Window window;
	Camera camera;
	// TODO: Change this to be vectors of different light types when added
	std::vector<Light> lights;
};

