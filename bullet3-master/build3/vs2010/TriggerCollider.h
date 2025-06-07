#pragma once
#include "GameObject.h"
#include "Event.h"
class TriggerCollider
{
public:
	TriggerCollider(btDynamicsWorld& dynamicsWorld, btVector3 colliderDimensions);
private:
	std::unique_ptr<btRigidBody> rigidBody;
	
};