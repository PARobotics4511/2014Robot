#pragma once
#include "WPILib.h"

class CIMPult {
public:
	CIMPult(void);
	void CIMLaunch(float pos, float launchAngle);
	bool CheckLoad(void);
	void Update(float pos);

private:
	Talon cim1;
	Talon cim2;
	double speed;
	double voltage;
	bool launching;
	float launch_speed;
	const float minVolt;
	const float maxVolt;
	float launchVolt;
};
