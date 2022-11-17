#pragma once
#include <string>

#include "AGameObject.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"

#include "VertexShader.h"
#include "PixelShader.h"
#include "Camera.h"

class Frustum : public AGameObject
{
public:
	Frustum(std::string name, void* shaderByteCode, size_t sizeShader);
	~Frustum();

	void update(float deltaTime) override;
	void draw(int width, int height) override;

	float m_scale = 1;
	float m_forward = 0.0f;
	float m_rightward = 0.0f;

	Camera* camera;

private:
	VertexBufferPtr vb;
	IndexBufferPtr ib;
	ConstantBufferPtr cb;

	VertexShaderPtr vs;
	PixelShaderPtr ps;

	float ticks = 0.0f;
	float deltaPos = 0.0f;
	float deltaTime = 0.0f;
	float speed = 1.0f;

	Camera* sceneCamera;

	Matrix4x4 m_world_cam;
	Matrix4x4 world_cam;
};
