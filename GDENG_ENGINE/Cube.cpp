#include "Cube.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "EngineTime.h"
#include "SceneCameraHandler.h"
#include "Vertex.h"

#include "SwapChain.h"

Cube::Cube(std::string name, void* shaderByteCode, size_t sizeShader): AGameObject(name)
{
	sceneCamera = SceneCameraHandler::getInstance()->getActiveCamera();

	Vector3D position_list[] =
	{
		//X, Y, Z
		//FRONT FACE
		{Vector3D(-0.5f,-0.5f,-0.5f)},
		{Vector3D(-0.5f,0.5f,-0.5f)},
		{Vector3D(0.5f,0.5f,-0.5f)},
		{Vector3D(0.5f,-0.5f,-0.5f)},

		//BACK FACE
		{Vector3D(0.5f,-0.5f,0.5f)},
		{Vector3D(0.5f,0.5f,0.5f)},
		{Vector3D(-0.5f,0.5f,0.5f)},
		{Vector3D(-0.5f,-0.5f,0.5f)},
	};

	Vector2D texcoord_list[] =
	{
		//X, Y, Z
		//FRONT FACE
		{Vector2D(0,0)},
		{Vector2D(0,1)},
		{Vector2D(1,0)},
		{Vector2D(1,1)},
	};

	Vertex::vertex vertex_list[] = 
	{
		{position_list[0], texcoord_list[1]},
		{position_list[1], texcoord_list[0]},
		{position_list[2], texcoord_list[2]},
		{position_list[3], texcoord_list[3]},

		{position_list[4], texcoord_list[1]},
		{position_list[5], texcoord_list[0]},
		{position_list[6], texcoord_list[2]},
		{position_list[7], texcoord_list[3]},

		{position_list[1], texcoord_list[1]},
		{position_list[6], texcoord_list[0]},
		{position_list[5], texcoord_list[2]},
		{position_list[2], texcoord_list[3]},

		{position_list[7], texcoord_list[1]},
		{position_list[0], texcoord_list[0]},
		{position_list[3], texcoord_list[2]},
		{position_list[4], texcoord_list[3]},

		{position_list[3], texcoord_list[1]},
		{position_list[2], texcoord_list[0]},
		{position_list[5], texcoord_list[2]},
		{position_list[4], texcoord_list[3]},

		{position_list[7], texcoord_list[1]},
		{position_list[6], texcoord_list[0]},
		{position_list[1], texcoord_list[2]},
		{position_list[0], texcoord_list[3]},
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
		8,9,10,
		10,11,8,
		//BOTTOM SIDE
		12,13,14,
		14,15,12,
		//RIGHT SIDE
		16,17,18,
		18,19,16,
		//LEFT SIDE
		20,21,22,
		22,23,20
	};

	ib = GraphicsEngine::get()->getRenderSystem()->createIndexBuffer(index_list, ARRAYSIZE(index_list));

	GraphicsEngine::get()->getRenderSystem()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shaderByteCode, &sizeShader);
	vs = GraphicsEngine::get()->getRenderSystem()->createVertexShader(shaderByteCode, sizeShader);

	vb = GraphicsEngine::get()->getRenderSystem()->createVertexBuffer(vertex_list, sizeof(Vertex::vertex), ARRAYSIZE(vertex_list), shaderByteCode, sizeShader);

	GraphicsEngine::get()->getRenderSystem()->releaseCompiledShader();

	GraphicsEngine::get()->getRenderSystem()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shaderByteCode, &sizeShader);
	ps = GraphicsEngine::get()->getRenderSystem()->createPixelShader(shaderByteCode, sizeShader);
	GraphicsEngine::get()->getRenderSystem()->releaseCompiledShader();

	constant cc;
	cc.m_angle = 0;

	cb = GraphicsEngine::get()->getRenderSystem()->createConstantBuffer(&cc, sizeof(constant));

	m_wood_tex = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\wood.jpg");
}

Cube::~Cube()
{
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
	DeviceContextPtr device = GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext();

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

	sceneCamera = SceneCameraHandler::getInstance()->getActiveCamera();

	float fov = sceneCamera->getFOV();
	float asp = sceneCamera->getAspectRatio();
	float nz = sceneCamera->getNearZ();
	float fz = sceneCamera->getFarZ();

	if (SceneCameraHandler::getInstance()->getActiveCamera() != SceneCameraHandler::getInstance()->getCamera())
	{
		cc.m_world *= SceneCameraHandler::getInstance()->getCameraWorldCamMatrix();

		Matrix4x4 proj;
		proj.setPerspectiveFovLH(fov, asp, nz, fz);

		cc.m_world *= proj;
	}

	float aspec = (float)width / (float)height;
	

	cc.m_view = SceneCameraHandler::getInstance()->getActiveCameraWorldCamMatrix();

	cc.m_proj.setPerspectiveFovLH(fov, asp, nz, fz);

	

	cb->update(GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext(), &cc);

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(vs, cb);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(ps, cb);

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setVertexShader(vs);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setPixelShader(ps);

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setTexture(ps, m_wood_tex);

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setVertexBuffer(vb);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setIndexBuffer(ib);

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->drawIndexedTriangleList(ib->getSizeIndexList(), vb->getSizeVertexList(), 0, 0);

}

void Cube::setAnimation(float speed, float interval, bool isSpeeding, float rotFactor)
{
	this->rotFactor = rotFactor;
	this->speed = speed;
	this->animationInterval = interval;
	this->isIncreasing = isSpeeding;
}
