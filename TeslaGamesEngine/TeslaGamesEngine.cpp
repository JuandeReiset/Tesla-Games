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

//HUD stuff
#include "HUDcreator.h"

//Shadow stuff
#include "Shadow.h"

//Ability stuff
#include "Caltrops.h"
#include "Bullet.h"

// AI stuff
#include "AIDrivingComponent.h"

// Stuff for imgui
#include "imGui/imgui.h"
#include "imGui/imgui_impl_glfw.h"
#include "imGui/imgui_impl_opengl3.h"

// end of stuff for imgui

struct localAxis {
	glm::vec3 front;
	glm::vec3 right;
	glm::vec3 up;
};


/* Rendering variables */
const float toRadians = 3.14159265f / 180.0f;

//sWindow mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;
std::vector<HUD*> HUDList;
std::vector<Shadow*> shadowList;
//std::vector<Caltrops*> caltropsList;
std::list<std::unique_ptr<Caltrops>> caltropsList;											//using list instead of vector since we will often insert and delete elements in the list
std::list<std::unique_ptr<Bullet>> bulletsList;
std::list <ShootComp*> shootList;
//std::list<std::unique_ptr<ShootComp*>> shootList;

Camera camera;

Shader shadowShader;

Texture brickTexture;
Texture dirtTexture;
Texture plainTexture;

//sahow textures
Texture shadowTexture;

Material shinyMaterial;
Material dullMaterial;

PhysicsEngine* physEng;

Model TeslaCar;
Model racetrack;
Model bulletobj;
Model boxTest;
Model racetrack_walls;
Model racetrack_floor;

DirectionalLight mainLight;
PointLight pointLights[MAX_POINT_LIGHTS];
SpotLight spotLights[MAX_SPOT_LIGHTS];


//helper variables
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

bool bullet_shot = false; //after shooting there will be a cooldown for the player before he can shoot again
bool bullet_sound_played = true;

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

//Angle of rotation for player/car obj  
//float car_rotation = 90;
//float current_rotation; //Calculates the angle at the moment of firing lazer
glm::vec3 car_front;

// Vertex Shader
static const char* vShader = "Shaders/shader.vert";

// Fragment Shader
static const char* fShader = "Shaders/shader.frag";

//Vertex shader of shadow_shader
static const char* vShadow_shader = "Shaders/shadow_shader.vert";

//Fragment shader of shadow_shader
static const char* fShadow_shader = "Shaders/shadow_shader.frag";


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

	//IMPLEMENT THINGS In the IFs

	//Is button Pressed demo
	if (controller->isButtonPressed(XButtons.A)) {
		//std::cout << controller->getIndex() << " " <<"A PRESSED" << std::endl;
	}
	if (controller->isButtonPressed(XButtons.X)) {
		//std::cout << controller->getIndex() << " " << "X PRESSED" << std::endl;
	}
	
	isCameraFlipped = (controller->isButtonPressed(XButtons.Y));


	if (controller->isButtonDown(XButtons.B)) {
		//std::cout << controller->getIndex() << " " << "B PRESSED and HELD" << std::endl;
	}
	
	if (controller->isButtonDown(XButtons.DPad_Up)) {
		//std::cout << controller->getIndex() << " " << "D-Pad Up PRESSED and HELD" << std::endl;
	}
	if (controller->isButtonDown(XButtons.DPad_Down)) {
		//std::cout << controller->getIndex() << " " << "D-Pad Down PRESSED and HELD" << std::endl;
	}
	if (controller->isButtonDown(XButtons.DPad_Right)) {
		//std::cout << controller->getIndex() << " " << "D-Pad Right PRESSED and HELD" << std::endl;
	}
	if (controller->isButtonDown(XButtons.DPad_Left)) {
		//std::cout << controller->getIndex() << " " << "D-Pad Left PRESSED and HELD" << std::endl;
	}
	if (controller->isButtonDown(XButtons.Start)) {
		//std::cout << controller->getIndex() << " " << "Start PRESSED and HELD" << std::endl;
	}
	if (controller->isButtonDown(XButtons.Back)) {
		//std::cout << controller->getIndex() << " " << "Back PRESSED and HELD" << std::endl;
	}
	if (controller->isButtonDown(XButtons.Back)) {
		//std::cout << controller->getIndex() << " " << "Back PRESSED and HELD" << std::endl;
	}
	if (controller->isButtonDown(XButtons.L_Thumbstick)) {
		//std::cout << controller->getIndex() << " " << "L3 PRESSED and HELD" << std::endl;
	}
	if (controller->isButtonDown(XButtons.R_Thumbstick)) {
		//std::cout << controller->getIndex() << " " << "R3 PRESSED and HELD" << std::endl;
	}

	//Sticks and triggers
	if (!controller->LStick_InDeadzone()) {
		//physEng.turn(controller->leftStick_X());
		float value = controller->leftStick_X();
		physEng->player->turn(value);
	}
	else {
		physEng->player->turn(0.f);
	}

	if (controller->rightTrigger() > 0.0 || controller->leftTrigger() > 0.0) {
		if (controller->rightTrigger() > 0.0) {
			physEng->player->forwards(controller->rightTrigger());
		}
		if (controller->leftTrigger() > 0.0) {
			physEng->player->reverse(controller->leftTrigger());
		}
	}
	else if (controller->rightTrigger() == 0.0 && controller->leftTrigger() == 0.0) {
		physEng->player->reverse(0.0f);
		physEng->player->forwards(0.0f);
	}
	

	// Update the gamepad for next frame MUST BE LAST
	controller->refreshState();
}

