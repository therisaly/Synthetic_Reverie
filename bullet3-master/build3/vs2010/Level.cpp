#include "Level.h"


Level::Level(int levelID, btDynamicsWorld& dynamicsWorld, btVector3 colliderDimensions)
    :
    levelID(levelID),
    triggerCollider(dynamicsWorld, colliderDimensions)
{
} 

void Level::Update()
{
    //ako neko udje u trigger kolajder
    //onda event.Invoke()
    if (!hasTriggered)
    {
        nextLevelEvent.Invoke();
        hasTriggered = true;
    }
}

void Level::Render(GraphicsSystem& gfx)
{
    for (const auto& go : visualObjects)
    {
        go->Render(gfx);
    }
     
    for (const auto& go : collidableObjects)
    {
        go->Render(gfx);
    }
}

void Level::Initialize(std::vector<std::unique_ptr<GameObject>>& levelObjects)
{
    for (auto& go : levelObjects)
    {
        AddObject(std::move(go));
    }

    // After this point, all elements in `levelObjects` are nullptrs (moved-from)
}

void Level::AddObject(std::unique_ptr<GameObject> gameObject)
{
    if (gameObject->GetType() == Type::VISUAL)
    {
        visualObjects.emplace_back(std::move(gameObject));  // move ownership
    }
    else if (gameObject->GetType() == Type::INTERACTABLE)
    {
        collidableObjects.emplace_back(std::move(gameObject));  // move ownership
    }
}

