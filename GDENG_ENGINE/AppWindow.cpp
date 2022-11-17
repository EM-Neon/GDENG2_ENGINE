#include "AppWindow.h"
#include <Windows.h>

#include "EngineTime.h"
#include "Vertex.h"

#include "Vector3D.h"
#include "Matrix4x4.h"

#include "Utils.h"
#include "InputSystem.h"
#include "SceneCameraHandler.h"

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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

}


AppWindow::~AppWindow()
{
}

void AppWindow::onCreate()
{
	EngineTime::initialize();
	Window::onCreate();
	
	SceneCameraHandler::initialize();
	InputSystem::get()->addListener(this);

	RECT rc = this->getClientWindowRect();
	m_swap_chain = GraphicsEngine::get()->getRenderSystem()->createSwapChain(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);


	//imgui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(m_hwnd);
	ImGui_ImplDX11_Init(GraphicsEngine::get()->getRenderSystem()->m_d3d_device, GraphicsEngine::get()->getRenderSystem()->m_imm_context);
	

	void* shaderByteCode = nullptr;
	size_t sizeShader = 0;

	cam = new Camera("Camera");
	sceneCam = new Camera("SceneCamera");

	float aspect = (float)(rc.right - rc.left) / (float)(rc.bottom - rc.top);
	static float nearZ = 1.0f;
	static float farZ = 50.0f;

	cam->setAspect(aspect);
	cam->setFOV(aspect);
	cam->setNearZ(nearZ);
	cam->setFarZ(farZ);

	sceneCam->setAspect(aspect);
	sceneCam->setFOV(aspect);
	sceneCam->setNearZ(1);
	sceneCam->setFarZ(100);


	SceneCameraHandler::getInstance()->SetCamera(cam);
	SceneCameraHandler::getInstance()->SetActiveCamera(sceneCam);

	/*frustum = new Frustum("Frustum", shaderByteCode, sizeShader);
	frustum->setPosition(0.0f, 0.0f, -3.0f);
	frustum->camera = cam;*/

	//1
	Cube* cube = new Cube("Card", shaderByteCode, sizeShader);
	cube->setPosition(0, 0, 0);
	cube->setScale(0.75, 0.001f, 1);
	cube->setRotation(1.25, 0, 0);
	object_lists.push_back(cube);

	//2
	cube = new Cube("Card", shaderByteCode, sizeShader);
	cube->setPosition(0, 0, -0.32);
	cube->setScale(0.75, 0.001f, 1);
	cube->setRotation(-1.25, 0, 0);
	object_lists.push_back(cube);

	//3
	cube = new Cube("Card", shaderByteCode, sizeShader);
	cube->setPosition(0, 0, -0.64);
	cube->setScale(0.75, 0.001f, 1);
	cube->setRotation(1.25, 0, 0);
	object_lists.push_back(cube);

	//4
	cube = new Cube("Card", shaderByteCode, sizeShader);
	cube->setPosition(0, 0, -0.64-0.32);
	cube->setScale(0.75, 0.001f, 1);
	cube->setRotation(-1.25, 0, 0);
	object_lists.push_back(cube);

	//5
	cube = new Cube("Card", shaderByteCode, sizeShader);
	cube->setPosition(0, 0, -0.64 - 0.32 -0.32);
	cube->setScale(0.75, 0.001f, 1);
	cube->setRotation(1.25, 0, 0);
	object_lists.push_back(cube);

	//6
	cube = new Cube("Card", shaderByteCode, sizeShader);
	cube->setPosition(0, 0, -0.64 - 0.32 - 0.32 - 0.32);
	cube->setScale(0.75, 0.001f, 1);
	cube->setRotation(-1.25, 0, 0);
	object_lists.push_back(cube);

	//7
	cube = new Cube("Card", shaderByteCode, sizeShader);
	cube->setPosition(0, 0.48, -0.48);
	cube->setScale(0.75, 0.001f, 1);
	cube->setRotation(0, 0, 0);
	object_lists.push_back(cube);

	//8
	cube = new Cube("Card", shaderByteCode, sizeShader);
	cube->setPosition(0, 0.48, -0.48 -0.6);
	cube->setScale(0.75, 0.001f, 1);
	cube->setRotation(0, 0, 0);
	object_lists.push_back(cube);

	//9
	cube = new Cube("Card", shaderByteCode, sizeShader);
	cube->setPosition(0, 0.96, -0.32);
	cube->setScale(0.75, 0.001f, 1);
	cube->setRotation(1.25, 0, 0);
	object_lists.push_back(cube);

	//10
	cube = new Cube("Card", shaderByteCode, sizeShader);
	cube->setPosition(0, 0.96, -0.32 -0.32);
	cube->setScale(0.75, 0.001f, 1);
	cube->setRotation(-1.25, 0, 0);
	object_lists.push_back(cube);

	//11
	cube = new Cube("Card", shaderByteCode, sizeShader);
	cube->setPosition(0, 0.96, -0.32 - 0.32 - 0.32);
	cube->setScale(0.75, 0.001f, 1);
	cube->setRotation(1.25, 0, 0);
	object_lists.push_back(cube);

	//12
	cube = new Cube("Card", shaderByteCode, sizeShader);
	cube->setPosition(0, 0.96, -0.32 - 0.32 - 0.32 - 0.32);
	cube->setScale(0.75, 0.001f, 1);
	cube->setRotation(-1.25, 0, 0);
	object_lists.push_back(cube);

	//13
	cube = new Cube("Card", shaderByteCode, sizeShader);
	cube->setPosition(0, 0.48 + 0.48 + 0.48, -0.78);
	cube->setScale(0.75, 0.001f, 1);
	cube->setRotation(0, 0, 0);
	object_lists.push_back(cube);

	//14
	cube = new Cube("Card", shaderByteCode, sizeShader);
	cube->setPosition(0, 0.96 + 0.96, -0.32-0.32);
	cube->setScale(0.75, 0.001f, 1);
	cube->setRotation(1.25, 0, 0);
	object_lists.push_back(cube);

	//15
	cube = new Cube("Card", shaderByteCode, sizeShader);
	cube->setPosition(0, 0.96 + 0.96, -0.32 - 0.32 -0.32);
	cube->setScale(0.75, 0.001f, 1);
	cube->setRotation(-1.25, 0, 0);
	object_lists.push_back(cube);

	int image_width = 0;
    int image_height = 0;
    unsigned char* image_data = stbi_load("DLSU_LOGO.png", &image_width, &image_height, NULL, 4);

    // Create texture
    D3D11_TEXTURE2D_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.Width = image_width;
    desc.Height = image_height;
    desc.MipLevels = 1;
    desc.ArraySize = 1;
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.SampleDesc.Count = 1;
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    desc.CPUAccessFlags = 0;

    ID3D11Texture2D* pTexture = NULL;
    D3D11_SUBRESOURCE_DATA subResource;
    subResource.pSysMem = image_data;
    subResource.SysMemPitch = desc.Width * 4;
    subResource.SysMemSlicePitch = 0;
    GraphicsEngine::get()->getRenderSystem()->m_d3d_device->CreateTexture2D(&desc, &subResource, &pTexture);

    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
    ZeroMemory(&srvDesc, sizeof(srvDesc));
    srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Texture2D.MipLevels = desc.MipLevels;
    srvDesc.Texture2D.MostDetailedMip = 0;
    GraphicsEngine::get()->getRenderSystem()->m_d3d_device->CreateShaderResourceView(pTexture, &srvDesc, &texture);
    pTexture->Release();

	/*cube = new Cube("Cube", shaderByteCode, sizeShader);
	cube->setPosition(0, 0, 0);
	cube->setScale(1, 1, 1);

	cube2 = new Cube("Cube2", shaderByteCode, sizeShader);
	cube2->setPosition(1, 1, 1);
	cube2->setScale(1, 1, 1);*/


//	m_world_cam.setTranslation(Vector3D(0, 0, -2));
//
//	Vertex::vertex vertex_list[] =
//	{
//		//X - Y - Z
//		//FRONT FACE
//		{Vector3D(-0.5f,-0.5f,-0.5f),Vector3D(1,0,0),	Vector3D(0,0,1)},
//		{Vector3D(-0.5f,0.5f,-0.5f),  Vector3D(1,1,0),Vector3D(0,1,1)},
//		{Vector3D(0.5f,0.5f, -0.5f),Vector3D(0,1,1), Vector3D(1,1,0)},
//		{Vector3D(0.5f,-0.5f,-0.5f),Vector3D(0,0,1),Vector3D(1,0,0)},
//
//		//BACK FACE
//		{Vector3D(0.5,-0.5f,0.5f),Vector3D(0,0,1),	Vector3D(1,0,0)},
//		{Vector3D(0.5f,0.5f,0.5f),  Vector3D(0,1,1),Vector3D(1,1,0)},
//		{Vector3D(-0.5f,0.5f, 0.5f),Vector3D(1,1,0), Vector3D(0,1,1)},
//		{Vector3D(-0.5f,-0.5f,0.5f),Vector3D(1,0,0),Vector3D(0,0,1)},
//	};
//
//	//Vertex::vertex plane_list[] =
//	//{
//	//	//front face
//	//	{Vector3D(-1.0f,-2.5f,-1.0f),Vector3D(1,1,1),	Vector3D(0,0,0)},
//	//	{Vector3D(-1.0f,-0.5f,-1.0f),  Vector3D(1,1,1),Vector3D(0,0,0)},
//	//	{Vector3D(1.0f,-0.5f, -1.0f),Vector3D(1,1,1), Vector3D(0,0,0)},
//	//	{Vector3D(1.0f,-2.5f,-1.0f),Vector3D(1,1,1),Vector3D(0,0,0)},
//
//	//	//back face
//	//	{Vector3D(1.0f,-2.5f,1.0f),Vector3D(1,1,1),	Vector3D(0,0,0)},
//	//	{Vector3D(1.0f,-0.5f,1.0f),  Vector3D(1,1,1),Vector3D(0,0,0)},
//	//	{Vector3D(-1.0f,-0.5f, 1.0f),Vector3D(1,1,1), Vector3D(0,0,0)},
//	//	{Vector3D(-1.0f,-2.5f,1.0f),Vector3D(1,1,1),Vector3D(0,0,0)},
//	//};
//
//	//quad.init(list[0], list[1], list[2], list[3]);
//
//		//LINES
//
//		//I
//	//std::vector<Vertex::vertex> lineVect
//	//{
//	//	{Vector3D(-0.75f,-0.5f,0.0f), Vector3D(-0.125f,0.5f,0.0f),Vector3D(1,1,0),Vector3D(0,1,1)},	//POS1
//	//	{Vector3D(- 0.5f,-0.5f,0.0f),Vector3D(-0.375f,0.5f,0.0f	),Vector3D(1,0,0),Vector3D(	0,1,0)},			//POS2
//	//	{Vector3D(-0.5f,0.5f,0.0f	),Vector3D (-0.375f,-0.5f,0.0f	),Vector3D(0,0,0),Vector3D(	0,0,0)},
//	//	{Vector3D (-0.25f	,0.5f,0.0f),Vector3D (-0.125f	,-0.5f,0.0f	), Vector3D(0,0,0),Vector3D(0,0,0)},
//	//};
//
//	//std::vector<Vertex::vertex> lineVect1
//	//{
//	//	{Vector3D (-0.75f	,0.5f	,0.0f	),Vector3D(0.0f,-0.5f,0.0f),Vector3D(1,1,0),Vector3D(	0,1,1)},	//POS1
//	//	{Vector3D (-0.5f	,0.5f	,0.0f	),Vector3D(0.0f,0.5f,0.0f),Vector3D(1,0,0),Vector3D(	0,1,0)},			//POS2
//	//	{Vector3D (-0.5f	,-0.5f,0.0f	),Vector3D(0.25f,0.5f,0.0f),Vector3D(0,0,0),Vector3D(	0,0,0)},
//	//	{Vector3D (-0.25f	,-0.5f,0.0f	),Vector3D(0.0f,0.0f,0.0f),Vector3D(0,0,0),Vector3D(	0,0,0)},
//	//	{Vector3D (-0.25f	,-0.5f,0.0f	),Vector3D(0.25f,-0.5f,0.0f),Vector3D(0,0,0),	Vector3D(0,0,0)},
//	//	{Vector3D (-0.25f	,-0.5f,0.0f	),Vector3D(0.0f,-0.5f,0.0f),Vector3D(0,0,0),Vector3D(	0,0,0)},
//	//};
//
//	/*improvedLine.init(lineVect);
//	improvedLine1.init(lineVect1);*/
//
//	//A
///*std::vector<Vertex::vertex> lineVect2
//{
//	{Vector3D (-0.25f	,-0.5f	,0.0f),	Vector3D(0.625f	,0.5f		,0.0f),Vector3D(1,1,0),Vector3D(	0,1,0)},
//	{Vector3D(0.0f	,0.5f	,0.0f),Vector3D	(0.625f	,-0.5f		,0.0f),Vector3D(1,1,0),	Vector3D(0,1,0)},
//	{Vector3D(0.25f	,-0.5f	,0.0f),	Vector3D(0.375f	,-0.5f		,0.0f),Vector3D(1,1,0),	Vector3D(0,1,0)},
//	{Vector3D(0.0f	,0.5f	,0.0f),	Vector3D(0.375f	,0.5f		,0.0f),Vector3D(1,1,0),	Vector3D(0,1,0)},
//};*/
//
///*std::vector<Vertex::vertex> lineVect3
//{
//	{Vector3D (-0.125f, 0.0f, 0.0f), Vector3D (-0.125f, 0.0f, 0.0f), Vector3D(1,1,0), Vector3D(0,1,0)},
//	{Vector3D(0.125f, 0.0f, 0.0f),  Vector3D (-0.375f, 0.0f, 0.0f), Vector3D(1,1,0), Vector3D(0,1,0)},
//};*/
//
///*improvedLine2.init(lineVect2);
//improvedLine3.init(lineVect3);*/
//
////N
///*std::vector<Vertex::vertex> lineVect4
//{
//	{Vector3D(0.25f	,-0.5f	,0.0f),	Vector3D (-0.5f		,0.5f		,0.0f),Vector3D(1,1,0),	Vector3D(0,1,0)},
//	{Vector3D(0.25f	,0.5f	,0.0f),	Vector3D (-0.75f	,0.5f		,0.0f),Vector3D(1,1,0),	Vector3D(0,1,0)},
//	{Vector3D(0.75f	,-0.5f	,0.0f),	Vector3D (-0.75f	,-0.5f	,0.0f),Vector3D(0,0,0),	Vector3D(0,0,0)},
//	{Vector3D(0.75f	,0.5f	,0.0f),	Vector3D (-0.5f		,-0.5f	,0.0f),Vector3D(0,0,0),	Vector3D(0,0,0)},
//};*/
//
///*improvedLine4.init(lineVect4);*/
//
//	m_vb = GraphicsEngine::get()->createVertexBuffer();
//	UINT size_list = ARRAYSIZE(vertex_list);
//
//	/*m_vb2 = GraphicsEngine::get()->createVertexBuffer();
//	UINT size_list1 = ARRAYSIZE(plane_list);*/
//
//	unsigned int index_list[] =
//	{
//		//FRONT SIDE
//		0,1,2,	//FIST TRIANGLE
//		2,3,0,	//SECOND TRIANGLE
//		//BACK SIDE
//		4,5,6,
//		6,7,4,
//		//TOP SIDE
//		1,6,5,
//		5,2,1,
//		//BOTTOM SIDE
//		7,0,3,
//		3,4,7,
//		//RIGHT SIDE
//		3,2,5,
//		5,4,3,
//		//LEFT SIDE
//		7,6,1,
//		1,0,7
//	};
//
//	/*unsigned int index_list1[] =
//	{
//		1,6,5,
//		5,2,1
//	};*/
//
//	m_ib=GraphicsEngine::get()->createIndexBuffer();
//	UINT size_index_list = ARRAYSIZE(index_list);
//
//	m_ib->load(index_list, size_index_list);
//
//	/*m_ib1 = GraphicsEngine::get()->createIndexBuffer();
//	UINT size_index_list1 = ARRAYSIZE(index_list1);
//	m_ib1->load(index_list1, size_index_list1);*/
//
//	void* shader_byte_code = nullptr;
//	size_t size_shader = 0;
//	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
//
//	m_vs=GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);
//
//	m_vb->load(vertex_list, sizeof(Vertex::vertex), size_list, shader_byte_code, size_shader);
//	/*m_vb2->load(plane_list, sizeof(Vertex::vertex), size_list1, shader_byte_code, size_shader);*/
//
//	
//
//	GraphicsEngine::get()->releaseCompiledShader();
//
//	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
//	m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);
//	GraphicsEngine::get()->releaseCompiledShader();
//
//	constant cc;
//	cc.m_angle = 0;
//
//	m_cb = GraphicsEngine::get()->createConstantBuffer();
//	m_cb->load(&cc,sizeof(constant));
}

