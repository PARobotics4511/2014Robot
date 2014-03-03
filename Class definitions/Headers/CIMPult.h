#pragma once
#include "WPILib.h"

class CIMPult {
public:
	CIMPult(void);
	void CIMLaunch(float,float); // Arguments: position, max angle, max speed
	bool CheckLoad(void);
	void Update(void);

private:
	Talon cim1;
	Talon cim2;
	double speed;
	double armVolt;
	bool launching;
	const float minVolt;
	const float maxVolt;
	float launchVolt;
	float launch_speed;
};
