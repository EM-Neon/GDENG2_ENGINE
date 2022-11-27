#include "BaseComponentSystem.h"
#include "PhysicsSystem.h"

BaseComponentSystem* BaseComponentSystem::sharedInstance = NULL;
BaseComponentSystem* BaseComponentSystem::get()
{
	return sharedInstance;
}

void BaseComponentSystem::initialize()
{
	sharedInstance = new BaseComponentSystem();
}

void BaseComponentSystem::destroy()
{
	delete sharedInstance;
}

PhysicsSystem* BaseComponentSystem::getPhysics()
{
	return this->physicsSystem;
}

BaseComponentSystem::BaseComponentSystem()
{
	this->physicsSystem = new PhysicsSystem;
}

BaseComponentSystem::~BaseComponentSystem()
{
	delete this->physicsSystem;
}
