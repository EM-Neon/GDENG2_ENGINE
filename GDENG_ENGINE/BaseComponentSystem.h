#pragma once
#include <string>

class PhysicsSystem;
class BaseComponentSystem
{
public:
	typedef std::string String;

	static BaseComponentSystem* get();
	static void initialize();
	static void destroy();

	PhysicsSystem* getPhysics();

private:
	BaseComponentSystem();
	~BaseComponentSystem();
	BaseComponentSystem(BaseComponentSystem const&) {};	//copy constructor
	BaseComponentSystem& operator=(BaseComponentSystem const&) {}; //assignment operator
	static BaseComponentSystem* sharedInstance;

	PhysicsSystem* physicsSystem;
};

