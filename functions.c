//Claw position constants
#define CLOSED 1 
#define OPEN 0
//Drive error source modes
#define ENCODERMODE 1 
#define GYROMODE 2
#define LINEMODE 3

//TrueSpeed array - remap joystick values to linear acceleration
const int tsArray[128] = {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 22, 23, 24, 24,
		25, 25, 25, 25, 26, 27, 27, 28, 28, 28,
		28, 29, 30, 30, 30, 31, 31, 32, 32, 32,
		33, 33, 34, 34, 35, 35, 35, 36, 36, 37,
		37, 37, 37, 38, 38, 39, 39, 39, 40, 40,
		41, 41, 42, 42, 43, 44, 44, 45, 45, 46,
		46, 47, 47, 48, 48, 49, 50, 50, 51, 52,
		52, 53, 54, 55, 56, 57, 57, 58, 59, 60,
		61, 62, 63, 64, 65, 66, 67, 67, 68, 70,
		71, 72, 72, 73, 74, 76, 77, 78, 79, 79,
		80, 81, 83, 84, 84, 86, 86, 87, 87, 88,
		88, 89, 89, 90, 90, 90, 90, 90
};

//Set claw target to the current value when starting
int lClawTarget = SensorValue[LeftClawPot]; 
int rClawTarget = SensorValue[RightClawPot];
int liftTarget = (SensorValue[LeftMiddleLiftEnc] + SensorValue[RightMiddleLiftEnc])/2; //Set lift target to current sensor value
//Set drive target to current sensor value
int lDrivePTarget = SensorValue[LeftBackDriveEnc]; 
int rDrivePTarget = SensorValue[RightBackDriveEnc]; 
int driveAnglePTarget = SensorValue[gyro]; //Set gyro target to current value

//Power to drive backwards when lining up on tape
int lLineErr = 65; 
int rLineErr = 65; 
int driveFeedbackSource = ENCODERMODE; //Start out with encoders as error source for drive

//Don't do position holding during driver mode
bool doClawHold = false;
bool doLiftHold = false;
bool doDriverDrive = true; //Let drivers control drive
bool doDriveP = false;

//Clip values to specified number - used to set max motor power
int clipValue( int value, int max = 127 )
{

	if( value > max ) value = max;
	else if( value < -max ) value = -max;

	return value;

}

//Apply TrueSpeed array to an input
int trueSpeed( int iInput )
{

	return sgn(iInput)*tsArray[abs(clipValue(iInput))];

}

bool completed = false; //Variable to check whether something is completed

//Wait until completed variable gets set to true
bool waitUntilComplete()
{

	while( !completed )
	{

		wait10Msec(10);

	}

	return true;

}

//Function for drive to set claw motor values
void claw( int pwr )
{

	motor[LeftClaw] = pwr;
	motor[RightClaw] = pwr;

}

//Driver control
void drive( int lpwr, int rpwr = lpwr )
{

	//Cap values at 90 - above this motor power increase is negligible
	clipValue(lpwr, 90); 
	clipValue(rpwr, 90); 

	if( abs(lpwr) > 15 ) //Set deadband - if outside of range
	{

		motor[LeftBottomDrive] = lpwr;
		motor[LeftTopDrive] = lpwr;

	}
	if( abs(rpwr) > 15 )
	{

		motor[RightBottomDrive] = rpwr;
		motor[RightTopDrive] = rpwr;

	}
	else //Otherwise, set power to 0
	{

		motor[RightBottomDrive] = 0;
		motor[RightTopDrive] = 0;
		motor[LeftBottomDrive] = 0;
		motor[LeftTopDrive] = 0;

	}

}

