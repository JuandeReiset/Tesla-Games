#pragma once

#include <GL\glew.h>
#include <glm\glm.hpp>

/*
 * Class representing lights. Used for lighting calculations
 */
class Light
{
public:
	Light();
	Light(GLfloat red, GLfloat green, GLfloat blue,
		GLfloat aIntensity, GLfloat dIntensity);

	~Light();

protected:
	glm::vec3 colour;
	GLfloat ambientIntensity;
	GLfloat diffuseIntensity;
};

