#pragma once
#include "GameObject.h"

class ClockObstacle
{
public:
	ClockObstacle() = default;
	ClockObstacle(int scale, btDynamicsWorld& dynamicsWorld);


private:
	GameObject shorterHand;
	GameObject longerHand;
	GameObject axisConstraint;


};

