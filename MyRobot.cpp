#include "Class Definitions\Headers\RobotCommands.h"

class RobotDemo : public SimpleRobot
{
	Joystick notLogitech;
	RobotCommands CIMeon;

public:
	RobotDemo() : notLogitech(1), CIMeon() {
		CIMeon.cComponents.DriveTrain.SetExpiration(0.1);
	}

	void Autonomous()
	{
		CIMeon.cComponents.DriveTrain.SetSafetyEnabled(true);
		//Do nothing for now
	}

	void OperatorControl()
	{
		CIMeon.cComponents.DriveTrain.SetSafetyEnabled(true);
		while (IsOperatorControl())
		{
			CIMeon.cComponents.DriveTrain.MecanumDrive_Cartesian(notLogitech.GetX(),notLogitech.GetY(),notLogitech.GetRawAxis(4)); //Drive with the motors on channels 4,5,6,7.  The arguments are x, y, direction, and not useful
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

