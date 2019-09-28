// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include <Xinput.h>
#include <string>
#include <chrono>
#include <thread>
#include <sstream>

#pragma comment (lib, "xinput.lib")


class ControllerState {

public:
	bool A = false;
	bool B = false;
	bool X = false;
	bool Y = false;

	bool RB = false;
	bool LB = false;

	bool DPAD_UP = false;
	bool DPAD_DOWN = false;
	bool DPAD_LEFT = false;
	bool DPAD_RIGHT = false;

	bool START = false;
	bool BACK = false;

	bool LS = false;
	bool RS = false;

	float left_stick_x = 0.0;
	float left_stick_y = 0.0;

	float right_stick_x = 0.0;
	float right_stick_y = 0.0;

	float right_trigger = 0.0;
	float left_trigger = 0.0;

	std::string toString() {

		std::stringstream ss;

		ss << "A " << A << std::endl;
		ss << "B " << B << std::endl;
		ss << "X " << X << std::endl;
		ss << "Y " << Y << std::endl;

		ss << "RB " << RB << std::endl;
		ss << "LB " << LB << std::endl;

		ss << "DPAD_UP " << DPAD_UP << std::endl;
		ss << "DPAD_DOWN " << DPAD_DOWN << std::endl;
		ss << "DPAD_LEFT " << DPAD_LEFT << std::endl;
		ss << "DPAD_RIGHT " << DPAD_RIGHT << std::endl;

		ss << "LS X " << left_stick_x << std::endl;
		ss << "LS Y " << left_stick_y << std::endl;

		ss << "LEFT TRIGGER " << left_trigger << std::endl;
		ss << "RIGHT TRIGGER " << right_trigger << std::endl;

		ss << "LEFT STICK X" << left_stick_x << std::endl;
		ss << "LEFT STICK Y " << left_stick_y << std::endl;

		ss << "RIGHT STICK X" << right_stick_x << std::endl;
		ss << "RIGHT STICK Y " << right_stick_y << std::endl;

		ss << std::endl;

		return ss.str();
	}

};


ControllerState getControllerState(int controller) {
	XINPUT_STATE state;
	ZeroMemory(&state, sizeof(XINPUT_STATE));

	ControllerState controllerState = ControllerState();

	if (XInputGetState(controller, &state) == ERROR_SUCCESS)
	{
		if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_A) != 0) {
			controllerState.A = true;
		}
		if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_B) != 0) {
			controllerState.B = true;
		}
		if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_X) != 0) {
			controllerState.X = true;
		}
		if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_Y) != 0) {
			controllerState.Y = true;
		}
		if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_START) != 0) {
			controllerState.START= true;
		}
		if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK) != 0) {
			controllerState.BACK = true;
		}

		if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) != 0) {
			controllerState.DPAD_LEFT = true;
		}
		if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) != 0) {
			controllerState.DPAD_RIGHT = true;
		}
		if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) != 0) {
			controllerState.DPAD_UP = true;
		}
		if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) != 0) {
			controllerState.DPAD_DOWN = true;
		}

		if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) != 0) {
			controllerState.LB = true;
		}

		if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) != 0) {
			controllerState.RB = true;
		}

		controllerState.left_trigger = (float)state.Gamepad.bLeftTrigger / 255;
		controllerState.right_trigger = (float)state.Gamepad.bRightTrigger / 255;




		float normLX = fmaxf(-1, (float)state.Gamepad.sThumbLX / 32767);
		float normLY = fmaxf(-1, (float)state.Gamepad.sThumbLY / 32767);

		float deadzoneX = 0.05f;
		float deadzoneY = 0.02f;

		controllerState.left_stick_x = (abs(normLX) < deadzoneX ? 0 : normLX);
		controllerState.left_stick_y = (abs(normLY) < deadzoneY ? 0 : normLY);

		float normRX = fmaxf(-1, (float)state.Gamepad.sThumbLX / 32767);
		float normRY = fmaxf(-1, (float)state.Gamepad.sThumbLY / 32767);



		controllerState.right_stick_x = (abs(normRX) < deadzoneX ? 0 : normRX);
		controllerState.right_stick_y = (abs(normRY) < deadzoneY ? 0 : normRY);

	}
	else {
		std::cout << "Controller " << controller << " not connected\n";
	}


	return controllerState;

	
}


int main()
{

	while (true) {
		std::cout << getControllerState(0).toString();

		std::this_thread::sleep_for(std::chrono::milliseconds(5000));
	}
    
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
