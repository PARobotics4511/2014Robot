#include "Class Definitions\Headers\RobotCommands.h"

class RobotDemo : public SimpleRobot
{
	RobotDrive myRobot;
	Joystick stick;
	RobotCommands CIMeon;

public:
	RobotDemo() : myRobot(4,5,6,7), stick(1), CIMeon() {
		myRobot.SetExpiration(0.1);
	}

	void Autonomous()
	{
		myRobot.SetSafetyEnabled(true);
		//Do nothing for now
	}

	void OperatorControl()
	{
		myRobot.SetSafetyEnabled(true);
		while (IsOperatorControl())
		{
			myRobot.MecanumDrive_Cartesian(0,0,0,0); //Drive with the motors on channels 4,5,6,7.  The arguments are x, y, direction, and not useful
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

