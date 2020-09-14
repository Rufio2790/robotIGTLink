#ifndef __IGTLINK_ROBOT_SERVER__
#define __IGTLINK_ROBOT_SERVER__

#include <iostream>
#include <math.h>
#include <cstdlib>

#include "igtlOSUtil.h"
#include "igtlTransformMessage.h"
#include "igtlServerSocket.h"
#include "robot.h"

#define _ERROR_CREATING_SERVER_SOCKET 701
#define _INVALID_ROBOT_POINTER 702
#define _CLIENT_NOT_CONNECTED 703
#define _INVALID_PORT_NUMBER 704
#define _INVALID_FPS_VALUE 705

class robot; //forward class declaration for the robot class

//create a server class for the robot through IGTLink, it's supposed to acceed to the robot informations like
//position, orientation.. and send through a configured port. A client will connect to the messages.
class IGTLink_Robot_Server
{
	public:

		 //Contructor: set up the connection default values with an initialization member list
		IGTLink_Robot_Server(robot *robot_client, int port=18944, double fps=100);						   
		~IGTLink_Robot_Server();		//Destructor
		
		int startSendingData();			//once is started, acceed to the info and send
		int stopSendingData();				//call the destructor
		int setConnection(igtl::ServerSocket::Pointer serverSocket);			//setting up the connection 

		//set and get the port value
		int setPortValue(int selectedPort);						
		int	getPortValue();

		//set and get the frame per second
		int	setFpsValue(double selectedFps);						
		double	getFpsValue();

		int setRobotDevice(robot *robot_client);

	protected:
	
	private:

		robot *robot_dev;
		int    port;
		double fps;
		bool sendData;

		int _disconnected_counter;
		int _error;

};

#endif