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

	HUD* player1 = new HUD();
	player1->createHUD(player1Vertices, indices, 20, 6);
	HUDList.push_back(player1);

	HUD* player2 = new HUD();
	player2->createHUD(player2Vertices, indices, 20, 6);
	HUDList.push_back(player2);

	HUD* player3 = new HUD();
	player3->createHUD(player3Vertices, indices, 20, 6);
	HUDList.push_back(player3);

	HUD* player4 = new HUD();
	player4->createHUD(player4Vertices, indices, 20, 6);
	HUDList.push_back(player4);
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

	player1Texture = Texture("Textures/p1.png");
	player1Texture.LoadTextureAlpha();

	player2Texture = Texture("Textures/p2.png");
	player2Texture.LoadTextureAlpha();

	player3Texture = Texture("Textures/p3.png");
	player3Texture.LoadTextureAlpha();

	player4Texture = Texture("Textures/p4.png");
	player4Texture.LoadTextureAlpha();

	
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

	if (p1Ready) {
		player1Texture.UseTexture();
		HUDList[4]->renderHUD();
	}

	if (p2Ready) {
		player2Texture.UseTexture();
		HUDList[5]->renderHUD();
	}

	if (p3Ready) {
		player3Texture.UseTexture();
		HUDList[6]->renderHUD();
	}

	if (p4Ready) {
		player4Texture.UseTexture();
		HUDList[7]->renderHUD();
	}

	glEnable(GL_DEPTH_TEST);

	return;
}

void ReadyScreen::loadController(Controller *controller, int num) {
	controller->update();

	if (controller->isButtonDown(XButtons.A)) {
		switch (num) {
		case 0:
			p1Ready = true;
			break;
		case 1:
			p2Ready = true;
			break;
		case 2:
			p3Ready = true;
			break;
		case 3:
			p4Ready = true;
			break;
		}
	}
	else if (controller->isButtonDown(XButtons.B)) {
		multiplayerScreenFlag = false;
		readyScreenFlag = false;
		menuFlag = true;
		startScreenFlag = false;
		gameFlag = false;
		pauseFlag = false;
	}

	switch (numOfPlayer) {
	case 1:
		if (p1Ready) {
			multiplayerScreenFlag = false;
			readyScreenFlag = false;
			gameFlag = true;
			startScreenFlag = false;
			menuFlag = false;
			pauseFlag = false;
		}
		break;
	case 2:
		if(p1Ready && p2Ready){
			multiplayerScreenFlag = false;
			readyScreenFlag = false;
			gameFlag = true;
			startScreenFlag = false;
			menuFlag = false;
			pauseFlag = false;
		}
		break;
	case 3:
		if(p1Ready&&p2Ready&&p3Ready){
			multiplayerScreenFlag = false;
			readyScreenFlag = false;
			gameFlag = true;
			startScreenFlag = false;
			menuFlag = false;
			pauseFlag = false;
		}
		break;
	case 4:
		if (p1Ready && p2Ready && p3Ready && p4Ready) {
			multiplayerScreenFlag = false;
			readyScreenFlag = false;
			gameFlag = true;
			startScreenFlag = false;
			menuFlag = false;
			pauseFlag = false;
		}
	}

	controller->refreshState();
}

void ReadyScreen::reset() {
	p1Ready = false;
	p2Ready = false;
	p3Ready = false;
	p4Ready = false;
}