void AppWindow::onUpdate()
{
	Window::onUpdate();

	InputSystem::get()->update();

	//CLEAR THE RENDER TARGET 
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
		0, 0.3f,0.4f, 1);
	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	RECT rc = this->getClientWindowRect();

	float width = rc.right - rc.left;
	float height = rc.bottom - rc.top;

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setViewportSize(width, height);

	SceneCameraHandler::getInstance()->update();

	Vector3D camPos = cam->getLocalPosition();
	Vector3D camRot = cam->getLocalRotation();

	

	/*frustum->update(EngineTime::getDeltaTime());

	if (!isUsingCameraObj)
		frustum->draw(rc.right - rc.left, rc.bottom - rc.top);*/

	for (int i = 0; i < object_lists.size(); i++)
	{
		object_lists[i]->update(EngineTime::getDeltaTime());
		object_lists[i]->draw(width, height);
	}

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();


	// Draw UI Here
	static bool isCredits = false;
	static bool isColor = false;

	ImGui::BeginMainMenuBar();
	if (ImGui::BeginMenu("About"))
	{
		if (ImGui::MenuItem("Credits"))
		{
			isCredits = true;
		}
		ImGui::EndMenu();
	}
	if (ImGui::MenuItem("ColorPicker"))
	{
		isColor = true;
	}

	ImGui::EndMainMenuBar();

	if(isCredits)
	{
		ImGui::Begin("Credits", &isCredits);
		ImGui::Image((void*)texture, { 300, 300 });
		ImGui::Text("Made by: Ian Joshua Nemeno");
		ImGui::Text("Submitted for: Sir Neil Del Gallego");
		ImGui::Text("References: PardCode");
		ImGui::End();
	}

	
	static float* col = new float[3] {0, 0, 0};
	if(isColor)
	{
		ImGui::Begin("Pick-A-Color", &isColor);
		ImGuiColorEditFlags flags;
		flags = ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoInputs;

		ImGui::ColorPicker4("Color", col, flags);
		ImGui::End();
	}

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	//GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	//GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);

	////SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	//GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(m_vs);
	//GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(m_ps);


	///*GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb2);
	//GraphicsEngine::get()->getImmediateDeviceContext()->setIndexBuffer(m_ib1);
	//GraphicsEngine::get()->getImmediateDeviceContext()->drawIndexedTriangleList(m_ib1->getSizeIndexList(), m_vb2->getSizeVertexList(), 0, 0);*/

	////SET THE VERTICES OF THE TRIANGLE TO DRAW
	//GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
	////SET THE INDICES OF THE TRIANGLE TO DRAW
	//GraphicsEngine::get()->getImmediateDeviceContext()->setIndexBuffer(m_ib);

	//// FINALLY DRAW THE TRIANGLE
	//GraphicsEngine::get()->getImmediateDeviceContext()->drawIndexedTriangleList(m_ib->getSizeIndexList(), m_vb->getSizeVertexList(), 0, 0);


	//
	///*improvedLine.draw();
	//improvedLine1.draw();
	//improvedLine2.draw();
	//improvedLine3.draw();
	//improvedLine4.draw();*/

	m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
}

