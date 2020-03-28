// TeslaGamesEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
// The TeslaGamesEngine will be changed to a .lib, not .exe and then be included in the TeslaGames Project

#include "pch.h"
#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <memory>
#include <list>

// Rendering includes
#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtx\rotate_vector.hpp>

#include "Window.h"
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"
#include "Texture.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Material.h"
#include "Model.h"
#include "Skybox.h"

//Health stuff
#include "Combat.h"
#include "HealthComponent.h"
#include "DamagingObject.h"
#include "Vehicle.h"
#include "Game.h"

//AudioStuff
#include "AudioEngine.h"
#include "AudioBoomBox.h"

//Controller stuff
#include "Controller.h"

//PhysX and Physics Engine
#include "PhysicsEngine.h"

//UI stuff
#include "HUDcreator.h"
#include "StartScreen.h"
#include "Menu.h"
#include "ReadyScreen.h"
#include "PauseScreen.h"

//Shadow stuff
#include "Shadow.h"

//Ability stuff
#include "Caltrops.h"
#include "Bullet.h"

// AI stuff
#include "AIDrivingComponent.h"
#include "AIShootingComponent.h"

// Stuff for imgui
#include "imGui/imgui.h"
#include "imGui/imgui_impl_glfw.h"
#include "imGui/imgui_impl_opengl3.h"

// end of stuff for imgui

bool hideDebug = true;

struct localAxis {
	glm::vec3 front;
	glm::vec3 right;
	glm::vec3 up;
};


/* Rendering variables */
const float toRadians = 3.14159265f / 180.0f;

Skybox skybox;

GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
uniformSpecularIntensity = 0, uniformShininess = 0;

//sWindow mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;
std::vector<HUD*> HUDList;
std::vector<Shadow*> shadowList;
//std::list<std::unique_ptr<Caltrops>> caltropsList;											//using list instead of vector since we will often insert and delete elements in the list
std::list<std::unique_ptr<Bullet>> bulletsList;
std::list <ShootComp*> shootList;
//std::list<std::unique_ptr<ShootComp*>> shootList;

std::vector<Camera> cameras;

Shader shadowShader;

Texture brickTexture;
Texture dirtTexture;
Texture plainTexture;

//sahow textures
Texture shadowTexture;

Material shinyMaterial;
Material dullMaterial;

PhysicsEngine* physEng;

//Player 1 objs
//Model TeslaCar;
Model Teslacar_chasis;
Model T_turret;
//Player 2 objs
Model Teslacar2_chasis;
Model T2_turret;
//Player 3 objs
Model Teslacar3_chasis;
Model T3_turret;
//Player 4 objs
Model Teslacar4_chasis;
Model T4_turret;

//AI Objs
Model TeslaCarAI;
Model TeslacarAI_chasis;
Model TAI_turret;

Model racetrack;
Model racetrack_walls;
Model racetrack_floor;
Model bulletobj;
Model boxTest;
Model oil;

//Pickup models
Model defense_pickup;
Model ammo_pickup;

Model drivingPointModel;

DirectionalLight mainLight;
PointLight pointLights[MAX_POINT_LIGHTS];
SpotLight spotLights[MAX_SPOT_LIGHTS];


//helper variables
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

bool isCameraFlipped = false;

float shoot_distance_x = 0; // Bullet vector movement for x
float shoot_distance_y = 0; // Bullet vector movement for y
float shoot_distance_z = 0; //Bullet vector movement for z
float bullet_speed = 0.5f;  //velocity of bullet when traversing

float bullet_boundary = 15;

//Mesh positioning and rotation debugging for player/car obj (current position for CAR)
float pos_x = 0;
float pos_y = 0;
float pos_z = 0;


glm::vec3 car_front;

// Vertex Shader
static const char* vShader = "Shaders/shader.vert";

// Fragment Shader
static const char* fShader = "Shaders/shader.frag";

//Vertex shader of shadow_shader
static const char* vShadow_shader = "Shaders/shadow_shader.vert";

//Fragment shader of shadow_shader
static const char* fShadow_shader = "Shaders/shadow_shader.frag";

// Multiplayer stuff
int players = 2;


struct yawPitch {
	float yaw;
	float pitch;
};

void update(localAxis a, float yaw, float pitch) {
	a.front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	a.front.y = sin(glm::radians(pitch));
	a.front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	a.front = glm::normalize(a.front);

	a.right = glm::normalize(glm::cross(a.front, glm::vec3(0,1,0)));
	a.up = glm::normalize(glm::cross(a.right, a.front));
}

/* End of rendering variables */

void CreateShaders()
{
	Shader *shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
	
	shadowShader.createShadowFromFiles(vShadow_shader, fShadow_shader);
}

void createShadows() {
	unsigned int shadowIndecis[] = {
		0, 1, 3,
		2, 1, 3
	};

	GLfloat shadowVertices[] = {
		-1.95f, -0.8f, -2.0f,		0.0, 0.0,
		-1.95f, -0.8f, 2.0f,		0.0, 1.0,
		2.05f, -0.8f, 2.0f,		1.0, 1.0,
		2.05f, -0.8f, -2.0f,		1.0, 0.0
	};

	Shadow* shadow = new Shadow();
	shadow->createShadow(shadowVertices, shadowIndecis, 20, 6);
	shadowList.push_back(shadow);
}

