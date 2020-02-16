#include "HUDcreator.h"
#include <iostream>


void HUDcreator::loadHUD() {
	HUD* weaponUI = new HUD();
	weaponUI->createHUD(weaponUIVertices, HUDindices, 20, 6);
	HUDList.push_back(weaponUI);

	HUD* numOfWeapon = new HUD();
	numOfWeapon->createHUD(numOfWeaponVertices, HUDindices, 20, 6);
	HUDList.push_back(numOfWeapon);

	HUD* bar1 = new HUD();
	bar1->createHUD(emptyBar1Vertices, HUDindices, 20, 6);
	HUDList.push_back(bar1);

	HUD* bar2 = new HUD();
	bar2->createHUD(emptyBar2Vertices, HUDindices, 20, 6);
	HUDList.push_back(bar2);

	HUD* healthBar = new HUD();
	healthBar->createHUD(emptyBar1Vertices, HUDindices, 20, 6);
	HUDList.push_back(healthBar);

	HUD* nitroBar = new HUD();
	nitroBar->createHUD(emptyBar2Vertices, HUDindices, 20, 6);
	HUDList.push_back(nitroBar);

	HUD* plusSymbol = new HUD();
	plusSymbol->createHUD(plusVertices, HUDindices, 20, 6);
	HUDList.push_back(plusSymbol);

	HUD* nitroSymbol = new HUD();
	nitroSymbol->createHUD(nitroSymbolVertices, HUDindices, 20, 6);
	HUDList.push_back(nitroSymbol);

	HUD* cupUI = new HUD();
	cupUI->createHUD(cupVertices, HUDindices, 20, 6);
	HUDList.push_back(cupUI);

	HUD* rank1num = new HUD();
	rank1num->createHUD(rank1numVertices, HUDindices, 20, 6);
	HUDList.push_back(rank1num);

	HUD* rank2num = new HUD();
	rank2num->createHUD(rank2numVertices, HUDindices, 20, 6);
	HUDList.push_back(rank2num);

	HUD* flagUI = new HUD();
	flagUI->createHUD(flagVertices, HUDindices, 20, 6);
	HUDList.push_back(flagUI);

	HUD* lap1num = new HUD();
	lap1num->createHUD(lap1numVertices, HUDindices, 20, 6);
	HUDList.push_back(lap1num);

	HUD* lap2num = new HUD();
	lap2num->createHUD(lap2numVertices, HUDindices, 20, 6);
	HUDList.push_back(lap2num);

	HUD* personUI = new HUD();
	personUI->createHUD(personVertices, HUDindices, 20, 6);
	HUDList.push_back(personUI);

	HUD* alive1num = new HUD();
	alive1num->createHUD(alive1numVertices, HUDindices, 20, 6);
	HUDList.push_back(alive1num);

	HUD* alive2num = new HUD();
	alive2num->createHUD(alive2numVertices, HUDindices, 20, 6);
	HUDList.push_back(alive2num);
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
/*
	for (int i = 0; i < HUDList.size(); ++i) {
		TextureList[i].UseTexture();
		HUDList[i]->renderHUD();
	}
*/
//weapon UI
	weaponUITexture.UseTexture();
	HUDList[0]->renderHUD();

	//number of charges
	dig3Texture.UseTexture();
	HUDList[1]->renderHUD();

	//TODO: if out of charges, change ui

	//bars
	//empty bar1
	emptyBarTexture.UseTexture();
	HUDList[2]->renderHUD();

	//empty bar2
	emptyBarTexture.UseTexture();
	HUDList[3]->renderHUD();

	//health bar
	healthBarTexture.UseTexture();
	HUDList[4]->renderHUD();

	//nitro bar
	nitroBarTexture.UseTexture();
	HUDList[5]->renderHUD();

	//plus symbol
	plusSymbolTexture.UseTexture();
	HUDList[6]->renderHUD();

	//nitro symbol
	nitroSymbolTexture.UseTexture();
	HUDList[7]->renderHUD();

	//race info
	//current rank
	cupTexture.UseTexture();
	HUDList[8]->renderHUD();
	dig2Texture.UseTexture();
	HUDList[10]->renderHUD();

	//current laps
	flagTexture.UseTexture();
	HUDList[11]->renderHUD();
	dig3Texture.UseTexture();
	HUDList[13]->renderHUD();

	//current alive
	personTexture.UseTexture();
	HUDList[14]->renderHUD();
	dig1Texture.UseTexture();
	HUDList[15]->renderHUD();
	dig0Texture.UseTexture();
	HUDList[16]->renderHUD();

	glEnable(GL_DEPTH_TEST);
	std::cout << weaponUIVertices[1] << std::endl;

	return;
}