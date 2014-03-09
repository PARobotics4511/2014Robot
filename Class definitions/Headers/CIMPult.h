#pragma once
#include "WPILib.h"

class CIMPult {
public:
	CIMPult(void);
	void CIMLaunch(float,float); // Arguments: max angle, max speed
	void CIMLaunch(float);
	void CIMLaunch(void);
	bool CheckLoad(void);
	void Update(float); // Argument: armVolt
	float degToVolt(float);
	float voltToDeg(float);
	float currentVoltSet;
	float currentSpeedSet;

private:
	Talon cim1;
	Talon cim2;
	double speed;
	double armVolt;
	bool launching;
	const float minVolt;
	const float maxVolt;
	const float minAngle;
	const float maxAngle;
	float launchVolt;
	float launch_speed;
};
