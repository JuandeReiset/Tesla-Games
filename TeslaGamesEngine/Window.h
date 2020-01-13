#pragma once

/*
 * Class representing the wndow on which models are displayed
 */
class Window
{
public:
	Window();
	void Initialize(float h, float w);
	void CloseWindow();
	~Window();

private:
	// Initializes the callback functions for this window using glfw
	void CreateCallbacks();

	// GLFWwindow window;
	float height;
	float width;
};

