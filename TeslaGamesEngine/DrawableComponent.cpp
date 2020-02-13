#include "DrawableComponent.h"

#include <iostream>

DrawableComponent::DrawableComponent()
{
}

void DrawableComponent::Tick(float deltaTime)
{
	std::cout << deltaTime << std::endl;
}

DrawableComponent::~DrawableComponent()
{
}
