// ****************************************
// Program Title: Project 4
// Project File: Project_04.cpp
// Name: Anthony Dragotta
// Course Section: CPE-211-01
// Lab Section: 1
// Due Date: 6/14/18
// program description:
/*
    Using the equations	and information	provided below, this program will compute the following values for projectile motion:
    the time to reach maximum height, the time for the projectile to hit the ground, the maximum height achieved and the horizontal distance traveled.

    The program is to read the initial velocity (in meters/second and the starting angle (in degrees) of the projectile	from a user specified input file.
    The program is to prompt the user for the name of the input file, echo print the filename and then open the input file.

    Echo print means to print out the value just read (see the hints section on page 4 for more information).

    Echo printing will show the values used when running the scripts or redirected input. Immediately after opening the input file, place the code
            shown on page 3 in your program.
*/
// ****************************************
#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <string>
#include <cmath>
using namespace std;

int main()
{
    ifstream inFile;
    ofstream outFile;
    string fileName;
    const double gravity = 9.80665;	// m/s^2
    const double PI = 3.14159265;
    double initVelocity = 0.0;		// m/s
    //max height of the projectile
    double maxHeight = 0.0;
    //distance traveled by projectile
    double distTraveled = 0.0;
    //starting angle of projectile in degrees
    double startAngle = 0.0;
    //time to reach maximum height in seconds
    double timeMaxHeight = 0.0;
    //time for projectile to hit the ground in seconds
    double timeHitGround = 0.0;
    cout << endl;
    cout << string(30,'*') << endl;
    cout << string(5,'*') << " " << "Projectile Motion" << endl;
    cout << string(30,'*') << endl << endl;
    cout << "Enter the name of the input file: ";
    cin >> fileName;
    cout << fileName << endl << endl;
    inFile.open(fileName.c_str());
    if(inFile.fail())
    {
            cout << string(47,'*') << endl;
            cout << "==> Input file failed to open properly!\n";
            cout << "==> Name of file opened: " << fileName << endl;
            cout << "==> Terminating program!!!\n";
            cout << string(47, '*') << endl;
            return 1;
    }
    inFile >> initVelocity >> startAngle;
    double startAngleInRads = startAngle * PI / 180.0;
    cout << "Initial Velocity(in m/s): " << initVelocity << endl << endl;
    cout << "Starting angle(in degrees): " << startAngle << endl << endl;
    cout << "Results:\n";
    cout << string(8, '-') << endl;

    timeMaxHeight = (initVelocity * sin(startAngleInRads)) / gravity;
    timeHitGround = (2.0 * initVelocity * sin(startAngleInRads))/gravity;
    maxHeight = (pow(initVelocity, 2) * pow(sin(startAngleInRads), 2))/(2 * gravity);
    distTraveled = initVelocity * timeHitGround * cos(startAngleInRads);
    cout << fixed << setprecision(3) << left;
    cout << setw(25) << "Time to max height: " << timeMaxHeight << " seconds" << endl;
    cout << setw(25) << "Time to max distance: " << timeHitGround << " seconds" << endl;
    cout << setw(25) << "Maximum height: " << maxHeight << " meters" << endl;
    cout << setw(25) << "Maximum distance: " << distTraveled << " meters" << endl;
    cout << endl;
    return 0;
}

