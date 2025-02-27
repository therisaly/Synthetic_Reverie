#pragma once
#include <btBulletDynamicsCommon.h>
#include "Components.h"

class PhysicsSystem
{
public:
	static PhysicsSystem& GetInstance()
	{
		static PhysicsSystem instance; // Ensures a single instance
		return instance;
	}
	btDiscreteDynamicsWorld& GetDynamicsWorldRef()
	{
		return *dynamicsWorld;
	}
private:
	PhysicsSystem()
	{
		collisionConfig = new btDefaultCollisionConfiguration();
		dispatcher = new btCollisionDispatcher(collisionConfig);
		broadphase = new btDbvtBroadphase();
		solver = new btSequentialImpulseConstraintSolver();
		dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver,
			collisionConfig);
	}
	~PhysicsSystem()
	{
		delete collisionConfig;
		delete dispatcher;
		delete broadphase;
		delete solver;
		delete dynamicsWorld;
	}
private:
	// 1. Collision configuration (manages collision detection algorithms)
	btDefaultCollisionConfiguration* collisionConfig;

	// 2. Dispatcher (handles collision events)
	btCollisionDispatcher* dispatcher;

	// 3. Broadphase (optimizes collision checks for large worlds)
	btBroadphaseInterface* broadphase;

	// 4. Solver (handles forces, constraints, etc.)
	btSequentialImpulseConstraintSolver* solver;

	// 5. Dynamics world (manages all physics objects)
	btDiscreteDynamicsWorld* dynamicsWorld;

};