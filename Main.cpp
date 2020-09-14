//main program

#include "IGTLink_Robot_Server.h"
#include "robot.h"
#include <tchar.h>

int main()
{
	robot *robot_device = new robot;
	IGTLink_Robot_Server robot_server(robot_device);

	robot_server.startSendingData();

}

