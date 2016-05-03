#include "Controller.h"
#include <iostream>


Controller::Controller(int playerNr)
{
	_controllerNum = playerNr;
}


Controller::~Controller()
{
}

//Controller::Controller()
//{
//	Controller(0);
//}

//Retruns current controller state
XINPUT_STATE Controller::GetState(){
	//Delete current memory
	ZeroMemory(&_controllerState, sizeof(XINPUT_STATE));
	//Get controllerstate (state axis, buttons)
	XInputGetState(_controllerNum, &_controllerState);

	return _controllerState;

}
//Returns bool that tells if the controller is connected
bool Controller::IsConnected(){
	// Zeroise the state
	ZeroMemory(&_controllerState, sizeof(XINPUT_STATE));

	// Get the state

	DWORD Result = XInputGetState(_controllerNum, &_controllerState);

	//Check if Controller is connected
	if (Result == ERROR_SUCCESS)
	{
		return true;		//is connected
	}
	else
	{
		return false;		//is not connected
	}
}

//Returns the Button(only 1 button at a time is relevant)
Button Controller::getButton(){
	if (_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_A)
	{
		return Button::ButtonA;
	}

	if (_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_B)
	{
		return Button::ButtonB;
	}

	if (_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_Y)
	{
		return Button::ButtonY;
	}

	if (_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_BACK)
	{
		return Button::Back;
	}

	if (_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_X)
	{
		return Button::ButtonX;
	}
	return Button::None;

}
//Get the current axis state and returns it
XINPUT_AXIS Controller::getAxis(){
	XINPUT_AXIS axis;
	//Trigger 0 - 255
	axis.bLeftTrigger = _controllerState.Gamepad.bLeftTrigger;
	axis.bRightTrigger = _controllerState.Gamepad.bRightTrigger;

	//Analogstichks: -32768 - 32767 
	axis.sThumbLX = _controllerState.Gamepad.sThumbLX;
	axis.sThumbLY = _controllerState.Gamepad.sThumbLY;
	axis.sThumbRX = _controllerState.Gamepad.sThumbRX;
	axis.sThumbRY = _controllerState.Gamepad.sThumbRY;

	
	//check if value is in the deadzone
	return CheckDeadZone(axis);

	
}

//Corrects "dead" axis and returns the corrected value
XINPUT_AXIS Controller::CheckDeadZone(XINPUT_AXIS axis){
	//If Axe is in deadzone   negative deadzone(-7849) < value < positive deadzone(7849) 
	if (axis.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && axis.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
	{
		//set value = 0 => stick is in neutral position
		axis.sThumbLX = 0;
	}

	if (axis.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && axis.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
	{
		axis.sThumbLY = 0;
	}

	if (axis.sThumbRX < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && axis.sThumbRX > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
	{
		axis.sThumbRX = 0;
	}

	if (axis.sThumbRY < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && axis.sThumbRY > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
	{
		axis.sThumbRY = 0;
	}

	return axis;
}

//lets the controller vibrate
void Controller::Vibrate(int leftVal, int rightVal)
{
	// Create a Vibraton State
	XINPUT_VIBRATION Vibration;

	// Zeroise the Vibration
	ZeroMemory(&Vibration, sizeof(XINPUT_VIBRATION));

	// Set the Vibration Values
	Vibration.wLeftMotorSpeed = leftVal;
	Vibration.wRightMotorSpeed = rightVal;

	// Vibrate the controller
	XInputSetState(_controllerNum, &Vibration);
}