#include "IGTLink_Robot_Server.h"

using namespace std;

//Contructor
IGTLink_Robot_Server::IGTLink_Robot_Server(robot *robot_client, int _port, double _fps)
{
	
	_error = 0;
	_disconnected_counter = 0;
	sendData = false;

	setRobotDevice(robot_client);
	setPortValue(_port);
	setFpsValue(_fps);
}

//Destructor
IGTLink_Robot_Server::~IGTLink_Robot_Server()
{
}

//Contains the while loop that take the robot position and send it
int IGTLink_Robot_Server::startSendingData()
{

  //variables definition and initialization
  int interval = (int) (1000.0 / getFpsValue());
  igtl::Socket::Pointer socket;

   igtl::TransformMessage::Pointer transMsg;
  transMsg = igtl::TransformMessage::New();
  transMsg->SetDeviceName("Robot");

  igtl::ServerSocket::Pointer serverSocket;
  serverSocket = igtl::ServerSocket::New();

  igtl::Matrix4x4 robotMatrixTransform;			//trasformation matrix of robot position

  setConnection(serverSocket);					//configure the connection
  sendData = true;								//setting True sendData

  //modifing the Gui, stopTracking could modify a bool that set the condition for the while loop.
  while (sendData == true)
  {
	//------------------------------------------------------------
	// Waiting for Connection


	socket = serverSocket->WaitForConnection(5);
	
	if (socket.IsNotNull()) // if client connected
	{
		_disconnected_counter = 0;

		if(robot_dev != NULL) //if robot pointer is valid
		{
			
			robot_dev->getTransformationMatrix(robotMatrixTransform); //<------------- check this

			transMsg->SetMatrix(robotMatrixTransform);
			transMsg->Pack();
			socket->Send(transMsg->GetPackPointer(), transMsg->GetPackSize());
			igtl::Sleep(interval); // wait
		}
		else
		{
			std::cout << "Error: invalid robot pointer" << std::endl;
			stopSendingData();
			_error = _INVALID_ROBOT_POINTER;
			return _error;			
		}	
	}
	else
	{
		_disconnected_counter++; //counter for disconnections

		if (_disconnected_counter >= 2)
		{
			std::cout << "Error: the client is not connected" << std::endl;
		}
	}
	  
  }//finish while
    
  //------------------------------------------------------------
  // Close connection (The example code never reachs to this section ...)  
  socket->CloseSocket();
  return _error;
}

//change bool sendData to false
int IGTLink_Robot_Server::stopSendingData()
{
	sendData = false; 
	return _error;
}

//create server to a specific port, check is well done
int IGTLink_Robot_Server::setConnection(igtl::ServerSocket::Pointer serverSocket)
{
  int r = serverSocket->CreateServer(getPortValue());

  if (r < 0)
  {
	std::cout << "Cannot create a server socket." << std::endl;
	_error = _ERROR_CREATING_SERVER_SOCKET;
	return _error;
  }
  return _error;
}

//set port value
int IGTLink_Robot_Server::setPortValue(int input_port)
{
	if(input_port < 0)
	{
		_error = _INVALID_PORT_NUMBER;
		std::cout << "Invalid port number chosen" << std::endl;
		return _error;
	}
	port = input_port; 
	return _error;
}
//get port value
int IGTLink_Robot_Server::getPortValue()
{
	return port;
}
//set frame per second value
int IGTLink_Robot_Server::setFpsValue(double input_fps)
{
	if(input_fps <= 0)
	{
		_error = _INVALID_FPS_VALUE;
		std::cout << "The FPS Value should be positive and different from zero!" << std::endl;
		return _error;
	}
	fps = input_fps;
	return _error;
}
//get frame per second value
double IGTLink_Robot_Server::getFpsValue()
{
	return fps;
}

//link the robot pointer to the internal variable robot_dev
int IGTLink_Robot_Server::setRobotDevice(robot *robot_client)
{
	if(robot_client == NULL)
	{
		std::cout << "Error: invalid robot pointer" << std::endl;
		_error = _INVALID_ROBOT_POINTER;
		return _error;
	}

	robot_dev = robot_client;
	return _error;
}