#include "Headers\CIMPult.h"

CIMPult::CIMPult(void) : cim1(4), cim2(8), minVolt(0.4), maxVolt(2.2), minAngle(10), maxAngle(116) {
	launching = false;
	speed = 0.0;
	armVolt = minVolt;
}

void CIMPult::CIMLaunch(void) {
	CIMLaunch(maxVolt,1.0);
}

void CIMPult::CIMLaunch(float x) {
	CIMLaunch(x,1.0);
}

void CIMPult::CIMLaunch(float x, float y) {
    launchVolt = x;
    launch_speed = y;
	if (not launching and armVolt <= minVolt+0.05) launching = true;
}

void CIMPult::Update(float x) {
	armVolt = x;
    if (launch_speed > 1.0)
        launch_speed = 1.0;
	if (armVolt > maxVolt || armVolt > launchVolt) {
		launching = false;
		speed = 0.0;
	}
	if (launching) {
		speed += 0.1;
		if (speed > launch_speed)
            speed = launch_speed;
		cim1.Set(speed);
		cim2.Set(speed);
	}
	else {
		if (armVolt > minVolt) {
			cim1.Set(-0.05);
			cim2.Set(-0.05);
		}
		else {
			cim1.Set(0.0);
			cim2.Set(0.0);
		}
	}
}


bool CIMPult::CheckLoad(void) {
	return 0;
}

float CIMPult::degToVolt(float x) {
	if (x <= minAngle)
		return minVolt;
	else if (x >= maxAngle)
		return maxVolt;
	else
		return ((x-minAngle)/(maxAngle-minAngle))*(maxVolt-minVolt);
}
