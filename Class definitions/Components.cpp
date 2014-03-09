#include "Headers\Components.h"

Components::Components(void) : cCIMPult(), cElToro(), DriveTrain(3,2,7,6), cEyePad(), DriveTalon1(2), DriveTalon2(3), DriveTalon3(6), DriveTalon4(7), potentiometer() {
	m_LCD = DriverStationLCD::GetInstance();
	Sonar = new AnalogChannel(3);
}

void Components::cycle(void) {
	cElToro.Update();
	cCIMPult.Update(potentiometer.ana->GetVoltage());
	m_LCD->Printf(DriverStationLCD::Line(2),1,"armVolt: %f",potentiometer.ana->GetVoltage());
	m_LCD->Printf(DriverStationLCD::Line(3),1,"sonarVolt: %f",Sonar->GetVoltage());
	m_LCD->Printf(DriverStationLCD::Line(4),1,"Launch speed: %f",cCIMPult.currentSpeedSet);
	m_LCD->Printf(DriverStationLCD::Line(5),1,"Launch angle: %F",cCIMPult.voltToDeg(cCIMPult.currentVoltSet));
	m_LCD->UpdateLCD();
}
