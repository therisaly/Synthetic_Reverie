#include "Game.h"
#include <iostream>
#include "tiny_obj_loader.h"
#include <GL/glew.h>
#include "stb_image.h" 

Game::Game()
    : physicsSystem(PhysicsSystem::GetInstance()),
    gfx(GraphicsSystem::GetInstance())
{
    levels.push_back(std::make_unique<Level>(1, physicsSystem.GetDynamicsWorldRef(), btVector3(20, 20, 20)));
    levels.push_back(std::make_unique<Level>(1, physicsSystem.GetDynamicsWorldRef(), btVector3(20, 20, 20)));
    levels.push_back(std::make_unique<Level>(1, physicsSystem.GetDynamicsWorldRef(), btVector3(20, 20, 20)));

    // Subscribe to the event
    levels[0]->GetNextLevelEvent().Subscribe(&iterator);

}

Game::~Game() 
{
    
}

void Game::Init() 
{
    // Load the .obj file
     
    physicsSystem.GetDynamicsWorldRef().setDebugDrawer(&debugDrawer);
    debugDrawer.setDebugMode(
        btIDebugDraw::DBG_DrawWireframe |
        btIDebugDraw::DBG_DrawContactPoints |
        btIDebugDraw::DBG_DrawConstraints
    );

    testClock = GameObject("models/bigFloorRing.obj", physicsSystem.GetDynamicsWorldRef(), false, INTERACTABLE);
    testClock.SetRotation(btQuaternion(btVector3(0, 1, 0), SIMD_PI));

    testClocksmall = GameObject("models/smallFloorRing.obj", physicsSystem.GetDynamicsWorldRef(), false, INTERACTABLE);
    testClocksmall.SetRotation(btQuaternion(btVector3(0, 1, 0), SIMD_PI));

    bigHand = GameObject("models/bigHand.obj", physicsSystem.GetDynamicsWorldRef(), false, INTERACTABLE);
    bigHand.SetRotation(btQuaternion(btVector3(0, 1, 0), SIMD_PI));

    smallHand = GameObject("models/smallHand.obj", physicsSystem.GetDynamicsWorldRef(), false, INTERACTABLE);
    smallHand.SetRotation(btQuaternion(btVector3(0, 1, 0), SIMD_PI));

    bigAxis = GameObject("models/bigAxis.obj", physicsSystem.GetDynamicsWorldRef(), false, INTERACTABLE);
    bigAxis.SetRotation(btQuaternion(btVector3(0, 1, 0), SIMD_PI));

    smallAxis = GameObject("models/smallAxis.obj", physicsSystem.GetDynamicsWorldRef(), false, INTERACTABLE);
    smallAxis.SetRotation(btQuaternion(btVector3(0, 1, 0), SIMD_PI));
    //testClocksmall.Move(btVector3(0, 0, -2));
    //std::vector<std::unique_ptr<GameObject>> levelOneObjects;  


   // levelOneObjects.emplace_back(std::make_unique<GameObject>("models/housesLevelOne.obj", physicsSystem.GetDynamicsWorldRef(), true, Type::VISUAL));

    //levelOne.Initialize(levelOneObjects); 

    //testObj = new GameObject("models/cube.obj", physicsSystem.GetDynamicsWorldRef(), false);

    //btVector3 position = transform.getOrigin();

    //position.setY(10);

    //transform.setOrigin(position);

    //testObj->SetTransform(transform);

    //testObj->AddMovementPattern(std::make_unique<PlayerMovement>());

    //inputSystem.AddCharacter(*testObj); 


}

void Game::Update(float dT) 
{
    if (currentLevelIndex >= levels.size()) 
    {
        return;
    }

    physicsSystem.GetDynamicsWorldRef().stepSimulation(dT, 10, 1.0f / 240.0f);

    levels[currentLevelIndex]->Update();

    if (iterator.GetIterator() > currentLevelIndex)
    {
        std::cout << "Invoked level change for: " << currentLevelIndex + 1 << std::endl;

        levels[currentLevelIndex]->GetNextLevelEvent().Unsubscribe(&iterator);

        currentLevelIndex++;

        if (currentLevelIndex < levels.size())
        {
            levels[currentLevelIndex]->GetNextLevelEvent().Subscribe(&iterator);
        }
        else
        {
            std::cout << "No more levels. Game complete!" << std::endl;
        }
    }
}


void Game::Render() 
{
    testClock.Render(gfx);
    testClocksmall.Render(gfx);
    bigHand.Render(gfx);
    smallHand.Render(gfx);
    bigAxis.Render(gfx);
    smallAxis.Render(gfx);
}
