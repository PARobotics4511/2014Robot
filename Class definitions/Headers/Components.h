#pragma once
#include "WPILib.h"
#include "CIMPult.h"
#include "ElToro.h"

class Components {
public:
	Components(void);
	CIMPult cCIMPult;
	ElToro cElToro;
	
	//Drive components
	RobotDrive DriveTrain;
	Talon DriveTalon1;
	Talon DriveTalon2;
	Talon DriveTalon3;
	Talon DriveTalon4;
};
