#include "Headers/ElToro.h"

ElToro::ElToro(void) : tal1(1), tal2(5) {
	speed = 0.0;
}

void ElToro::Start(void) {
	speed = 1.0;
}

void ElToro::Set(double x) {
	if(x > 1.0)
		x = 1.0;
	if(x < -1.0)
		x = -1.0;
	speed = x;
}

void ElToro::Stop(void) {
	speed = 0.0;
}

void ElToro::Update(void) {
	tal1.SetSpeed(speed);
	tal2.SetSpeed(-speed);
}
