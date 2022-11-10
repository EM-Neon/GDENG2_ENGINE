#pragma once
#include <string>
#include "Vector3D.h"
#include "Matrix4x4.h"

using namespace std;

class VertexShader;
class PixelShader;
class AGameObject
{
public:
	AGameObject(string name);
	~AGameObject();

	virtual void update(float deltaTime) = 0;
	virtual void draw(int width, int height) = 0;

	void setPosition(float x, float y, float z);
	void setPosition(Vector3D pos);

	void setRotation(float x, float y, float z);
	void setRotation(Vector3D rot);

	void setScale(float x, float y, float z);
	void setScale(Vector3D scale);

	Vector3D getLocalPosition();
	Vector3D getLocalRotation();
	Vector3D getLocalScale();

	string getName();

	__declspec(align(16))
	struct constant
	{
		Matrix4x4 m_world;
		Matrix4x4 m_view;
		Matrix4x4 m_proj;

		float m_angle;
	};

protected:
	string name;
	Vector3D localPosition;
	Vector3D localRotation;
	Vector3D localScale;
	Matrix4x4 localMatrix;
};

