#pragma once
#include "WPILib.h"
#include "CIMPult.h"
#include "ElToro.h"
#include "EyePad.h"

class Components {
public:
	Components(void);
	CIMPult cCIMPult;
	ElToro cElToro;
	
	//Drive components
	RobotDrive DriveTrain;
	EyePad cEyePad;
	Talon DriveTalon1;
	Talon DriveTalon2;
	Talon DriveTalon3;
	Talon DriveTalon4;
};
