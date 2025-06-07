#pragma once
#include "GameObject.h"

class ClockObstacle
{
public:
	ClockObstacle() = default;
	ClockObstacle(int scale, btDynamicsWorld& dynamicsWorld);

	void Render(GraphicsSystem& gfx);
private:
	GameObject bigWheel;
	GameObject smallWheel;

	GameObject shorterHand;
	GameObject longerHand;

	GameObject bigAxis;
	GameObject smallAxis;
};

