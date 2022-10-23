#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "ConstantBuffer.h"
#include "Quad.h"
#include "Line.h"
#include "ImprovedLine.h"
#include <vector>

class AppWindow: public Window
{
public:
	AppWindow();
	~AppWindow();

	// Inherited via Window
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;
private:
	SwapChain * m_swap_chain;
	VertexBuffer* m_vb;
	VertexBuffer* m_vb2;
	VertexBuffer* m_vb3;
	VertexShader* m_vs;
	PixelShader* m_ps;
	ConstantBuffer* m_cb;

private:
	unsigned long m_old_time = 0;
	float m_delta_time = 0;
	float m_angle = 0;

private:
	Quad quad;
	Quad quad1;
	Quad quad2;
	Line line;
	ImprovedLine improvedLine;
};

