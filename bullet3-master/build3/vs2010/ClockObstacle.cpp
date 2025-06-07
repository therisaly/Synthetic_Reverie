#include "ClockObstacle.h"

ClockObstacle::ClockObstacle(int scale, btDynamicsWorld& dynamicsWorld)
{
    bigWheel = GameObject("models/bigFloorRing.obj", dynamicsWorld, DYNAMIC);
    smallWheel = GameObject("models/smallFloorRing.obj", dynamicsWorld, DYNAMIC);

    shorterHand = GameObject("models/smallHand.obj", dynamicsWorld, DYNAMIC);
    longerHand = GameObject("models/bigHand.obj", dynamicsWorld, DYNAMIC);

    bigAxis = GameObject("models/bigAxis.obj", dynamicsWorld, DYNAMIC);
    smallAxis = GameObject("models/smallAxis.obj", dynamicsWorld, DYNAMIC);

    auto addFixedConstraint = [&](btRigidBody* parent, btRigidBody* child) {
        btTransform parentTransform = parent->getWorldTransform();
        btTransform childTransform = child->getWorldTransform();

        btTransform localA = parentTransform.inverse() * childTransform;
        btTransform localB; localB.setIdentity();

        auto* fixed = new btFixedConstraint(*parent, *child, localA, localB);
        dynamicsWorld.addConstraint(fixed, true);

        //ukoliko se ovo ne postavi, ide sve u picku materinu
        child->setCollisionFlags(child->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
        };

    addFixedConstraint(bigWheel.GetRigidBody(), bigAxis.GetRigidBody());
    addFixedConstraint(bigAxis.GetRigidBody(), smallWheel.GetRigidBody());
    addFixedConstraint(smallWheel.GetRigidBody(), smallAxis.GetRigidBody());
    addFixedConstraint(smallAxis.GetRigidBody(), shorterHand.GetRigidBody());
    addFixedConstraint(smallAxis.GetRigidBody(), longerHand.GetRigidBody());
}

void ClockObstacle::Render(GraphicsSystem& gfx)
{
	bigWheel.Render(gfx);
	smallWheel.Render(gfx);

	shorterHand.Render(gfx); 
	longerHand.Render(gfx); 

	bigAxis.Render(gfx); 
	smallAxis.Render(gfx); 
}