//Proportional control task for drive
task drivePControl()
{

	int lErr; //Init variables for error
	int rErr;

	while( true ) //Run forever
	{

		while( doDriveP ) //Whenever this variable is true (task turned on)
		{

			completed = false; //Start incomplete

			switch( driveFeedbackSource ) //Check which source of error is given
			{

				case ENCODERMODE: //Use encoder values as error

					lErr = (lDrivePTarget - SensorValue[LeftBackDriveEnc])/4;
					rErr = (rDrivePTarget + SensorValue[RightBackDriveEnc])/4;

				break;

				case GYROMODE: //Use gyro as error source

					lErr = (-driveAnglePTarget + SensorValue[gyro])/2;
					rErr = -lErr;

				break;

				case LINEMODE: //Use line sensors as error

					lErr = lLineErr;
					rErr = rLineErr;

				break;

				default: //If anything else, do nothing



				break;

			}

			if( driveFeedbackSource == 2 && driveAnglePTarget < 0 ) //If using gyro and going to a negative angle, turn the other way
			{

				motor[LeftBottomDrive] = motor[LeftTopDrive] = trueSpeed(lErr);
				motor[RightBottomDrive] = motor[RightTopDrive] = trueSpeed(rErr);

			}
			else //Otherwise, use normal values
			{
				//Set drive power to the error
				motor[LeftBottomDrive] = motor[LeftTopDrive] = trueSpeed(lErr); 
				motor[RightBottomDrive] = motor[RightTopDrive] = trueSpeed(rErr); 
			}

			if( abs( lErr ) < 20 && abs( rErr ) < 20 ) //If within 20 (less than the motors can move) of target, set as completed
				completed = true;

			wait1Msec( 15 ); //Allow other tasks to run in the background

		}

		wait1Msec( 5 ); //Allow other tasks to run

	}

}
//Set current target (absolute movement) (no inputs gives reset to current sensor values)
void setDriveTarget( int lTarget = SensorValue[LeftBackDriveEnc], int rTarget = ( lTarget == SensorValue[LeftBackDriveEnc] ) ? -SensorValue[RightBackDriveEnc] : lTarget )
{

	lDrivePTarget = lTarget; //Set drive to given target
	rDrivePTarget = rTarget;

	driveFeedbackSource = ENCODERMODE; //Make sure that we are using encoders

}

void moveDriveTarget( int lTarget, int rTarget = lTarget ) //add or subtract from the current target (relative movement)
{

	lDrivePTarget += lTarget;
	rDrivePTarget += rTarget;

}

void setGyroTarget( int angleTarget ) //make turns by setting the drive targets toward a gyro angle (absolute movement)
{

	setDriveTarget(); //Set targets to current encoder values

	driveFeedbackSource = GYROMODE; //Use gyro as feedback source for turns

	driveAnglePTarget = angleTarget;

}

void moveGyroTarget( int angleTarget ) //make turns by moving the drive targets toward a gyro angle (relative movement)
{

	setDriveTarget(); //Set targets to current encoder values

	driveFeedbackSource = GYROMODE; //Use gyro as feedback source for turns

	driveAnglePTarget += angleTarget;

	setDriveTarget(); //Set targets to current encoder values

}

void autonLift( int pwr ) //Separate function for lifting in auton without extra buttons
{

	motor[LeftBottomLift] = pwr;
	motor[RightBottomLift] = pwr;
	motor[MiddleLift] = pwr;
	motor[TopLift] = pwr;

}

//Normal drive lift mode
void lift( int pwr )
{

	if(vexRT[Btn7UXmtr2]) //When pressing 7U
	{

		doDriverDrive = false; //Have program control drive
		clearTimer(T1);
		while(time1[T1] < 750) //For .75 seconds
		{

			drive(127, 127); //Drive full speed - to tilt back

		}
		drive(0);
		pwr = -127; //Lift down to hang

	}

	doDriverDrive = true; //Resume driver drive control

	if( vexRT[Btn8RXmtr2] ) //If 8R Pressed
	{

		doLiftHold = true; //Proportional control of lift
		doClawHold = true; //Proportional control of claw

			liftTarget = 1000; //High position - for knocking stars off left + right of fence
			lClawTarget = 200;
			rClawTarget = 960;

	}
	else if( vexRT[Btn8LXmtr2] ) //Button 8L
	{

		doLiftHold = true;
		doClawHold = true;

			liftTarget = 800; //Low position - for knocking stars off middle of fence
			lClawTarget = 610;
			rClawTarget = 1300;
	}
	else
	{

		if( !vexRT[Btn8UXmtr2] && !vexRT[Btn8DXmtr2] ) //If these aren't pressed, resume drive control
		{
			doLiftHold = false;
			doClawHold = false;

		}

	}

	motor[LeftBottomLift] = pwr; //Set lift to requested power
	motor[RightBottomLift] = pwr;
	motor[MiddleLift] = pwr;
	motor[TopLift] = pwr;

}

//Function to set drive motor power when drivers are in control
void driverDrive( int lpwr, int rpwr )
{

	if( doDriverDrive ) //Check if drivers are in control
	{

			motor[RightBottomDrive] = rpwr;
			motor[RightTopDrive] = rpwr;
			motor[LeftBottomDrive] = lpwr;
			motor[LeftTopDrive] = lpwr;

	}

}

