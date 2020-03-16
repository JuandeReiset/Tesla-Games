#include "Menu.h"

void Menu::loadVertices() {
	HUD* background = new HUD();
	background->createHUD(backgroundVertices, indices, 20, 6);
	HUDList.push_back(background);

	HUD* audio = new HUD();
	audio->createHUD(audioVertices, indices, 20, 6);
	HUDList.push_back(audio);

	HUD* HUDsize = new HUD();
	HUDsize->createHUD(HUDVertices, indices, 20, 6);
	HUDList.push_back(HUDsize);

	HUD* goBack = new HUD();
	goBack->createHUD(goBackVertices, indices, 20, 6);
	HUDList.push_back(goBack);

	HUD* menu = new HUD();
	menu->createHUD(menuVertices, indices, 20, 6);
	HUDList.push_back(menu);
}

void Menu::loadTextures() {
	backgroundTexture = Texture("Textures/background.png");
	backgroundTexture.LoadTextureAlpha();
	goBackTxt = Texture("Textures/goback.png");
	goBackTxt.LoadTextureAlpha();
	menuTxt = Texture("Textures/menu.png");
	menuTxt.LoadTextureAlpha();

	audioTxt1 = Texture("Textures/audio1.png");
	audioTxt1.LoadTextureAlpha();
	audioTxt2 = Texture("Textures/audio2.png");
	audioTxt2.LoadTextureAlpha();
	audioTxt = audioTxt2;

	HUDSizeTxt1 = Texture("Textures/hudsize.png");
	HUDSizeTxt1.LoadTextureAlpha();
	HUDSizeTxt2 = Texture("Textures/hudsize1.png");
	HUDSizeTxt2.LoadTextureAlpha();
	HUDSizeTxt = HUDSizeTxt1;
}

void Menu::loadShader() {
	hudShader.createHUDFromFiles(vHshader, fHshader);
}

void Menu::load() {
	loadShader();
	loadTextures();
	loadVertices();
}

void Menu::use() {
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

	audioTxt.UseTexture();
	HUDList[1]->renderHUD();

	HUDSizeTxt.UseTexture();
	HUDList[2]->renderHUD();

	goBackTxt.UseTexture();
	HUDList[3]->renderHUD();

	menuTxt.UseTexture();
	HUDList[4]->renderHUD();

	glEnable(GL_DEPTH_TEST);
}

void Menu::setOption(int op) {
	if (op == 0) {
		audioTxt = audioTxt2;
		HUDSizeTxt = HUDSizeTxt1;
	}
	else if (op == 1) {
		audioTxt = audioTxt1;
		HUDSizeTxt = HUDSizeTxt2;
	}
}