#include "Headers\CIMPult.h"

CIMPult::CIMPult(void) : cim1(4), cim2(8) {
	speed = 0.0;
	launching = false;
	launch_speed = 0;
}

void CIMPult::CIMLaunch(float pos) {
	if (not launching and pos <= 0.15) launching = true;
}

void CIMPult::Update(float pos) {
	if (pos > 1.75) {
		launching = false;
		launch_speed = 0;
	}
	if (launching) {
		launch_speed += 0.1;
		if (launch_speed > 1.0) launch_speed = 1.0;
		cim1.Set(launch_speed);
		cim2.Set(launch_speed);
	}
	else {
		if (pos > 0.1) {
			cim1.Set(-0.05);
			cim2.Set(-0.05);
		}
		else {
			cim1.Set(0);
			cim2.Set(0);
		}
	}
}


bool CIMPult::CheckLoad(void) {
	return 0;
}
