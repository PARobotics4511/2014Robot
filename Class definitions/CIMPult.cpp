#include "Headers\CIMPult.h"

CIMPult::CIMPult(void) : cim1(4), cim2(8), minVolt(0.5), maxVolt(2.0) {
	launching = false;
	speed = 0.0;
}

void CIMPult::CIMLaunch(float x = maxVolt, float y = 1.0) {
    launchVolt = x;
    launch_speed = y;
	if (not launching and armVolt <= minVolt+0.05) launching = true;
}

void CIMPult::Update() {
    if (launch_speed > 1.0)
        launch_speed = 1.0;
	if (armVolt > maxVolt || armVolt > launchVolt) {
		launching = false;
		speed = 0.0;
	}
	if (launching) {
		speed += 0.1;
		if (speed > launching_speed)
            speed = launching_speed;
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
