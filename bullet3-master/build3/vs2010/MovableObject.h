#pragma once
#include "OpenGLMotionState.h"
#include "MeshLoader.h"
#include "btBulletCollisionCommon.h"
#include "PhysicsSystem.h"
#include "GraphicsSystem.h"

class MovableObject
{
public:
	MovableObject() = default;
	MovableObject(const char* meshFileName, btDynamicsWorld& dynamicsWorld);
	void Render(GraphicsSystem& gfx)
	{
		btScalar transf[16];

		transform->GetWorldTransform(transf);

		gfx.RenderMesh(transf, mesh);
	}
	void MoveObject(btVector3 dir, float speed, float dT)
	{
		btTransform transf;

		transform->getWorldTransform(transf);

		transf.setOrigin(transf.getOrigin() + (dir * speed * dT));

		transform->setWorldTransform(transf);

	}
	Mesh GetMesh() const
	{
		return mesh;
	}
	OpenGLMotionState GetTransform() const
	{
		return *transform;
	}
private:
	OpenGLMotionState* transform;
	Mesh mesh;
	btRigidBody* rigidBody;
};

