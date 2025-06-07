#pragma once
#include <btBulletDynamicsCommon.h>

class IMovement
{
public:
    virtual ~IMovement() = default;
    virtual void Update(float deltaTime, btRigidBody* rigidBody) = 0; 
};