//Porportional control of claw
task clawHold()
{

	int lClawErr; //Init error
	int rClawErr;

	while( true ) //Always run
	{

		while( doClawHold ) //Check if in control
		{

			lClawErr = (lClawTarget - SensorValue[LeftClawPot])/3; //Error = how far away from target
			rClawErr = (rClawTarget - SensorValue[RightClawPot])/3;

			//Set motor to error value
			motor[LeftClaw] = -clipValue( lClawErr ); 
			motor[RightClaw] = -clipValue( rClawErr ); 

			wait1Msec( 15 ); //Allow other tasks to run

		}

		wait1Msec( 5 ); //Allow other tasks to run

	}

}

//Proportional control of lift
task liftHold()
{

	int err; //Init error

	while( true ) //Run always
	{

		while( doLiftHold ) //Check if in control
		{

			err = (liftTarget - ( -SensorValue[LeftMiddleLiftEnc] + SensorValue[RightMiddleLiftEnc] ) / 2 ); //error = how far away from target

			autonLift( clipValue( err ) ); //Set motors to error

			wait1Msec( 15 ); //Allow other tasks to run

		}

		wait1Msec( 5 ); //Allow other tasks to run

	}

}

//Driver control function for claw
void driverClaw( int lpwr, int rpwr = lpwr )
{

	if( SensorValue[LeftClawPot] < 1550 || vexRT[Btn6UXmtr2] ) //Stop claw from going past closed position
	{

		motor[ LeftClaw ] = lpwr; //Set to power

	}
	else
	{

		motor[ LeftClaw ] = 10; //Otherwise, give power to keep in place

	}
	if( SensorValue[RightClawPot] < 2600 || vexRT[Btn6UXmtr2] ) //Stop claw from going past closed position
	{

		motor[ RightClaw ] = rpwr; //Set to power

	}
	else
	{

		motor[ RightClaw ] = 10; //Give power to keep in place

	}

	if( vexRT[Btn8UXmtr2] ) //Claw home button - sets to sensor values in case claw becomes misaligned
 	{

 		doClawHold = true; //Allow program to control claw

  	lClawTarget = 1500; //Set to position
  	rClawTarget = 2450;

  }
  else //When not, make sure driver has control
  {

  	doClawHold = false;

  }

  if( vexRT[Btn8DXmtr2] ) //Top secret position - watch when hanging to find out
  {

  	doClawHold = true;

  	lClawTarget = 2500;
  	rClawTarget = 1500;

  }

}

//Give different claw position options from keywords
void clawPos( int pos )
{

	switch( pos )
	{

		case 0: //Claw open

			lClawTarget = 350;
			rClawTarget = 1050;

		break;

		case 1: //Claw closed

			lClawTarget = 1400;
			rClawTarget = 2450;

		break;

		default:



		break;

	}

}

//Reset gyro by lining up to white tape on field - input sensor threshold and what angle to set to
void lineUp( int threshold = 2000, int resetTo = 0 )
{

	driveFeedbackSource = LINEMODE; //Set error to line sensors (starts driving backwards from preset values at top of program)

	while( lLineErr > -19 || rLineErr > -19 ) //While driving forwards
	{

		if( SensorValue[ LeftLine ] < threshold ) //If line detected
		{

			lLineErr = -20; //Slowly drive backwards

		}
		if( SensorValue[ RightLine ] < threshold ) //If line detected (other side)
		{

			rLineErr = -20; //Slowly drive backwards

		}

		wait1Msec( 5 ); //Allow other tasks to run

	}

	wait1Msec( 300 ); //Give time to settle

	while( lLineErr < 0 || rLineErr < 0 ) //While either side going backwards
	{

		if( SensorValue[ LeftLine ] < threshold ) //If line detected
		{

			lLineErr = 0; //Stop side

		}
		if( SensorValue[ RightLine ] < threshold ) //If line detected
		{

			rLineErr = 0; //Stop side

		}

		wait1Msec( 5 ); //Allow other tasks to run

	}

	wait1Msec( 300 ); //Allow to settle

	//Make sure stopped
	rLineErr = 0; 
	lLineErr = 0; 

	wait1Msec(500);

	SensorValue[ gyro ] = resetTo; //Reset gyro values to specified input

	driveFeedbackSource = GYROMODE; //Go back to using the gyro as source of error

}
