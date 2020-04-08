#include "HUDcreator.h"


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
	bar2->createHUD(emptyBar1Vertices, HUDindices, 20, 6);
	HUDList.push_back(bar2);

	HUD* healthBar = new HUD();
	healthBar->createHUD(emptyBar2Vertices, HUDindices, 20, 6);
	HUDList.push_back(healthBar);

	HUD* nitroBar = new HUD();
	nitroBar->createHUD(emptyBar1Vertices, HUDindices, 20, 6);
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

	HUD* gameStateUI = new HUD();
	gameStateUI->createHUD(gameStateVertices, HUDindices, 20, 6);
	HUDList.push_back(gameStateUI);

	HUD* rankSlash = new HUD();
	rankSlash->createHUD(rankSlashVertices, HUDindices, 20, 6);
	HUDList.push_back(rankSlash);

	HUD* totalRank1 = new HUD();
	totalRank1->createHUD(totalRank1Vertices, HUDindices, 20, 6);
	HUDList.push_back(totalRank1);

	HUD* totalRank2 = new HUD();
	totalRank2->createHUD(totalRank2Vertices, HUDindices, 20, 6);
	HUDList.push_back(totalRank2);

	HUD* lapSlash = new HUD();
	lapSlash->createHUD(lapSlashVertices, HUDindices, 20, 6);
	HUDList.push_back(lapSlash);

	HUD* totalLap1 = new HUD();
	totalLap1->createHUD(totalLap1Vertices, HUDindices, 20, 6);
	HUDList.push_back(totalLap1);

	HUD* totalLap2 = new HUD();
	totalLap2->createHUD(totalLap2Vertices, HUDindices, 20, 6);
	HUDList.push_back(totalLap2);

	HUD* aliveSlash = new HUD();
	aliveSlash->createHUD(aliveSlashVertices, HUDindices, 20, 6);
	HUDList.push_back(aliveSlash);

	HUD* totalAlive1 = new HUD();
	totalAlive1->createHUD(totalAlive1Vertices, HUDindices, 20, 6);
	HUDList.push_back(totalAlive1);

	HUD* totalAlive2 = new HUD();
	totalAlive2->createHUD(totalAlive2Vertices, HUDindices, 20, 6);
	HUDList.push_back(totalAlive2);

	HUD* bullet = new HUD();
	bullet->createHUD(bulletVertices, HUDindices, 20, 6);
	HUDList.push_back(bullet);

	HUD* bulletNum1 = new HUD();
	bulletNum1->createHUD(bulletNum1Vertices, HUDindices, 20, 6);
	HUDList.push_back(bulletNum1);

	HUD* bulletNum2 = new HUD();
	bulletNum2->createHUD(bulletNum2Vertices, HUDindices, 20, 6);
	HUDList.push_back(bulletNum2);

	HUD* oiled = new HUD();
	oiled->createHUD(oiledVertices, HUDindices, 20, 6);
	HUDList.push_back(oiled);
	
	HUD* smoked = new HUD();
	smoked->createHUD(smokedVertices, HUDindices, 20, 6);
	HUDList.push_back(smoked);
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
	dig4Texture = Texture("Textures/numbers/4.png");
	dig4Texture.LoadTextureAlpha();
	dig5Texture = Texture("Textures/numbers/5.png");
	dig5Texture.LoadTextureAlpha();
	dig6Texture = Texture("Textures/numbers/6.png");
	dig6Texture.LoadTextureAlpha();
	dig7Texture = Texture("Textures/numbers/7.png");
	dig7Texture.LoadTextureAlpha();
	dig8Texture = Texture("Textures/numbers/8.png");
	dig8Texture.LoadTextureAlpha();
	dig9Texture = Texture("Textures/numbers/9.png");
	dig9Texture.LoadTextureAlpha();
	slashTexture = Texture("Textures/numbers/slash.png");
	slashTexture.LoadTextureAlpha();


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
	outOfWeaponTexture = Texture("Textures/HUD/outOfWeapon.png");
	outOfWeaponTexture.LoadTextureAlpha();
	winTexture = Texture("Textures/win.png");
	winTexture.LoadTextureAlpha();
	loseTexture = Texture("Textures/lose.png");
	loseTexture.LoadTextureAlpha();
	gameState = Texture();
	bulletSymbolTexture = Texture("Textures/bulletIcon.png");
	bulletSymbolTexture.LoadTextureAlpha();
	outOfBulletTexture = Texture("Textures/ShootingDisabled.png");
	outOfBulletTexture.LoadTextureAlpha();
	smokedTexture = Texture("Textures/smoked.png");
	smokedTexture.LoadTextureAlpha();
	oiledTexture = Texture("Textures/oiled.png");
	oiledTexture.LoadTextureAlpha();

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
	glm::mat4 ortho = glm::ortho(0.0f, (float)mainWindow.getWidth(), (float)mainWindow.getHeight(), 0.0f);

	glDisable(GL_DEPTH_TEST);																									//disable the depth-testing

	glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(ortho));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));


	//weapon UI
	weaponTexture.UseTexture();
	HUDList[0]->renderHUD();

	//number of charges
	abilityNum.UseTexture();
	HUDList[1]->renderHUD();

	//bars
	//empty bar1
	emptyBarTexture.UseTexture();
	HUDList[2]->renderHUD();

	//empty bar2
	//emptyBarTexture.UseTexture();
	//HUDList[3]->renderHUD();

	//health bar
	model = glm::translate(model, glm::vec3(1200.0 / 1600.0 * mainWindow.getWidth(), 0, 0));
	model = glm::scale(model, glm::vec3(currentHealth / 100, 1, 1));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	healthBarTexture.UseTexture();
	HUDList[4]->renderHUD();

	model = glm::mat4(1.f);
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	//nitro bar
	//nitroBarTexture.UseTexture();
	//HUDList[5]->renderHUD();

	//plus symbol
	plusSymbolTexture.UseTexture();
	HUDList[6]->renderHUD();

	//nitro symbol
	//nitroSymbolTexture.UseTexture();
	//HUDList[7]->renderHUD();

	//race info
	//current rank
	cupTexture.UseTexture();
	HUDList[8]->renderHUD();
	posNum1.UseTexture();
	HUDList[9]->renderHUD();
	posNum2.UseTexture();
	HUDList[10]->renderHUD();

	//current laps
	flagTexture.UseTexture();
	HUDList[11]->renderHUD();
	lapNum1.UseTexture();
	HUDList[12]->renderHUD();
	lapNum2.UseTexture();
	HUDList[13]->renderHUD();

	//current alive
	//personTexture.UseTexture();
	//HUDList[14]->renderHUD();
	//aliveNum1.UseTexture();
	//HUDList[15]->renderHUD();
	//aliveNum2.UseTexture();
	//HUDList[16]->renderHUD();

	//win or lose
	if (winOrLose) {
		gameState.UseTexture();
		HUDList[17]->renderHUD();
	}

	//total number stuff
	slashTexture.UseTexture();
	HUDList[18]->renderHUD();
	//dig2Texture.UseTexture();
	aliveNum1.UseTexture();
	HUDList[19]->renderHUD();
	//dig0Texture.UseTexture();
	aliveNum2.UseTexture();
	HUDList[20]->renderHUD();

	// Total laps
	slashTexture.UseTexture();
	HUDList[21]->renderHUD();
	dig0Texture.UseTexture();
	HUDList[22]->renderHUD();
	dig5Texture.UseTexture();
	HUDList[23]->renderHUD();
