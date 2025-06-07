#pragma once

#include "GameObject.h"
#include "PhysicsSystem.h"
#include "GraphicsSystem.h"
#include "BulletDebugDrawer.h" 
#include "tiny_obj_loader.h"
#include "Input.h"
#include "Level.h"
#include "Event.h"
#include "LevelsIterator.h"
#include "ClockObstacle.h"

class Game
{
public:
	Game();
	~Game();

	void Init();

	void Update(float dT);
	void Render();

	Input& GetInputSystem()
	{
		return inputSystem;
	}
private:

	//Systems
	PhysicsSystem& physicsSystem;
	GraphicsSystem& gfx;
	Input inputSystem;
	//User defined variables
	std::vector<std::unique_ptr<Level>> levels;
	LevelsIterator iterator;
	int currentLevelIndex = 0;
	ClockObstacle clockObstacle;
	GameObject testClock;
	GameObject testClocksmall;
	GameObject bigHand;
	GameObject smallHand;
	GameObject bigAxis;
	GameObject smallAxis;

	BulletDebugDrawer debugDrawer; 
};