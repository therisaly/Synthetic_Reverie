#pragma once
#include "MeshLoader.h"
#include "btBulletCollisionCommon.h"
#include "PhysicsSystem.h"
#include "IMovement.h"
#include "GraphicsSystem.h"
#include "CustomMotionState.h"

enum Type
{
	DYNAMIC,
	STATIC,
	KINEMATIC
};

class GameObject
{
public:
	GameObject() = default;
	GameObject(std::string meshFileName, btDynamicsWorld& dynamicsWorld, Type type = Type::DYNAMIC);

	void Render(GraphicsSystem& gfx);
	void MoveObject(btVector3 dir, float speed, float dT);

	Mesh GetMesh() const;
	btTransform GetTransform() const;
	Type GetType() const;
	void SetTransform(btTransform transf);
	void SetRotation(btQuaternion rotation);

	void Move(btVector3 transofrm);

	void AddMovementPattern(std::unique_ptr<IMovement> newMovement);
	IMovement* GetMovement();

	btRigidBody* GetRigidBody();
private:
	Mesh mesh;
	std::unique_ptr<btRigidBody> rigidBody;
	Type objectType = Type::DYNAMIC;
	std::unique_ptr<IMovement> movement;

	bool isGrounded = false;
};

