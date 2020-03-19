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

class Menu
{
public:
	Menu() = default;

	void loadVertices();
	void loadTextures();
	void use();
	void load();
	void loadShader();

	void loadController(Controller* controller);

private:
	std::vector<HUD*> HUDList;
	Shader hudShader;

	int op = 0;
	int tn = 0;
	int an = 9;

	unsigned int indices[6] = {
		0, 1, 3,
		2, 1, 3
	};

	Texture backgroundTexture;
	Texture trackTexture;
	Texture leftupTexture;
	Texture rightupTexture;
	Texture leftdownTexture;
	Texture rightdownTexture;
	Texture trackTxt;
	Texture startTxt;
	Texture aiTxt;
	Texture aiNumTxt;

	Texture track1Texture;
	Texture track2Texture;
	Texture right1Texture;
	Texture right2Texture;
	Texture left1Texture;
	Texture left2Texture;
	Texture track11Txt;
	Texture track12Txt;
	Texture track21Txt;
	Texture track22Txt;
	Texture ai1Txt;
	Texture ai2TXt;
	Texture start1Txt;
	Texture start2Txt;

	Texture dig0Texture;
	Texture dig1Texture;
	Texture dig2Texture;
	Texture dig3Texture;
	Texture dig4Texture;
	Texture dig5Texture;
	Texture dig6Texture;
	Texture dig7Texture;
	Texture dig8Texture;
	Texture dig9Texture;

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

	GLfloat trackImgVertices[20] = {
		600.f / 1600 * mainWindow.getWidth(), 50.f / 900.0f * mainWindow.getHeight(), 1.0f,	0.0f, 0.0f,
		600.f / 1600 * mainWindow.getWidth(), 450.f / 900.0f * mainWindow.getHeight(), 1.0f,		0.0f, 1.0f,
		1000.f / 1600 * mainWindow.getWidth(), 450.f / 900.0f * mainWindow.getHeight(), 1.0f,		1.0f, 1.0f,
		1000.f / 1600 * mainWindow.getWidth(), 50.f / 900.0f * mainWindow.getHeight(), 1.0f,	1.0f, 0.0f
	};

	GLfloat trackNameVertices[20] = {
		675.f / 1600 * mainWindow.getWidth(), 470.f / 900.0f * mainWindow.getHeight(), 1.0f,	0.0f, 0.0f,
		675.f / 1600 * mainWindow.getWidth(), 570.f / 900.0f * mainWindow.getHeight(), 1.0f,		0.0f, 1.0f,
		925.f / 1600 * mainWindow.getWidth(), 570.f / 900.0f * mainWindow.getHeight(), 1.0f,		1.0f, 1.0f,
		925.f / 1600 * mainWindow.getWidth(), 470.f / 900.0f * mainWindow.getHeight(), 1.0f,	1.0f, 0.0f
	};

	GLfloat left1Vertices[20] = {
		615.f / 1600 * mainWindow.getWidth(), 495.f / 900.0f * mainWindow.getHeight(), 1.0f,	0.0f, 0.0f,
		615.f / 1600 * mainWindow.getWidth(), 545.f / 900.0f * mainWindow.getHeight(), 1.0f,		0.0f, 1.0f,
		665.f / 1600 * mainWindow.getWidth(), 545.f / 900.0f * mainWindow.getHeight(), 1.0f,		1.0f, 1.0f,
		665.f / 1600 * mainWindow.getWidth(), 495.f / 900.0f * mainWindow.getHeight(), 1.0f,	1.0f, 0.0f
	};

