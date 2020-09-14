#ifndef __ROBOT_CLASS__
#define __ROBOT_CLASS__

#include <iostream>
#include <math.h>
#include <cstdlib>

#include "igtlOSUtil.h"
#include "igtlTransformMessage.h"
#include "igtlServerSocket.h"

class robot
{
	public:

		robot(){};
		~robot(){};
		void getTransformationMatrix(igtl::Matrix4x4 &matrix)
		{  
		  float position[3];
		  float orientation[4];

		  // random position
		  static float phi = 0.0;
		  position[0] = 50.0 * cos(phi);
		  position[1] = 50.0 * sin(phi);
		  position[2] = 50.0 * cos(phi);
		  phi = phi + 0.2;

		  // random orientation
		  static float theta = 0.0;
		  orientation[0]=0.0;
		  orientation[1]=0.6666666666*cos(theta);
		  orientation[2]=0.577350269189626;
		  orientation[3]=0.6666666666*sin(theta);
		  theta = theta + 0.1;

		  //igtl::Matrix4x4 matrix;
		  igtl::QuaternionToMatrix(orientation, matrix);

		  matrix[0][3] = position[0];
		  matrix[1][3] = position[1];
		  matrix[2][3] = position[2];
		};

	protected:

	private:

};

#endif