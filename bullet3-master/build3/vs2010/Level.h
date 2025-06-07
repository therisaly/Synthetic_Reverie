#pragma once
#include "GameObject.h"
#include "PhysicsSystem.h"
#include "GraphicsSystem.h"
#include "IEventListener.h"
#include "TriggerCollider.h"

class Level
{
public:
	Level(int levelID, btDynamicsWorld& dynamicsWorld, btVector3 colliderDimensions);

	void Update();
	void Render(GraphicsSystem& gfx);

	Event& GetNextLevelEvent()
	{
		return nextLevelEvent;
	}
	void Initialize(std::vector<std::unique_ptr<GameObject>>& levelObjects);
	void AddObject(std::unique_ptr<GameObject> gameObject);
protected:
	int levelID = 0;
	TriggerCollider triggerCollider;
	Event nextLevelEvent;
	std::vector<std::unique_ptr<GameObject>> visualObjects;
	std::vector<std::unique_ptr<GameObject>> collidableObjects;

	bool hasTriggered = false;
};

