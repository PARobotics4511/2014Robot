#pragma once
#include "WPILib.h"
#include "CIMPult.h"
#include "ElToro.h"
#include "EyePad.h"
#include "Potentiometer.h"

class Components {
public:
	Components(void);
	void cycle(void);
	CIMPult cCIMPult;
	ElToro cElToro;
	DriverStationLCD *m_LCD;
	
	//Drive components
	RobotDrive DriveTrain;
	EyePad cEyePad;
	Talon DriveTalon1;
	Talon DriveTalon2;
	Talon DriveTalon3;
	Talon DriveTalon4;
	Potentiometer potentiometer;
};