// A function to obtain input, called each frame
//add vehicle movement to these FOR NOW
//TO DO: Someone comment all the controls for each button
void parseControllerInput(Controller* controller)
{
	// Update controller object with current input MUST BE FIRST
	controller->update();

	// TODO: Change this to get player from controller ID
	auto id = controller->getIndex();
	auto player = physEng->playerVehicles[id];
	if (controller->isButtonPressed(XButtons.B)) {
		if (!controller->LStick_InDeadzone()) {
			player->handbrakeTurn(0.9f, controller->leftStick_X());
		}
		else {
			player->handbrakeTurn(0.9f, 0.f);
		}
		//std::cout << controller->getIndex() << " " << "B PRESSED and HELD" << std::endl;
	}
	else {
		player->handbrakeTurn(0.0f, 0.f);
	}

	isCameraFlipped = (controller->isButtonPressed(XButtons.Y));
	
	if (controller->isButtonDown(XButtons.Start)) {
		gameFlag = false;
		pauseFlag = true;
	}

	//press up to suicide (for testing health bar)
	if (controller->isButtonDown(XButtons.DPad_Up)) {
		player->update_health();

		std::cout << "Current health: " << player->getHealthComponent()->GetHealth() << std::endl;
	}
	
	//Sticks and triggers
	if (!controller->LStick_InDeadzone()) {
		//physEng.turn(controller->leftStick_X());
		float value = controller->leftStick_X();
		player->turn(value);
	}
	else {
		player->turn(0.f);
	}

	if (controller->rightTrigger() > 0.0 || controller->leftTrigger() > 0.0) {
		if (controller->rightTrigger() > 0.0) {
			player->forwards(controller->rightTrigger());
		}
		if (controller->leftTrigger() > 0.0) {
			player->reverse(controller->leftTrigger());
		}
	}
	else if (controller->rightTrigger() == 0.0 && controller->leftTrigger() == 0.0) {
		player->reverse(0.0f);
		player->forwards(0.0f);
	}
	

	// Update the gamepad for next frame MUST BE LAST
	controller->refreshState();
}

void SetPlayers(int p)
{
	int MAXPLAYERS = 2;
	if (p > MAXPLAYERS) {
		players = MAXPLAYERS;
	}
	else if (p < 1) {
		players = 1;
	}
	else {
		players = p;
	}

}

