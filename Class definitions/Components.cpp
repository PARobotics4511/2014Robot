#include "Headers\Components.h"

Components::Components(void) : cCIMPult(), cElToro(), DriveTrain(3,2,7,6), cEyePad(), DriveTalon1(2), DriveTalon2(3), DriveTalon3(6), DriveTalon4(7), potentiometer() {
	m_LCD = DriverStationLCD::GetInstance();
}

void Components::cycle(void) {
	cElToro.Update();
	cCIMPult.Update(potentiometer.ana->GetVoltage());
	m_LCD->Printf(DriverStationLCD::Line(2),1,"Arm Voltage: %f",potentiometer.ana->GetVoltage());
	m_LCD->UpdateLCD();
}
