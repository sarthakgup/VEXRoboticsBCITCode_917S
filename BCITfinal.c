#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    ExpanderStatus, sensorAnalog)
#pragma config(Sensor, in2,    ArmPot,         sensorPotentiometer)
#pragma config(Sensor, dgtl7,  Bumper,         sensorTouch)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_3,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_4,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           LeftClaw,      tmotorVex393_HBridge, openLoop, reversed, encoderPort, I2C_4)
#pragma config(Motor,  port2,           TowerRight13,  tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           TowerRight2,   tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           LF,            tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port5,           LB,            tmotorVex393HighSpeed_MC29, openLoop, encoderPort, I2C_2)
#pragma config(Motor,  port6,           RF,            tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           RB,            tmotorVex393HighSpeed_MC29, openLoop, reversed, encoderPort, I2C_1)
#pragma config(Motor,  port8,           TowerLeft13,   tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           TowerLeft2,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          RightClaw,     tmotorVex393_HBridge, openLoop, encoderPort, I2C_3)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Description: Competition template for VEX EDR                      */
/*                                                                           */
/*---------------------------------------------------------------------------*/

// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"

const short leftButton = 1;
const short centerButton = 2;
const short rightButton = 4;

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton()
{
  // Set bStopTasksBetweenModes to false if you want to keep user created tasks
  // running between Autonomous and Driver controlled modes. You will need to
  // manage all user created tasks if set to false.
  bStopTasksBetweenModes = true;

	// Set bDisplayCompetitionStatusOnLcd to false if you don't want the LCD
	// used by the competition include file, for example, you might want
	// to display your team name on the LCD in this function.
	// bDisplayCompetitionStatusOnLcd = false;

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/
float expanderStatus = 0;
task Display()
{
	bLCDBacklight = true;									// Turn on LCD Backlight
	string mainBattery, expanderBattery, backupBattery;

	while(true)														// An infinite loop to keep the program running until you terminate it
	{
		clearLCDLine(0);											// Clear line 1 (0) of the LCD
		clearLCDLine(1);											// Clear line 2 (1) of the LCD

		//Display the Primary Robot battery voltage
		displayLCDString(0, 0, "Primary: ");
		sprintf(mainBattery, "%1.2f%c", nImmediateBatteryLevel/1000.0,'V'); //Build the value to be displayed
		displayNextLCDString(mainBattery);

		//Display the power expander battery voltage,
		// assuming power expander status is connected to int 1 (analog 1 port)
		displayLCDString(1, 0, "Expander: ");
		expanderStatus = (sensorValue[ExpanderStatus] - 210.0)/255.0 ; // just find the no-battery value and divisor manually
		sprintf(expanderBattery, "%1.2f%c", expanderStatus,'V'); //Build the value to be displayed
		displayNextLCDString(expanderBattery);

		//Display the Backup battery voltage
		//displayLCDString(1, 0, "Backup: ");
		//sprintf(backupBattery, "%1.2f%c", BackupBatteryLevel/1000.0, 'V');	//Build the value to be displayed
		//displayNextLCDString(backupBattery);

		//Short delay for the LCD refresh rate
		wait1Msec(100);
	}
}

task autonomous()
{
  // ..........................................................................
  // Insert user code here.
  // ..........................................................................

  // Remove this function call once you have "real" code.
  AutonomousCodePlaceholderForTesting();
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/
task DisplayArmPot()
{
	bLCDBacklight = true;									// Turn on LCD Backlight
	string armPot;

	while(true)														// An infinite loop to keep the program running until you terminate it
	{
		clearLCDLine(0);											// Clear line 1 (0) of the LCD
		clearLCDLine(1);											// Clear line 2 (1) of the LCD

		//Display the arm potentiometer value
		displayLCDString(0, 0, "Arm Potentiometer ");
		sprintf(armPot, "%d", sensorValue[ArmPot]); //Build the value to be displayed
		displayLCDString(1, 0, armPot);

		//Short delay for the LCD refresh rate
		wait1Msec(100);
	}
}

task DisplayClawMotors()
{
	bLCDBacklight = true;									// Turn on LCD Backlight
	string clawMotor;
	string clawencoder;

	while(true)														// An infinite loop to keep the program running until you terminate it
	{
		clearLCDLine(0);											// Clear line 1 (0) of the LCD
		clearLCDLine(1);											// Clear line 2 (1) of the LCD

		displayLCDString(0, 0, "Claw:");
		sprintf(clawencoder, "%d,%d", nMotorEncoder[LeftClaw], nMotorEncoder[RightClaw] ); //Build the value to be displayed
		displayNextLCDString(clawencoder);

		//Display the encoders
		displayLCDString(1, 0, "Pow:");
		sprintf(clawMotor, "%d, %d", Motor[LeftClaw], Motor[RightClaw]); //Build the value to be displayed
		displayNextLCDString(clawMotor);

		//Short delay for the LCD refresh rate
		wait1Msec(100);
	}
}

task DisplayArmMotors()
{
	bLCDBacklight = true;									// Turn on LCD Backlight
	string armEncoder;
	string armpower;

	while(true)														// An infinite loop to keep the program running until you terminate it
	{
		clearLCDLine(0);											// Clear line 1 (0) of the LCD
		clearLCDLine(1);											// Clear line 2 (1) of the LCD

		//Display the encoders
		displayLCDString(0, 0, "Arm: ");
		//sprintf(armEncoder, "%d", nMotorEncoder[ArmRight]); //Build the value to be displayed
		//displayNextLCDString(armEncoder);

		displayLCDString(1, 0, "Pow:");
		sprintf(armpower, "%d,%d", Motor[TowerLeft13], Motor[TowerRight13] ); //Build the value to be displayed
		displayNextLCDString(armpower);

		//Short delay for the LCD refresh rate
		wait1Msec(100);
	}
}

task BatteryDisplay()
{
	bLCDBacklight = true;									// Turn on LCD Backlight
	string mainBattery, expanderBattery, backupBattery;

	while(true)														// An infinite loop to keep the program running until you terminate it
	{
		clearLCDLine(0);											// Clear line 1 (0) of the LCD
		clearLCDLine(1);											// Clear line 2 (1) of the LCD

		//Display the Primary Robot battery voltage
		displayLCDString(0, 0, "Primary: ");
		sprintf(mainBattery, "%1.2f%c", nImmediateBatteryLevel/1000.0,'V'); //Build the value to be displayed
		displayNextLCDString(mainBattery);

		//Display the power expander battery voltage,
		// assuming power expander status is connected to int 1 (analog 1 port)
		displayLCDString(1, 0, "Expander: ");
		float expanderStatus = (sensorValue[ExpanderStatus] - 210.0)/255.0 ; // just find the no-battery value and divisor manually
		sprintf(expanderBattery, "%1.2f%c", expanderStatus,'V'); //Build the value to be displayed
		displayNextLCDString(expanderBattery);

		//Display the Backup battery voltage
		//displayLCDString(1, 0, "Backup: ");
		//sprintf(backupBattery, "%1.2f%c", BackupBatteryLevel/1000.0, 'V');	//Build the value to be displayed
		//displayNextLCDString(backupBattery);

		//Short delay for the LCD refresh rate
		wait1Msec(100);
	}
}

void waitForPress()
{
	while(nLCDButtons == 0){}
	wait1Msec(5);
}
//----------------------------------------------------------------

//Wait for Release------------------------------------------------
void waitForRelease()
{
	while(nLCDButtons != 0){}
	wait1Msec(5);
}
// check for button press. If left or right button, Stop the task
void waitForLeftOrRightButtonPress()
{
	while(!(nLCDButtons == leftButton || nLCDButtons == rightButton))
	{
		wait1Msec(500);
	}
}

task LcdMenu()
{
	while () {

		//Declare count variable to keep track of our choice
		int count = 0;

		//------------- Beginning of User Interface Code ---------------
		//Clear LCD
		clearLCDLine(0);
		clearLCDLine(1);
		//Loop while center button is not pressed
		while(nLCDButtons != centerButton)
		{
			//Switch case that allows the user to choose from 4 different options
			switch(count){
			case 0:
				//Display first choice
				displayLCDCenteredString(0, "Battery Status");
				displayLCDCenteredString(1, "<		 Enter		>");
				waitForPress();
				//Increment or decrement "count" based on button press
				if(nLCDButtons == leftButton)
				{
					waitForRelease();
					count = 3;
				}
				else if(nLCDButtons == rightButton)
				{
					waitForRelease();
					count++;
				}
				break;
			case 1:
				//Display second choice
				displayLCDCenteredString(0, "Arm potentiometer");
				displayLCDCenteredString(1, "<		 Enter		>");
				waitForPress();
				//Increment or decrement "count" based on button press
				if(nLCDButtons == leftButton)
				{
					waitForRelease();
					count--;
				}
				else if(nLCDButtons == rightButton)
				{
					waitForRelease();
					count++;
				}
				break;
			case 2:
				//Display third choice
				displayLCDCenteredString(0, "Arm Motor Stat");
				displayLCDCenteredString(1, "<		 Enter		>");
				waitForPress();
				//Increment or decrement "count" based on button press
				if(nLCDButtons == leftButton)
				{
					waitForRelease();
					count--;
				}
				else if(nLCDButtons == rightButton)
				{
					waitForRelease();
					count++;
				}
				break;
			case 3:
				//Display fourth choice
				displayLCDCenteredString(0, "Claw Motor Stat");
				displayLCDCenteredString(1, "<		 Enter		>");
				waitForPress();
				//Increment or decrement "count" based on button press
				if(nLCDButtons == leftButton)
				{
					waitForRelease();
					count--;
				}
				else if(nLCDButtons == rightButton)
				{
					waitForRelease();
					count = 0;
				}
				break;
			default:
				count = 0;
				break;
			}
		}
		//------------- End of User Interface Code ---------------------

		//------------- Beginning of Robot Movement Code ---------------
		//Clear LCD
		clearLCDLine(0);
		clearLCDLine(1);
		//Switch Case that actually runs the user choice
		switch(count){
		case 0:
			//If count = 0, run the code correspoinding with choice 1
			// start battery status task
			startTask(BatteryDisplay);
			waitForLeftOrRightButtonPress()
			StopTask(BatteryDisplay);
			wait1Msec(50);						// Robot waits for 2000 milliseconds
			break;
		case 1:
			//If count = 1, run the code correspoinding with choice 2
			// start battery status task
			startTask(DisplayArmPot);
			waitForLeftOrRightButtonPress()
			StopTask(DisplayArmPot);
			wait1Msec(50);						// Robot waits for 2000 milliseconds
			break;
		case 2:
			//If count = 2, run the code correspoinding with choice 3
			startTask(DisplayArmMotors);
			waitForLeftOrRightButtonPress()
			StopTask(DisplayArmMotors);
			wait1Msec(50);						// Robot waits for 2000 milliseconds
			break;
		case 3:
			//If count = 3, run the code correspoinding with choice 4
			startTask(DisplayClawMotors);
			waitForLeftOrRightButtonPress()
			StopTask(DisplayClawMotors);
			wait1Msec(50);						// Robot waits for 2000 milliseconds
			break;
		default:
			displayLCDCenteredString(0, "No valid choice");
			displayLCDCenteredString(1, "was made!");
			break;
		}
		//------------- End of Robot Movement Code -----------------------
	}
}

task clawControl()
{
	int PIDTargetValue = (nMotorEncoder[LeftClaw] + nMotorEncoder[RightClaw])/2;
	//PID constants. Do research if you don't know what these are
	float kp = 0.5; //0.5;
	float ki = 0.01;
	float kd = 0.00001;
	int error;
	int integral = 0;
	int derivative;
	int lastError;
	int PIDDrive;
	while(true)
	{
		if(vexRT[Btn5D] == 1)
		{
			//open claw
			motor[RightClaw] = 127;
			motor[LeftClaw] = 127;
			PIDTargetValue = (nMotorEncoder[LeftClaw] + nMotorEncoder[RightClaw])/2;
		}
		else if(vexRT[Btn5U] == 1)
		{
			//close claw
			motor[RightClaw] = -127;
			motor[LeftClaw] = -127;
			PIDTargetValue = (nMotorEncoder[LeftClaw] + nMotorEncoder[RightClaw])/2;
		}
		else
		{
			//PID to hold
			error = PIDTargetValue - (nMotorEncoder[LeftClaw] + nMotorEncoder[RightClaw])/2;

		  //error = PIDTargetValue - (SensorValue[LeftClawPot] + SensorValue[RightClawPot])/2;
			integral += error;
			derivative = error - lastError;
			PIDDrive = kp*error + ki*integral + kd*derivative;
			motor[RightClaw] = PIDDrive;
			motor[LeftClaw] = PIDDrive;
			lastError = error;
		}
		wait1msec(15);//don't hog cpu
	}
}

task Drive()
{
  while(1 == 1)
  {
    //Right side of the robot is controlled by the right joystick, Y-axis
    motor[RF] = vexRT[Ch2];
    motor[RB]  = vexRT[Ch2];
    //Left side of the robot is controlled by the left joystick, Y-axis
    motor[LF] = vexRT[Ch3];
    motor[LB]  = vexRT[Ch3];
  }
}

task usercontrol()
{
	startTask(LcdMenu);
	startTask(Drive);
	startTask(ClawControl);

	//startTask(LcdMenu);
		//if (vexRT[Btn7U] == 1 && clawTaskStarted == false)
		//while (vexRT[Btn7U] == 0){ wait1Msec(10);}
			//startTask(ClawControl, 49);
			//clawTaskStarted = true;

  // User control code here, inside the loop
  while (true)
  {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    // Remove this function call once you have "real" code.
    if (VexRT[Btn6U] == 1 && vexRT[Btn6D] == 0)
    {
    	motor[TowerLeft13] = 127;
    	motor[TowerRight13] = 127;
    	motor[TowerLeft2] = 127;
    	motor[TowerRight2] = 127;
    }
    else if (VexRT[Btn6D] == 1 && vexRT[Btn6U] == 0)
    {
    	motor[TowerLeft13] = -127;
    	motor[TowerRight13] = -127;
    	motor[TowerLeft2] = -127;
    	motor[TowerRight2] = -127;
    }
    else
    {
    	motor[TowerLeft13] = 0;
    	motor[TowerRight13] = 0;
    	motor[TowerLeft2] = 0;
    	motor[TowerRight2] = 0;
    }
  }
}
