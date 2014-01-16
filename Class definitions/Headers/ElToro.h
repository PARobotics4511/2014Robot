#pragma once
#include "WPILib.h"

class ElToro {
public:
	ElToro(void);
	void Start(void);
	void Stop(void);
	
private:
	Talon tal1;
	Talon tal2;
};
