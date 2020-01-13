#include "pch.h"
#include "Game.h"


Game::Game()
{
}

void Game::Play()
{
	while (1) {
		// Get input from Renderer->window

		// Get change in time
		float deltaTime = 0.0f;

		for (auto object : objects) {
			object.Tick(deltaTime);
		}
	}
}


Game::~Game()
{
}
