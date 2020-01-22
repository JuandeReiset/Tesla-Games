#include "pch.h"
#include "Game.h"

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
		double last = now;
		std::cout << deltaTime << std::endl;

		// Calculate framerate

		// Simulate all objects
		for (auto object : objects) {
			object->Tick(deltaTime);
		}

		// Repeat

	}
}


Game::~Game()
{
}
