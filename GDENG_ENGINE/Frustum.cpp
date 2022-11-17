#include "Frustum.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "EngineTime.h"
#include "SceneCameraHandler.h"
#include "Utils.h"

#include "SwapChain.h"
#include "Vertex.h"

Frustum::Frustum(std::string name, void* shaderByteCode, size_t sizeShader) :AGameObject(name)
{
	sceneCamera = SceneCameraHandler::getInstance()->getActiveCamera();


	//create buffers for drawing. Vertex data that needs to be drawn are temporarily placed here.
	Vertex::vertex fustrumList[] = {
		//X, Y, Z
		//FRONT FACE
		{Vector3D(-1.0f,-1.0f,-1.0f),     Vector3D(1,1,1), Vector3D(1,1,1) },
		{Vector3D(-1.0f,1.0f,-1.0f),      Vector3D(1,1,1), Vector3D(1,1,1) },
		{Vector3D(1.0f,1.0f,-1.0f),       Vector3D(1,1,1), Vector3D(1,1,1) },
		{Vector3D(1.0f,-1.0f,-1.0f),      Vector3D(1,1,1), Vector3D(1,1,1) },

		//BACK FACE
		{Vector3D(1.0f,-1.0f,1.0f),       Vector3D(1,1,1), Vector3D(1,1,1) },
		{Vector3D(1.0f,1.0f,1.0f),        Vector3D(1,1,1), Vector3D(1,1,1) },
		{Vector3D(-1.0f,1.0f,1.0f),       Vector3D(1,1,1), Vector3D(1,1,1) },
		{Vector3D(-1.0f,-1.0f,1.0f),      Vector3D(1,1,1), Vector3D(1,1,1) },
	};

	unsigned int index_list[] =
	{
		//FRONT SIDE
		0,1,2,  //FIRST TRIANGLE
		2,3,0,  //SECOND TRIANGLE
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

	// INDEX BUFFER
	ib = GraphicsEngine::get()->getRenderSystem()->createIndexBuffer(index_list, ARRAYSIZE(index_list));

	// VERTEX SHADER
	GraphicsEngine::get()->getRenderSystem()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shaderByteCode, &sizeShader);
	vs = GraphicsEngine::get()->getRenderSystem()->createVertexShader(shaderByteCode, sizeShader);

	// VERTEX BUFFER
	vb = GraphicsEngine::get()->getRenderSystem()->createVertexBuffer(fustrumList, sizeof(Vertex), ARRAYSIZE(fustrumList), shaderByteCode, sizeShader);

	GraphicsEngine::get()->getRenderSystem()->releaseCompiledShader();

	// PIXEL SHADER
	GraphicsEngine::get()->getRenderSystem()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shaderByteCode, &sizeShader);
	ps = GraphicsEngine::get()->getRenderSystem()->createPixelShader(shaderByteCode, sizeShader);
	GraphicsEngine::get()->getRenderSystem()->releaseCompiledShader();

	// CONSTANT BUFFER
	constant cc;
	cc.m_angle = 0;

	cb = GraphicsEngine::get()->getRenderSystem()->createConstantBuffer(&cc, sizeof(constant));
}

Frustum::~Frustum()
{
	AGameObject::~AGameObject();
}

void Frustum::update(float deltaTime)
{
	this->ticks += deltaTime;
	this->deltaTime = deltaTime;
}

