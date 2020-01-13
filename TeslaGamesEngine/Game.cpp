#include "pch.h"
#include "Game.h"

Game::Game()
{
}

void Game::Play()
{
	while (1) {
		// Get input

		// Get change in time
		float deltaTime = 0.0f;

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
