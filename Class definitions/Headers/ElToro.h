#pragma once
#include "WPILib.h"

class ElToro {
public:
	ElToro(void);
	void Start(void);
	void Stop(void);
	void Set(double);
	void Update(void);
	
private:
	Talon tal1;
	Talon tal2;
	double speed;
};
