#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <process.h>
#include <windows.h>

enum DIRECTION {
	FORWARD = 0,
	BACKWARD,
	LEFT,
	RIGHT
};

using namespace std;

class FestoRobotAPI {
public:
	FestoRobotAPI();

	//Connect to robot in simulator
	void connect();

	//Disconnect to robot in simulator
	void disconnect();

	//Move the robot any direction. 
	// Possible arguments are {FORWARD, BACKWARD, LEFT, RIGHT}
	void move(DIRECTION);

	//Rotate to any side.
	// Possible arguments are {LEFT, RIGHT}
	void rotate(DIRECTION);

	//Stop the robot
	void stop();

	// i: sensor index, return the distance in meters, (There are 9 sensors)
	double getIRRange(int i);

	// Get koordinates of the robot (X: position at x-axis, Y: Position at y-axis, TH: heading angle)
	void getXYTh(double& X, double& Y, double& TH);

	//Get Lidar Range Data
	void getLidarRange(float*);

	//Get Lidar Range Number (the number of lidar range data)
	int getLidarRangeNumber();

};


