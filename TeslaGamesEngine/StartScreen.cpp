#include "StartScreen.h"

void StartScreen::loadVertices() {
	HUD* background = new HUD();
	background->createHUD(backgroundVertices, indices, 20, 6);
	HUDList.push_back(background);

	HUD* logo = new HUD();
	logo->createHUD(logoVertices, indices, 20, 6);
	HUDList.push_back(logo);

	HUD* start = new HUD();
	start->createHUD(startVertices, indices, 20, 6);
	HUDList.push_back(start);

	HUD* setting = new HUD();
	setting->createHUD(settingVertices, indices, 20, 6);
	HUDList.push_back(setting);

	HUD* exit = new HUD();
	exit->createHUD(exitVertices, indices, 20, 6);
	HUDList.push_back(exit);

	HUD* select = new HUD();
	select->createHUD(selectVertices, indices, 20, 6);
	HUDList.push_back(select);

	HUD* dpad = new HUD();
	dpad->createHUD(dpadVertices, indices, 20, 6);
	HUDList.push_back(dpad);
}

void StartScreen::loadTextures() {
	backgroundTexture = Texture("Textures/background.png");
	backgroundTexture.LoadTextureAlpha();

	logoTexture = Texture("Textures/logo.jpg");
	logoTexture.LoadTexture();

	startText1 = Texture("Textures/single1.png");
	startText1.LoadTextureAlpha();
	startText2 = Texture("Textures/single2.png");
	startText2.LoadTextureAlpha();
	startText = startText2;

	settingText1 = Texture("Textures/multi1.png");
	settingText1.LoadTextureAlpha();
	settingText2 = Texture("Textures/multi2.png");
	settingText2.LoadTextureAlpha();
	settingText = settingText1;

	exitText1 = Texture("Textures/exit.png");
	exitText1.LoadTextureAlpha();
	exitText2 = Texture("Textures/exit2.png");
	exitText2.LoadTextureAlpha();
	exitText = exitText1;
	dpadTexture = Texture("Textures/dpad.png");
	dpadTexture.LoadTextureAlpha();
	selectTexture = Texture("Textures/a_select.png");
	selectTexture.LoadTextureAlpha();

	return;
}

void StartScreen::loadShader() {
	hudShader.createHUDFromFiles(vHshader, fHshader);

	return;
}

void StartScreen::load() {
	loadShader();
	loadTextures();
	loadVertices();

	op = 0;
	return;
}

void StartScreen::use() {
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

	logoTexture.UseTexture();
	HUDList[1]->renderHUD();
	
	startText.UseTexture();
	HUDList[2]->renderHUD();

	settingText.UseTexture();
	HUDList[3]->renderHUD();

	exitText.UseTexture();
	HUDList[4]->renderHUD();

	selectTexture.UseTexture();
	HUDList[5]->renderHUD();

	dpadTexture.UseTexture();
	HUDList[6]->renderHUD();

	glEnable(GL_DEPTH_TEST);

	return;
}

void StartScreen::setOption(int op) {
	if (op == 0) {
		startText = startText2;
		settingText = settingText1;
		exitText = exitText1;
	}
	else if (op == 1) {
		startText = startText1;
		settingText = settingText2;
		exitText = exitText1;
	}
	else if (op == 2) {
		startText = startText1;
		settingText = settingText1;
		exitText = exitText2;
	}
}

void StartScreen::loadController(Controller *controller) {
	controller->update();
	
	if (controller->isButtonDown(XButtons.DPad_Up)) {
		if (op == 0)
			;
		else
			--op;
		setOption(op);
	}
	else if (controller->isButtonDown(XButtons.DPad_Down)) {
		if (op == 2)
			;
		else
			++op;
		setOption(op);
	}
	else if (controller->isButtonDown(XButtons.A)) {
		if (op == 0) {
			multiplayerScreenFlag = false;
			startScreenFlag = false;
			menuFlag = true;
			gameFlag = false;
			readyScreenFlag = false;
			pauseFlag = false;
			multiplayerFlag = false;
		}
		else if (op == 1) {
			multiplayerScreenFlag = true;
			menuFlag = false;
			startScreenFlag = false;
			gameFlag = false;
			readyScreenFlag = false;
			pauseFlag = false;
			multiplayerFlag = true;
		}
		else if (op == 2) {
			multiplayerScreenFlag = false;
			closeWindowFlag = true;
			startScreenFlag = false;
			gameFlag = false;
			menuFlag = false;
			readyScreenFlag = false;
			pauseFlag = false;
		}
	}

	controller->refreshState();
}