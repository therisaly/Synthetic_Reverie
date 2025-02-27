#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "btBulletCollisionCommon.h"

class OpenGLAppConfiguration
{
public:
	OpenGLAppConfiguration()
	{
		cameraPosition = btVector3(10.0f, 5.0f, 0.0f);
		cameraTarget = btVector3(0.0f, 0.0f, 0.0f);
		upVector = btVector3(0.0f, 1.0f, 0.0f);
		nearPlane = 1.0f;
		farPlane = 1000.0f;
		screenWidth = 500;
		screenHeight = 350;
		cameraDistance = 15.0f;
		cameraPitch = 20.0f;
		cameraYaw = 0.0f;
	}
public:

	btVector3 cameraPosition;
	btVector3 cameraTarget;
	btVector3 upVector;
	float nearPlane;
	float farPlane;
	float cameraDistance; 
	float cameraPitch; 
	float cameraYaw;

	int screenWidth;
	int screenHeight;
};