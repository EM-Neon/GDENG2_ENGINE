#include "Cube.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "EngineTime.h"
#include "SceneCameraHandler.h"
#include "Vertex.h"

#include "SwapChain.h"

Cube::Cube(string name, void* shaderByteCode, size_t sizeShader): AGameObject(name)
{
	sceneCamera = SceneCameraHandler::getInstance()->getSceneCamera();

	Vertex::vertex vertex_list[] = 
	{
		//X, Y, Z
		//FRONT FACE
		{Vector3D(-0.5f,-0.5f,-0.5f),    Vector3D(1,1,1), Vector3D(1,1,1) },
		{Vector3D(-0.5f,0.5f,-0.5f),     Vector3D(1,1,1), Vector3D(1,1,1) },
		{Vector3D(0.5f,0.5f,-0.5f),      Vector3D(0,0,0), Vector3D(0,0,0) },
		{Vector3D(0.5f,-0.5f,-0.5f),     Vector3D(0,0,0), Vector3D(0,0,0) },

		//BACK FACE
		{Vector3D(0.5f,-0.5f,0.5f),      Vector3D(1,1,1), Vector3D(1,1,1) },
		{Vector3D(0.5f,0.5f,0.5f),       Vector3D(1,1,1), Vector3D(1,1,1) },
		{Vector3D(-0.5f,0.5f,0.5f),      Vector3D(0,0,0), Vector3D(0,0,0) },
		{Vector3D(-0.5f,-0.5f,0.5f),     Vector3D(0,0,0), Vector3D(0,0,0) },
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

	ib = GraphicsEngine::get()->createIndexBuffer();
	ib->load(index_list, ARRAYSIZE(index_list));

	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shaderByteCode, &sizeShader);
	vs = GraphicsEngine::get()->createVertexShader(shaderByteCode, sizeShader);

	vb = GraphicsEngine::get()->createVertexBuffer();
	vb->load(vertex_list, sizeof(Vertex::vertex), ARRAYSIZE(vertex_list), shaderByteCode, sizeShader);

	GraphicsEngine::get()->releaseCompiledShader();

	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shaderByteCode, &sizeShader);
	ps = GraphicsEngine::get()->createPixelShader(shaderByteCode, sizeShader);
	GraphicsEngine::get()->releaseCompiledShader();

	constant cc;
	cc.m_angle = 0;

	cb = GraphicsEngine::get()->createConstantBuffer();
	cb->load(&cc, sizeof(constant));
}

Cube::~Cube()
{
	this->vb->release();
	this->ib->release();
	this->cb->release();
	this->ps->release();
	this->vs->release();
	AGameObject::~AGameObject();
}

void Cube::update(float deltaTime)
{
	this->ticks += deltaTime;
	this->deltaTime = deltaTime;
}

void Cube::draw(int width, int height)
{
	if(ticks >= animationInterval)
	{
		isIncreasing = !isIncreasing;
		ticks = 0;
	}

	if(isIncreasing)
	{
		rotFactor += deltaTime;
	}
	else
	{
		rotFactor -= deltaTime;
	}

	GraphicsEngine* engine = GraphicsEngine::get();
	DeviceContext* device = GraphicsEngine::get()->getImmediateDeviceContext();

	constant cc;
	Matrix4x4 temp;
	temp.setIdentity();

	Matrix4x4 trans;
	trans.setIdentity();
	trans.setTranslation(this->getLocalPosition());

	Matrix4x4 scale;
	scale.setIdentity();
	scale.setScale(this->getLocalScale());

	Matrix4x4 x, y, z, rot;

	x.setIdentity();
	y.setIdentity();
	z.setIdentity();
	Vector3D rotation = this->getLocalRotation();

	x.setRotationZ(rotation.m_z);
	y.setRotationX(rotation.m_x);
	z.setRotationX(rotation.m_y);

	rot.setIdentity();

	rot *= x;
	rot *= y;
	rot *= z;

	temp *= scale;
	temp *= rot;
	temp *= trans;

	cc.m_world = temp;

	cc.m_view = SceneCameraHandler::getInstance()->getSceneCameraWorldCamMatrix();

	float aspec = (float)width / (float)height;
	sceneCamera = SceneCameraHandler::getInstance()->getSceneCamera();

	float fov = sceneCamera->getFOV();
	float asp = sceneCamera->getAspectRatio();
	float nz = sceneCamera->getNearZ();
	float fz = sceneCamera->getFarZ();

	cc.m_proj.setPerspectiveFovLH(fov, asp, nz, fz);

	cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);

	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(vs, cb);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(ps, cb);

	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(vs);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(ps);

	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(vb);
	GraphicsEngine::get()->getImmediateDeviceContext()->setIndexBuffer(ib);

	GraphicsEngine::get()->getImmediateDeviceContext()->drawIndexedTriangleList(ib->getSizeIndexList(), vb->getSizeVertexList(), 0, 0);

}

void Cube::setAnimation(float speed, float interval, bool isSpeeding, float rotFactor)
{
	this->rotFactor = rotFactor;
	this->speed = speed;
	this->animationInterval = interval;
	this->isIncreasing = isSpeeding;
}
