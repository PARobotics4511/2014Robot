#include "Headers\Components.h"

Components::Components(void) : cCIMPult(), cElToro(), DriveTrain(3,2,7,6), cEyePad(), DriveTalon1(2), DriveTalon2(3), DriveTalon3(6), DriveTalon4(7), potentiometer() {
	m_LCD = DriverStationLCD::GetInstance();
	armVolt = potentiometer.ana->GetVoltage();
}

void Components::cycle(void) {
	cElToro.Update();
	armVolt = potentiometer.ana->GetVoltage();
	cCIMPult.Update();
	m_LCD->Printf(DriverStationLCD::Line(2),1,"Arm Voltage: %f",armVolt);
	m_LCD->UpdateLCD();
}
