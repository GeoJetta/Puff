void lFull(  ) //Left Side Full Auton Routine - also used as part of skills run
{

	//setDriveTarget();

	liftTarget = 750; //Lift to hit stars on fence
	clawPos( OPEN ); //Make sure claw folds out
	clawPos( OPEN ); //^^

	wait1Msec(200);

	moveDriveTarget( 1750 ); //Drive to fence
	waitUntilComplete(); //Wait until at fence

	wait1Msec( 200 ); //Allow to roll to a stop

	liftTarget = 1000; //Lift up to make it over fence when driving back

	wait1Msec( 2000 );

	moveDriveTarget( -900 ); //Drive backwards
	waitUntilComplete();

	wait1Msec( 750 );

	liftTarget = 0; //Lift down

	wait1Msec( 1000 );

	clawPos( CLOSED ); //CLose the claw so no objects are stuck in claw

	setGyroTarget( -950/*skillsDir*/ ); //Turn towards cube - negative for skills run
	wait1Msec( 200 );
	waitUntilComplete();

	wait1Msec( 200 );

	setDriveTarget(); //Set proportional drive target to current sensor values to reset position

	lClawTarget = 1050; //Open claw half way
	rClawTarget = 1950; //^^

	wait1Msec( 200 );

	moveDriveTarget( 1000 ); //Drive up to cube
	waitUntilComplete();
	drive(127); //Drive into cube at full speed

	wait1Msec( 500 );

	drive(0);

	wait1Msec( 800 );

	clawPos( CLOSED ); //Grab cube

	liftTarget = 150; //Lift a small amount

	wait1Msec( 200 );

	setGyroTarget( -1800 ); //Turn to back into fence
	wait1Msec( 200 );
	waitUntilComplete();

	wait1Msec( 200 );

	setDriveTarget();

	wait1Msec( 200 );

	moveDriveTarget( -1300 ); //Back up into fence
	liftTarget = 1200; //Lift all the way
	waitUntilComplete();
	wait1Msec( 1000 );

	clawPos( OPEN ); //Open claw to release cube
	wait1Msec( 600 );

	moveDriveTarget( 1500 ); //Drive to get stars
	liftTarget = 0; //Lift down to ground to get stars
	waitUntilComplete();

	lClawTarget = 1600; //Close claw further than normal to grab stars
	rClawTarget = 2650;
	wait1Msec( 500 );
	liftTarget = 400; //Lift up a small amount
	wait1Msec( 200 );

	moveDriveTarget( -1500 ); //Back up to fence
	waitUntilComplete();

	wait1Msec( 1000 );
	liftTarget = 1200; //Dump
	wait1Msec( 1000 );
	clawPos( OPEN ); //Release stars
	wait1Msec( 600 );

	wait1Msec( 5000 );

}

void rFull() //Right Side Full Auton routine - same as left with turns reversed
{

	liftTarget = 900;
	clawPos( OPEN );
	clawPos( OPEN );

	moveDriveTarget( 1750 );
	waitUntilComplete();

	wait1Msec( 200 );

	liftTarget = 1000;

	wait1Msec( 500 );

	moveDriveTarget( -900 );
	//wait1Msec( 200 );
	waitUntilComplete();

	wait1Msec( 750 );

	liftTarget = 0;

	wait1Msec( 200 );

	setGyroTarget( 1000 );
	wait1Msec( 200 );
	waitUntilComplete();

	wait1Msec( 200 );

	setDriveTarget();

	moveDriveTarget( 1000 );
	waitUntilComplete();
	drive(127);

	wait1Msec( 500 );

	drive(0);
	clawPos( CLOSED );

	wait1Msec( 800 );

	liftTarget = 150;

	wait1Msec( 200 );

	setGyroTarget( 1800 );
	wait1Msec( 200 );
	waitUntilComplete();

	wait1Msec( 200 );

	setDriveTarget();

	wait1Msec( 200 );

	moveDriveTarget( -1300 );
	liftTarget = 1200;
	waitUntilComplete();
	wait1Msec( 1000 );

	clawPos( OPEN );
	wait1Msec( 600 );

	moveDriveTarget( 1500 );
	liftTarget = 0;
	waitUntilComplete();

	lClawTarget = 1600;
	rClawTarget = 2650;
	wait1Msec( 500 );
	liftTarget = 400;
	wait1Msec( 200 );

	moveDriveTarget( -1500 );
	waitUntilComplete();

	wait1Msec( 1000 );
	liftTarget = 1200;
	wait1Msec( 1000 );
	clawPos( OPEN );
	wait1Msec( 600 );

}