	GLfloat right1Vertices[20] = {
		935.f / 1600 * mainWindow.getWidth(), 495.f / 900.0f * mainWindow.getHeight(), 1.0f,	0.0f, 0.0f,
		935.f / 1600 * mainWindow.getWidth(), 545.f / 900.0f * mainWindow.getHeight(), 1.0f,		0.0f, 1.0f,
		985.f / 1600 * mainWindow.getWidth(), 545.f / 900.0f * mainWindow.getHeight(), 1.0f,		1.0f, 1.0f,
		985.f / 1600 * mainWindow.getWidth(), 495.f / 900.0f * mainWindow.getHeight(), 1.0f,	1.0f, 0.0f
	};

	GLfloat aiVertices[20] = {
		675.f / 1600 * mainWindow.getWidth(), 600.f / 900.0f * mainWindow.getHeight(), 1.0f,	0.0f, 0.0f,
		675.f / 1600 * mainWindow.getWidth(), 700.f / 900.0f * mainWindow.getHeight(), 1.0f,		0.0f, 1.0f,
		925.f / 1600 * mainWindow.getWidth(), 700.f / 900.0f * mainWindow.getHeight(), 1.0f,		1.0f, 1.0f,
		925.f / 1600 * mainWindow.getWidth(), 600.f / 900.0f * mainWindow.getHeight(), 1.0f,	1.0f, 0.0f
	};

	GLfloat aiNumVertices[20] = {
		852.5f / 1600 * mainWindow.getWidth(), 625.f / 900.0f * mainWindow.getHeight(), 1.0f,	0.0f, 0.0f,
		852.5f / 1600 * mainWindow.getWidth(), 675.f / 900.0f * mainWindow.getHeight(), 1.0f,		0.0f, 1.0f,
		877.5f / 1600 * mainWindow.getWidth(), 675.f / 900.0f * mainWindow.getHeight(), 1.0f,		1.0f, 1.0f,
		877.5f / 1600 * mainWindow.getWidth(), 625.f / 900.0f * mainWindow.getHeight(), 1.0f,	1.0f, 0.0f
	};

	GLfloat left2Vertices[20] = {
		770.f / 1600 * mainWindow.getWidth(), 625.f / 900.0f * mainWindow.getHeight(), 1.0f,	0.0f, 0.0f,
		770.f / 1600 * mainWindow.getWidth(), 675.f / 900.0f * mainWindow.getHeight(), 1.0f,		0.0f, 1.0f,
		830.f / 1600 * mainWindow.getWidth(), 675.f / 900.0f * mainWindow.getHeight(), 1.0f,		1.0f, 1.0f,
		830.f / 1600 * mainWindow.getWidth(), 625.f / 900.0f * mainWindow.getHeight(), 1.0f,	1.0f, 0.0f
	};

	GLfloat right2Vertices[20] = {
		900.f / 1600 * mainWindow.getWidth(), 625.f / 900.0f * mainWindow.getHeight(), 1.0f,	0.0f, 0.0f,
		900.f / 1600 * mainWindow.getWidth(), 675.f / 900.0f * mainWindow.getHeight(), 1.0f,		0.0f, 1.0f,
		950.f / 1600 * mainWindow.getWidth(), 675.f / 900.0f * mainWindow.getHeight(), 1.0f,		1.0f, 1.0f,
		950.f / 1600 * mainWindow.getWidth(), 625.f / 900.0f * mainWindow.getHeight(), 1.0f,	1.0f, 0.0f
	};

	GLfloat startVertices[20] = {
		550.f / 1600 * mainWindow.getWidth(), 700.f / 900.0f * mainWindow.getHeight(), 1.0f,	0.0f, 0.0f,
		550.f / 1600 * mainWindow.getWidth(), 900.f / 900.0f * mainWindow.getHeight(), 1.0f,		0.0f, 1.0f,
		1050.f / 1600 * mainWindow.getWidth(), 900.f / 900.0f * mainWindow.getHeight(), 1.0f,		1.0f, 1.0f,
		1050.f / 1600 * mainWindow.getWidth(), 700.f / 900.0f * mainWindow.getHeight(), 1.0f,	1.0f, 0.0f
	};

 	void setOption(int op);
};
