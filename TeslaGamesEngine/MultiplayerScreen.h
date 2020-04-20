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

class MultiplayerScreen
{
public:
	MultiplayerScreen() = default;

	void loadVertices();
	void loadTextures();
	void use();
	void load();
	void loadShader();

	void setPlayerNum(int num);
	void loadController(Controller* controller);
	int getNumOfPlayer() { return numOfPlayer; };

private:
	std::vector<HUD*> HUDList;
	Shader hudShader;
	GLfloat last;
	int arrow = -1;

	unsigned int indices[6] = {
		0, 1, 3,
		2, 1, 3
	};

	// Vertex Shader of HUD_shader
	const char* vHshader = "Shaders/HUD_shader.vert";

	//Fragment shader of HUD_shader
	const char* fHshader = "Shaders/HUD_shader.frag";

	Texture backgroundTexture;
	Texture leftTexture;
	Texture rightTexture;
	Texture playerNumTxt;
	Texture backTexture;
	Texture readyTexture;
	Texture numTxt;

	Texture left1Texture;
	Texture left2Texture;
	Texture right1Texture;
	Texture right2Texture;
	Texture dpadTexture;
	Texture selectTexture;

	Texture dig1Texture;
	Texture dig2Texture;
	Texture dig3Texture;
	Texture dig4Texture;

	GLfloat backgroundVertices[20] = {
		0.0f / 1600 * mainWindow.getWidth(), 0.f / 900.0f * mainWindow.getHeight(), 0.0f,	0.0f, 0.0f,								//bottom left
		0.0f / 1600 * mainWindow.getWidth(), 900.0f / 900.0f * mainWindow.getHeight(), 0.0f,		0.0f, 1.0f,								//top left
		1600.0f / 1600 * mainWindow.getWidth(), 900 / 900.0f * mainWindow.getHeight(), 0.0f,		1.0f, 1.0f,								//top right
		1600.0f / 1600 * mainWindow.getWidth(), 0.f / 900.0f * mainWindow.getHeight(), 0.0f,	1.0f, 0.0f								//bottom right
	};

	GLfloat selectPlayerVertices[20] = {
		300.0f / 1600 * mainWindow.getWidth(), 250.f / 900.0f * mainWindow.getHeight(), 0.0f,	0.0f, 0.0f,								
		300.0f / 1600 * mainWindow.getWidth(), 650.0f / 900.0f * mainWindow.getHeight(), 0.0f,		0.0f, 1.0f,								
		1300.0f / 1600 * mainWindow.getWidth(), 650 / 900.0f * mainWindow.getHeight(), 0.0f,		1.0f, 1.0f,								
		1300.0f / 1600 * mainWindow.getWidth(), 250.f / 900.0f * mainWindow.getHeight(), 0.0f,	1.0f, 0.0f								
	};

	GLfloat playerNumVertices[20] = {
		750.0f / 1600 * mainWindow.getWidth(), 550.f / 900.0f * mainWindow.getHeight(), 0.0f,	0.0f, 0.0f,
		750.0f / 1600 * mainWindow.getWidth(), 650.0f / 900.0f * mainWindow.getHeight(), 0.0f,		0.0f, 1.0f,
		850.0f / 1600 * mainWindow.getWidth(), 650 / 900.0f * mainWindow.getHeight(), 0.0f,		1.0f, 1.0f,
		850.0f / 1600 * mainWindow.getWidth(), 550.f / 900.0f * mainWindow.getHeight(), 0.0f,	1.0f, 0.0f
	};

	GLfloat leftVertices[20] = {
		640.0f / 1600 * mainWindow.getWidth(), 550.f / 900.0f * mainWindow.getHeight(), 0.0f,	0.0f, 0.0f,
		640.0f / 1600 * mainWindow.getWidth(), 650.0f / 900.0f * mainWindow.getHeight(), 0.0f,		0.0f, 1.0f,
		740.0f / 1600 * mainWindow.getWidth(), 650 / 900.0f * mainWindow.getHeight(), 0.0f,		1.0f, 1.0f,
		740.0f / 1600 * mainWindow.getWidth(), 550.f / 900.0f * mainWindow.getHeight(), 0.0f,	1.0f, 0.0f
	};