void AppWindow::onFocus()
{
	//InputSystem::get()->addListener(this);
}

void AppWindow::onKillFocus()
{
	//InputSystem::get()->removeListener(this);
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
	else if (key == 9)
	{
		isUsingCameraObj = !isUsingCameraObj;

		if(isUsingCameraObj)
		{
			SceneCameraHandler::getInstance()->SetActiveCamera(cam);
		}
		else if(!isUsingCameraObj)
		{
			SceneCameraHandler::getInstance()->SetActiveCamera(sceneCam);
		}
	}
}

void AppWindow::onKeyUp(int key)
{
	/*m_forward = 0.0f;
	m_rightward = 0.0f;*/
}

void AppWindow::onMouseMove(const Point mouse_pos)
{
	/*int width = (this->getClientWindowRect().right - this->getClientWindowRect().left);
	int height = (this->getClientWindowRect().bottom - this->getClientWindowRect().top);

	m_rot_x += (mouse_pos.m_y-(height/2.0f)) * EngineTime::getDeltaTime() * 0.1f;
	m_rot_y += (mouse_pos.m_x-(width /2.0f)) * EngineTime::getDeltaTime() * 0.1f;

	InputSystem::get()->setCursorPosition(Point(width / 2.0f, height / 2.0f));*/
}

void AppWindow::onLeftMouseDown(const Point delta_mouse_pos)
{
	m_scale_cube = 0.5;
}

void AppWindow::onLeftMouseUp(const Point delta_mouse_pos)
{
	m_scale_cube = 1.0f;
}

void AppWindow::onRightMouseDown(const Point delta_mouse_pos)
{
	m_scale_cube = 2.0f;
}

void AppWindow::onRightMouseUp(const Point delta_mouse_pos)
{
	m_scale_cube = 1.0f;
}
