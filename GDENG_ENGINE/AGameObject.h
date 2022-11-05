#pragma once
#include <string>
#include "Vector3D.h"
#include "Matrix4x4.h"
#include "Vertex.h"

using namespace std;

class VertexShader;
class PixelShader;
class AGameObject
{
public:
	AGameObject(string name);
	~AGameObject();

	virtual void update(float deltaTime);
	virtual void draw(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader);

	void setPosition(float x, float y, float z);
	void setPosition(Vector3D pos);
	Vector3D getLocalPosition();

	void setScale(float x, float y, float z);
	void setScale(Vector3D scale);
	Vector3D getLocalScale();

	void setRotation(float x, float y, float z);
	void setRotation(Vector3D rot);
	Vector3D getLocalRotation();

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
	Vector3D localScale;
	Vector3D localRotation;
	Matrix4x4 localMatrix;
};

