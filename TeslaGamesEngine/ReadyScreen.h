#pragma once

#include <GL\glew.h>
#include <glm/glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <vector>

#include "Global.h"
#include "Shader.h"
#include "Window.h"
#include "HUD.h"
#include "Texture.h"
#include "Controller.h"

class ReadyScreen
{
public:
	ReadyScreen() = default;

	void loadVertices();
	void loadTextures();
	void use();
	void load();
	void loadShader();

	void loadController(Controller* controller, int player);

private:
	std::vector<HUD*> HUDList;
	Shader hudShader;

	unsigned int indices[6] = {
		0, 1, 3,
		2, 1, 3
	};

	// Vertex Shader of HUD_shader
	const char* vHshader = "Shaders/HUD_shader.vert";

	//Fragment shader of HUD_shader
	const char* fHshader = "Shaders/HUD_shader.frag";

	Texture backgroundTexture;
	Texture controllerTexture;
	Texture readyTexture;
	Texture backTexture;
	Texture player1Texture;
	Texture player2Texture;

	bool p1Ready = false;
	bool p2Ready = false;

	GLfloat backgroundVertices[20] = {
		0.0f / 1600 * mainWindow.getWidth(), 0.f / 900.0f * mainWindow.getHeight(), 0.0f,	0.0f, 0.0f,								//bottom left
		0.0f / 1600 * mainWindow.getWidth(), 900.0f / 900.0f * mainWindow.getHeight(), 0.0f,		0.0f, 1.0f,								//top left
		1600.0f / 1600 * mainWindow.getWidth(), 900 / 900.0f * mainWindow.getHeight(), 0.0f,		1.0f, 1.0f,								//top right
		1600.0f / 1600 * mainWindow.getWidth(), 0.f / 900.0f * mainWindow.getHeight(), 0.0f,	1.0f, 0.0f								//bottom right
	};


	GLfloat controllerVertices[20] = {
		370.8f / 1600 * mainWindow.getWidth(), 20.f / 900.0f * mainWindow.getHeight(), 1.0f,	0.0f, 0.0f,
		370.8f / 1600 * mainWindow.getWidth(), 543.2f / 900.0f * mainWindow.getHeight(), 1.0f,		0.0f, 1.0f,
		1229.2f / 1600 * mainWindow.getWidth(), 543.2f / 900.0f * mainWindow.getHeight(), 1.0f,		1.0f, 1.0f,
		1229.2f / 1600 * mainWindow.getWidth(), 20.f / 900.0f * mainWindow.getHeight(), 1.0f,	1.0f, 0.0f
	};

	GLfloat readyVertices[20] = {
		550.f / 1600 * mainWindow.getWidth(), 460.f / 900.0f * mainWindow.getHeight(), 1.0f,	0.0f, 0.0f,
		550.f / 1600 * mainWindow.getWidth(), 660.f / 900.0f * mainWindow.getHeight(), 1.0f,		0.0f, 1.0f,
		1050.f / 1600 * mainWindow.getWidth(), 660.f / 900.0f * mainWindow.getHeight(), 1.0f,		1.0f, 1.0f,
		1050.f / 1600 * mainWindow.getWidth(), 460.f / 900.0f * mainWindow.getHeight(), 1.0f,	1.0f, 0.0f
	};

	GLfloat backVertices[20] = {
		1400.f / 1600 * mainWindow.getWidth(), 820.f / 900.0f * mainWindow.getHeight(), 1.0f,	0.0f, 0.0f,
		1400.f / 1600 * mainWindow.getWidth(), 900.f / 900.0f * mainWindow.getHeight(), 1.0f,		0.0f, 1.0f,
		1600.f / 1600 * mainWindow.getWidth(), 900.f / 900.0f * mainWindow.getHeight(), 1.0f,		1.0f, 1.0f,
		1600.f / 1600 * mainWindow.getWidth(), 820.f / 900.0f * mainWindow.getHeight(), 1.0f,	1.0f, 0.0f
	};

	GLfloat player1Vertices[20] = {
		50.f / 1600 * mainWindow.getWidth(), 750.f / 900.0f * mainWindow.getHeight(), 1.0f,	0.0f, 0.0f,
		50.f / 1600 * mainWindow.getWidth(), 850.f / 900.0f * mainWindow.getHeight(), 1.0f,		0.0f, 1.0f,
		150.f / 1600 * mainWindow.getWidth(), 850.f / 900.0f * mainWindow.getHeight(), 1.0f,		1.0f, 1.0f,
		150.f / 1600 * mainWindow.getWidth(), 750.f / 900.0f * mainWindow.getHeight(), 1.0f,	1.0f, 0.0f
	};

	GLfloat player2Vertices[20] = {
		350.f / 1600 * mainWindow.getWidth(), 750.f / 900.0f * mainWindow.getHeight(), 1.0f,	0.0f, 0.0f,
		350.f / 1600 * mainWindow.getWidth(), 850.f / 900.0f * mainWindow.getHeight(), 1.0f,		0.0f, 1.0f,
		450.f / 1600 * mainWindow.getWidth(), 850.f / 900.0f * mainWindow.getHeight(), 1.0f,		1.0f, 1.0f,
		450.f / 1600 * mainWindow.getWidth(), 750.f / 900.0f * mainWindow.getHeight(), 1.0f,	1.0f, 0.0f
	};
};

