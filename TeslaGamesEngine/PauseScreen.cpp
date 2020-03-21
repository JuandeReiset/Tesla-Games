#include "PauseScreen.h"

void PauseScreen::loadVertices() {
	HUD* background = new HUD();
	background->createHUD(backgroundVertices, indices, 20, 6);
	HUDList.push_back(background);

	HUD* logo = new HUD();
	logo->createHUD(logoVertices, indices, 20, 6);
	HUDList.push_back(logo);

	HUD* resume = new HUD();
	resume->createHUD(resumeVertices, indices, 20, 6);
	HUDList.push_back(resume);

	HUD* title = new HUD();
	title->createHUD(titleVertices, indices, 20, 6);
	HUDList.push_back(title);
}

void PauseScreen::loadTextures() {
	backgroundTexture = Texture("Textures/background.png");
	backgroundTexture.LoadTextureAlpha();

	logoTexture = Texture("Textures/paused.png");
	logoTexture.LoadTextureAlpha();

	resume1Txt = Texture("Textures/resume1.png");
	resume1Txt.LoadTextureAlpha();
	resume2Txt = Texture("Textures/resume2.png");
	resume2Txt.LoadTextureAlpha();

	title1Txt = Texture("Textures/backToTitle1.png");
	title1Txt.LoadTextureAlpha();
	title2Txt = Texture("Textures/backToTitle2.png");
	title2Txt.LoadTextureAlpha();

	resumeTxt = resume2Txt;
	titleTxt = title1Txt;
}

void PauseScreen::loadShader() {
	hudShader.createHUDFromFiles(vHshader, fHshader);
}

void PauseScreen::load() {
	loadShader();
	loadTextures();
	loadVertices();

	op = 0;
}

void PauseScreen::use() {
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

	resumeTxt.UseTexture();
	HUDList[2]->renderHUD();

	titleTxt.UseTexture();
	HUDList[3]->renderHUD();

	glEnable(GL_DEPTH_TEST);

	return;
}

void PauseScreen::loadController(Controller* controller) {
	controller->update();

	if (controller->isButtonDown(XButtons.DPad_Up)) {
		if (op == 0)
			;
		else
			--op;
		setOption();
	}
	else if (controller->isButtonDown(XButtons.DPad_Down)) {
		if (op == 1)
			;
		else
			++op;
		setOption();
	}
	else if (controller->isButtonDown(XButtons.A)) {
		if (op == 0) {
			pauseFlag = false;
			gameFlag = true;
			startScreenFlag = false;
			menuFlag = false;
			readyScreenFlag = false;
		}
		else if (op == 1) {
			pauseFlag = false;
			startScreenFlag = true;
			gameFlag = false;
			menuFlag = false;
			readyScreenFlag = false;
			op = 0;
			setOption();
		}
	}
}

void PauseScreen::setOption() {
	if (op == 0) {
		resumeTxt = resume2Txt;
		titleTxt = title1Txt;
	}
	else if (op == 1) {
		resumeTxt = resume1Txt;
		titleTxt = title2Txt;
	}
}