#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "ConstantBuffer.h"
#include "Vertex.h"
#include "EngineTime.h"
#include <vector>

#pragma once

class ImprovedLine
{
public:
	ImprovedLine();
	~ImprovedLine();

public:
	void init(std::vector<Vertex::vertex> vertices);
	void draw();
	void onDestroy();

private:
	VertexBuffer* m_vb;
	VertexShader* m_vs;
	PixelShader* m_ps;
	ConstantBuffer* m_cb;

	std::vector<Vertex::vertex> vertexVect;
	Vertex::vertex vertexArr[2];
	float m_delta_time = 0;
	float m_angle = 0;

	float time = 1.57;
};