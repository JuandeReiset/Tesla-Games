#include "pch.h"
#include "Game.h"
#include "Global.h"

Game::Game()
{
}

void Game::AddObject(Object* obj)
{
	objects.push_back(obj);
}

void Game::Play()
{
	// 
	double last = glfwGetTime();
	while (1) {
		// Get input

		// Get change in time
		double now = glfwGetTime();
		double deltaTime = now - last;
		last = now;
		//std::cout << deltaTime << std::endl;

		// Calculate framerate

		// Simulate all objects
		for (auto object : objects) {
			object->Tick(deltaTime);
		}

		if (dead_flag == 1) {
			std::cout << "YOU ARE DEAD" << std::endl;
			break;
		}

		// Repeat

	}
}


Game::~Game()
{
}
