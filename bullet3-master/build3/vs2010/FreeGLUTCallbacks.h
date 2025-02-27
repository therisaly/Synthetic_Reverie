#ifndef _FREEGLUTCALLBACKS_H_
#define _FREEGLUTCALLBACKS_H_

#define RADIANS_PER_DEGREE 0.01745329f
#define CAMERA_STEP_SIZE 1.0f

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "btBulletCollisionCommon.h"
#include "Game.h"
#include "OpenGLAppConfiguration.h"
#include "GraphicsSystem.h"


static Game* game; 
static OpenGLAppConfiguration config;
btClock _clock;


static void UpdateCamera()
{
	if (config.screenWidth == 0 && config.screenHeight == 0)
		return;

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	float aspectRatio = config.screenWidth / (float)config.screenHeight;

	glFrustum(-aspectRatio * config.nearPlane, aspectRatio * config.nearPlane, -config.nearPlane, config.nearPlane, config.nearPlane, config.farPlane);


	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	float pitch = config.cameraPitch * RADIANS_PER_DEGREE;
	float yaw = config.cameraYaw * RADIANS_PER_DEGREE;

	btQuaternion rotation(config.upVector, yaw);

	btVector3 cameraPosition(0, 0, 0);
	cameraPosition[2] = -config.cameraDistance;

	btVector3 forward(cameraPosition[0], cameraPosition[1], cameraPosition[2]);
	if (forward.length2() < SIMD_EPSILON) {
		forward.setValue(1.f, 0.f, 0.f);
	}

	btVector3 right = config.upVector.cross(forward);

	btQuaternion roll(right, -pitch);

	cameraPosition = btMatrix3x3(rotation) * btMatrix3x3(roll) * cameraPosition;

	config.cameraPosition[0] = cameraPosition.getX();
	config.cameraPosition[1] = cameraPosition.getY();
	config.cameraPosition[2] = cameraPosition.getZ();
	config.cameraPosition += config.cameraTarget;


	gluLookAt(config.cameraPosition[0], config.cameraPosition[1], config.cameraPosition[2], config.cameraTarget[0], config.cameraTarget[1], config.cameraTarget[2], config.upVector.getX(), config.upVector.getY(), config.upVector.getZ());
	// the view matrix is now set
}

static void ZoomCamera(float distance) {

	config.cameraDistance -= distance;

	if (config.cameraDistance < 0.1f)config.cameraDistance = 0.1f;

	UpdateCamera();
}

static void KeyboardCallback(unsigned char key, int x, int y) {
	switch (key) {
	case 'z': 
		ZoomCamera(+CAMERA_STEP_SIZE);
		break;
	case 'x':
		ZoomCamera(-CAMERA_STEP_SIZE);
		break;
	case 'w':
		break;

	case 'b':
		break;
	}
}
static void KeyboardUpCallback(unsigned char key, int x, int y) {
	//
}
void RotateCamera(float& angle, float value) {

	angle -= value;

	if (angle < 0) angle += 360;
	if (angle >= 360) angle -= 360;

	UpdateCamera();
}

static void SpecialCallback(int key, int x, int y) {
	switch (key) {
		// the arrow keys rotate the camera up/down/left/right
	case GLUT_KEY_LEFT:
		RotateCamera(config.cameraYaw, +CAMERA_STEP_SIZE); break;
	case GLUT_KEY_RIGHT:
		RotateCamera(config.cameraYaw, -CAMERA_STEP_SIZE); break;
	case GLUT_KEY_UP:
		RotateCamera(config.cameraPitch, +CAMERA_STEP_SIZE); break;
	case GLUT_KEY_DOWN:
		RotateCamera(config.cameraPitch, -CAMERA_STEP_SIZE); break;
	}

}
static void SpecialUpCallback(int key, int x, int y) {
	//
}
static void ReshapeCallback(int w, int h) {
	config.screenWidth = w;

	config.screenHeight = h;
	
	glViewport(0, 0, w, h);

	UpdateCamera();
}

static void MouseCallback(int button, int state, int x, int y) {
	//
}
static void MotionCallback(int x,int y) {
	//
}
static void DisplayCallback(void) {
	//
}

static void Init()
{
	game->Init();
	GraphicsSystem::InitLight();
}

static void TimerCallback(int value)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	float dT = _clock.getTimeMilliseconds() / 1000.0f; // Time since last frame
	_clock.reset();

	game->Update(dT);
	UpdateCamera();
	game->Render();

	glutSwapBuffers();

	// Schedule next frame
	glutTimerFunc(16, TimerCallback, 0); // ~60 FPS
}

int glutmain(int argc, char **argv, const char* title, Game* gameObj) {

	game = gameObj;

	// initialize the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(config.screenWidth, config.screenHeight);
	glutCreateWindow(title);
	glutSetOption (GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	Init();

	glutKeyboardFunc(KeyboardCallback);
	glutKeyboardUpFunc(KeyboardUpCallback);
	glutSpecialFunc(SpecialCallback);
	glutSpecialUpFunc(SpecialUpCallback);
	glutReshapeFunc(ReshapeCallback);

	glutMouseFunc(MouseCallback);
	glutPassiveMotionFunc(MotionCallback);
	glutMotionFunc(MotionCallback);
	glutDisplayFunc(DisplayCallback );
	glutTimerFunc(0, TimerCallback, 0);

	
	glutMainLoop();
	return 0;
}
#endif