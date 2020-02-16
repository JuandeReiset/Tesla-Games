#include "HUDcreator.h"
#include <iostream>

HUDcreator::HUDcreator(const Window& window) { mainWindow = window; }

void HUDcreator::loadHUD() {
	HUD* weaponUI = new HUD();
	weaponUI->createHUD(weaponUIVertices, HUDindices, 20, 6);
	HUDList.push_back(weaponUI);
	TextureList.push_back(weaponUITexture);

	HUD* numOfWeapon = new HUD();
	numOfWeapon->createHUD(numOfWeaponVertices, HUDindices, 20, 6);
	HUDList.push_back(numOfWeapon);
	TextureList.push_back(dig3Texture);

	HUD* bar1 = new HUD();
	bar1->createHUD(emptyBar1Vertices, HUDindices, 20, 6);
	HUDList.push_back(bar1);
	TextureList.push_back(emptyTexture);

	HUD* bar2 = new HUD();
	bar2->createHUD(emptyBar2Vertices, HUDindices, 20, 6);
	HUDList.push_back(bar2);
	TextureList.push_back(emptyTexture);

	HUD* healthBar = new HUD();
	healthBar->createHUD(emptyBar1Vertices, HUDindices, 20, 6);
	HUDList.push_back(healthBar);
	TextureList.push_back(healthBarTexture);

	HUD* nitroBar = new HUD();
	nitroBar->createHUD(emptyBar2Vertices, HUDindices, 20, 6);
	HUDList.push_back(nitroBar);
	TextureList.push_back(nitroBarTexture);

	HUD* plusSymbol = new HUD();
	plusSymbol->createHUD(plusVertices, HUDindices, 20, 6);
	HUDList.push_back(plusSymbol);
	TextureList.push_back(plusSymbolTexture);

	HUD* nitroSymbol = new HUD();
	nitroSymbol->createHUD(nitroSymbolVertices, HUDindices, 20, 6);
	HUDList.push_back(nitroSymbol);
	TextureList.push_back(nitroSymbolTexture);

	HUD* cupUI = new HUD();
	cupUI->createHUD(cupVertices, HUDindices, 20, 6);
	HUDList.push_back(cupUI);
	TextureList.push_back(cupTexture);

	HUD* rank1num = new HUD();
	rank1num->createHUD(rank1numVertices, HUDindices, 20, 6);
	HUDList.push_back(rank1num);
	TextureList.push_back(emptyTexture);

	HUD* rank2num = new HUD();
	rank2num->createHUD(rank2numVertices, HUDindices, 20, 6);
	HUDList.push_back(rank2num);
	TextureList.push_back(dig2Texture);

	HUD* flagUI = new HUD();
	flagUI->createHUD(flagVertices, HUDindices, 20, 6);
	HUDList.push_back(flagUI);
	TextureList.push_back(flagTexture);

	HUD* lap1num = new HUD();
	lap1num->createHUD(lap1numVertices, HUDindices, 20, 6);
	HUDList.push_back(lap1num);
	TextureList.push_back(emptyTexture);

	HUD* lap2num = new HUD();
	lap2num->createHUD(lap2numVertices, HUDindices, 20, 6);
	HUDList.push_back(lap2num);
	TextureList.push_back(dig3Texture);

	HUD* personUI = new HUD();
	personUI->createHUD(personVertices, HUDindices, 20, 6);
	HUDList.push_back(personUI);
	TextureList.push_back(personTexture);

	HUD* alive1num = new HUD();
	alive1num->createHUD(alive1numVertices, HUDindices, 20, 6);
	HUDList.push_back(alive1num);
	TextureList.push_back(dig1Texture);

	HUD* alive2num = new HUD();
	alive2num->createHUD(alive2numVertices, HUDindices, 20, 6);
	HUDList.push_back(alive2num);
	TextureList.push_back(dig0Texture);

	return;
}

void HUDcreator::loadTextures() {
	//load digits textures
	dig0Texture = Texture("Textures/numbers/0.png");
	dig0Texture.LoadTextureAlpha();
	dig1Texture = Texture("Textures/numbers/1.png");
	dig1Texture.LoadTextureAlpha();
	dig2Texture = Texture("Textures/numbers/2.png");
	dig2Texture.LoadTextureAlpha();
	dig3Texture = Texture("Textures/numbers/3.png");
	dig3Texture.LoadTextureAlpha();

	//load HUD textures
	weaponUITexture = Texture("Textures/HUD/WeaponsUI.png");
	weaponUITexture.LoadTextureAlpha();
	emptyBarTexture = Texture("Textures/HUD/emptybar.png");
	emptyBarTexture.LoadTextureAlpha();
	healthBarTexture = Texture("Textures/HUD/healthbar.png");
	healthBarTexture.LoadTextureAlpha();
	nitroBarTexture = Texture("Textures/HUD/nitro.png");
	nitroBarTexture.LoadTextureAlpha();
	plusSymbolTexture = Texture("Textures/HUD/plus.png");
	plusSymbolTexture.LoadTextureAlpha();
	nitroSymbolTexture = Texture("Textures/HUD/nitrosymbol.png");
	nitroSymbolTexture.LoadTextureAlpha();
	personTexture = Texture("Textures/HUD/alive.png");
	personTexture.LoadTextureAlpha();
	cupTexture = Texture("Textures/HUD/cup.png");
	cupTexture.LoadTextureAlpha();
	flagTexture = Texture("Textures/HUD/flags.png");
	flagTexture.LoadTextureAlpha();

	return;
}

void HUDcreator::loadShader() {
	hudShader.createHUDFromFiles(vHshader, fHshader);
}

void HUDcreator::load() {
	loadShader();
	loadTextures();
	loadHUD();

	return;
}

void HUDcreator::use() {

	hudShader.UseShader();

	GLint uniformModel = hudShader.GetModelLocation();
	GLint uniformProjection = hudShader.GetProjectionLocation();

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 ortho = glm::ortho(0.0f, (float)mainWindow.getWidth(), (float)mainWindow.getHeight(), 0.0f);						//orthograohic projection

	glDisable(GL_DEPTH_TEST);																									//disable the depth-testing

	glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(ortho));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

	for (int i = 0; i < HUDList.size(); ++i) {
		TextureList[i].UseTexture();
		HUDList[i]->renderHUD();
	}

	glEnable(GL_DEPTH_TEST);

	return;
}