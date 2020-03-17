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



class StartScreen
{
public:
	StartScreen() = default;

	void loadVertices();
	void loadTextures();
	void use();
	void load();
	void loadShader();

	void setOption(int op);

private:
	//I think it's more like a 2D graphic shader than a HUD shader, wrong name now :(
	std::vector<HUD*> HUDList;
	Shader hudShader;

	unsigned int indices[6] = {
		0, 1, 3,
		2, 1, 3
	};

	Texture backgroundTexture;
	Texture logoTexture;
	Texture startText;
	Texture settingText;
	Texture exitText;
	Texture startText1;
	Texture startText2;
	Texture settingText1;
	Texture settingText2;
	Texture exitText1;
	Texture exitText2;

	// Vertex Shader of HUD_shader
	const char* vHshader = "Shaders/HUD_shader.vert";

	//Fragment shader of HUD_shader
	const char* fHshader = "Shaders/HUD_shader.frag";

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

	GLfloat startVertices[20] = {
		675.f / 1600 * mainWindow.getWidth(), 600.f / 900.0f * mainWindow.getHeight(), 1.0f,	0.0f, 0.0f,
		675.f / 1600 * mainWindow.getWidth(), 700.f / 900.0f * mainWindow.getHeight(), 1.0f,		0.0f, 1.0f,
		925.f / 1600 * mainWindow.getWidth(), 700.f / 900.0f * mainWindow.getHeight(), 1.0f,		1.0f, 1.0f,
		925.f / 1600 * mainWindow.getWidth(), 600.f / 900.0f * mainWindow.getHeight(), 1.0f,	1.0f, 0.0f
	};
	
	GLfloat settingVertices[20] = {
		675.f / 1600 * mainWindow.getWidth(), 700.f / 900.0f * mainWindow.getHeight(), 1.0f,	0.0f, 0.0f,
		675.f / 1600 * mainWindow.getWidth(), 800.f / 900.0f * mainWindow.getHeight(), 1.0f,		0.0f, 1.0f,
		925.f / 1600 * mainWindow.getWidth(), 800.f / 900.0f * mainWindow.getHeight(), 1.0f,		1.0f, 1.0f,
		925.f / 1600 * mainWindow.getWidth(), 700.f / 900.0f * mainWindow.getHeight(), 1.0f,	1.0f, 0.0f
	};
	
	GLfloat exitVertices[20] = {
		675.f / 1600 * mainWindow.getWidth(), 800.f / 900.0f * mainWindow.getHeight(), 1.0f,	0.0f, 0.0f,
		675.f / 1600 * mainWindow.getWidth(), 900.f / 900.0f * mainWindow.getHeight(), 1.0f,		0.0f, 1.0f,
		925.f / 1600 * mainWindow.getWidth(), 900.f / 900.0f * mainWindow.getHeight(), 1.0f,		1.0f, 1.0f,
		925.f / 1600 * mainWindow.getWidth(), 800.f / 900.0f * mainWindow.getHeight(), 1.0f,	1.0f, 0.0f
	};
};

