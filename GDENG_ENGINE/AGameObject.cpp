#include "AGameObject.h"

AGameObject::AGameObject(std::string name)
{
	this->name = name;
	this->localRotation = Vector3D(0, 0, 0);
	this->localPosition = Vector3D(0, 0, 0);
	this->localScale = Vector3D(1, 1, 1);
}

AGameObject::~AGameObject()
{
}

void AGameObject::setPosition(float x, float y, float z)
{
	this->localPosition = Vector3D(x, y, z);
}

void AGameObject::setPosition(Vector3D pos)
{
	this->localPosition = pos;
}

void AGameObject::setRotation(float x, float y, float z)
{
	this->localRotation = Vector3D(x, y, z);
}

void AGameObject::setRotation(Vector3D rot)
{
	this->localRotation = rot;
}

void AGameObject::setScale(float x, float y, float z)
{
	this->localScale = Vector3D(x, y, z);
}

void AGameObject::setScale(Vector3D scale)
{
	this->localScale = scale;
}

Vector3D AGameObject::getLocalPosition()
{
	return this->localPosition;
}

Vector3D AGameObject::getLocalRotation()
{
	return this->localRotation;
}

Vector3D AGameObject::getLocalScale()
{
	return this->localScale;
}

void AGameObject::attachComponent(AComponent* component)
{
	this->componentList.push_back(component);
	component->attachOwner(this);
}

void AGameObject::detachComponent(AComponent* component)
{
	int index = -1;
	for(int i =0; i < this->componentList.size();i++)
	{
		if(this->componentList[i] == component)
		{
			index = i;
			break;
		}
	}
	if(index != 1)
	{
		this->componentList.erase(this->componentList.begin() + index);
	}
}

AComponent* AGameObject::findComponentByName(String name)
{
	for(int i = 0; i < this->componentList.size(); i++)
	{
		if(this->componentList[i]->getName() == name)
		{
			return this->componentList[i];
		}
	}

	return NULL;
}

AComponent* AGameObject::findComponentOfType(AComponent::ComponentType type, String name)
{
	for (int i = 0; i < this->componentList.size(); i++) {
		if (this->componentList[i]->getName() == name && this->componentList[i]->getType() == type) {
			return this->componentList[i];
		}
	}

	return NULL;
}

AGameObject::ComponentList AGameObject::getComponentsOfType(AComponent::ComponentType type)
{
	ComponentList foundList;
	for (int i = 0; i < this->componentList.size(); i++) {
		if (this->componentList[i]->getType() == type) {
			foundList.push_back(this->componentList[i]);
		}
	}

	return foundList;
}

AGameObject::ComponentList AGameObject::getComponentsOfTypeRecursive(AComponent::ComponentType type)
{
	ComponentList foundList;
	for (int i = 0; i < this->componentList.size(); i++) {
		if (this->componentList[i]->getType() == type) {
			foundList.push_back(this->componentList[i]);
		}
	}

	return foundList;
}

void AGameObject::updateLocalMatrix()
{
	Matrix4x4 all; all.setIdentity();
	Matrix4x4 trans; trans.setIdentity(); trans.setTranslation(this->getLocalPosition());
	Matrix4x4 scale; scale.setScale(this->getLocalScale());
	Vector3D rotation = this->getLocalRotation();
	Matrix4x4 x; x.setRotationX(rotation.m_x);
	Matrix4x4 y; y.setRotationY(rotation.m_y);
	Matrix4x4 z; z.setRotationZ(rotation.m_z);

	//Scale --> Rotate --> Transform as recommended order.
	Matrix4x4 rot; rot.setIdentity();
	rot *= x;
	rot *= y;
	rot *= z;

	all *= scale;
	all *= rot;
	all *= trans;

	this->localMatrix = all;
}

void AGameObject::recomputeMatrix(float matrix[16])
{
	float matrix4x4[4][4];
	matrix4x4[0][0] = matrix[0];
	matrix4x4[0][1] = matrix[1];
	matrix4x4[0][2] = matrix[2];
	matrix4x4[0][3] = matrix[3];

	matrix4x4[1][0] = matrix[4];
	matrix4x4[1][1] = matrix[5];
	matrix4x4[1][2] = matrix[6];
	matrix4x4[1][3] = matrix[7];

	matrix4x4[2][0] = matrix[8];
	matrix4x4[2][1] = matrix[9];
	matrix4x4[2][2] = matrix[10];
	matrix4x4[2][3] = matrix[11];

	matrix4x4[3][0] = matrix[12];
	matrix4x4[3][1] = matrix[13];
	matrix4x4[3][2] = matrix[14];
	matrix4x4[3][3] = matrix[15];

	Matrix4x4 newMatrix; newMatrix.setMatrix(matrix4x4);
	Matrix4x4 scaleMatrix; scaleMatrix.setScale(this->localScale);
	Matrix4x4 transMatrix; transMatrix.setTranslation(this->localPosition);

	Matrix4x4 temp;
	temp *= scaleMatrix;
	temp *= transMatrix;
	temp *= newMatrix;

	this->localMatrix = temp;
	this->overrideMatrix = true;
}

float* AGameObject::getMatrix()
{
	float* matrix = this->localMatrix.getMatrix();
	return matrix;
}

float* AGameObject::getPhysicsLocalMatrix()
{
	Matrix4x4 allMatrix; allMatrix.setIdentity();
	Matrix4x4 trans; trans.setIdentity();
	trans.setTranslation(this->getLocalRotation());
	Matrix4x4 scaleMatrix; scaleMatrix.setScale(Vector3D(1, 1, 1));
	Vector3D rot = this->getLocalRotation();
	Matrix4x4 x; x.setRotationX(rot.m_x);
	Matrix4x4 y; y.setRotationY(rot.m_y);
	Matrix4x4 z; z.setRotationZ(rot.m_z);

	//Scale --> Rotate --> Transform as recommended order.
	Matrix4x4 rotMatrix; rotMatrix.setIdentity();
	rotMatrix *= x;
	rotMatrix *= y;
	rotMatrix *= z;

	allMatrix *= scaleMatrix;
	allMatrix *= rotMatrix;
	allMatrix *= trans;

	return allMatrix.getMatrix();
}

std::string AGameObject::getName()
{
	return this->name;
}
