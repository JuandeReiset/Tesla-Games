// TeslaGamesEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
// The TeslaGamesEngine will be changed to a .lib, not .exe and then be included in the TeslaGames Project

#include "pch.h"

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <iostream>
#include <vector>
#include <PhysX/PxPhysicsAPI.h>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "Object.h"
#include "Game.h"
#include "Vihecle.h"
#include "DamagingObject.h"

// Stuff for imgui
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"

// end of stuff for imgui

// Stuff TA Ben added
#include <PhysX/PxPhysicsAPI.h>
using namespace physx;
// End of stuff TA Ben added

int main(void) {
	Game mainGame;
	Object* car = new Vihecle(1);
	Object* bullet = new DamagingObject(20, 1);

	mainGame.AddObject(car);
	mainGame.AddObject(bullet);

	mainGame.Play();

	return 0;
}