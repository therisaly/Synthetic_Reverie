#include "ClockObstacle.h"

ClockObstacle::ClockObstacle(int scale, btDynamicsWorld& dynamicsWorld)
{
	shorterHand = GameObject("", dynamicsWorld, true, INTERACTABLE);
	longerHand = GameObject("", dynamicsWorld, true, INTERACTABLE);
	axisConstraint = GameObject("", dynamicsWorld, false, INTERACTABLE);
}
