#include "AppWindow.h"
#include <Windows.h>

#include "EngineTime.h"
#include "Vertex.h"

//__declspec(align(16))
//struct constant
//{
//	float m_angle;
//};

AppWindow::AppWindow()
{
}


AppWindow::~AppWindow()
{
}

void AppWindow::onCreate()
{
	EngineTime::initialize();
	Window::onCreate();
	GraphicsEngine::get()->init();
	m_swap_chain=GraphicsEngine::get()->createSwapChain();

	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	Vertex::vertex list[] = 
	{
		//X - Y - Z
		{-0.9f,0.f,0.0f,		-0.9f, 0.f, 0.0f,		1,1,1,		0,0,0},	// POS1
		{-0.5f,0.f,0.0f,		-0.5f, 0.f, 0.0f,		1,1,1,		0,0,0},	// POS2
		{-0.5f,0.4f, 0.0f,	-0.5f, 0.4f,0.0f,		1,1,1,		0,0,0},
		{-0.9f,0.4f,0.0f,	-0.9f, 0.4f,0.0f,		1,1,1,		0,0,0}	// POS2
	};

	quad.init(list[0], list[1], list[2], list[3]);

	Vertex::vertex list1[] =
	{
		{-0.75f,-0.7f,0.0f,		-0.5f,0.8f,0.0f,		1,0,0,		0,1,0},	// POS1
		{-0.5f,0.8f,0.0f,	0.9f,0.3f, 0.0f,		1,1,0,		0,1,1},	// POS2
		{0.35f,-0.6f,0.0f,		-0.75f, -0.7f,0.0f,		0,0,1,		1,0,0},	// POS2
		{0.9f,0.3f, 0.0f,	0.0f,0.0f,0.0f,		1,1,1,		0,1,1}	// 0.2f, 0.4f,0.0f
	};

	quad1.init(list1[0], list1[1], list1[2], list1[3]);

	Vertex::vertex list2[] =
	{
		{0.5f,0.0f,0.0f,		0.5f,0.f,0.0f,			0,0,0,		0,1,0},	// POS1
		{0.5f,0.4f,0.0f,		0.5f,0.4f,0.0f,		1,1,1,		0,1,1},	// POS2
		{0.9f,0.f,0.0f,		0.9f, 0.f,0.0f,		0,0,1,		1,0,0},	// POS2
		{0.9f,0.4f, 0.0f,	0.9f, 0.4f,0.0f,		1,1,1,		1,0,1}	// 0.9f, 0.4f,0.0f
	};

	quad2.init(list2[0], list2[1], list2[2], list2[3]);

	Vertex::vertex line_list[] =
	{
		{-0.75f,-0.7f,0.0f,		-0.5f,0.8f,0.0f,		1,1,0,		0,1,1},
		{-0.5f,0.8f,0.0f,	0.9f,0.3f, 0.0f,		1,0,0,		0,1,0}
	};

	line.init(line_list[0], line_list[1]);

	//m_vb=GraphicsEngine::get()->createVertexBuffer();
	////m_vb2=GraphicsEngine::get()->createVertexBuffer();
	////m_vb3=GraphicsEngine::get()->createVertexBuffer();
	//UINT size_list = ARRAYSIZE(quad);

	///*UINT size2_list = ARRAYSIZE(list2);
	//UINT size3_list = ARRAYSIZE(list3);*/

	//void* shader_byte_code = nullptr;
	//size_t size_shader = 0;
	//GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	//m_vs=GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);

	//m_vb->load(quad, sizeof(Vertex::vertex), size_list, shader_byte_code, size_shader);
	///*m_vb2->load(list2, sizeof(vertex), size2_list, shader_byte_code, size_shader);
	//m_vb3->load(list3, sizeof(vertex), size3_list, shader_byte_code, size_shader);*/

	//GraphicsEngine::get()->releaseCompiledShader();

	//GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	//m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);
	//GraphicsEngine::get()->releaseCompiledShader();

	//constant cc;
	//cc.m_angle = 0;

	//m_cb = GraphicsEngine::get()->createConstantBuffer();
	//m_cb->load(&cc,sizeof(constant));

	// JUST RANDOM THING I FOUND
	/*int width = 1920;
	int height = 1080;

	HWND handle = ::FindWindow(NULL, ("DirectX Application"));

	::SetWindowPos(handle, 0, 0, 0, width, height, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);*/
}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	//CLEAR THE RENDER TARGET 
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
		0, 0.3f,0.4f, 1);
	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);



	/*constant cc;
	cc.m_angle = ::GetTickCount();*/

	//unsigned long new_time = 0;
	//if (m_old_time)
	//	new_time = ::GetTickCount() - m_old_time;
	//m_delta_time = new_time / 1000.0f;
	//m_old_time = ::GetTickCount();
	//m_angle += 1.57 * m_delta_time;
	//constant cc;
	//cc.m_angle = m_angle;

	//m_cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);

	//GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	//GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);

	////SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	//GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(m_vs);
	//GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(m_ps);

	////SET THE VERTICES OF THE TRIANGLE TO DRAW
	//GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);

	//// FINALLY DRAW THE TRIANGLE
	//GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(m_vb->getSizeVertexList(), 0);

	//GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb2);

	// FINALLY DRAW THE TRIANGLE
	//GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleList(m_vb2->getSizeVertexList(), 0);

	//GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb3);

	// FINALLY DRAW THE TRIANGLE
	//GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(m_vb3->getSizeVertexList(), 0);

	//quad.draw();
	quad1.draw();
	//quad2.draw();

	line.draw();

	m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	m_swap_chain->release();
	GraphicsEngine::get()->release();
	quad.onDestroy();
	quad1.onDestroy();
	quad2.onDestroy();
}
