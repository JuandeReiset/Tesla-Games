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
	// Create a default 800 x 600 window
	Window();

	// Create a window of specified size
	Window(GLint windowWidth, GLint windowHeight);

	// Initialise the window for viewing
	int Initialise();

	// Accessors
	GLint getBufferWidth() { return bufferWidth; }
	GLint getBufferHeight() { return bufferHeight; }
	GLint getWidth() { return width; };
	GLint getHeight() { return height; };
	bool getShouldClose() { return glfwWindowShouldClose(mainWindow); }
	void setWindowClose() { glfwSetWindowShouldClose(mainWindow, GL_TRUE); }


	bool* getsKeys() { return keys; }
	GLfloat getXChange();
	GLfloat getYChange();

	void swapBuffers() { glfwSwapBuffers(mainWindow); }

	GLFWwindow* getWindow() { return mainWindow;  }
	~Window();

private:
	GLFWwindow* mainWindow;

	GLint width, height;
	GLint bufferWidth, bufferHeight;

	bool keys[1024];

	GLfloat lastX;
	GLfloat lastY;
	GLfloat xChange;
	GLfloat yChange;
	bool mouseFirstMoved;

	void createCallbacks();
	static void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);
	static void handleMouse(GLFWwindow* window, double xPos, double yPos);
};