void lCube() //Left Side Auton - Grabs only cube
{

	liftTarget = 200; //Raise to unlock claw
	clawPos( OPEN ); //Make sure claw is deployed
	clawPos( OPEN );

	wait1Msec( 200 );

	moveDriveTarget( 850 ); //Drive foward until parallel with cube
	wait1Msec( 750 );
	liftTarget = 0; //Put lift down
	waitUntilComplete();

	wait1Msec( 200 );

	setGyroTarget( -900 ); //Turn 90 degrees to cube
	wait1Msec( 200 );
	waitUntilComplete();

	wait1Msec( 200 );

	setDriveTarget();

	moveDriveTarget( 800 ); //Move to cube
	waitUntilComplete();

	wait1Msec( 200 );

	lClawTarget = 1800; //Close claw more than usual to get firm grab
	rClawTarget = 2850;

	wait1Msec( 400 );

	liftTarget = 200; //Lift up a little

	wait1Msec( 200 );

	moveDriveTarget( -1000 ); //Back up to right side of field
	waitUntilComplete();

	wait1Msec( 1500 );

	setGyroTarget( -1800 ); //Turn to fence
	wait1Msec( 200 );
	waitUntilComplete();

	wait1Msec( 200 );

	setDriveTarget();

	moveDriveTarget( -600 ); //Back up to fence
	waitUntilComplete();
	liftTarget = 1200; //Dump
	wait1Msec( 1000 );
	clawPos( OPEN ); //Release Cube
	wait1Msec( 400 );

	wait1Msec( 5000 ); //Wait for end of autonomous period

}

void rCube() //Right Side Cube Auton - Same as left with reversed turns
{

	liftTarget = 200;
	clawPos( OPEN );
	clawPos( OPEN );

	wait1Msec( 200 );

	moveDriveTarget( 850 );
	wait1Msec( 750 );
	liftTarget = 0;
	waitUntilComplete();

	wait1Msec( 200 );

	setGyroTarget( 900 );
	wait1Msec( 200 );
	waitUntilComplete();

	wait1Msec( 200 );

	setDriveTarget();

	moveDriveTarget( 800 );
	waitUntilComplete();

	wait1Msec( 200 );

	lClawTarget = 1800;
	rClawTarget = 2850;

	wait1Msec( 400 );

	liftTarget = 200;

	wait1Msec( 200 );

	moveDriveTarget( -1000 );
	waitUntilComplete();

	wait1Msec( 1500 );

	setGyroTarget( 1800 );
	wait1Msec( 200 );
	waitUntilComplete();

	wait1Msec( 200 );

	setDriveTarget();

	moveDriveTarget( -600 );
	waitUntilComplete();
	liftTarget = 1200;
	wait1Msec( 1000 );
	clawPos( OPEN );
	wait1Msec( 400 );

	wait1Msec( 5000 );

}

