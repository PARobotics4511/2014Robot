#include "Class Definitions\Headers\RobotCommands.h"
#include <cmath>
#include "math.h"
#include <algorithm>

class RobotDemo : public SimpleRobot
{
	Joystick notLogitech;
	RobotCommands CIMeon;

public:
	RobotDemo() : notLogitech(1), CIMeon() {
		CIMeon.cComponents.DriveTrain.SetExpiration(0.1);
		CIMeon.cComponents.DriveTrain.SetSafetyEnabled(true);
		CIMeon.cComponents.DriveTrain.SetInvertedMotor(CIMeon.cComponents.DriveTrain.kFrontRightMotor,true);
		CIMeon.cComponents.DriveTrain.SetInvertedMotor(CIMeon.cComponents.DriveTrain.kRearRightMotor,true);
		CIMeon.cComponents.m_LCD->Clear();

	}

	void Autonomous()
	{
	    for(int i = 0; i < 2000; i++)
	    {
	    	if (i >= 100 && i < 500)
	    		CIMeon.cComponents.DriveTrain.MecanumDrive_Cartesian(0.0,-0.4,0.0);
	    	else
	    		CIMeon.cComponents.DriveTrain.MecanumDrive_Cartesian(0.0,0.0,0.0);
	    		
	    	if (i >= 0 && i < 100)
	    		CIMeon.cComponents.cElToro.Set(0.9);
	    	else
	    		CIMeon.cComponents.cElToro.Set(0.0);
	    	
	        //if (i == 1100) CIMeon.cComponents.cCIMPult.CIMLaunch();
	        CIMeon.cComponents.cycle();
	        Wait(0.005);
	    }
	}

	void OperatorControl()
	{
		bool buttonPressed1 = false;
		float deadzone_x = notLogitech.GetX();
		float deadzone_y = -notLogitech.GetY();
		float deadzone_z = notLogitech.GetRawAxis(4)/3.0;

		while (IsOperatorControl())
		{
			deadzone_x = notLogitech.GetX();
			deadzone_y = notLogitech.GetY();
			deadzone_z = notLogitech.GetRawAxis(4);

			if (deadzone_x>0) deadzone_x = max(deadzone_x-0.25,0)*(1/0.75);
			if (deadzone_y>0) deadzone_y = max(deadzone_y-0.25,0)*(1/0.75);
			if (deadzone_z>0) deadzone_z = max(deadzone_z-0.15,0)*(1/0.85);
			if (deadzone_x<0) deadzone_x = min(deadzone_x+0.25,0)*(1/0.75);
			if (deadzone_y<0) deadzone_y = min(deadzone_y+0.25,0)*(1/0.75);
			if (deadzone_z<0) deadzone_z = min(deadzone_z+0.15,0)*(1/0.85);
			deadzone_z /= 3;

			//
			// Remap this button to right shoulder; left shoulder will be lock-on
			//
			if (notLogitech.GetRawButton(2) and not buttonPressed1) {
				CIMeon.cComponents.cEyePad.picFunctions();
				buttonPressed1 = true;
				if (CIMeon.cComponents.cEyePad.rHot)
                    CIMeon.cComponents.m_LCD->Printf(DriverStationLCD::Line(0),1,"Hot: True");
				else if (not CIMeon.cComponents.cEyePad.rHot)
                    CIMeon.cComponents.m_LCD->Printf(DriverStationLCD::Line(0),1,"Hot: False");
				CIMeon.cComponents.m_LCD->Printf(DriverStationLCD::Line(1),1,"Distance to goal: %f",CIMeon.cComponents.cEyePad.rDistance);
			}
			else buttonPressed1 = false;


			if (notLogitech.GetRawButton(1)) {
				CIMeon.cComponents.cCIMPult.CIMLaunch();
			}
			else if (notLogitech.GetRawButton(2)) {
				CIMeon.cComponents.cCIMPult.CIMLaunch(CIMeon.cComponents.cCIMPult.degToVolt(110.0),1.0);
			}
			else if (notLogitech.GetRawButton(3)) {
				CIMeon.cComponents.cCIMPult.CIMLaunch(CIMeon.cComponents.cCIMPult.degToVolt(120.0),0.3);
			}
			else if (notLogitech.GetRawButton(4)) {
				//CIMeon.cComponents.cCIMPult.CIMLaunch(CIMeon.cComponents.cCIMPult.currentVoltSet,CIMeon.cComponents.cCIMPult.currentSpeedSet);
				CIMeon.cComponents.cCIMPult.CIMLaunch(CIMeon.cComponents.cCIMPult.degToVolt(100.0),1.0);
			}
			
			if (notLogitech.GetDirectionDegrees() == 90) CIMeon.cComponents.cCIMPult.currentSpeedSet += 0.05;
			if (notLogitech.GetDirectionDegrees() == 270) CIMeon.cComponents.cCIMPult.currentSpeedSet -= 0.05;
			if (notLogitech.GetDirectionDegrees() == 180) CIMeon.cComponents.cCIMPult.currentVoltSet += 0.1;
			if (notLogitech.GetDirectionDegrees() == 0 || notLogitech.GetDirectionDegrees() == 360) CIMeon.cComponents.cCIMPult.currentVoltSet -= 0.1;
			CIMeon.cComponents.DriveTrain.MecanumDrive_Cartesian(deadzone_x, deadzone_y, deadzone_z); //Drive with the motors on channels 4,5,6,7.  The arguments are x, y, direction, and not useful
			CIMeon.cComponents.cElToro.Set(-notLogitech.GetRawAxis(3)/1.5);
			CIMeon.cComponents.cycle();
			Wait(0.005);
		}
	}

	void Test() {

	}
};

START_ROBOT_CLASS(RobotDemo);

