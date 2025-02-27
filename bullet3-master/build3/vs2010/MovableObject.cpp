#include "MovableObject.h"

MovableObject::MovableObject(const char* meshFileName, btDynamicsWorld& dynamicsWorld)
{
	btTransform trans;
	trans.setIdentity();
	trans.setOrigin(btVector3(0.0f, 0.0f, 0.0f));

	transform = new OpenGLMotionState(trans);

	MeshLoader::LoadModel(meshFileName, mesh);
	btBoxShape* boxShape = new btBoxShape(mesh.dimensions / 2);

	btVector3 fallInertia(0, 0, 0);
	boxShape->calculateLocalInertia(1.0f, fallInertia);
	btRigidBody::btRigidBodyConstructionInfo info(1.0f, transform, boxShape, fallInertia);

	rigidBody = new btRigidBody(info);

	//dynamicsWorld.addRigidBody(rigidBody);
}
