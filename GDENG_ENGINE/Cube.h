#pragma once
#include "AGameObject.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"

#include "VertexShader.h"
#include "PixelShader.h"
#include "Camera.h"

class Cube: public AGameObject
{
public:
	Cube(std::string name, void* shaderByteCode, size_t sizeShader);
	~Cube();

	void update(float deltaTime) override;
	void draw(int width, int height) override;
	void setAnimation(float speed, float interval, bool isSpeeding, float rotFactor);

	float m_scale_cube = 1;
	float m_forward = 0.0f;
	float m_rightward = 0.0f;

private:
	VertexBufferPtr vb;
	IndexBufferPtr ib;
	ConstantBufferPtr cb;

	VertexShaderPtr vs;
	PixelShaderPtr ps;

	TexturePtr m_wood_tex;

	float ticks = 0;
	float deltaPos = 0;
	float deltaTime = 0;
	float speed = 1.0f;

	Camera* sceneCamera;

	Matrix4x4 m_world_cam;
	Matrix4x4 world_cam;

	bool isIncreasing = false;
	float rotFactor = 0;
	float animationInterval = 0;
};

