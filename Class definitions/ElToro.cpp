#include "Headers/ElToro.h"

ElToro::ElToro(void) : tal1(2), tal2(3) {
	
}

void ElToro::Start(void) {
	tal1.SetSpeed(1);
	tal2.SetSpeed(1);
}

void ElToro::Stop(void) {
	tal1.SetSpeed(0);
	tal2.SetSpeed(0);
}
