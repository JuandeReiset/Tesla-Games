#pragma once

#include "stdio.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>

/*
 * Class representing the window on which models are displayed
 */

class Window
{
public:
	// Create a defaul 800 x 600 window
	Window();

	// Create a window of specified size
	Window(GLint windowWidth, GLint windowHeight);

	// Initialise the window for viewing
	int Initialise();

	// Accessors
	GLint getBufferWidth() { return bufferWidth; }
	GLint getBufferHeight() { return bufferHeight; }
	bool getShouldClose() { return glfwWindowShouldClose(mainWindow); }

	void swapBuffers() { glfwSwapBuffers(mainWindow); }

	~Window();

private:
	GLFWwindow* mainWindow;

	GLint width, height;
	GLint bufferWidth, bufferHeight;
};

