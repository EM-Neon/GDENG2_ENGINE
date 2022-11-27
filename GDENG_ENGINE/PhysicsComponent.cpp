#include "PhysicsComponent.h"
#include <iostream>
#include "BaseComponentSystem.h"
#include "PhysicsSystem.h"
#include "Vector3D.h"
#include "AComponent.h"
#include "AGameObject.h"

PhysicsComponent::PhysicsComponent(String name, AGameObject* owner): AComponent(name, AComponent::ComponentType::Physics, owner)
{
	//Whenever a new phsyics component is initialized. Register to physics system
	BaseComponentSystem::get()->getPhysics()->registerComponent(this);
	PhysicsCommon* physicCommon = BaseComponentSystem::get()->getPhysics()->getPhysicsCommon();
	PhysicsWorld* physicsWorld = BaseComponentSystem::get()->getPhysics()->getPhysicsWorld();

	//create a rigid body in the world;
	Vector3D scale = this->getOwner()->getLocalScale();
	Transform transform; transform.setFromOpenGL(this->getOwner()->getPhysicsLocalMatrix());
	BoxShape* boxShape = physicCommon->createBoxShape(Vector3(scale.m_x / 2, scale.m_y / 2, scale.m_z / 2)); //half extent.
	this->rigidBody = physicsWorld->createRigidBody(transform);
	this->rigidBody->addCollider(boxShape, transform);
	this->rigidBody->updateMassPropertiesFromColliders();
	this->rigidBody->setMass(this->mass);
	this->rigidBody->setType(BodyType::DYNAMIC);

	transform = this->rigidBody->getTransform();
	float matrix[16];
	transform.getOpenGLMatrix(matrix);

	this->getOwner()->recomputeMatrix(matrix);
}

PhysicsComponent::~PhysicsComponent()
{
	AComponent::~AComponent();
	BaseComponentSystem::get()->getPhysics()->unregisterComponent(this);
}

void PhysicsComponent::perform(float deltaTime)
{
	std::cout << "Updating Component\n";
	const Transform transform = this->rigidBody->getTransform();
	float matrix[16];
	transform.getOpenGLMatrix(matrix);

	this->getOwner()->recomputeMatrix(matrix);
}

RigidBody* PhysicsComponent::getRigidBody()
{
	return this->rigidBody;
}