int main()
{
	const char* glsl_version = "#version 130"; // USED FOR IMGUI SETTING
	// TODO: Make this a variable value set in code
	mainWindow = Window(1280, 720);
	mainWindow.Initialise();

	//bool startScreenFlag = true;
	//int menuFlag = 0;
	bool setupGame = true;

	HUDcreator hud;
	hud.load();

	StartScreen startScreen;
	startScreen.load();
	Menu menu;
	menu.load();
	ReadyScreen readyScreen;
	readyScreen.load();
	PauseScreen pauseScreen;
	pauseScreen.load();


	physEng = new PhysicsEngine();

	physEng->createPickupTriggerVolume(18, -2, -67);

	// Rendering setup
	CreateShaders();
	createShadows();

	bool winFlag = false;
	bool loseFlag = false;

	brickTexture = Texture("Textures/brick.png");
	brickTexture.LoadTextureAlpha();
	dirtTexture = Texture("Textures/dirt.png");
	dirtTexture.LoadTextureAlpha();
	plainTexture = Texture("Textures/plain.png");
	plainTexture.LoadTextureAlpha();
	shadowTexture = Texture("Textures/shadow.png");
	shadowTexture.LoadTextureAlpha();

	
	shinyMaterial = Material(4.0f, 256);
	dullMaterial = Material(0.3f, 4);

	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
		0.5f, 0.5f,
		0.0f, 0.0f, -1.0f);

	unsigned int pointLightCount = 0;
	pointLights[0] = PointLight(0.0f, 0.0f, 1.0f,
								0.0f, 0.1f,
								0.0f, 0.0f, 0.0f,
								0.3f, 0.2f, 0.1f);
	//pointLightCount++;
	pointLights[1] = PointLight(0.0f, 1.0f, 0.0f,
								0.0f, 0.1f,
								-4.0f, 2.0f, 0.0f,
								0.3f, 0.1f, 0.1f);
	//pointLightCount++;

	unsigned int spotLightCount = 0;
	spotLights[0] = SpotLight(1.0f, 1.0f, 1.0f,
						0.0f, 2.0f,
						0.0f, 0.0f, 0.0f,
						0.0f, -1.0f, 0.0f,
						1.0f, 0.0f, 0.0f,
						20.0f);
	spotLightCount++;
	spotLights[1] = SpotLight(1.0f, 1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, -1.5f, 0.0f,
		-100.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		20.0f);
	spotLightCount++;

	std::vector<std::string> skyboxFaces;
	///*
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_rt.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_lf.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_up.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_dn.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_bk.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_ft.tga");
	//*/
	/*
	skyboxFaces.push_back("Textures/Skybox/Sunny_01A_right.jpg");
	skyboxFaces.push_back("Textures/Skybox/Sunny_01A_left.jpg");
	skyboxFaces.push_back("Textures/Skybox/Sunny_01A_up.jpg");
	skyboxFaces.push_back("Textures/Skybox/Sunny_01A_down.jpg");
	skyboxFaces.push_back("Textures/Skybox/Sunny_01A_back.jpg");
	skyboxFaces.push_back("Textures/Skybox/Sunny_01A_front.jpg");
	*/
	skybox = Skybox(skyboxFaces);

	glfwSwapInterval(1);

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// Setup Platform/Renderer bindings

	ImGui_ImplGlfw_InitForOpenGL(mainWindow.getWindow(), true);
	ImGui_ImplOpenGL3_Init(glsl_version);

	// Imgui setting END

	//Audio system setup
	AudioEngine audioSystem = AudioEngine();

	AudioBoomBox mainMenuMusic = audioSystem.createBoomBox(audioConstants::SOUND_FILE_TTG_MAIN_MENU);
	AudioBoomBox raceMusic;

	mainMenuMusic.setVolume(0.4f);
	mainMenuMusic.loopSound(true);

	// Multiplayer set up begins
	SetPlayers(2);

	glm::mat4 projection;

		switch (players) {
		case 1:
			// Player 1
			cameras.push_back(Camera(glm::vec3(0.0f, 2.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 20.0f, -20.0f, 5.0f, 2.f));
		case 2:
			// Player 1
			cameras.push_back(Camera(glm::vec3(0.0f, 2.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 20.0f, -20.0f, 5.0f, 2.f));
			// Player 2
			cameras.push_back(Camera(glm::vec3(0.0f, 2.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 20.0f, -20.0f, 5.0f, 2.f));
			break;
		case 3:
			// Fall through for now
		case 4:
			// Fall through for now
		default:
			cameras.push_back(Camera(glm::vec3(0.0f, 2.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 20.0f, -20.0f, 5.0f, 2.f));
		}

	// Multiplayer set up ends

	//Loading TeslaTrucks models
	////////////////////////////////////////////////////////////////////////
	std::vector<Model> playerChassisModels;
	std::vector<Model> playerTurretModels;

	Teslacar_chasis.LoadModel("Models/TeslaGamesTruck2_yellowchasis.obj");
	T_turret.LoadModel("Models/TeslaGamesTruck2_yellowturret.obj");

	Teslacar2_chasis.LoadModel("Models/TeslaGamesTruck2_bluechasis.obj");
	T2_turret.LoadModel("Models/TeslaGamesTruck2_blueturret.obj");

	Teslacar3_chasis.LoadModel("Models/TeslaGamesTruck2_greenchasis.obj");
	T3_turret.LoadModel("Models/TeslaGamesTruck2_greenturret.obj");

	Teslacar4_chasis.LoadModel("Models/TeslaGamesTruck2_purplechasis.obj");
	T4_turret.LoadModel("Models/TeslaGamesTruck2_purpleturret.obj");

	playerChassisModels.push_back(Teslacar_chasis);
	playerChassisModels.push_back(Teslacar2_chasis);
	playerChassisModels.push_back(Teslacar3_chasis);
	playerChassisModels.push_back(Teslacar4_chasis);

	playerTurretModels.push_back(T_turret);
	playerTurretModels.push_back(T2_turret);
	playerTurretModels.push_back(T3_turret);
	playerTurretModels.push_back(T4_turret);

	TeslacarAI_chasis.LoadModel("Models/TeslaGamesTruck2_redchasis.obj");
	TAI_turret.LoadModel("Models/TeslaGamesTruck2_redturret.obj");
	//////////////////////////////////////////////////////////////////////////
	boxTest.LoadModel("Models/wall.obj");
	//caltrop.LoadModel("Models/caltrops.obj");
	//racetrack.LoadModel("Models/track2.obj");
	
	
	bulletobj.LoadModel("Models/bullet.obj");
	defense_pickup.LoadModel("Models/defense_box.obj");
	ammo_pickup.LoadModel("Models/ammo_box.obj");

	oil.LoadModel("Models/oil.obj");

	drivingPointModel.LoadModel("Models/bullet.obj");
	// Loop until window closed

	//Controller
	std::vector<Controller> controllers;
	Controller player1 = Controller(1);
	Controller player2 = Controller(2);
	controllers.push_back(player1);
	controllers.push_back(player2);


	std::cout << "Player1 connected: " << controllers[0].isConnected() << std::endl;
	std::cout << "Player2 connected: " << controllers[1].isConnected() << std::endl;

	bool P1Connected = controllers[0].isConnected();
	bool P2Connected = controllers[1].isConnected();


	//This does all the Ai stuff as far TeslaGameEngine is concerned
	Track raceTrack;
	std::vector<AIShootingComponent> aiShootingComponents;

	glm::vec3 front = glm::normalize(glm::vec3(0.f, -0.5f, 1.f));
	cameras[0].setFront(front.x, front.y, front.z);

	while (!mainWindow.getShouldClose()) {
		if (closeWindowFlag) {
			mainWindow.setWindowClose();
			continue;
		}

		while (startScreenFlag) {
			if (!mainMenuMusic.isSoundPlaying()) {
				mainMenuMusic.playSound();
			}
			if (fromGameFlag) {
				if (glfwGetTime() - backTime > 0.5) {
					startScreen.loadController(&player1);
					fromGameFlag = false;
				}
			}
			else
				startScreen.loadController(&player1);

			startScreen.use();

			mainWindow.swapBuffers();
		}

		while (menuFlag) {
			menu.loadController(&player1);
			menu.use();
			mainWindow.swapBuffers();
		}

		while (readyScreenFlag) {
			readyScreen.loadController(&player1);
			readyScreen.use();
			mainWindow.swapBuffers();
		}

		while (pauseFlag) {
			int display_w, display_h;
			glfwGetFramebufferSize(mainWindow.getWindow(), &display_w, &display_h);
			glViewport(0, 0, display_w, display_h);
			audioSystem.pauseAllActiveSources();
			pauseScreen.loadController(&controllers[0]);
			pauseScreen.use();
			mainWindow.swapBuffers();
		}

		if (setupGame) {
			//Reset this variable to reset the game
			physEng->initAudioForVehicles(&audioSystem);
			cameras[0].initializeAudio(&audioSystem);

			setupGame = false;

			int gameMode = menu.getSelectedGameMode();
			int trackNum = menu.getSelectedTrack();
			int AINum = menu.getSelectedNumOfAI();
			std::cout << trackNum << std::endl;

			if (trackNum == trackTypeConstants::HYPERLOOP) {
				racetrack_walls.LoadModel("Models/track2finalwalls.obj", physEng->gPhysics, physEng->gCooking, physEng->gMaterial, physEng->gScene, false);
				racetrack_floor.LoadModel("Models/track2finalfloor.obj", physEng->gPhysics, physEng->gCooking, physEng->gMaterial, physEng->gScene, true);

				raceMusic = audioSystem.createBoomBox(audioConstants::SOUND_FILE_TTG_RACE_HYPERLOOP);
				raceMusic.setVolume(0.35f);
				raceMusic.loopSound(true);
			}
			else if (trackNum == trackTypeConstants::STARLINK) {
				racetrack_walls.LoadModel("Models/track2final_Twalls.obj", physEng->gPhysics, physEng->gCooking, physEng->gMaterial, physEng->gScene, false);
				racetrack_floor.LoadModel("Models/track2final_Tfloor.obj", physEng->gPhysics, physEng->gCooking, physEng->gMaterial, physEng->gScene, true);

				raceMusic = audioSystem.createBoomBox(audioConstants::SOUND_FILE_TTG_RACE_STARLINK);
				raceMusic.setVolume(0.35f);
				raceMusic.loopSound(true);
			}

			if (multiplayerFlag) {
				switch (players) {
				case 2:
					projection = glm::perspective(45.0f, (GLfloat)(mainWindow.getBufferWidth() / mainWindow.getBufferHeight()) * 2, 0.1f, 1000.0f);
					break;
				case 3:
					// Fall through for now
				case 4:
					// Fall through for now
				default:
					projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);
					break;
				}
			}
			else {
				projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);
			}

			raceTrack.initializeTrackPoints(trackNum);
			raceTrack.initializeLapMarkers(trackNum);
			physEng->setTrack(&raceTrack);
			physEng->initAITrack(&raceTrack);

			// TODO: Using to make multiplayer testing easier. Will remove
			if (!multiplayerFlag) {
				players = 1;
			}

			for (int i = 0; i < AINum; i++) {
				physEng->addEnemyVehicle(i);
			}

			for (int i = 0; i < players; i++) {
				physEng->addPlayerVehicle(AINum + controllers[i].getIndex());
			}

			if (trackNum == trackTypeConstants::STARLINK) {
				for (auto AI : physEng->enemyVehicles) {
					AI->incrementAITrackPoint();
				}
			}

			//setup all track traps
			for (int i = 0; i < raceTrack.listOfLaneStrips.size(); i++) {
				TrackInteractableStrip& zone = *raceTrack.listOfLaneStrips.at(i);
				for (int j = 0; j < zone.listOfLanePoints.size(); j++) {
					TrackDrivingPoint& p = *zone.listOfLanePoints[j];
					
					switch (p.actionToTake)
					{
					case -2:	//ammo pickup
						break;
					case -3:	//normal pickup
						physEng->createPickupTriggerVolume(p.x, p.y, p.z);
						break;
					case -4:	//caltrops
						physEng->createTrackCaltrops(p.x, p.y, p.z, -1.f);	//make new function for track placement
						break;
					case -5:	//oil
						physEng->createTrackOil(p.x, p.y, p.z, -1.f);	//make new function for track placement
						break;
					case -6:	//smoke
						physEng->createTrackSmoke(p.x, p.y, p.z, -1.f);	//make new function for track placement
						break;
					}
				}
			}

			std::vector<Vehicle*> vehicles;
			std::vector<Vehicle*> playerVehicles = physEng->playerVehicles;
			std::vector<Vehicle*> aiVehicles = physEng->enemyVehicles;
			vehicles.insert(vehicles.end(), playerVehicles.begin(), playerVehicles.end());
			vehicles.insert(vehicles.end(), aiVehicles.begin(), aiVehicles.end());
			physEng->allVehicles = vehicles;
			shaderList[0].UseShader();
			for (auto ai : aiVehicles) {
				AIShootingComponent aiShooting = AIShootingComponent(ai);
				aiShooting.SetVehicles(vehicles);
				aiShooting.SetUniformLocations(shaderList[0].GetModelLocation(), shaderList[0].GetSpecularIntensityLocation(), shaderList[0].GetShininessLocation());
				aiShootingComponents.push_back(aiShooting);
			}

			physEng->loadLapMarkers();
			for (auto v : vehicles) {
				v->numberOfMarkersInTrack = physEng->lapmarkers.size();
			}

			physEng->allVehicles = vehicles;
		}

		while (gameFlag)
		{
			/* Parse input */
			if (P1Connected)
				parseControllerInput(&controllers[0]);
			if (P2Connected)
				parseControllerInput(&controllers[1]);

			GLfloat now = glfwGetTime();
			deltaTime = now - lastTime;
			lastTime = now;

			// Get + Handle User Input
			glfwPollEvents();

			//cameras[1].keyControl(mainWindow.getsKeys(), deltaTime);
			//camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

			// ONLY BEING USED TO TEST PLAYER 2
			// PRESS W TO DRIVE, A TO TURN LEFT, S TO REVERSE, D TO TURN RIGHT 
			auto keys = mainWindow.getsKeys();
			if (!P2Connected) {
				if (keys['W']) {
					physEng->playerVehicles[1]->forwards(0.75f);
				}
				if (keys['A']) {
					physEng->playerVehicles[1]->turn(-0.5f);
				}
				if (keys['S']) {
					physEng->playerVehicles[1]->reverse(0.75f);
				}
				if (keys['D']) {
					physEng->playerVehicles[1]->turn(0.5f);
				}
			}

			if (keys['H']) {
				hideDebug = true;
			}
			if (keys['U']) {
				hideDebug = false;
			}

			/* Game logic */ 

			// Physics
			physEng->stepPhysics();

			// AI - should only go once per game loop
			// TODO: Move this call
			for (int i = 0; i < aiShootingComponents.size(); i++) {
				aiShootingComponents[i].Aim();
			}

			/* Render */ 
			// Clear the window
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


			// Render for each player
			for (int player = 0; player < players; player++) {

				//  Get values from physics engine
				const physx::PxVehicleDrive4W* vehicle = physEng->playerVehicles[player]->gVehicle4W;	
				const physx::PxRigidDynamic* vDynamic = vehicle->getRigidDynamicActor();
				physx::PxQuat vehicleQuaternion = vDynamic->getGlobalPose().q;
				physx::PxVec3 v_dir = vehicleQuaternion.getBasisVector2();
				const physx::PxVec3 vehiclePositionPhysx = vDynamic->getGlobalPose().p;
				glm::vec3 vehiclePosition(vehiclePositionPhysx.x, vehiclePositionPhysx.y, vehiclePositionPhysx.z);

				// Init viewport
				int display_w, display_h;
				glfwGetFramebufferSize(mainWindow.getWindow(), &display_w, &display_h);

				// Setup viewports depending on if it is or is not multiplayer
				if (multiplayerFlag) {
					if (player == 0) {
						glViewport(0, display_h / 2, display_w, display_h / 2);
					}
					if (player == 1) {
						glViewport(0, 0, display_w, display_h / 2);
					}
				}
				else {
					glViewport(0, 0, display_w, display_h);
				}

				// Update camera
				glm::vec3 dir = glm::normalize(glm::vec3(v_dir.x, 0, v_dir.z));
				glm::vec3 dirToUse;
				if (isCameraFlipped) {
					dirToUse = dir * -1.f;
				}
				else {
					dirToUse = dir;
				}

				if (controllers[player].RStick_InDeadzone()) {
					cameras[player].stickControl(0.f, vehiclePosition, dirToUse, controllers[player].isButtonDown(XButtons.R_Thumbstick), isCameraFlipped);
				}
				else {
					cameras[player].stickControl(controllers[player].rightStick_X(), vehiclePosition, dirToUse, controllers[player].isButtonDown(XButtons.R_Thumbstick), isCameraFlipped);
				}

				// Skybox
				skybox.DrawSkybox(cameras[player].calculateViewMatrix(), projection);

				// Setup shader
				shaderList[0].UseShader();
				uniformModel = shaderList[0].GetModelLocation();
				uniformProjection = shaderList[0].GetProjectionLocation();
				uniformView = shaderList[0].GetViewLocation();
				uniformEyePosition = shaderList[0].GetEyePositionLocation();
				uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
				uniformShininess = shaderList[0].GetShininessLocation();

				shaderList[0].SetDirectionalLight(&mainLight);
				shaderList[0].SetPointLights(pointLights, pointLightCount);
				shaderList[0].SetSpotLights(spotLights, spotLightCount);

				physx::PxVec3 carPos = physEng->playerVehicles[player]->GetPosition();	//position of TeslaCar

				glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
				glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(cameras[player].calculateViewMatrix()));
				glUniform3f(uniformEyePosition, cameras[player].getCameraPosition().x, cameras[player].getCameraPosition().y, cameras[player].getCameraPosition().z);

				shaderList[0].UseShader();
				uniformModel = shaderList[0].GetModelLocation();
				uniformProjection = shaderList[0].GetProjectionLocation();

				// Initial model matrix
				glm::mat4 model = glm::mat4(1.0f);

				// Draw racing track & TrackDrivingPoints
				model = glm::mat4(1.0f);
				model = glm::translate(model, glm::vec3(0.0f, -5.f, -3.2));
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
				racetrack_walls.RenderModel();
				racetrack_floor.RenderModel();


				/* Can uncomment to draw the TrackDrivingPoints if needed for testing
				for (int i = 0; i < raceTrack.listOfPoints.size(); i++) {
					TrackDrivingPoint point = *raceTrack.listOfPoints.at(i);
					model = model = glm::mat4(1.0f);
					model = glm::translate(model, glm::vec3(point.x, point.y, point.z));
					glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
					shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
					drivingPointModel.RenderModel();
				}*/ 

				// Draw pickup boxes
				auto pickup = physEng->pickupBoxes.begin();
				while (pickup != physEng->pickupBoxes.end()) {
					// If it is picked up, delete it from the list
					// It looks like it won't be triggered once it is deleted, but I think it's still in the triggerActor list
					if ((*pickup)->getIsPicked()) {
						physEng->pickupBoxes.erase(pickup++);
					}
					else {
						physx::PxVec3 wallPos = (*pickup)->actor->getGlobalPose().p;
						glm::vec3 wallp(wallPos.x, wallPos.y + 1.f, wallPos.z);
						model = glm::mat4(1.0f);
						model = glm::translate(model, wallp);
						/* Consider making the pickup boxes a hardcoded size and hardcoding the
							trigger volumes to be the same size */
						model = glm::scale(model, glm::vec3(0.8f, 0.8, 0.8f));	//keep these scale values!
						glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
						shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
						// boxTest.RenderModel();
						defense_pickup.RenderModel();
						++pickup;
					}
				}

				physx::PxVec3 forwardvec = physx::PxVec3(vehicleQuaternion.x, 0, vehicleQuaternion.z);
				physx::PxVec3  Direction = vehicleQuaternion.getBasisVector2();

				// Draw bullets & turret
				ShootComp* ba = physEng->playerVehicles[player]->getShootingComponent();
				HealthComponent* ha = physEng->playerVehicles[player]->getHealthComponent();

				glm::vec3 camDir = cameras[player].getCameraDirection();
				if ((ha->GetHealth()) > 0) {
					// Draw bullets after Refactor. If affected by smoke they cant shoot
					if ((controllers[player].isButtonDown(XButtons.R_Shoulder) || controllers[player].isButtonDown(XButtons.L_Shoulder)) && !physEng->playerVehicles[player]->affectedBySmoke) {
						if (isCameraFlipped) {
							ba->fire(vehiclePosition, uniformModel, uniformSpecularIntensity, uniformShininess, Direction.x, Direction.y, Direction.z);
						}
						else {
							ba->fire(vehiclePosition, uniformModel, uniformSpecularIntensity, uniformShininess, camDir.x, Direction.y, camDir.z);
						}
					}

					// Player 2 can fire with Q as well (only when no controller detected)
					if (player == 1 && keys['Q'] && !physEng->playerVehicles[player]->affectedBySmoke && !P2Connected) {
						if (isCameraFlipped) {
							ba->fire(vehiclePosition, uniformModel, uniformSpecularIntensity, uniformShininess, Direction.x, Direction.y, Direction.z);
						}
						else {
							ba->fire(vehiclePosition, uniformModel, uniformSpecularIntensity, uniformShininess, camDir.x, Direction.y, camDir.z);
						}
						keys['Q'] = false;
					}
					ba->renderAllBullets();

					physx::PxMat44 modelMat(vDynamic->getGlobalPose());	// Make model matrix from transform of rigid dynamic
					modelMat.scale(physx::PxVec4(0.3f, 0.3f, 0.3f, 1.f));	// Scales the model
					glUniformMatrix4fv(uniformModel, 1, GL_FALSE, modelMat.front());

					shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
					playerChassisModels[player].RenderModel();

					// Reset model
					model = glm::mat4(1.0f);
					glm::vec3 y_rot(0.0, 1.0, 0.0); // Axis of rotation
					glm::vec3 tem = glm::vec3(modelMat.getPosition().x, modelMat.getPosition().y, modelMat.getPosition().z);
					model = glm::translate(model, tem); // Update turret pos with position of vehicle
					model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f)); // Resize turret
					// TODO: This moves to ShootComp class
					float angleAroundY = glm::degrees(atan2(camDir.x, camDir.z)); // Calculate angle of rotation
					float angletoUse = angleAroundY * 3.14 / 180; // Convert to radians
					model = glm::rotate(model, angletoUse, y_rot);

					if (isCameraFlipped) {
						glUniformMatrix4fv(uniformModel, 1, GL_FALSE, modelMat.front());
					}
					else {
						glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
					}

					playerTurretModels[player].RenderModel(); //renders turret	
				}

				// Draw and create caltrops
				if (controllers[player].isButtonDown(XButtons.DPad_Down) && !physEng->playerVehicles[player]->affectedBySmoke) {
					PxVec3 p(physEng->playerVehicles[player]->GetPosition());
					physEng->createCaltropsTriggerVolume(p.x, p.y, p.z, 5.f, player);
				}

				auto c = physEng->caltropsList.begin();
				while (c != physEng->caltropsList.end()) {	//remove dead caltrops
					if ((*c)->isDead()) {
						physEng->gScene->removeActor(*((*c)->actor));
						physEng->caltropsList.erase(c++);
					}
					else {
						(*c)->load(uniformModel, uniformSpecularIntensity, uniformShininess);
						(*c)->renderCaltrops();
						++c;
					}
				}

				// Draw and create oil
				if (controllers[player].isButtonDown(XButtons.DPad_Right) && !physEng->playerVehicles[player]->affectedBySmoke) {
					PxVec3 p(physEng->playerVehicles[player]->GetPosition());
					physEng->createOilTriggerVolume(p.x, p.y, p.z, 5.f, player);
				}

				auto o = physEng->oilList.begin();
				while (o != physEng->oilList.end()) {	//remove dead caltrops
					if ((*o)->isDead()) {
						physEng->gScene->removeActor(*((*o)->actor));
						physEng->oilList.erase(o++);
					}
					else {
						(*o)->load(uniformModel, uniformSpecularIntensity, uniformShininess);
						(*o)->renderOil();
						++o;
					}
				}

				// Draw and create smoke
				if (controllers[player].isButtonDown(XButtons.DPad_Left) && !physEng->playerVehicles[player]->affectedBySmoke) {
					PxVec3 p(physEng->playerVehicles[player]->GetPosition());
					physEng->createSmokeTriggerVolume(p.x, p.y, p.z, 5.f, player);
				}

				auto s = physEng->smokeList.begin();
				while (s != physEng->smokeList.end()) {	//remove dead smoke
					if ((*s)->isDead()) {
						physEng->gScene->removeActor(*((*s)->actor));
						physEng->smokeList.erase(s++);
					}
					else {
						(*s)->load(uniformModel, uniformSpecularIntensity, uniformShininess);
						(*s)->renderSmoke();
						++s;
					}
				}

				// Render AI cars
				if (!physEng->enemyVehicles.empty()) {
					for (int i = 0; i < physEng->enemyVehicles.size(); i++) {
						Vehicle* v = physEng->enemyVehicles.at(i);
						const physx::PxVehicleDrive4W* enemyV = v->gVehicle4W;	// Get vehicle
						const physx::PxRigidDynamic* enemyvDynamic = enemyV->getRigidDynamicActor();
						physx::PxQuat enemyvehicleQuaternion = enemyvDynamic->getGlobalPose().q;
						physx::PxVec3 enemyv_dir = enemyvehicleQuaternion.getBasisVector2();
						const physx::PxVec3 enemyvehiclePositionPhysx = enemyvDynamic->getGlobalPose().p;
						glm::vec3 enemyvehiclePosition(enemyvehiclePositionPhysx.x, enemyvehiclePositionPhysx.y, enemyvehiclePositionPhysx.z);

						physx::PxMat44 enemymodelMat(enemyvDynamic->getGlobalPose());	// <ake model matrix from transform of rigid dynamic
						enemymodelMat.scale(physx::PxVec4(0.3f, 0.3f, 0.3f, 1.f));	// Scales the model
						glUniformMatrix4fv(uniformModel, 1, GL_FALSE, enemymodelMat.front());

						shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
						TeslacarAI_chasis.RenderModel();

						model = glm::mat4(1.0f);
						glm::vec3 y_rot(0.0, 1.0, 0.0); // Axis of rotation
						glm::vec3 tem = glm::vec3(enemymodelMat.getPosition().x, enemymodelMat.getPosition().y, enemymodelMat.getPosition().z);
						model = glm::translate(model, tem); // Update turret pos with position of vehicle
						model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f)); // Resize turret
						auto aimdir_x = v->getShootingComponent()->Direction_x;
						auto aimdir_z = v->getShootingComponent()->Direction_z;
						float angleAroundY = glm::degrees(atan2(aimdir_x, aimdir_z)); // Calculate angle of rotation
						float angletoUse = angleAroundY * 3.14 / 180; // Convert to radians
						model = glm::rotate(model, angletoUse, y_rot);
						glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
						TAI_turret.RenderModel();
					}
				}

				// Render other players cars
				if (multiplayerFlag) {
					for (int i = 0; i < physEng->playerVehicles.size(); i++) {
						if (i == player) continue; // Don't render self
						Vehicle* v = physEng->playerVehicles.at(i);
						const physx::PxVehicleDrive4W* enemyV = v->gVehicle4W;	// Get vehicle
						const physx::PxRigidDynamic* enemyvDynamic = enemyV->getRigidDynamicActor();
						physx::PxQuat enemyvehicleQuaternion = enemyvDynamic->getGlobalPose().q;
						physx::PxVec3 enemyv_dir = enemyvehicleQuaternion.getBasisVector2();
						const physx::PxVec3 enemyvehiclePositionPhysx = enemyvDynamic->getGlobalPose().p;
						glm::vec3 enemyvehiclePosition(enemyvehiclePositionPhysx.x, enemyvehiclePositionPhysx.y, enemyvehiclePositionPhysx.z);

						physx::PxMat44 enemymodelMat(enemyvDynamic->getGlobalPose());	// <ake model matrix from transform of rigid dynamic
						enemymodelMat.scale(physx::PxVec4(0.3f, 0.3f, 0.3f, 1.f));	// Scales the model
						glUniformMatrix4fv(uniformModel, 1, GL_FALSE, enemymodelMat.front());

						shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
						// This
						playerChassisModels[i].RenderModel();

						model = glm::mat4(1.0f);
						glm::vec3 y_rot(0.0, 1.0, 0.0); // Axis of rotation
						glm::vec3 tem = glm::vec3(enemymodelMat.getPosition().x, enemymodelMat.getPosition().y, enemymodelMat.getPosition().z);
						model = glm::translate(model, tem); // Update turret pos with position of vehicle
						model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f)); // Resize turret
						auto aimdir_x = v->getShootingComponent()->Direction_x;
						auto aimdir_z = v->getShootingComponent()->Direction_z;
						float angleAroundY = glm::degrees(atan2(aimdir_x, aimdir_z)); // Calculate angle of rotation
						float angletoUse = angleAroundY * 3.14 / 180; // Convert to radians
						model = glm::rotate(model, angletoUse, y_rot);
						glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
						// This
						playerTurretModels[i].RenderModel();
					}
				}

				// Render AI bullets and traps
				for (auto ai : physEng->enemyVehicles) {
					ai->getShootingComponent()->renderAllBullets();
				}

				// Render all other player bullets and traps
				for (int i = 0; i < players; i++) {
					if (i != player) {
						physEng->playerVehicles[i]->getShootingComponent()->renderAllBullets();
					}
				}

				// Render shadows
				model = glm::mat4(1.0f);
				glm::vec3 tem = glm::vec3(53, -2, -83);
				model = glm::translate(model, tem); //Update turret pos with position of vehicle
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

				shadowShader.UseShader();
				uniformModel = shadowShader.GetModelLocation();
				uniformProjection = shadowShader.GetProjectionLocation();
				uniformView = shadowShader.GetViewLocation();

				// Player vehicle's shadow
				for (auto v : physEng->playerVehicles) {
					physx::PxMat44 AIcarModel(v->GetTransform());

					glUniformMatrix4fv(uniformModel, 1, GL_FALSE, AIcarModel.front());
					glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
					//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
					glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(cameras[player].calculateViewMatrix()));

					shadowTexture.UseTexture();
					shadowList[0]->renderShadow();
				}

				// AI vehicles' shadows 
				for (auto v : physEng->enemyVehicles) {
					physx::PxMat44 AIcarModel(v->GetTransform());

					glUniformMatrix4fv(uniformModel, 1, GL_FALSE, AIcarModel.front());
					glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
					//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
					glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(cameras[player].calculateViewMatrix()));


					shadowTexture.UseTexture();
					shadowList[0]->renderShadow();
				}

				glEnable(GL_DEPTH_TEST);

				// HUD
				if (physEng->playerVehicles[player]->numLaps == 5)
					winFlag = true;
				else
					for (auto v : physEng->enemyVehicles)
						if (v->numLaps == 5)
							loseFlag = true;

				if (winFlag == true)
					hud.setGameState(true);
				if (loseFlag == true)
					hud.setGameState(false);
				if (winFlag)
					hud.setLapNumber(physEng->playerVehicles[player]->numLaps);
				else
					hud.setLapNumber(physEng->playerVehicles[player]->numLaps + 1);


				int playerID = physEng->playerVehicles[player]->ID;
				auto iter = std::find_if(physEng->allVehicles.begin(), physEng->allVehicles.end(), [&playerID](const Vehicle* v) {return v->ID == playerID; });
				int index = std::distance(physEng->allVehicles.begin(), iter);

				hud.setAbilityNumber(physEng->playerVehicles[player]->ability);
				hud.setAliveNumber(physEng->allVehicles.size());
				hud.setPositionNumber(index + 1);
				hud.setBulletNum(physEng->playerVehicles[player]->getShootingComponent()->ammo);
				hud.setHealth(physEng->playerVehicles[player]->getHealthComponent()->GetHealth());

				hud.use();
			}

			/* Audio */ 
			if (audioSystem.allHaveBeenPaused == true) {
				audioSystem.resumeAllActiveSources();
			}
			if (mainMenuMusic.isSoundPlaying()) {
				mainMenuMusic.stopSound();
			}
			if (!raceMusic.isSoundPlaying()) {
				raceMusic.playSound();
			}


			// ImGUI debugging info

			glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(cameras[0].calculateViewMatrix()));

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
			{
				static float f = 0.0f;
				static int counter = 0;

			ImGui::Begin("Debug");
			ImGui::Text("Driving mode and Position");
			ImGui::Text("Frame per Second counter"); // Display some text (you can use a format strings too)
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			// ImGui::Text(": %i Xpos: %.2f Ypos: %.2f Zpos: %.2f", physEng->getModeType(), carPos.x, carPos.y, carPos.z);
			// ImGui::Text("Drivemode: %i Xpos: %f Ypos: %f Zpos: %f", physEng->getModeType(), carPos.x, carPos.y, carPos.z);
			ImGui::Text("Camera Xvec: %f Yvec: %f Zvec: %f", cameras[0].getCameraPosition().x, cameras[0].getCameraPosition().y, cameras[0].getCameraPosition().z);
			// ImGui::Text("Drivemode: %i Xvec: %f Yvec: %f Zvec: %f", physEng->getModeType(), v_dir.x, v_dir.y, v_dir.z);

				ImGui::End();
			}

			// Rendering imgui
			if (!hideDebug) {
				ImGui::Render();
				ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
			}

			mainWindow.swapBuffers();

			if (mainWindow.getShouldClose() == true) {
				gameFlag = false;
			}
		}
	}

	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	
	return 0;
}