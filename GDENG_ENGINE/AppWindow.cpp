#include "AppWindow.h"
#include <Windows.h>

#include "EngineTime.h"
#include "Vertex.h"

#include "Vector3D.h"
#include "Matrix4x4.h"

#include "InputSystem.h"

__declspec(align(16))
struct constant
{
	Matrix4x4 m_world;
	Matrix4x4 m_view;
	Matrix4x4 m_proj;
	float m_angle;
};

AppWindow::AppWindow()
{
}

void AppWindow::update()
{
	m_angle += EngineTime::getDeltaTime();
	constant cc;
	cc.m_angle = m_angle;

	m_delta_pos += EngineTime::getDeltaTime() / 5.0f;
	if (m_delta_pos > 1.0f)
		m_delta_pos = 0;

	Matrix4x4 temp;

	m_delta_scale += EngineTime::getDeltaTime() / 0.5f;

	//cc.m_world.setTranslation(Vector3D::lerp(Vector3D(-1.5,-1.5,0),Vector3D(1.5,1.5,0), m_delta_pos));
	//cc.m_world.setScale(Vector3D::lerp(Vector3D(0.5,0.5,0),Vector3D(2,2,0), (sin(m_delta_scale)+1.0f)/2.0f));

	//temp.setTranslation(Vector3D::lerp(Vector3D(-1.5, -1.5, 0), Vector3D(1.5, 1.5, 0), m_delta_pos));

	//cc.m_world *= temp;

	/*cc.m_world.setScale(Vector3D(m_scale_cube, m_scale_cube, m_scale_cube));

	temp.setIdentity();
	temp.setRotationZ(0.0f);
	cc.m_world *= temp;

	temp.setIdentity();
	temp.setRotationY(m_rot_y);
	cc.m_world *= temp;

	temp.setIdentity();
	temp.setRotationX(m_rot_x);
	cc.m_world *= temp;*/

	cc.m_world.setIdentity();

	Matrix4x4 world_cam;
	world_cam.setIdentity();

	temp.setIdentity();
	temp.setRotationX(m_rot_x);
	world_cam *= temp;

	temp.setIdentity();
	temp.setRotationY(m_rot_y);
	world_cam *= temp;

	Vector3D new_pos = m_world_cam.getTranslation() + world_cam.getZDirection() * (m_forward * 0.3f);

	new_pos = new_pos + world_cam.getXDirection() * (m_rightward * 0.3f);

	world_cam.setTranslation(new_pos);

	m_world_cam = world_cam;

	world_cam.inverse();


	cc.m_view = world_cam;
	/*cc.m_proj.setOrthoLH
	(
		(this->getClientWindowRect().right - this->getClientWindowRect().left)/400.0f,
		(this->getClientWindowRect().bottom - this->getClientWindowRect().top)/400.0f,
		-4.0f,
		4.0f
	);*/


	int width = (this->getClientWindowRect().right - this->getClientWindowRect().left);
	int height = (this->getClientWindowRect().bottom - this->getClientWindowRect().top);

	cc.m_proj.setPerspectiveFovLH(1.57f, ((float)width / (float)height), 0.1f, 100.0f);
	

	m_cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);
}


AppWindow::~AppWindow()
{
}

