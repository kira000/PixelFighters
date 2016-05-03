
#define WIN32_LEAN_AND_MEAN

#pragma once
#include "targetver.h"
#include <Windows.h>
#include "xinput.h"


#pragma comment(lib, "XInput9_1_0.lib")

//Enumerationclass for buttons access: Button::ButtonA
enum class Button{ButtonA, ButtonB, ButtonX, ButtonY, Back,None};

//Struct with the relevant Axe-informations
typedef struct _XINPUT_AXIS {
	BYTE bLeftTrigger;
	BYTE bRightTrigger;
	SHORT sThumbLX;
	SHORT sThumbLY;
	SHORT sThumbRX;
	SHORT sThumbRY;
} XINPUT_AXIS;

//Class to get access to a Microsoft Gamepad
class Controller
{
public:
	Controller(int playerNr = 0);
	//Controller();
	~Controller();
	//Retruns current controller state
	XINPUT_STATE GetState();
	//Returns bool that tells if the controller is connected
	bool IsConnected();
	//Returns the Button(only 1 button at a time is relevant)
	Button getButton();
	//Get the current axis state and returns it
	XINPUT_AXIS getAxis();
	//lets the controller vibrate
	void Vibrate(int leftVal = 0, int rightVal = 0);	
	

private:
	//Nr of the corresponding controller
	int _controllerNum;
	//Struct with the controller values
	XINPUT_STATE _controllerState;

	//Corrects "dead" axis and returns the corrected value
	XINPUT_AXIS CheckDeadZone(XINPUT_AXIS axis);
};