/*
	slashTexture.UseTexture();
	HUDList[24]->renderHUD();
	dig2Texture.UseTexture();
	HUDList[25]->renderHUD();
	dig0Texture.UseTexture();
	HUDList[26]->renderHUD();
*/

	bulletTexture.UseTexture();
	HUDList[27]->renderHUD();
	bulletNum1.UseTexture();
	HUDList[28]->renderHUD();
	bulletNum2.UseTexture();
	HUDList[29]->renderHUD();

	if (isOiled) {
		oiledTexture.UseTexture();
		HUDList[30]->renderHUD();
	}

	if (isSmoked) {
		smokedTexture.UseTexture();
		HUDList[31]->renderHUD();
	}

	glEnable(GL_DEPTH_TEST);

	return;
}

void HUDcreator::setAbilityNumber(int ability) {
	switch (ability) {
		case 0:	
			abilityNum = dig0Texture;
			weaponTexture = outOfWeaponTexture;
			break;
		case 1:
			abilityNum = dig1Texture;
			weaponTexture = weaponUITexture;
			break;
		case 2:
			abilityNum = dig2Texture;
			weaponTexture = weaponUITexture;
			break;
		case 3:
			abilityNum = dig3Texture;
			weaponTexture = weaponUITexture;
			break;
		case 4:
			abilityNum = dig4Texture;
			weaponTexture = weaponUITexture;
			break;
		case 5:
			abilityNum = dig5Texture;
			weaponTexture = weaponUITexture;
			break;
		case 6:
			abilityNum = dig6Texture;
			weaponTexture = weaponUITexture;
			break;
		case 7:
			abilityNum = dig7Texture;
			weaponTexture = weaponUITexture;
			break;
		case 8:
			abilityNum = dig8Texture;
			weaponTexture = weaponUITexture;
			break;
		case 9:
			abilityNum = dig9Texture;
			weaponTexture = weaponUITexture;
	}
}