void Frustum::draw(int width, int height)
{
	camera->getFOV();
	// setting up camera
	static float FOV = camera->getFOV();
	static float nearZ = camera->getNearZ();
	static float farZ = camera->getFarZ();

	float nearHeight = 2 * tan(FOV / 2) * nearZ;
	float farHeight = 2 * tan(FOV / 2) * (farZ - nearZ);
	float nearWidth = nearHeight * camera->getAspectRatio();
	float farWidth = farHeight * camera->getAspectRatio();

	Vector3D NBL = Vector3D(-(nearWidth * 0.5), (-nearHeight * 0.5), nearZ / 2);
	Vector3D NBR = Vector3D((nearWidth * 0.5), (-nearHeight * 0.5), nearZ / 2);
	Vector3D NTL = Vector3D((-nearWidth * 0.5), (nearHeight * 0.5), nearZ / 2);
	Vector3D NTR = Vector3D((nearWidth * 0.5), (nearHeight * 0.5), nearZ / 2);

	Vector3D FBL = Vector3D(-(farWidth * 0.5), (-farHeight * 0.5), (farZ - nearZ));
	Vector3D FBR = Vector3D((farWidth * 0.5), (-farHeight * 0.5), (farZ - nearZ));
	Vector3D FTL = Vector3D((-farWidth * 0.5), (farHeight * 0.5), (farZ - nearZ));
	Vector3D FTR = Vector3D((farWidth * 0.5), (farHeight * 0.5), (farZ - nearZ));


	//create buffers for drawing. Vertex data that needs to be drawn are temporarily placed here.
	Vertex::vertex frustumList[] = {
		//X, Y, Z
		//FRONT FACE
		{NBL, Vector3D(1,1,1), Vector3D(1,1,1) },//NBL
		{NTL, Vector3D(1,1,1), Vector3D(1,1,1) },//NTL
		{NTR, Vector3D(1,1,1), Vector3D(1,1,1) },//NTR
		{NBR, Vector3D(1,1,1), Vector3D(1,1,1) },//NBR

		//BACK FACE
		{FBR, Vector3D(1,1,1), Vector3D(1,1,1) },//FBR
		{FTR, Vector3D(1,1,1), Vector3D(1,1,1) },//FTR
		{FTL, Vector3D(1,1,1), Vector3D(1,1,1) },//FTL
		{FBL, Vector3D(1,1,1), Vector3D(1,1,1) },//FBL
	};

	unsigned int index_list[] =
	{
		//FRONT SIDE
		0,1,2,  //FIRST TRIANGLE
		2,3,0,  //SECOND TRIANGLE
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

	void* shaderByteCode = nullptr;
	size_t sizeShader = 0;

	// INDEX BUFFER
	ib = GraphicsEngine::get()->getRenderSystem()->createIndexBuffer(index_list, ARRAYSIZE(index_list));

	// VERTEX SHADER
	GraphicsEngine::get()->getRenderSystem()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shaderByteCode, &sizeShader);
	vs = GraphicsEngine::get()->getRenderSystem()->createVertexShader(shaderByteCode, sizeShader);

	// VERTEX BUFFER
	vb = GraphicsEngine::get()->getRenderSystem()->createVertexBuffer(frustumList, sizeof(Vertex::vertex), ARRAYSIZE(frustumList), shaderByteCode, sizeShader);

	GraphicsEngine::get()->getRenderSystem()->releaseCompiledShader();

	// PIXEL SHADER
	GraphicsEngine::get()->getRenderSystem()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shaderByteCode, &sizeShader);
	ps = GraphicsEngine::get()->getRenderSystem()->createPixelShader(shaderByteCode, sizeShader);
	GraphicsEngine::get()->getRenderSystem()->releaseCompiledShader();

	// CONSTANT BUFFER
	constant cc;
	cc.m_angle = 0;

	cb = GraphicsEngine::get()->getRenderSystem()->createConstantBuffer(&cc, sizeof(constant));


	GraphicsEngine* graphEngine = GraphicsEngine::get();
	DeviceContextPtr deviceContext = GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext();

	//Constant cc;
	Matrix4x4 temp;
	temp.setIdentity();


	float fov = camera->getFOV();
	float asp = camera->getAspectRatio();
	float zNear = camera->getNearZ();
	float zFar = camera->getFarZ();
	float zRange = zNear - zFar;
	float tanHalfFOV = tanf(camera->getFOV() / 2);

	cc.m_world.setIdentity();

	//TRANSLATION
	Matrix4x4 translationMatrix;
	translationMatrix.setIdentity();
	Vector3D pos = camera->getLocalPosition();
	translationMatrix.setTranslation(Vector3D(pos.m_x, pos.m_y, pos.m_z + (zNear / 2)));

	//SCALE
	Matrix4x4 scaleMatrix;
	scaleMatrix.setIdentity();
	//scaleMatrix.setScale(Vector3D(1.0f/(tanHalfFOV * asp), (1.0f/tanHalfFOV), (zFar-zNear)));

	//ROTATION
	Matrix4x4 xMatrix, yMatrix, zMatrix, rotMatrix;

	xMatrix.setIdentity();
	yMatrix.setIdentity();
	zMatrix.setIdentity();
	Vector3D rotation = camera->getLocalRotation();

	xMatrix.setRotationZ(rotation.m_z);
	yMatrix.setRotationX(rotation.m_x);
	zMatrix.setRotationY(rotation.m_y);

	rotMatrix.setIdentity();

	rotMatrix *= xMatrix;
	rotMatrix *= yMatrix;
	rotMatrix *= zMatrix;

	// APPLICATION
	//temp *= scaleMatrix;
	temp *= rotMatrix;
	temp *= translationMatrix;
	cc.m_world = temp;

	float fieldOfView = sceneCamera->getFOV();
	float aspectRatio = sceneCamera->getAspectRatio();
	float nz = sceneCamera->getNearZ();
	float fz = sceneCamera->getFarZ();

	if (SceneCameraHandler::getInstance()->getActiveCamera() != SceneCameraHandler::getInstance()->getCamera())
	{
		cc.m_world *= SceneCameraHandler::getInstance()->getCameraWorldCamMatrix();

		Matrix4x4 proj;
		proj.setPerspectiveFovLH(fieldOfView, aspectRatio, nz, fz);

		cc.m_world *= proj;
	}

	//CAMERA
	cc.m_view = SceneCameraHandler::getInstance()->getActiveCameraWorldCamMatrix();
	sceneCamera = SceneCameraHandler::getInstance()->getActiveCamera();
	//cc.projMatrix.setOrthoLH(width / 400.0f, height / 400.0f, -4.0f, 4.0f);
	cc.m_proj.setPerspectiveFovLH(sceneCamera->getFOV(), sceneCamera->getAspectRatio(), sceneCamera->getNearZ(), sceneCamera->getFarZ());
	cb->update(GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext(), &cc);

	// SET CONSTANT BUFFER
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(vs, cb);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(ps, cb);

	//SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setVertexShader(vs);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setPixelShader(ps);


	//SET THE VERTICES OF THE TRIANGLE TO DRAW
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setVertexBuffer(vb);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setIndexBuffer(ib);

	// FINALLY DRAW THE TRIANGLE
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->drawIndexedLineList(ib->getSizeIndexList(), vb->getSizeVertexList(), 0, 0);
}
