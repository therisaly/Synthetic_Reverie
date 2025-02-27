#include "Game.h"
#include <iostream>
#include "tiny_obj_loader.h"
#include <GL/glew.h>
#include "stb_image.h" // Include stb_image for texture loading

Game::Game()
    : physicsSystem(PhysicsSystem::GetInstance()),
    gfx(GraphicsSystem::GetInstance()) {
}

Game::~Game() {
    delete testObj;
}

void Game::Init() {
    // Load the .obj file

    testObj = new MovableObject("models/rotatingPlatform.obj", physicsSystem.GetDynamicsWorldRef());
    testObj1 = new MovableObject("models/road.obj", physicsSystem.GetDynamicsWorldRef());

    if (!testObj1->GetMesh().warn.empty()) {
        std::cout << "Warning: " << testObj1->GetMesh().warn << std::endl;
    }
    if (!testObj1->GetMesh().err.empty()) {
        std::cerr << "Error: " << testObj1->GetMesh().err << std::endl;
    }

}

void Game::Update(float dT) {
    physicsSystem.GetDynamicsWorldRef().stepSimulation(dT);

    btTransform transform;
    testObj->GetTransform().getWorldTransform(transform);


    testObj1->GetTransform().getWorldTransform(transform);

    btVector3 position = transform.getOrigin();
    // Use `position` to update the object's position in the rendering system
   // std::cout << "Object position: " << position.getX() << ", " << position.getY() << ", " << position.getZ() << std::endl;

}

void Game::Render() {

    testObj1->Render(gfx);
}
