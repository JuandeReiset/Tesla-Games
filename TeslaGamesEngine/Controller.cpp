#include "pch.h"
#include "Controller.h"
#pragma comment(lib, "Xinput.lib")

//Followed https://lcmccauley.wordpress.com/2014/01/05/gamepad-input-tutorial/

XButtonIDs XButtons;
// 'XButtonIDs' - Default constructor
XButtonIDs::XButtonIDs()
{
	// These values are used to index the XINPUT_Buttons array,
	// accessing the matching XINPUT button value

	A = 0;
	B = 1;
	X = 2;
	Y = 3;

	DPad_Up = 4;
	DPad_Down = 5;
	DPad_Left = 6;
	DPad_Right = 7;

	L_Shoulder = 8;
	R_Shoulder = 9;

	L_Thumbstick = 10;
	R_Thumbstick = 11;

	Start = 12;
	Back = 13;
}

Controller::Controller()
{
}
Controller::Controller(int playerNum)
{
	playerIndex = playerNum - 1;
	// Iterate through all gamepad buttons
	for (int i = 0; i < BUTTON_COUNT; i++)
	{
		bPrev_ButtonStates[i] = false;
		bButtonStates[i] = false;
		bController_ButtonsDown[i] = false;
	}
}
Controller::~Controller()
{
}

XINPUT_STATE Controller::getState()
{
	// Temporary XINPUT_STATE to return
	XINPUT_STATE GamepadState;

	// Zero memory
	RtlSecureZeroMemory(&GamepadState, sizeof(XINPUT_STATE));

	// Get the state of the gamepad
	XInputGetState(playerIndex, &GamepadState);

	// Return the gamepad state
	return GamepadState;
}
// Return gamepad index
int Controller::getIndex()
{
	return playerIndex;
}
bool Controller::isConnected()
{
	// Zero memory
	RtlSecureZeroMemory(&controllerState, sizeof(XINPUT_STATE));

	// Get the state of the gamepad
	DWORD Result = XInputGetState(playerIndex, &controllerState);

	if (Result == ERROR_SUCCESS) {//I changed the windows SDK (Project -> Properties -> General -> Windows SDK Version -> select 10.0.15063.0)
		return true;  // The gamepad is connected
	}
	else {
		return false; // The gamepad is not connected
	}
		
}
// Update gamepad state
void Controller::update()
{
	controllerState = getState(); // Obtain current gamepad state

	 // Iterate through all gamepad buttons
	for (int i = 0; i < BUTTON_COUNT; i++)
	{
		// Set button state for current frame
		bButtonStates[i] = (controllerState.Gamepad.wButtons & XINPUT_Buttons[i]) == XINPUT_Buttons[i];

		// Set 'DOWN' state for current frame
		bController_ButtonsDown[i] = !bPrev_ButtonStates[i] && bButtonStates[i];
	}
}
// Update button states for next frame
void Controller::refreshState()
{
	memcpy(bPrev_ButtonStates, bButtonStates, sizeof(bPrev_ButtonStates));
}

// Deadzone check for Left Thumbstick
bool Controller::LStick_InDeadzone()
{
	// Obtain the X & Y axes of the stick
	short sX = controllerState.Gamepad.sThumbLX;
	short sY = controllerState.Gamepad.sThumbLY;

	// X axis is outside of deadzone
	if (sX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ||
		sX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		return false;

	// Y axis is outside of deadzone
	if (sY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ||
		sY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		return false;

	// One (or both axes) axis is inside of deadzone
	return true;
}

// Deadzone check for Right Thumbstick
bool Controller::RStick_InDeadzone()
{
	// Obtain the X & Y axes of the stick
	short sX = controllerState.Gamepad.sThumbRX;
	short sY = controllerState.Gamepad.sThumbRY;

	// X axis is outside of deadzone
	if (sX > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ||
		sX < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
		return false;

	// Y axis is outside of deadzone
	if (sY > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ||
		sY < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
		return false;

	// One (or both axes) axis is inside of deadzone
	return true;
}
// Return X axis of left stick
float Controller::leftStick_X()
{
	// Obtain X axis of left stick
	short sX = controllerState.Gamepad.sThumbLX;

	// Return axis value, converted to a float
	return (static_cast<float>(sX) / 32768.0f);
}

// Return Y axis of left stick
float Controller::leftStick_Y()
{
	// Obtain Y axis of left stick
	short sY = controllerState.Gamepad.sThumbLY;

	// Return axis value, converted to a float
	return (static_cast<float>(sY) / 32768.0f);
}

// Return X axis of right stick
float Controller::rightStick_X()
{
	// Obtain X axis of right stick
	short sX = controllerState.Gamepad.sThumbRX;

	// Return axis value, converted to a float
	return (static_cast<float>(sX) / 32768.0f);
}

// Return Y axis of right stick
float Controller::rightStick_Y()
{
	// Obtain the Y axis of the left stick
	short sY = controllerState.Gamepad.sThumbRY;

	// Return axis value, converted to a float
	return (static_cast<float>(sY) / 32768.0f);
}

// Return value of left trigger
float Controller::leftTrigger()
{
	// Obtain value of left trigger
	BYTE Trigger = controllerState.Gamepad.bLeftTrigger;

	if (Trigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
		return Trigger / 255.0f;

	return 0.0f; // Trigger was not pressed
}

// Return value of right trigger
float Controller::rightTrigger()
{
	// Obtain value of right trigger
	BYTE Trigger = controllerState.Gamepad.bRightTrigger;

	if (Trigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
		return Trigger / 255.0f;

	return 0.0f; // Trigger was not pressed
}

// Vibrate the gamepad (values of 0.0f to 1.0f only)
void Controller::rumble(float a_fLeftMotor, float a_fRightMotor)
{
	// Vibration state
	XINPUT_VIBRATION VibrationState;

	// Zero memory
	RtlSecureZeroMemory(&VibrationState, sizeof(XINPUT_VIBRATION));

	// Calculate vibration values
	int iLeftMotor = int(a_fLeftMotor * 65535.0f);
	int iRightMotor = int(a_fRightMotor * 65535.0f);

	// Set vibration values
	VibrationState.wLeftMotorSpeed = iLeftMotor;
	VibrationState.wRightMotorSpeed = iRightMotor;

	// Set the vibration state
	XInputSetState(playerIndex, &VibrationState);
}

// Return true if button is pressed, false if not
bool Controller::isButtonPressed(int a_iButton)
{
	if (controllerState.Gamepad.wButtons & XINPUT_Buttons[a_iButton])
	{
		return true; // The button is pressed
	}

	return false; // The button is not pressed
}
// Frame-specific version of 'GetButtonPressed' function
bool Controller::isButtonDown(int a_iButton)
{
	return bController_ButtonsDown[a_iButton];
}
