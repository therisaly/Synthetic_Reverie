#include "GameObject.h"

GameObject::GameObject(std::string meshFileName, btDynamicsWorld& dynamicsWorld, Type type)
    :
    objectType(type)
{
    //set initial transform
    btTransform startTransform;
    startTransform.setIdentity();
    startTransform.setOrigin(btVector3(0, 0, 0));
    startTransform.setRotation(btQuaternion::getIdentity());

    //mesh and collision shape
    MeshLoader::LoadModel(meshFileName.c_str(), mesh);
    btBoxShape* boxShape = new btBoxShape(mesh.dimensions / 2);

    //mass and inertia

    //if its dynamic, its mass is 1, otherwise its either static or kinematic
    float mass = type == Type::DYNAMIC ? 1.0f : 0.0f;

    btVector3 inertia(0, 0, 0);
    if (mass > 0.0f)
        boxShape->calculateLocalInertia(mass, inertia);

    // use your custom motion state
    MyMotionState* motionState = new MyMotionState(startTransform);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, boxShape, inertia);
    rigidBody = std::make_unique<btRigidBody>(rbInfo); 

    switch (type)
    {
    case DYNAMIC:
        //default
        break;
    case STATIC:
        rigidBody->setCollisionFlags(rigidBody->getCollisionFlags() | btCollisionObject::CF_STATIC_OBJECT); 
        break;
    case KINEMATIC:
        rigidBody->setCollisionFlags(rigidBody->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT); 
        rigidBody->setActivationState(DISABLE_DEACTIVATION); 
        break;
    }

    rigidBody->setWorldTransform(startTransform);
    dynamicsWorld.addRigidBody(rigidBody.get()); 
}

void GameObject::Render(GraphicsSystem& gfx)
{
	btScalar transf[16];

    btTransform worldTransform = rigidBody->getWorldTransform(); 

    worldTransform.getOpenGLMatrix(transf);

	gfx.RenderMesh(transf, mesh); 
	
}

void GameObject::MoveObject(btVector3 dir, float speed, float dT) 
{
    btTransform transf;
    rigidBody->getMotionState()->getWorldTransform(transf);

    // Preserve existing rotation while moving
    transf.setOrigin(transf.getOrigin() + (dir * speed * dT));
    rigidBody->setWorldTransform(transf);
    rigidBody->activate();
}

Mesh GameObject::GetMesh() const
{
	return mesh;
}

btTransform GameObject::GetTransform() const
{
	return rigidBody->getWorldTransform(); 
}

Type GameObject::GetType() const
{
    return objectType; 
}

void GameObject::SetTransform(btTransform transf) 
{
    rigidBody->setWorldTransform(transf);
    if (rigidBody->getMotionState()) {
        rigidBody->getMotionState()->setWorldTransform(transf);
    }
} 

void GameObject::SetRotation(btQuaternion deltaRotation) 
{
    btTransform transf;
    rigidBody->getMotionState()->getWorldTransform(transf);

    btQuaternion currentRotation = transf.getRotation();
    btQuaternion newRotation = deltaRotation * currentRotation;

    transf.setRotation(newRotation);
    SetTransform(transf);
}

void GameObject::Move(btVector3 transofrm)
{
    btTransform transf;
    rigidBody->getMotionState()->getWorldTransform(transf);

    btVector3 currentPosition = transf.getOrigin();
    btVector3 newPosition = currentPosition + transofrm;

    transf.setOrigin(newPosition);
    SetTransform(transf);
}

void GameObject::AddMovementPattern(std::unique_ptr<IMovement> newMovement)
{
    movement = std::move(newMovement);
}

IMovement* GameObject::GetMovement()
{
    return movement.get();
}

btRigidBody* GameObject::GetRigidBody()
{
    return rigidBody.get(); // Use get() to return the raw pointer
}

