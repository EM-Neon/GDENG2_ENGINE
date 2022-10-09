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

#pragma once

class Line
{
public:
	Line();
	~Line();

public:
	void init(Vertex::vertex a, Vertex::vertex b);
	void draw();
	void onDestroy();

private:
	VertexBuffer* m_vb;
	VertexShader* m_vs;
	PixelShader* m_ps;
	ConstantBuffer* m_cb;

	Vertex::vertex line[2];
	float m_delta_time = 0;
	float m_angle = 0;

	float time = 1.57;
};

