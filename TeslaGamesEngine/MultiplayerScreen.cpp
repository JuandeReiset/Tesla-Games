#include "MultiplayerScreen.h"

void MultiplayerScreen::loadVertices() {
	HUD* background = new HUD();
	background->createHUD(backgroundVertices, indices, 20, 6);
	HUDList.push_back(background);

	HUD* selectPlayer = new HUD();
	selectPlayer->createHUD(selectPlayerVertices, indices, 20, 6);
	HUDList.push_back(selectPlayer);

	HUD* playerNum = new HUD();
	playerNum->createHUD(playerNumVertices, indices, 20, 6);
	HUDList.push_back(playerNum);

	HUD* left = new HUD();
	left->createHUD(leftVertices, indices, 20, 6);
	HUDList.push_back(left);

	HUD* right = new HUD();
	right->createHUD(rightVertices, indices, 20, 6);
	HUDList.push_back(right);

	HUD* ready = new HUD();
	ready->createHUD(readyVertices, indices, 20, 6);
	HUDList.push_back(ready);

	HUD* back = new HUD();
	back->createHUD(backVertices, indices, 20, 6);
	HUDList.push_back(back);
	HUD* select = new HUD();
	select->createHUD(selectVertices, indices, 20, 6);
	HUDList.push_back(select);

	HUD* dpad = new HUD();
	dpad->createHUD(dpadVertices, indices, 20, 6);
	HUDList.push_back(dpad);
}

void MultiplayerScreen::loadTextures() {
	dig1Texture = Texture("Textures/numbers/1.png");
	dig1Texture.LoadTextureAlpha();
	dig2Texture = Texture("Textures/numbers/2.png");
	dig2Texture.LoadTextureAlpha();
	dig3Texture = Texture("Textures/numbers/3.png");
	dig3Texture.LoadTextureAlpha();
	dig4Texture = Texture("Textures/numbers/4.png");
	dig4Texture.LoadTextureAlpha();

	backgroundTexture = Texture("Textures/background.png");
	backgroundTexture.LoadTextureAlpha();
	right1Texture = Texture("Textures/right.png");
	right1Texture.LoadTextureAlpha();
	right2Texture = Texture("Textures/right2.png");
	right2Texture.LoadTextureAlpha();
	left1Texture = Texture("Textures/left.png");
	left1Texture.LoadTextureAlpha();
	left2Texture = Texture("Textures/left2.png");
	left2Texture.LoadTextureAlpha();
	readyTexture = Texture("Textures/ready.png");
	readyTexture.LoadTextureAlpha();
	backTexture = Texture("Textures/goback.png");
	backTexture.LoadTextureAlpha();
	playerNumTxt = Texture("Textures/playerNum.png");
	playerNumTxt.LoadTextureAlpha();
	dpadTexture = Texture("Textures/dpad.png");
	dpadTexture.LoadTextureAlpha();
	selectTexture = Texture("Textures/a_select.png");
	selectTexture.LoadTextureAlpha();

	numTxt = dig1Texture;
	leftTexture = left1Texture;
	rightTexture = right1Texture;
}

void MultiplayerScreen::loadShader() {
	hudShader.createHUDFromFiles(vHshader, fHshader);
}

void MultiplayerScreen::load() {
	loadShader();
	loadTextures();
	loadVertices();
}

void MultiplayerScreen::use() {
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

	playerNumTxt.UseTexture();
	HUDList[1]->renderHUD();

	numTxt.UseTexture();
	HUDList[2]->renderHUD();


	leftTexture.UseTexture();
	HUDList[3]->renderHUD();

	rightTexture.UseTexture();
	HUDList[4]->renderHUD();

	readyTexture.UseTexture();
	HUDList[5]->renderHUD();

	backTexture.UseTexture();
	HUDList[6]->renderHUD();

	//selectTexture.UseTexture();
	//HUDList[7]->renderHUD();

	dpadTexture.UseTexture();
	HUDList[8]->renderHUD();

	glEnable(GL_DEPTH_TEST);
}


void MultiplayerScreen::setPlayerNum(int num) {
	numOfPlayer = num;
	maxPlayer = num;

	setPlayerNumTexture();
}

void MultiplayerScreen::setPlayerNumTexture() {
	switch (numOfPlayer){
	case 2:
		numTxt = dig2Texture;
		break;
	case 3:
		numTxt = dig3Texture;
		break;
	case 4:
		numTxt = dig4Texture;
	default:
		break;
	}
}

void MultiplayerScreen::loadController(Controller* controller) {
	controller->update();
	GLfloat now = glfwGetTime();
	if (now - last >= 0.1)
		resetArrow();

	if (controller->isButtonDown(XButtons.DPad_Left)) {
		if(numOfPlayer > 2)
			--numOfPlayer;
		
		arrow = 0;

		setArrow();
		setPlayerNumTexture();
	}
	else if (controller->isButtonDown(XButtons.DPad_Right)) {

		if (numOfPlayer < maxPlayer)
			++numOfPlayer;

		arrow = 1;
		
		setArrow();
		setPlayerNumTexture();
	}
	else if (controller->isButtonDown(XButtons.A)) {
		multiplayerScreenFlag = false;
		menuFlag = true;
		readyScreenFlag = false;
		startScreenFlag = false;
		pauseFlag = false;
		gameFlag = false;
	}
	else if (controller->isButtonDown(XButtons.B)) {
		multiplayerScreenFlag = false;
		menuFlag = false;
		startScreenFlag = true;
		gameFlag = false;
		readyScreenFlag = false;
		pauseFlag = false;
	}
	controller->refreshState();

}

void MultiplayerScreen::setArrow() {
	last = glfwGetTime();

	if (arrow == 0)
		leftTexture = left2Texture;
	else if (arrow == 1)
		rightTexture = right2Texture;

	arrow = -1;
}

void MultiplayerScreen::resetArrow() {
	leftTexture = left1Texture;
	rightTexture = right1Texture;
}