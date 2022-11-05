#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "InputListener.h"
#include "Matrix4x4.h"

#include "ConstantBuffer.h"
#include "Quad.h"
#include "Line.h"
#include "ImprovedLine.h"
#include <vector>


class AppWindow: public Window,public InputListener
{
public:
	AppWindow();

	void update();

	~AppWindow();

	// Inherited via Window
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;
	virtual void onFocus() override;
	virtual void onKillFocus() override;

	// Inherited via InputListener
	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;
	virtual void onMouseMove(const Point& mouse_pos) override;

	virtual void onLeftMouseDown(const Point& delta_mouse_pos) override;
	virtual void onLeftMouseUp(const Point& delta_mouse_pos) override;
	virtual void onRightMouseDown(const Point& delta_mouse_pos) override;
	virtual void onRightMouseUp(const Point& delta_mouse_pos) override;

private:
	SwapChain * m_swap_chain;
	VertexBuffer* m_vb;
	VertexBuffer* m_vb2;
	VertexBuffer* m_vb3;
	VertexShader* m_vs;
	PixelShader* m_ps;
	ConstantBuffer* m_cb;
	IndexBuffer* m_ib;
	IndexBuffer* m_ib1;

private:
	unsigned long m_old_time = 0;
	float m_delta_time = 0;
	float m_angle = 0;
	float m_delta_pos;
	float m_delta_scale;

	float m_rot_x = 0;
	float m_rot_y = 0;
	float m_scale_cube = 1;
	float m_forward = 0.0f;
	float m_rightward = 0.0f;

	Matrix4x4 m_world_cam;

private:
	Quad quad;
	ImprovedLine improvedLine;
	ImprovedLine improvedLine1;
	ImprovedLine improvedLine2;
	ImprovedLine improvedLine3;
	ImprovedLine improvedLine4;
};

