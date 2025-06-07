#pragma once
#include "IMovement.h"
#include "GameObject.h"

class EnemyChase : public IMovement
{
public:
    explicit EnemyChase(GameObject* target) 
        : target(target) 
    {}
    void Update(float deltaTime, btRigidBody* rigidBody) override
    {  }
private:
    GameObject* target; 
};