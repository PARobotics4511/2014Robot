#include "Class Definitions\Headers\RobotCommands.h"

class RobotDemo : public SimpleRobot
{
	Joystick notLogitech;
	RobotCommands CIMeon;

public:
	RobotDemo() : notLogitech(1), CIMeon() {
		CIMeon.cComponents.DriveTrain.SetExpiration(0.1);
		CIMeon.cComponents.DriveTrain.SetSafetyEnabled(true);
	}

	void Autonomous()
	{
		//Do nothing for now
	}

	void OperatorControl()
	{
		float deadzone_y = notLogitech.GetX();
		float deadzone_x = -notLogitech.GetY();
		float deadzone_z = notLogitech.GetRawAxis(4)/3.0;
		while (IsOperatorControl())
		{
			deadzone_x = -notLogitech.GetY();
			deadzone_y = notLogitech.GetX();
			deadzone_z = notLogitech.GetRawAxis(4)/3.0;
			
			if (pow((deadzone_x*deadzone_x+deadzone_y*deadzone_y),0.5) < 0.15) {
				deadzone_x = 0;
				deadzone_y = 0;
			}
			if (abs(deadzone_z) < 0.15) {
				deadzone_z = 0;
			}
			
			CIMeon.cComponents.DriveTrain.MecanumDrive_Cartesian(deadzone_x, deadzone_y, deadzone_z+0.025); //Drive with the motors on channels 4,5,6,7.  The arguments are x, y, direction, and not useful
			
			Wait(0.005);
		}
	}
	
	/**
	 * Runs during test mode
	 */
	void Test() {

	}
};

START_ROBOT_CLASS(RobotDemo);

