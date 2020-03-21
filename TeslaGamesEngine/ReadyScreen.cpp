#include "ReadyScreen.h"

void ReadyScreen::loadVertices() {
	HUD* background = new HUD();
	background->createHUD(backgroundVertices, indices, 20, 6);
	HUDList.push_back(background);

	HUD* controller = new HUD();
	controller->createHUD(controllerVertices, indices, 20, 6);
	HUDList.push_back(controller);

	HUD* ready = new HUD();
	ready->createHUD(readyVertices, indices, 20, 6);
	HUDList.push_back(ready);

	HUD* back = new HUD();
	back->createHUD(backVertices, indices, 20, 6);
	HUDList.push_back(back);
}

void ReadyScreen::loadTextures() {
	backgroundTexture = Texture("Textures/background.png");
	backgroundTexture.LoadTextureAlpha();

	controllerTexture = Texture("Textures/controller_scheme.png");
	controllerTexture.LoadTextureAlpha();

	readyTexture = Texture("Textures/ready.png");
	readyTexture.LoadTextureAlpha();

	backTexture = Texture("Textures/goback.png");
	backTexture.LoadTextureAlpha();
}

void ReadyScreen::loadShader() {
	hudShader.createHUDFromFiles(vHshader, fHshader);

	return;
}

void ReadyScreen::load() {
	loadShader();
	loadTextures();
	loadVertices();
}

void ReadyScreen::use() {
	hudShader.UseShader();

	GLint uniformModel = hudShader.GetModelLocation();
	GLint uniformProjection = hudShader.GetProjectionLocation();

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 ortho = glm::ortho(0.0f, (float)mainWindow.getWidth(), (float)mainWindow.getHeight(), 0.0f);						//orthograohic projection

	glDisable(GL_DEPTH_TEST);																									//disable the depth-testing

	glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(ortho));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

	backgroundTexture.UseTexture();
	HUDList[0]->renderHUD();

	controllerTexture.UseTexture();
	HUDList[1]->renderHUD();

	readyTexture.UseTexture();
	HUDList[2]->renderHUD();

	backTexture.UseTexture();
	HUDList[3]->renderHUD();

	glEnable(GL_DEPTH_TEST);

	return;
}

void ReadyScreen::loadController(Controller *controller) {
	controller->update();

	if (controller->isButtonDown(XButtons.A)) {
		readyScreenFlag = false;
		gameFlag = true;
		startScreenFlag = false;
		menuFlag = false;
		pauseFlag = false;
	}
	else if (controller->isButtonDown(XButtons.B)) {
		readyScreenFlag = false;
		menuFlag = true;
		startScreenFlag = false;
		gameFlag = false;
		pauseFlag = false;
	}

	controller->refreshState();
}