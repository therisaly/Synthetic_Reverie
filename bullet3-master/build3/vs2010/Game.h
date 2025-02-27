#pragma once

#include "MovableObject.h"
#include "PhysicsSystem.h"
#include "GraphicsSystem.h"
#include "tiny_obj_loader.h"

class Game
{
public:
	Game();
	~Game();

	void Init();

	void Update(float dT);
	void Render();
private:

	//Systems
	PhysicsSystem& physicsSystem;
	GraphicsSystem& gfx;
	//User defined variables
	MovableObject* testObj;
	MovableObject* testObj1;
};