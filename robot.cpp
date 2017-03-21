#include <iostream>
#include "WPILib.h"
#include "utils.hpp" // look for this file in github.com/robobibb/main-bot-2017


class Robot: public frc::IterativeRobot {

private:
	// robot parts:
	RobotDrive myRobot; 	 // drive train
	Joystick xBox, climber;  // single xbox360 controller

public:

	Robot():
		myRobot(0, 4, 1, 3),	// drive train
		xBox(0), climber(1)		// xbox360 controller
	{ myRobot.SetExpiration(0.1); }


	void RobotInit() override {};
	void RobotPeriodic() override {};

	void AutonomousInit() override {};

	void TeleopInit() override {};
	void TeleopPeriodic() override {

		// Y switches directions
		static bool dir_reversable = true, isForward = true;
		if (dir_reversable && xBox.GetRawButton(4)) {
			isForward = !isForward;
			dir_reversable = false;
		} else if (!dir_reversable && !xBox.GetRawButton(4))
			dir_reversable = true;

		// joystick data from previous cycle
		static double stickX = 0, stickY = 0; // `static` keeps this local variable in memory

		// drive the robot
		myRobot.ArcadeDrive(
			utils::expReduceBrownout(0.7 * (isForward ? -1 : 1)
									 * xBox.GetRawAxis(1), stickY),
			-utils::expReduceBrownout(xBox.GetRawAxis(4), stickX) * 0.5
		);

	}

	void DisabledInit() override
		{ std::cout <<"Robot disabled" <<std::endl;	}


};



START_ROBOT_CLASS(Robot);
