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

class PauseScreen
{
public:
	PauseScreen() = default;

	void loadVertices();
	void loadTextures();
	void use();
	void load();
	void loadShader();

	void loadController(Controller* controller);

	std::vector<HUD*> HUDList;
	Shader hudShader;
	int op = 0;

	unsigned int indices[6] = {
		0, 1, 3,
		2, 1, 3
	};

	// Vertex Shader of HUD_shader
	const char* vHshader = "Shaders/HUD_shader.vert";

	//Fragment shader of HUD_shader
	const char* fHshader = "Shaders/HUD_shader.frag";

	Texture backgroundTexture;
	Texture logoTexture;
	Texture resumeTxt;
	Texture titleTxt;

	Texture resume1Txt;
	Texture resume2Txt;
	Texture title1Txt;
	Texture title2Txt;

	GLfloat backgroundVertices[20] = {
		0.0f / 1600 * mainWindow.getWidth(), 0.f / 900.0f * mainWindow.getHeight(), 0.0f,	0.0f, 0.0f,								//bottom left
		0.0f / 1600 * mainWindow.getWidth(), 900.0f / 900.0f * mainWindow.getHeight(), 0.0f,		0.0f, 1.0f,								//top left
		1600.0f / 1600 * mainWindow.getWidth(), 900 / 900.0f * mainWindow.getHeight(), 0.0f,		1.0f, 1.0f,								//top right
		1600.0f / 1600 * mainWindow.getWidth(), 0.f / 900.0f * mainWindow.getHeight(), 0.0f,	1.0f, 0.0f								//bottom right
	};

	GLfloat logoVertices[20] = {
		468.5f / 1600 * mainWindow.getWidth(), 0.f / 900.0f * mainWindow.getHeight(), 1.0f,	0.0f, 0.0f,
		468.5f / 1600 * mainWindow.getWidth(), 858.f / 900.0f * mainWindow.getHeight(), 1.0f,		0.0f, 1.0f,
		1131.5f / 1600 * mainWindow.getWidth(), 858.f / 900.0f * mainWindow.getHeight(), 1.0f,		1.0f, 1.0f,
		1131.5f / 1600 * mainWindow.getWidth(), 0.f / 900.0f * mainWindow.getHeight(), 1.0f,	1.0f, 0.0f
	};

	GLfloat resumeVertices[20] = {
		550.f / 1600 * mainWindow.getWidth(), 550.f / 900.0f * mainWindow.getHeight(), 1.0f,	0.0f, 0.0f,
		550.f / 1600 * mainWindow.getWidth(), 750.f / 900.0f * mainWindow.getHeight(), 1.0f,		0.0f, 1.0f,
		1050.f / 1600 * mainWindow.getWidth(), 750.f / 900.0f * mainWindow.getHeight(), 1.0f,		1.0f, 1.0f,
		1050.f / 1600 * mainWindow.getWidth(), 550.f / 900.0f * mainWindow.getHeight(), 1.0f,	1.0f, 0.0f
	};

	GLfloat titleVertices[20] = {
		550.f / 1600 * mainWindow.getWidth(), 650.f / 900.0f * mainWindow.getHeight(), 1.0f,	0.0f, 0.0f,
		550.f / 1600 * mainWindow.getWidth(), 850.f / 900.0f * mainWindow.getHeight(), 1.0f,		0.0f, 1.0f,
		1050.f / 1600 * mainWindow.getWidth(), 850.f / 900.0f * mainWindow.getHeight(), 1.0f,		1.0f, 1.0f,
		1050.f / 1600 * mainWindow.getWidth(), 650.f / 900.0f * mainWindow.getHeight(), 1.0f,	1.0f, 0.0f
	};

	void setOption();
};

