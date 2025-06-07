#pragma once
#include "IMovement.h"

class PlayerMovement : public IMovement
{
public:
    explicit PlayerMovement()
    {
    }
    void Update(float deltaTime, btRigidBody* rigidBody) override   
    { 
        btTransform transform; 
        rigidBody->getMotionState()->getWorldTransform(transform); 

        btVector3 newPosition = transform.getOrigin() + (movementDirection * speed * deltaTime); 

        transform.setOrigin(newPosition); 

        rigidBody->getMotionState()->setWorldTransform(transform); 
        rigidBody->setCenterOfMassTransform(transform);  
    }
    void SetCurrentDirection(btVector3 movementDir)
    {
        movementDirection = movementDir;  
    }
private:
    float speed = 10.0f;
    btVector3 movementDirection{ 0.0, 0.0, 0.0 };  
};