int main()
{
	const char* glsl_version = "#version 130"; // USED FOR IMGUI SETTING
	mainWindow = Window(1280, 720);
	mainWindow.Initialise();

	HUDcreator hud;
	hud.load();

	physEng = new PhysicsEngine();

	Renderer r = Renderer(mainWindow, camera);

	Game mainGame = Game(r);
	Object* car = new Vehicle(1);
	Object* car2 = new Vehicle(2);
	Object* bullet = new DamagingObject(20, 1);


	//need a model for each ai vehicle

	mainGame.AddObject(car);
	mainGame.AddObject(car2);
	mainGame.AddObject(bullet);

	mainGame.Play();

	// Rendering setup
	CreateShaders();
	createShadows();

	camera = Camera(glm::vec3(0.0f, 2.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 20.0f, -20.0f, 5.0f, 2.f);
	yawPitch yp;
	yp.yaw = 90.f;
	yp.pitch = -20.0f;


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

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);

	TeslaCar.LoadModel("Models/TeslaGamesTruck2.obj");
	boxTest.LoadModel("Models/wall.obj");
	//TeslaCar.LoadModel("Models/TeslaGamesTruck.obj");
	racetrack.LoadModel("Models/track2.obj");
	racetrack_walls.LoadModel("Models/track2walls.obj");
	racetrack_floor.LoadModel("Models/track2floor.obj");
	
	bulletobj.LoadModel("Models/bullet.obj");
	// TODO: Put FPS code into Game.Play()
	// Loop until window closed

	glfwSwapInterval(1);
	// imGui setting BEGINNING
	/*
#if __APPLE__
// GL 3.2 + GLSL 150
	const char* glsl_version = "#version 150";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
	// GL 3.0 + GLSL 130

	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif
*/
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
	AudioBoomBox raceMusic = audioSystem.createBoomBox(audioConstants::SOUND_FILE_TTG_RACE);

	
	physEng->initAudioForVehicles(&audioSystem);
	camera.initializeAudio(&audioSystem);

	//The key is now that multiple sounds can be played at once. As long as sound card can support it
	//Comment out one sound if you dont wanna hear it
	//audioObject.playSound();
	raceMusic.setVolume(0.5f);
	raceMusic.loopSound(true);
	raceMusic.playSound();

	//Controller
	Controller player1 = Controller(1);
	Controller player2 = Controller(2);

	bool P1Connected = player1.isConnected();
	bool P2Connected = player2.isConnected();

	std::cout << "Player1 connected: " << P1Connected << std::endl;
	std::cout << "Player2 connected: " << P2Connected << std::endl;

	//physEng.upwards();
	//End of audio system setup/demo

	// Creating an enemy vehicle 
	physEng->addEnemyVehicle(6, 5, 0);
	AIDrivingComponent aiDriving = AIDrivingComponent(physEng->enemyVehicles[0]);
	aiDriving.AddDrivingTarget(25, 30);
	aiDriving.AddDrivingTarget(138, 42);	//lap marker
	aiDriving.AddDrivingTarget(215, 25);
	aiDriving.AddDrivingTarget(220, -55);
	aiDriving.AddDrivingTarget(162, -89);	//lap marker
	aiDriving.AddDrivingTarget(-65, -80);
	aiDriving.AddDrivingTarget(-90, -50);
	aiDriving.AddDrivingTarget(-80, 45);
	aiDriving.AddDrivingTarget(-76, 43);	//lap marker
	aiDriving.AddDrivingTarget(0, 10);		//lap marker (start/finish)

	physEng->addEnemyVehicle(15, 5, 0);
	AIDrivingComponent aiDriving2 = AIDrivingComponent(physEng->enemyVehicles[1]);
	aiDriving2.AddDrivingTarget(45, 40);
	aiDriving2.AddDrivingTarget(215, -70);
	aiDriving2.AddDrivingTarget(-90, -75);
	aiDriving2.AddDrivingTarget(-65, 55);

	glm::vec3 front = glm::normalize(glm::vec3(0.f, -0.5f, 1.f));
	camera.setFront(front.x, front.y, front.z);
	while (!mainWindow.getShouldClose())
	{
		physEng->stepPhysics();

		const physx::PxVehicleDrive4W* vehicle = physEng->player->gVehicle4W;	//get vehicle
		const physx::PxRigidDynamic* vDynamic = vehicle->getRigidDynamicActor();
		physx::PxQuat vehicleQuaternion = vDynamic->getGlobalPose().q;
		physx::PxVec3 v_dir = vehicleQuaternion.getBasisVector2();
		const physx::PxVec3 vehiclePositionPhysx = vDynamic->getGlobalPose().p;
		glm::vec3 vehiclePosition(vehiclePositionPhysx.x, vehiclePositionPhysx.y, vehiclePositionPhysx.z);



		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		lastTime = now;

		// For AI testing
		aiDriving.Tick(deltaTime);
		//aiDriving2.Tick(deltaTime);


		// Get + Handle User Input
		glfwPollEvents();
		if (P1Connected)
			parseControllerInput(&player1);
		if (P2Connected)
			parseControllerInput(&player2);

		//camera.keyControl(mainWindow.getsKeys(), deltaTime);
		//camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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

		physx::PxVec3 carPos = physEng->player->GetPosition();	//position of TeslaCar

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();

		// Draw pyramid one
		glm::mat4 model = glm::mat4(1.0f);


		//render all pickup boxes
		if (!physEng->pickupBoxes.empty()) {
			float width, height, depth;
			for (int i = 0; i < physEng->pickupBoxes.size(); i++) {
				physx::PxVec3 wallPos = physEng->pickupBoxes.at(i)->actor->getGlobalPose().p;
				glm::vec3 wallp(wallPos.x, wallPos.y, wallPos.z);

				model = glm::mat4(1.0f);
				model = glm::translate(model, wallp);
				//Consider making the pickup boxes a hardcoded size and hardcoding the 
				//trigger volumes to be the same size
				model = glm::scale(model, glm::vec3(1.1f, 0.3f, 0.4f));	
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
				boxTest.RenderModel();
			}
		}

		//////////////////////////////////////////////////////////////////////////


				// Draw racing track
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -5.f, -3.2f));
		model = glm::scale(model, glm::vec3(20.f, 20.f, 20.f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
		//racetrack.RenderModel();
		racetrack_walls.RenderModel();
		racetrack_floor.RenderModel();

///////////////////////////////////////////////////////////////////////
		physx::PxVec3 forwardvec = physx::PxVec3(vehicleQuaternion.x, 0, vehicleQuaternion.z);	//holds camera vectors that match the car

		physx::PxVec3  Direction = vehicleQuaternion.getBasisVector2();
		/////////////////////////////////////////////////////////////////////////////////
				//RENDERING BULLLETS AND PLAYING SHOOTING SOUND

		ShootComp* ba = physEng->player->getShootingComponent();
		HealthComponent* ha = physEng->player->getHealthComponent();

		//Vehicle* payer1 = physEng.player;
		

		if ((ha->GetHealth()) > 0) {
			//Draw bullets after Refactor
			if ((player1.isButtonDown(XButtons.R_Shoulder) || player1.isButtonDown(XButtons.L_Shoulder))) {
				//payer1->shoot(vehiclePosition,uniformModel,uniformSpecularIntensity,uniformShininess,Direction.x,Direction.y,Direction.z);
				glm::vec3 camDir = camera.getCameraDirection();
				if (isCameraFlipped) {
					ba->addBullet_toList(vehiclePosition, uniformModel, uniformSpecularIntensity, uniformShininess, Direction.x, Direction.y, Direction.z);
				}
				else {
					ba->addBullet_toList(vehiclePosition, uniformModel, uniformSpecularIntensity, uniformShininess, camDir.x, Direction.y, camDir.z);
				}
				
				//ha->SetHealth(0);// This hear will prevent bullet and car from rendering
			 }
			ba->renderAllBullets();
			//payer1->renderBullets();

			physx::PxMat44 modelMat(vDynamic->getGlobalPose());	//make model matrix from transform of rigid dynamic
			modelMat.scale(physx::PxVec4(0.3f, 0.3f, 0.3f, 1.f));	//scales the model
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, modelMat.front());

			shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
			TeslaCar.RenderModel();
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		//Enemy CARS rendering
		//there is probably a much better way of rendering the other enemy cars, but this works for now
		if (!physEng->enemyVehicles.empty()) {
			for (int i = 0; i < physEng->enemyVehicles.size(); i++) {
				Vehicle* v = physEng->enemyVehicles.at(i);
				const physx::PxVehicleDrive4W* enemyV = v->gVehicle4W;	//get vehicle
				const physx::PxRigidDynamic* enemyvDynamic = enemyV->getRigidDynamicActor();
				physx::PxQuat enemyvehicleQuaternion = enemyvDynamic->getGlobalPose().q;
				physx::PxVec3 enemyv_dir = enemyvehicleQuaternion.getBasisVector2();
				const physx::PxVec3 enemyvehiclePositionPhysx = enemyvDynamic->getGlobalPose().p;
				glm::vec3 enemyvehiclePosition(enemyvehiclePositionPhysx.x, enemyvehiclePositionPhysx.y, enemyvehiclePositionPhysx.z);

				physx::PxMat44 enemymodelMat(enemyvDynamic->getGlobalPose());	//make model matrix from transform of rigid dynamic
				enemymodelMat.scale(physx::PxVec4(0.3f, 0.3f, 0.3f, 1.f));	//scales the model
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, enemymodelMat.front());

				shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
				TeslaCar.RenderModel();
			}
		}

		//caltrops
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//Rendering caltrops

		//if press down button, use caltrops
		if (player1.isButtonDown(XButtons.DPad_Down)) {
			std::unique_ptr<Caltrops> caltrop(new Caltrops());//using unique_ptr instead of pointer since we will release memory
			caltrop->createCaltrops(vehiclePosition, uniformModel, uniformSpecularIntensity, uniformShininess);
			caltropsList.push_back(std::move(caltrop));
		}
		
		auto c = caltropsList.begin();
		while (c != caltropsList.end()) {
			if ((*c)->isDead())
				caltropsList.erase(c++);
			else {
				(*c)->renderCaltrops();
				++c;
			}
		}
		//caltrops end here


		//camera
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//update camera
		//now distance and other stuff are inside camera class
		glm::vec3 dir = glm::normalize(glm::vec3(v_dir.x, 0, v_dir.z));
		glm::vec3 dirToUse;
		if(isCameraFlipped) {
			dirToUse = dir * -1.f;
		}
		else {
			dirToUse = dir;
		}

		if (player1.RStick_InDeadzone()) {
			camera.stickControl(0.f, vehiclePosition, dirToUse, player1.isButtonDown(XButtons.R_Thumbstick), isCameraFlipped);
		}
		else {
			camera.stickControl(player1.rightStick_X(), vehiclePosition, dirToUse, player1.isButtonDown(XButtons.R_Thumbstick), isCameraFlipped);
		}
		
		//end camera stuff



		//shadow
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//Rendering shadows

		//turn on blend mode
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		shadowShader.UseShader();
		uniformModel = shadowShader.GetModelLocation();
		uniformProjection = shadowShader.GetProjectionLocation();
		uniformView = shadowShader.GetViewLocation();


		model = glm::mat4(1.0f);
		physx::PxMat44 carModel(vDynamic->getGlobalPose());	//make model matrix from transform of rigid dynamic
		//modelMat.scale(physx::PxVec4(0.3f, 0.3f, 0.3f, 1.f));	//scales the model
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, carModel.front());
		

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));

		shadowTexture.UseTexture();
		shadowList[0]->renderShadow();
		glEnable(GL_DEPTH_TEST);

		//Shadows end here


		//HUD
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//Rendering HUD
		//HUD stars here
		hud.use();
		
		//HUD ends here

		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));

		// End of rendering 

		// Start the Dear ImGui frame

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
		{
			static float f = 0.0f;
			static int counter = 0;

			ImGui::Begin("Debug");
			ImGui::Text("Driving mode and Position");
			ImGui::Text("Frame per Second counter");               // Display some text (you can use a format strings too)
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::Text("Drivemode: %i Xpos: %f Ypos: %f Zpos: %f", physEng->getModeType(), carPos.x, carPos.y, carPos.z);
			ImGui::Text("Drivemode: %i Xvec: %f Yvec: %f Zvec: %f", physEng->getModeType(), vehicleQuaternion.x, vehicleQuaternion, vehicleQuaternion.z);
			ImGui::Text("Drivemode: %i Xvec: %f Yvec: %f Zvec: %f", physEng->getModeType(), v_dir.x, v_dir.y, v_dir.z);

			ImGui::End();
		}

		// Rendering imgui
		ImGui::Render();
		int display_w, display_h;
		glfwGetFramebufferSize(mainWindow.getWindow(), &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		//glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
		//glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		//glClear(GL_COLOR_BUFFER_BIT);

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		// imgui ends here

		// TODO: Load shader in a material struct in the model (Basically all of the following code refactored to being in model


		mainWindow.swapBuffers();


		//Shooting actions
		
		
	}
	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	


	return 0;
}