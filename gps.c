int x_pos;
int y_pos;
int lastSense[2];

void gpsCalc( int lDist, int rDist = lDist, int ang )
{

	lDist -= lastSense[0];
	rDist -= lastSense[1];

	x_pos += (lDist+rDist)/2*cosDegrees(ang);
	y_pos += (lDist+rDist)/2*sinDegrees(ang);

	lastSense[0] += lDist;
	lastSense[1] += rDist;

}

string x_display;
string y_display;

void gpsDisplay (  )
{

	sprintf( x_display, "X: %1.2f%c", x_pos );    //Build the value to be displayed
	sprintf( y_display, "Y: %1.2f%c", y_pos );    //Build the value to be displayed
	//Display the Backup battery voltage
	displayLCDString( 0, 0, x_display );
	displayLCDString( 1, 0, y_display );

}

task gps()
{

	while( true )
	{

		gpsCalc( SensorValue[lEnc], SensorValue[rEnc], SensorValue[gyro] );

		wait1Msec( 10 );

	}

}

task gpsDisplayLoop()
{

	while( true )
	{

		gpsDisplay();

		wait1Msec( 500 );

	}

}