void HUDcreator::setGameState(bool isPlayer) {
	if (isPlayer)
		gameState = winTexture;
	else
		gameState = loseTexture;

	winOrLose = true;
}

void HUDcreator::setLapNumber(int lap) {
	int num2 = lap % 10;
	int num1 = lap / 10;

	switch (num1) {
	case 0:
		lapNum1 = dig0Texture;
		break;
	case 1:
		lapNum1 = dig1Texture;
		break;
	case 2:
		lapNum1 = dig2Texture;
		break;
	case 3:
		lapNum1 = dig3Texture;
		break;
	case 4:
		lapNum1 = dig4Texture;
		break;
	case 5:
		lapNum1 = dig5Texture;
		break;
	case 6:
		lapNum1 = dig6Texture;
		break;
	case 7:
		lapNum1 = dig7Texture;
		break;
	case 8:
		lapNum1 = dig8Texture;
		break;
	case 9:
		lapNum1 = dig9Texture;
	}

	switch (num2) {
	case 0:
		lapNum2 = dig0Texture;
		break;
	case 1:
		lapNum2 = dig1Texture;
		break;
	case 2:
		lapNum2 = dig2Texture;
		break;
	case 3:
		lapNum2 = dig3Texture;
		break;
	case 4:
		lapNum2 = dig4Texture;
		break;
	case 5:
		lapNum2 = dig5Texture;
		break;
	case 6:
		lapNum2 = dig6Texture;
		break;
	case 7:
		lapNum2 = dig7Texture;
		break;
	case 8:
		lapNum2 = dig8Texture;
		break;
	case 9:
		lapNum2 = dig9Texture;
	}
}

void HUDcreator::setAliveNumber(int alive) {
	int num2 = alive % 10;
	int num1 = alive / 10;

	switch (num1) {
	case 0:
		aliveNum1 = dig0Texture;
		break;
	case 1:
		aliveNum1 = dig1Texture;
		break;
	case 2:
		aliveNum1 = dig2Texture;
		break;
	case 3:
		aliveNum1 = dig3Texture;
		break;
	case 4:
		aliveNum1 = dig4Texture;
		break;
	case 5:
		aliveNum1 = dig5Texture;
		break;
	case 6:
		aliveNum1 = dig6Texture;
		break;
	case 7:
		aliveNum1 = dig7Texture;
		break;
	case 8:
		aliveNum1 = dig8Texture;
		break;
	case 9:
		aliveNum1 = dig9Texture;
	}

	switch (num2) {
	case 0:
		aliveNum2 = dig0Texture;
		break;
	case 1:
		aliveNum2 = dig1Texture;
		break;
	case 2:
		aliveNum2 = dig2Texture;
		break;
	case 3:
		aliveNum2 = dig3Texture;
		break;
	case 4:
		aliveNum2 = dig4Texture;
		break;
	case 5:
		aliveNum2 = dig5Texture;
		break;
	case 6:
		aliveNum2 = dig6Texture;
		break;
	case 7:
		aliveNum2 = dig7Texture;
		break;
	case 8:
		aliveNum2 = dig8Texture;
		break;
	case 9:
		aliveNum2 = dig9Texture;
	}
}

