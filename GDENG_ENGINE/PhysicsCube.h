#pragma once
#include "Cube.h"

class PhysicsCube: public Cube
{
public:
	PhysicsCube(String name, void* shaderByteCode, size_t sizeShader);
	~PhysicsCube();

	void update(float deltaTime) override;
	void draw(int width, int height) override;

protected:
	float mass = 3.0f;
};

