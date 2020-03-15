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

class Menu
{
public:
	Menu() = default;

	void loadVertices();
	void loadTextures();
	void use();
	void load();
	void loadShader();

	void setOption(int op);

private:
	std::vector<HUD*> HUDList;
	Shader hudShader;

	unsigned int indices[6] = {
		0, 1, 3,
		2, 1, 3
	};

	Texture backgroundTexture;
	Texture menuTxt;
	Texture audioTxt;
	Texture HUDSizeTxt;
	Texture goBackTxt;

	Texture audioTxt1;
	Texture audioTxt2;
	Texture HUDSizeTxt1;
	Texture HUDSizeTxt2;


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

	GLfloat menuVertices[20] = {
		300.f / 1600 * mainWindow.getWidth(), 50.f / 900.0f * mainWindow.getHeight(), 1.0f,	0.0f, 0.0f,
		300.f / 1600 * mainWindow.getWidth(), 450.f / 900.0f * mainWindow.getHeight(), 1.0f,		0.0f, 1.0f,
		1300.f / 1600 * mainWindow.getWidth(), 450.f / 900.0f * mainWindow.getHeight(), 1.0f,		1.0f, 1.0f,
		1300.f / 1600 * mainWindow.getWidth(), 50.f / 900.0f * mainWindow.getHeight(), 1.0f,	1.0f, 0.0f
	};

	GLfloat audioVertices[20] = {
		675.f / 1600 * mainWindow.getWidth(), 550.f / 900.0f * mainWindow.getHeight(), 1.0f,	0.0f, 0.0f,
		675.f / 1600 * mainWindow.getWidth(), 650.f / 900.0f * mainWindow.getHeight(), 1.0f,		0.0f, 1.0f,
		925.f / 1600 * mainWindow.getWidth(), 650.f / 900.0f * mainWindow.getHeight(), 1.0f,		1.0f, 1.0f,
		925.f / 1600 * mainWindow.getWidth(), 550.f / 900.0f * mainWindow.getHeight(), 1.0f,	1.0f, 0.0f
	};

	GLfloat HUDVertices[20] = {
		675.f / 1600 * mainWindow.getWidth(), 670.f / 900.0f * mainWindow.getHeight(), 1.0f, 0.0f, 0.0f,
		675.f / 1600 * mainWindow.getWidth(), 770.f / 900.0f * mainWindow.getHeight(), 1.0f, 0.0f, 1.0f,
		925.f / 1600 * mainWindow.getWidth(), 770.f / 900.0f * mainWindow.getHeight(), 1.0f, 1.0f, 1.0f,
		925.f / 1600 * mainWindow.getWidth(), 670.f / 900.0f * mainWindow.getHeight(), 1.0f, 1.0f, 0.0f
	};

	GLfloat goBackVertices[20] = {
		1350.f / 1600 * mainWindow.getWidth(), 770.f / 900.0f * mainWindow.getHeight(), 1.0f, 0.0f, 0.0f,
		1350.f / 1600 * mainWindow.getWidth(), 850.f / 900.0f * mainWindow.getHeight(), 1.0f, 0.0f, 1.0f,
		1550.f / 1600 * mainWindow.getWidth(), 850.f / 900.0f * mainWindow.getHeight(), 1.0f, 1.0f, 1.0f,
		1550.f / 1600 * mainWindow.getWidth(), 770.f / 900.0f * mainWindow.getHeight(), 1.0f, 1.0f, 0.0f
	};
};

