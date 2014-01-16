#pragma once
#include "WPILib.h"

class CIMPult {
public:
	CIMPult(void);
	void CIMLaunch(void);
	bool CheckLoad(void);
	double ArmPosition(void);
	
private:
	Talon cim1;
	Talon cim2;
};