void HUDcreator::setPositionNumber(int position)
{
	int num2 = position % 10;
	int num1 = position / 10;

	switch (num1) {
	case 0:
		posNum1 = dig0Texture;
		break;
	case 1:
		posNum1 = dig1Texture;
		break;
	case 2:
		posNum1 = dig2Texture;
		break;
	case 3:
		posNum1 = dig3Texture;
		break;
	case 4:
		posNum1 = dig4Texture;
		break;
	case 5:
		posNum1 = dig5Texture;
		break;
	case 6:
		posNum1 = dig6Texture;
		break;
	case 7:
		posNum1 = dig7Texture;
		break;
	case 8:
		posNum1 = dig8Texture;
		break;
	case 9:
		posNum1 = dig9Texture;
	}

	switch (num2) {
	case 0:
		posNum2 = dig0Texture;
		break;
	case 1:
		posNum2 = dig1Texture;
		break;
	case 2:
		posNum2 = dig2Texture;
		break;
	case 3:
		posNum2 = dig3Texture;
		break;
	case 4:
		posNum2 = dig4Texture;
		break;
	case 5:
		posNum2 = dig5Texture;
		break;
	case 6:
		posNum2 = dig6Texture;
		break;
	case 7:
		posNum2 = dig7Texture;
		break;
	case 8:
		posNum2 = dig8Texture;
		break;
	case 9:
		posNum2 = dig9Texture;
	}
}

void HUDcreator::setBulletNum(int bullet) {
	if (bullet == 0) {
		bulletTexture = outOfBulletTexture;
		bulletNum1 = dig0Texture;
		bulletNum2 = dig0Texture;

		return;
	}

	int num2 = bullet % 10;
	int num1 = bullet / 10;

	bulletTexture = bulletSymbolTexture;

	switch (num1) {
	case 0:
		bulletNum1 = dig0Texture;
		break;
	case 1:
		bulletNum1 = dig1Texture;
		break;
	case 2:
		bulletNum1 = dig2Texture;
		break;
	case 3:
		bulletNum1 = dig3Texture;
		break;
	case 4:
		bulletNum1 = dig4Texture;
		break;
	case 5:
		bulletNum1 = dig5Texture;
		break;
	case 6:
		bulletNum1 = dig6Texture;
		break;
	case 7:
		bulletNum1 = dig7Texture;
		break;
	case 8:
		bulletNum1 = dig8Texture;
		break;
	case 9:
		bulletNum1 = dig9Texture;
	}

	switch (num2) {
	case 0:
		bulletNum2 = dig0Texture;
		break;
	case 1:
		bulletNum2 = dig1Texture;
		break;
	case 2:
		bulletNum2 = dig2Texture;
		break;
	case 3:
		bulletNum2 = dig3Texture;
		break;
	case 4:
		bulletNum2 = dig4Texture;
		break;
	case 5:
		bulletNum2 = dig5Texture;
		break;
	case 6:
		bulletNum2 = dig6Texture;
		break;
	case 7:
		bulletNum2 = dig7Texture;
		break;
	case 8:
		bulletNum2 = dig8Texture;
		break;
	case 9:
		bulletNum2 = dig9Texture;
	}
}

void HUDcreator::setDisabled(bool isDisabled) {
	if (isDisabled) {
		bulletTexture = outOfBulletTexture;
		weaponTexture = outOfWeaponTexture;

	}
}

void HUDcreator::reset() {
	size = 1.0f;										
	winOrLose = false;
	currentHealth = 100;
	isSmoked = false;
	isOiled = false;

}