void AppWindow::onCreate()
{
	EngineTime::initialize();
	Window::onCreate();

	InputSystem::get()->addListener(this);
	InputSystem::get()->showCursor(false);

	GraphicsEngine::get()->init();
	m_swap_chain = GraphicsEngine::get()->createSwapChain();

	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	m_world_cam.setTranslation(Vector3D(0, 0, -2));

	Vertex::vertex vertex_list[] =
	{
		//X - Y - Z
		//FRONT FACE
		{Vector3D(-0.5f,-0.5f,-0.5f),Vector3D(1,0,0),	Vector3D(0,1,0)},
		{Vector3D(-0.5f,0.5f,-0.5f),  Vector3D(1,1,0),Vector3D(0,1,1)},
		{Vector3D(0.5f,0.5f, -0.5f),Vector3D(0,0,1), Vector3D(1,0,0)},
		{Vector3D(0.5f,-0.5f,-0.5f),Vector3D(1,1,1),Vector3D(0,1,1)},

		//BACK FACE
		{Vector3D(0.5,-0.5f,0.5f),Vector3D(1,0,0),	Vector3D(0,1,0)},
		{Vector3D(0.5f,0.5f,0.5f),  Vector3D(1,1,0),Vector3D(0,1,1)},
		{Vector3D(-0.5f,0.5f, 0.5f),Vector3D(0,0,1), Vector3D(1,0,0)},
		{Vector3D(-0.5f,-0.5f,0.5f),Vector3D(1,1,1),Vector3D(0,1,1)},
	};


	//165 521 -> 703 347
	//Vertex::vertex plane_list[] =
	//{
	//	//front face
	//	{Vector3D(-1.0f,-2.5f,-1.0f),Vector3D(1,1,1),	Vector3D(0,0,0)},
	//	{Vector3D(-1.0f,-0.5f,-1.0f),  Vector3D(1,1,1),Vector3D(0,0,0)},
	//	{Vector3D(1.0f,-0.5f, -1.0f),Vector3D(1,1,1), Vector3D(0,0,0)},
	//	{Vector3D(1.0f,-2.5f,-1.0f),Vector3D(1,1,1),Vector3D(0,0,0)},

	//	//back face
	//	{Vector3D(1.0f,-2.5f,1.0f),Vector3D(1,1,1),	Vector3D(0,0,0)},
	//	{Vector3D(1.0f,-0.5f,1.0f),  Vector3D(1,1,1),Vector3D(0,0,0)},
	//	{Vector3D(-1.0f,-0.5f, 1.0f),Vector3D(1,1,1), Vector3D(0,0,0)},
	//	{Vector3D(-1.0f,-2.5f,1.0f),Vector3D(1,1,1),Vector3D(0,0,0)},
	//};

	//quad.init(list[0], list[1], list[2], list[3]);

		//LINES

		//I
	//std::vector<Vertex::vertex> lineVect
	//{
	//	{Vector3D(-0.75f,-0.5f,0.0f), Vector3D(-0.125f,0.5f,0.0f),Vector3D(1,1,0),Vector3D(0,1,1)},	//POS1
	//	{Vector3D(- 0.5f,-0.5f,0.0f),Vector3D(-0.375f,0.5f,0.0f	),Vector3D(1,0,0),Vector3D(	0,1,0)},			//POS2
	//	{Vector3D(-0.5f,0.5f,0.0f	),Vector3D (-0.375f,-0.5f,0.0f	),Vector3D(0,0,0),Vector3D(	0,0,0)},
	//	{Vector3D (-0.25f	,0.5f,0.0f),Vector3D (-0.125f	,-0.5f,0.0f	), Vector3D(0,0,0),Vector3D(0,0,0)},
	//};

	//std::vector<Vertex::vertex> lineVect1
	//{
	//	{Vector3D (-0.75f	,0.5f	,0.0f	),Vector3D(0.0f,-0.5f,0.0f),Vector3D(1,1,0),Vector3D(	0,1,1)},	//POS1
	//	{Vector3D (-0.5f	,0.5f	,0.0f	),Vector3D(0.0f,0.5f,0.0f),Vector3D(1,0,0),Vector3D(	0,1,0)},			//POS2
	//	{Vector3D (-0.5f	,-0.5f,0.0f	),Vector3D(0.25f,0.5f,0.0f),Vector3D(0,0,0),Vector3D(	0,0,0)},
	//	{Vector3D (-0.25f	,-0.5f,0.0f	),Vector3D(0.0f,0.0f,0.0f),Vector3D(0,0,0),Vector3D(	0,0,0)},
	//	{Vector3D (-0.25f	,-0.5f,0.0f	),Vector3D(0.25f,-0.5f,0.0f),Vector3D(0,0,0),	Vector3D(0,0,0)},
	//	{Vector3D (-0.25f	,-0.5f,0.0f	),Vector3D(0.0f,-0.5f,0.0f),Vector3D(0,0,0),Vector3D(	0,0,0)},
	//};

	/*improvedLine.init(lineVect);
	improvedLine1.init(lineVect1);*/

	//A
/*std::vector<Vertex::vertex> lineVect2
{
	{Vector3D (-0.25f	,-0.5f	,0.0f),	Vector3D(0.625f	,0.5f		,0.0f),Vector3D(1,1,0),Vector3D(	0,1,0)},
	{Vector3D(0.0f	,0.5f	,0.0f),Vector3D	(0.625f	,-0.5f		,0.0f),Vector3D(1,1,0),	Vector3D(0,1,0)},
	{Vector3D(0.25f	,-0.5f	,0.0f),	Vector3D(0.375f	,-0.5f		,0.0f),Vector3D(1,1,0),	Vector3D(0,1,0)},
	{Vector3D(0.0f	,0.5f	,0.0f),	Vector3D(0.375f	,0.5f		,0.0f),Vector3D(1,1,0),	Vector3D(0,1,0)},
};*/

/*std::vector<Vertex::vertex> lineVect3
{
	{Vector3D (-0.125f, 0.0f, 0.0f), Vector3D (-0.125f, 0.0f, 0.0f), Vector3D(1,1,0), Vector3D(0,1,0)},
	{Vector3D(0.125f, 0.0f, 0.0f),  Vector3D (-0.375f, 0.0f, 0.0f), Vector3D(1,1,0), Vector3D(0,1,0)},
};*/

/*improvedLine2.init(lineVect2);
improvedLine3.init(lineVect3);*/

//N
/*std::vector<Vertex::vertex> lineVect4
{
	{Vector3D(0.25f	,-0.5f	,0.0f),	Vector3D (-0.5f		,0.5f		,0.0f),Vector3D(1,1,0),	Vector3D(0,1,0)},
	{Vector3D(0.25f	,0.5f	,0.0f),	Vector3D (-0.75f	,0.5f		,0.0f),Vector3D(1,1,0),	Vector3D(0,1,0)},
	{Vector3D(0.75f	,-0.5f	,0.0f),	Vector3D (-0.75f	,-0.5f	,0.0f),Vector3D(0,0,0),	Vector3D(0,0,0)},
	{Vector3D(0.75f	,0.5f	,0.0f),	Vector3D (-0.5f		,-0.5f	,0.0f),Vector3D(0,0,0),	Vector3D(0,0,0)},
};*/

/*improvedLine4.init(lineVect4);*/

	m_vb = GraphicsEngine::get()->createVertexBuffer();
	UINT size_list = ARRAYSIZE(vertex_list);

	/*m_vb2 = GraphicsEngine::get()->createVertexBuffer();
	UINT size_list1 = ARRAYSIZE(plane_list);*/

	unsigned int index_list[] =
	{
		//FRONT SIDE
		0,1,2,	//FIST TRIANGLE
		2,3,0,	//SECOND TRIANGLE
		//BACK SIDE
		4,5,6,
		6,7,4,
		//TOP SIDE
		1,6,5,
		5,2,1,
		//BOTTOM SIDE
		7,0,3,
		3,4,7,
		//RIGHT SIDE
		3,2,5,
		5,4,3,
		//LEFT SIDE
		7,6,1,
		1,0,7
	};

	/*unsigned int index_list1[] =
	{
		1,6,5,
		5,2,1
	};*/

	m_ib=GraphicsEngine::get()->createIndexBuffer();
	UINT size_index_list = ARRAYSIZE(index_list);

	m_ib->load(index_list, size_index_list);

	/*m_ib1 = GraphicsEngine::get()->createIndexBuffer();
	UINT size_index_list1 = ARRAYSIZE(index_list1);
	m_ib1->load(index_list1, size_index_list1);*/

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	m_vs=GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);

	m_vb->load(vertex_list, sizeof(Vertex::vertex), size_list, shader_byte_code, size_shader);
	/*m_vb2->load(plane_list, sizeof(Vertex::vertex), size_list1, shader_byte_code, size_shader);*/

	

	GraphicsEngine::get()->releaseCompiledShader();

	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->releaseCompiledShader();

	constant cc;
	cc.m_angle = 0;

	m_cb = GraphicsEngine::get()->createConstantBuffer();
	m_cb->load(&cc,sizeof(constant));
}

