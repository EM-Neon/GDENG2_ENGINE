#include "PhysicsCube.h"
#include "PhysicsComponent.h"

PhysicsCube::PhysicsCube(String name, void* shaderByteCode, size_t sizeShader):Cube(name, shaderByteCode, sizeShader)
{
	this->setPosition(0.0f, 5.0f, 0.0f);
	this->setScale(1.0f, 1.0f, 1.0f);
	this->updateLocalMatrix();
	this->attachComponent(new PhysicsComponent("PhysicsComponent", this));
}

PhysicsCube::~PhysicsCube()
{
	Cube::~Cube();
}

void PhysicsCube::update(float deltaTime)
{
	std::cout << "Updating Cube\n";
	Cube::update(deltaTime);
}

void PhysicsCube::draw(int width, int height)
{
	Cube::draw(width, height);
}