void skills() //Programming skills routine - start robot backwards
{

	lClawTarget = 1050; //Open claw half way to get driver loads
	rClawTarget = 1950;
	liftTarget = 300; //Lift to deploy claw

	moveDriveTarget( -500 ); //Drive backwards to deploy intake
	waitUntilComplete();
	liftTarget = 0; //Lift down

	wait1Msec( 200 );

	moveDriveTarget( 230 ); //Forward to pick up loads
	waitUntilComplete();

	wait1Msec( 500 );

	clawPos( CLOSED ); //Grab objects

	wait1Msec( 800 );

	moveDriveTarget( -1250 ); //Back up to fence
	liftTarget = 1200; //Dump
	waitUntilComplete();
	wait1Msec( 1800 );
	clawPos( OPEN ); //Release objects
	wait1Msec( 1000 );
	lClawTarget = 1050; //Close claw halfway
	rClawTarget = 1950;

	moveDriveTarget( 1250 ); //Go foward to get next load
	liftTarget = 0; //Lift down
	waitUntilComplete();

	wait1Msec( 2000 );

	clawPos( CLOSED ); //Grab objects

	wait1Msec( 800 );

	moveDriveTarget( -1250 ); //Go back to fence
	liftTarget = 1200; //Dump
	waitUntilComplete();
	wait1Msec( 1800 );
	clawPos( OPEN ); //Release
	wait1Msec( 1000 );

	lClawTarget = 1050; //Open claw half way
	rClawTarget = 1950; //^^

	wait1Msec( 200 );

	moveDriveTarget( 400 ); //Forward a small margin
	liftTarget = 0; //Lift down
	waitUntilComplete();

	wait1Msec( 2000 );

	lineUp( 2000, 1800 ); //Resets gyro drift based on line sensors

	//Start Full Auton

	setGyroTarget( 950 ); //Turn towards cube - positive for skills run
	wait1Msec( 200 );
	waitUntilComplete();

	wait1Msec( 200 );

	setDriveTarget(); //Set proportional drive target to current sensor values to reset position

	wait1Msec( 200 );

	moveDriveTarget( 1000 ); //Drive up to cube
	waitUntilComplete();
	drive(127); //Drive into cube at full speed

	wait1Msec( 500 );

	drive(0);

	wait1Msec( 800 );

	clawPos( CLOSED ); //Grab cube

	liftTarget = 150; //Lift a small amount

	wait1Msec( 200 );

	setGyroTarget( 0 ); //Turn to back into fence
	wait1Msec( 200 );
	waitUntilComplete();

	wait1Msec( 200 );

	setDriveTarget();

	wait1Msec( 200 );

	moveDriveTarget( -1300 ); //Back up into fence
	liftTarget = 1200; //Lift all the way
	waitUntilComplete();
	wait1Msec( 1000 );

	clawPos( OPEN ); //Open claw to release cube
	wait1Msec( 600 );

	setGyroTarget( 0 ); //Turn to back into fence
	wait1Msec( 200 );
	waitUntilComplete();

	wait1Msec( 200 );

	setDriveTarget();

	wait1Msec( 200 );

	moveDriveTarget( 1450 ); //Drive to get stars
	liftTarget = 0; //Lift down to ground to get stars
	waitUntilComplete();

	wait1Msec( 5000 );

	lClawTarget = 1600; //Close claw further than normal to grab stars
	rClawTarget = 2650;
	wait1Msec( 500 );
	liftTarget = 400; //Lift up a small amount
	wait1Msec( 200 );

	moveDriveTarget( -1450 ); //Back up to fence
	waitUntilComplete();

	wait1Msec( 1000 );
	liftTarget = 1200; //Dump
	wait1Msec( 1000 );
	clawPos( OPEN ); //Release stars
	wait1Msec( 600 );

	//End Full Auton

	//At this point, we have dumped the three stars in front - on to picking up last three stars and attmepting to hang
	liftTarget = 0; //Lift down
	moveDriveTarget( 400 ); //Move forward
	waitUntilComplete();

	setGyroTarget( 1800 ); //Face stars
	wait1Msec( 200 );
	waitUntilComplete();

	wait1Msec( 200 );

	setDriveTarget();

	moveDriveTarget( 400 ); //Move to stars
	waitUntilComplete();

	wait1Msec( 1000 );
	lClawTarget = 1600; //Close claw further than normal to grab stars
	rClawTarget = 2650;

	moveDriveTarget( -400 ); //Back up
	waitUntilComplete();

	wait1Msec( 200 );
	liftTarget = 200; //Raise to the bottom of the fence
	wait1Msec( 800 );
	liftTarget = 400; //Raise stars above ground

	setGyroTarget( -1800 ); //Turn to dump
	wait1Msec( 200 );
	waitUntilComplete();

	wait1Msec( 200 );

	setDriveTarget();

	moveDriveTarget( -400 ); //Drive Back to fence
	liftTarget = 1200; //Dump
	waitUntilComplete();

	wait1Msec( 1000 );
	clawPos( OPEN ); //Release
	wait1Msec( 600 );
	liftTarget = 0;

	setGyroTarget( -1200 ); //Turn to cube on square
	wait1Msec( 200 );
	waitUntilComplete();

	wait1Msec( 200 );

	setDriveTarget();

	moveDriveTarget( 1200 ); //Drive to cube
	waitUntilComplete();

	wait1Msec( 1500 );
	lClawTarget = 1050; //Close on cube - grab firm
	rClawTarget = 2250;

	setGyroTarget( -1800 ); //Turn to dump
	wait1Msec( 200 );
	waitUntilComplete();

	wait1Msec( 200 );

	setDriveTarget();

	wait1Msec( 200 );

	moveDriveTarget( -1300 ); //Back up to fence
	liftTarget = 1200; //Dump
	waitUntilComplete();
	wait1Msec( 1000 );

	clawPos( OPEN ); //Release
	wait1Msec( 600 );

	lineUp( ); //Reset gyro by lining up with field tape

	setGyroTarget( 910 ); //Turn towards side of field
	wait1Msec( 200 );
	waitUntilComplete();

	wait1Msec( 200 );

	setDriveTarget();

	wait1Msec( 200 );

	while( SensorValue[ Ultra ] > 5 || SensorValue[ Ultra ] < 0 ) //Back up to side of field to reset position - drive until 5 inches away
	{

		lDrivePTarget = -10000;
		rDrivePTarget = -10000;

	}

	setDriveTarget();

	lDrivePTarget += -300; //Back up slowly into wall
	rDrivePTarget += -300;

	wait1Msec( 200 );

	moveDriveTarget( 1000 ); //Drive forward to line up to hang
	waitUntilComplete();

	wait1Msec( 200 );

	setGyroTarget( 1330 ); //Turn towards hang pole
	wait1Msec( 200 );
	waitUntilComplete();
	liftTarget = 1200;

	wait1Msec( 200 );

	setDriveTarget();

	wait1Msec( 200 );

	liftTarget = 1200; //Start lifting to hang position

	moveDriveTarget( -1200 ); //Drive into hang pull
	waitUntilComplete();

	wait1Msec(1500);

	liftTarget = -50; //Hang!

}

void justStars()
{

	liftTarget = 750; //Lift to hit stars on fence
	clawPos( OPEN ); //Make sure claw folds out
	clawPos( OPEN ); //^^

	wait1Msec(200);

	moveDriveTarget( 1750 ); //Drive to fence
	waitUntilComplete(); //Wait until at fence

	wait1Msec( 200 ); //Allow to roll to a stop

	liftTarget = 1000; //Lift up to make it over fence when driving back

	wait1Msec( 2000 );

	moveDriveTarget( -900 ); //Drive backwards
	waitUntilComplete();

	wait1Msec( 750 );

	liftTarget = 0; //Lift down

	wait1Msec( 1000 );

	clawPos( CLOSED ); //CLose the claw so no objects are stuck in claw

}