void AppWindow::onUpdate()
{
	Window::onUpdate();

	InputSystem::get()->update();

	//CLEAR THE RENDER TARGET 
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
		0, 0.3f,0.4f, 1);
	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	update();

	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);

	//SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(m_ps);


	/*GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb2);
	GraphicsEngine::get()->getImmediateDeviceContext()->setIndexBuffer(m_ib1);
	GraphicsEngine::get()->getImmediateDeviceContext()->drawIndexedTriangleList(m_ib1->getSizeIndexList(), m_vb2->getSizeVertexList(), 0, 0);*/

	//SET THE VERTICES OF THE TRIANGLE TO DRAW
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
	//SET THE INDICES OF THE TRIANGLE TO DRAW
	GraphicsEngine::get()->getImmediateDeviceContext()->setIndexBuffer(m_ib);

	// FINALLY DRAW THE TRIANGLE
	GraphicsEngine::get()->getImmediateDeviceContext()->drawIndexedTriangleList(m_ib->getSizeIndexList(), m_vb->getSizeVertexList(), 0, 0);


	
	/*improvedLine.draw();
	improvedLine1.draw();
	improvedLine2.draw();
	improvedLine3.draw();
	improvedLine4.draw();*/

	m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	m_swap_chain->release();
	GraphicsEngine::get()->release();

	if (m_vb != NULL)
		m_vb->release();
	if (m_ib != NULL)
		m_ib->release();
	if (m_cb != NULL)
		m_cb->release();
	if (m_vs != NULL)
		m_vs->release();
	if (m_ps != NULL)
		m_ps->release();

	quad.onDestroy();
	improvedLine.onDestroy();
	improvedLine1.onDestroy();
	improvedLine2.onDestroy();
	improvedLine3.onDestroy();
	improvedLine4.onDestroy();
}

