#pragma once

#include "Component.h"
#include <Windows.h>
#include <Xinput.h>

class Controller
{
	public:
		Controller();
		Controller(int playerNum);
		~Controller();

		void update(); // Update gamepad state
		void refreshState(); // Update button states for next frame


		XINPUT_STATE getState(); // Return gamepad state
		int getIndex();          // Return gamepad index
		bool isConnected();        // Return true if gamepad is connected

		 // Thumbstick functions (LS and RS)
		 // - Return true if stick is inside deadzone, false if outside
		bool LStick_InDeadzone();
		bool RStick_InDeadzone();
		float leftStick_X();  // Return X axis of left stick
		float leftStick_Y();  // Return Y axis of left stick
		float rightStick_X(); // Return X axis of right stick
		float rightStick_Y(); // Return Y axis of right stick

		// Trigger functions (LT and RT)
		float leftTrigger();  // Return value of left trigger
		float rightTrigger(); // Return value of right trigger

		 // Vibrate the gamepad (0.0f cancel, 1.0f max speed)
		void rumble(float a_fLeftMotor = 0.0f, float a_fRightMotor = 0.0f);

		// Button functions
		// - 'Pressed' - Return true if pressed, false if not
		// - 'Down'    - Same as 'Pressed', but ONLY on current frame
		bool isButtonPressed(int a_iButton);
		bool isButtonDown(int a_iButton);

	private:
		XINPUT_STATE controllerState; // Current gamepad state
		int playerIndex;  // Gamepad index (eg. 1,2,3,4)

		static const int BUTTON_COUNT = 14;    // Total gamepad buttons

		bool bPrev_ButtonStates[BUTTON_COUNT]; // Previous frame button states
		bool bButtonStates[BUTTON_COUNT];      // Current frame button states

		// Buttons pressed on current frame
		bool bController_ButtonsDown[BUTTON_COUNT];
};

//A,B,X,Y, Start, Back, DPAD ,clicking LS and RS, RB and LB
// XInput Button values
static constexpr WORD XINPUT_Buttons[] = {
	  XINPUT_GAMEPAD_A,
	  XINPUT_GAMEPAD_B,
	  XINPUT_GAMEPAD_X,
	  XINPUT_GAMEPAD_Y,
	  XINPUT_GAMEPAD_DPAD_UP,
	  XINPUT_GAMEPAD_DPAD_DOWN,
	  XINPUT_GAMEPAD_DPAD_LEFT,
	  XINPUT_GAMEPAD_DPAD_RIGHT,
	  XINPUT_GAMEPAD_LEFT_SHOULDER,
	  XINPUT_GAMEPAD_RIGHT_SHOULDER,
	  XINPUT_GAMEPAD_LEFT_THUMB,
	  XINPUT_GAMEPAD_RIGHT_THUMB,
	  XINPUT_GAMEPAD_START,
	  XINPUT_GAMEPAD_BACK
};

// XInput Button IDs
struct XButtonIDs
{
	XButtonIDs(); // Default constructor

	// 'Action' buttons
	int A, B, X, Y;

	// Directional Pad (D-Pad)
	int DPad_Up, DPad_Down, DPad_Left, DPad_Right;

	// Shoulder ('Bumper') buttons
	int L_Shoulder, R_Shoulder;

	// Thumbstick buttons
	int L_Thumbstick, R_Thumbstick;

	int Start; // 'START' button
	int Back;  // 'BACK' button
};

// Externally define the 'XButtonIDs' struct as 'XButtons'
extern XButtonIDs XButtons;

