#include "TriggerCollider.h"

TriggerCollider::TriggerCollider(btDynamicsWorld& dynamicsWorld, btVector3 colliderDimensions)
{
    //set initial transform
    btTransform startTransform;
    startTransform.setIdentity();
    startTransform.setOrigin(btVector3(0, 0, 0));
    startTransform.setRotation(btQuaternion::getIdentity());

    //mesh and collision shape
    btBoxShape* boxShape = new btBoxShape(colliderDimensions / 2);

    //mass and inertia
    float mass = 0.0f;
    btVector3 inertia(0, 0, 0);
    if (mass > 0.0f)
        boxShape->calculateLocalInertia(mass, inertia);

    // use your custom motion state
    MyMotionState* motionState = new MyMotionState(startTransform);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, boxShape, inertia);
    rigidBody = std::make_unique<btRigidBody>(rbInfo);


    rigidBody->setCollisionFlags(
        rigidBody->getCollisionFlags() |
        btCollisionObject::CF_NO_CONTACT_RESPONSE); 

    rigidBody->setWorldTransform(startTransform);
    dynamicsWorld.addRigidBody(rigidBody.get());
}
