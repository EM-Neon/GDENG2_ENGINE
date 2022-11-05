#include "Cube.h"
#include "GraphicsEngine.h"
#include "InputSystem.h"
#include "SwapChain.h"


#include "Vertex.h"

Cube::Cube(string name, void* shaderByteCode, size_t sizeShader): AGameObject(name)
{
	Vertex::vertex quadList[] =
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

	this->vertexBuffer = GraphicsEngine::get()->createVertexBuffer();
	this->vertexBuffer->load(quadList, sizeof(Vertex::vertex), ARRAYSIZE(quadList), shaderByteCode, sizeShader);

	unsigned int indexList[] =
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
	this->indexBuffer = GraphicsEngine::get()->createIndexBuffer();
	this->indexBuffer->load(indexList, ARRAYSIZE(indexList));

	constant cc = {};
	cc.m_angle = 0;
	this->constantBuffer = GraphicsEngine::get()->createConstantBuffer();
	this->constantBuffer->load(&cc, sizeof(constant));
}

Cube::~Cube()
{
	this->vertexBuffer->release();
	this->indexBuffer->release();
	AGameObject::~AGameObject();
}

void Cube::update(float deltaTime)
{
	this->deltaTime = deltaTime;
}

void Cube::draw(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader)
{
	GraphicsEngine* graphEngine = GraphicsEngine::get();
	DeviceContext* deviceContext = graphEngine->getImmediateDeviceContext();

	constant cc = {};

	if(this->deltaPos > 1.0f)
	{
		this->deltaPos = 0.0f;
	}
	else
	{
		this->deltaPos += this->deltaTime * 0.1f;
	}

	Matrix4x4 allMatrix; allMatrix.setIdentity();
	Matrix4x4 translationMatrix; translationMatrix.setIdentity(); translationMatrix.setTranslation(this->getLocalPosition());
	Matrix4x4 scaleMatrix; scaleMatrix.setScale(this->getLocalScale());
	Vector3D rotation = this->getLocalRotation();
	Matrix4x4 zMatrix; zMatrix.setRotationZ(rotation.m_z);
	Matrix4x4 xMatrix; xMatrix.setRotationX(rotation.m_x);
	Matrix4x4 yMatrix; yMatrix.setRotationY(rotation.m_y);

	//Scale --> Rotate --> Transform as recommended order.
	Matrix4x4 rotMatrix; rotMatrix.setIdentity();
	rotMatrix *= xMatrix;
	rotMatrix *= yMatrix;
	rotMatrix *= zMatrix;

	allMatrix *= scaleMatrix;
	allMatrix *= rotMatrix;
	allMatrix *= translationMatrix;
	cc.m_world = allMatrix;

	Matrix4x4 cameraMatrix = 
}

void Cube::setAnimSpeed(float speed)
{
}
