#pragma once
#include "Component.h"

class DrawableComponent :
	public Component
{
public:
	DrawableComponent();
	void Tick(float deltaTime);
	~DrawableComponent();

private:

};