void AppWindow::onFocus()
{
	InputSystem::get()->addListener(this);
}

void AppWindow::onKillFocus()
{
	InputSystem::get()->removeListener(this);
}

void AppWindow::onKeyDown(int key)
{
	if (key == 'W')
	{
		//m_rot_x += 0.707f * EngineTime::getDeltaTime();
		m_forward = 1.0f;
	}
	else if (key == 'S')
	{
		//m_rot_x -= 0.707f * EngineTime::getDeltaTime();
		m_forward = -1.0f;
	}
	else if (key == 'A')
	{
		//m_rot_y += 0.707f * EngineTime::getDeltaTime();
		m_rightward = -1.0f;
	}
	else if (key == 'D')
	{
		//m_rot_y -= 0.707f * EngineTime::getDeltaTime();
		m_rightward = 1.0f;
	}
}

void AppWindow::onKeyUp(int key)
{
	m_forward = 0.0f;
	m_rightward = 0.0f;
}

void AppWindow::onMouseMove(const Point& mouse_pos)
{
	int width = (this->getClientWindowRect().right - this->getClientWindowRect().left);
	int height = (this->getClientWindowRect().bottom - this->getClientWindowRect().top);

	m_rot_x += (mouse_pos.m_y-(height/2.0f)) * EngineTime::getDeltaTime() * 0.1f;
	m_rot_y += (mouse_pos.m_x-(width /2.0f)) * EngineTime::getDeltaTime() * 0.1f;

	InputSystem::get()->setCursorPosition(Point(width / 2.0f, height / 2.0f));
}

void AppWindow::onLeftMouseDown(const Point& delta_mouse_pos)
{
	m_scale_cube = 0.5;
}

void AppWindow::onLeftMouseUp(const Point& delta_mouse_pos)
{
	m_scale_cube = 1.0f;
}

void AppWindow::onRightMouseDown(const Point& delta_mouse_pos)
{
	m_scale_cube = 2.0f;
}

void AppWindow::onRightMouseUp(const Point& delta_mouse_pos)
{
	m_scale_cube = 1.0f;
}
