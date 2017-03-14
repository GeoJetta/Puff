// DECLARE VARIABLES ETC

const short leftButton = 1;
const short centerButton = 2;
const short rightButton = 4;

//LCD FUNCTIONS

string mainBattery, backupBattery; //Strings to hold battery values

void LCDInit ()
{

	bLCDBacklight = true;

}

void LCDClear ()
{

	clearLCDLine( 0 );                                            // Clear line 1 (0) of the LCD
	clearLCDLine( 1 );                                            // Clear line 2 (1) of the LCD

}

void waitForPress ()
{

	while(nLCDButtons == 0){}
	wait1Msec(5);

}

void waitForRelease ()
{

	while(nLCDButtons != 0){}
	wait1Msec(5);

}

int choice = 0;

void chooseAuton ()
{

	//Declare count variable to keep track of our choice
	int count = 0;

	//------------- Beginning of User Interface Code ---------------

	//Clear LCD
	LCDClear();

	clearTimer(T1);

	//Loop while center button is not pressed
	while(nLCDButtons != centerButton && bIfiRobotDisabled/*&& !(time1[T1] > 5000)*/)
	{

		//Switch case that allows the user to choose from 4 different options
		switch( count )
		{

			case 0:

				//Display first choice
				displayLCDString( 0, 0, "Left Full Auton " );
				displayLCDString( 1, 0, "<    Enter    > " );
				waitForPress();

				//Increment or decrement "count" based on button press
				if(nLCDButtons == leftButton)
				{

					waitForRelease();
					count = 5;

				}

				else if(nLCDButtons == rightButton)
				{

					waitForRelease();
					count++;

				}

			break;

			case 1:

				//Display second choice
				displayLCDString( 0, 0, "Right Full Auton" );
				displayLCDString( 1, 0, "<    Enter     >" );
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

				//Display second choice
				displayLCDString( 0, 0, "Left Cube Auton " );
				displayLCDString( 1, 0, "<    Enter    > " );
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

				//Display second choice
				displayLCDString( 0, 0, "Right Cube Auton" );
				displayLCDString( 1, 0, "<    Enter     >" );
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

			case 4:

				//Display second choice
				displayLCDString( 0, 0, "   Just Stars   " );
				displayLCDString( 1, 0, "<    Enter     >" );
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

			case 5:

				//Display third choice
				displayLCDString( 0, 0, "     Skills     " );
				displayLCDString( 1, 0, "<    Enter     >" );
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

		wait1Msec(20);

	}

	//return count;

	choice = count;

}

//Run chosen auton
void runLCDAuton ()
{

	switch( choice )
	{

		case 0:

			lFull();

		break;

		case 1:

			rFull();

		break;

		case 2:

			lCube();

		break;

		case 3:

			rCube();

		break;

		case 4:

			justStars();

		break;

		case 5:

			skills();

		break;

	}

}


void primaryBatteryDisplay ( int line = 0 )
{

	//Display the Primary Robot battery voltage
	displayLCDString( line, 0, "Primary: " );
	sprintf( mainBattery, "%1.2f%c", nImmediateBatteryLevel / 1000.0,'V' ); //Build the value to be displayed
	displayNextLCDString( mainBattery );

}

void backupBatteryDisplay ( int line = 1 )
{

	//Display the Backup battery voltage
	displayLCDString( line, 0, "Backup: " );
	sprintf( backupBattery, "%1.2f%c", BackupBatteryLevel / 1000.0, 'V' );    //Build the value to be displayed
	displayNextLCDString( backupBattery );

}
