// TeslaGamesEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Game.h"

#include <string>

#include "pch.h"
#include <iostream>

class TestComponent : public Component {
public:
	TestComponent() {}
	~TestComponent() {}
	void Tick(float deltaTime) {}
	void Tick(float deltaTime, std::string debugString) {
		std::cout << "I got this string: ";
		std::cout << debugString << std::endl;
	}
};

class TestObject : public Object {
public:
	TestComponent component;
	TestObject() {}
	~TestObject() {}
	void Tick(float deltaTime) {
		std::string str = "Test";
		component.Tick(deltaTime, str);
	}
};

int main()
{
	Game mainGame;
	Object* obj = new TestObject();
	mainGame.AddObject(obj);
	mainGame.Play();
    std::cout << "Hello World!\n";
	return 1;
}
