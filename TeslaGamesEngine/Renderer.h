#pragma once

#include "Transform.h"
#include "Window.h"
#include "Model.h"
#include "Shader.h"
#include "Material.h"
#include "Transform.h"
#include "Camera.h"
#include "Light.h"

/*
 * Class responsible for all rendering in the game. Only rendering related class referenced by the game directly
 */
class Renderer
{
public:
	Renderer();
	Renderer(Window w, Camera c);

	// Draws a specific model to the window
	void DrawModel(Model m, Shader s, Material mat, glm::mat4 modelMatrix);

	~Renderer();

private: 
	Window window;
	Camera camera;
	// TODO: Change this to be vectors of different light types when added
	std::vector<Light> lights;
};

