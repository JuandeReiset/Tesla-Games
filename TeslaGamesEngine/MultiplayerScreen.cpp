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

	numTxt = dig1Texture;
	leftTexture = left1Texture;
	rightTexture = right1Texture;
}

void MultiplayerScreen::loadShader() {
	hudShader.createHUDFromFiles(vHshader, fHshader);
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

	glEnable(GL_DEPTH_TEST);
}