	GLfloat rightVertices[20] = {
		860.0f / 1600 * mainWindow.getWidth(), 550.f / 900.0f * mainWindow.getHeight(), 0.0f,	0.0f, 0.0f,
		860.0f / 1600 * mainWindow.getWidth(), 650.0f / 900.0f * mainWindow.getHeight(), 0.0f,		0.0f, 1.0f,
		960.0f / 1600 * mainWindow.getWidth(), 650 / 900.0f * mainWindow.getHeight(), 0.0f,		1.0f, 1.0f,
		960.0f / 1600 * mainWindow.getWidth(), 550.f / 900.0f * mainWindow.getHeight(), 0.0f,	1.0f, 0.0f
	};

	GLfloat readyVertices[20] = {
		675.0f / 1600 * mainWindow.getWidth(), 700.f / 900.0f * mainWindow.getHeight(), 0.0f,	0.0f, 0.0f,
		675.0f / 1600 * mainWindow.getWidth(), 800.f / 900.0f * mainWindow.getHeight(), 0.0f,		0.0f, 1.0f,
		925.0f / 1600 * mainWindow.getWidth(), 800.f / 900.0f * mainWindow.getHeight(), 0.0f,		1.0f, 1.0f,
		925.0f / 1600 * mainWindow.getWidth(), 700.f / 900.0f * mainWindow.getHeight(), 0.0f,	1.0f, 0.0f
	};

	GLfloat backVertices[20] = {
		1400.f / 1600 * mainWindow.getWidth(), 820.f / 900.0f * mainWindow.getHeight(), 1.0f,	0.0f, 0.0f,
		1400.f / 1600 * mainWindow.getWidth(), 900.f / 900.0f * mainWindow.getHeight(), 1.0f,		0.0f, 1.0f,
		1600.f / 1600 * mainWindow.getWidth(), 900.f / 900.0f * mainWindow.getHeight(), 1.0f,		1.0f, 1.0f,
		1600.f / 1600 * mainWindow.getWidth(), 820.f / 900.0f * mainWindow.getHeight(), 1.0f,	1.0f, 0.0f
	};

	GLfloat dpadVertices[20] = {
		0.f / 1600 * mainWindow.getWidth(), 800.f / 900.0f * mainWindow.getHeight(), 1.0f,	0.0f, 0.0f,
		0.f / 1600 * mainWindow.getWidth(), 920.f / 900.0f * mainWindow.getHeight(), 1.0f,		0.0f, 1.0f,
		300.f / 1600 * mainWindow.getWidth(), 920.f / 900.0f * mainWindow.getHeight(), 1.0f,		1.0f, 1.0f,
		300.f / 1600 * mainWindow.getWidth(), 800.f / 900.0f * mainWindow.getHeight(), 1.0f,	1.0f, 0.0f
	};

	GLfloat selectVertices[20] = {
		0.f / 1600 * mainWindow.getWidth(), 760.f / 900.0f * mainWindow.getHeight(), 1.0f,	0.0f, 0.0f,
		0.f / 1600 * mainWindow.getWidth(), 880.f / 900.0f * mainWindow.getHeight(), 1.0f,		0.0f, 1.0f,
		300.f / 1600 * mainWindow.getWidth(), 880.f / 900.0f * mainWindow.getHeight(), 1.0f,		1.0f, 1.0f,
		300.f / 1600 * mainWindow.getWidth(), 760.f / 900.0f * mainWindow.getHeight(), 1.0f,	1.0f, 0.0f
	};
	int numOfPlayer = 1;
	int maxPlayer = 4;

	void setPlayerNumTexture();
	void setArrow();
	void resetArrow();
};

