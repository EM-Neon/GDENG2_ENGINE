#include "Camera.h"
#include "InputSystem.h"
#include "EngineTime.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "Utils.h"
#include "SceneCameraHandler.h"

Camera::Camera(std::string name) : AGameObject(name)
{
	this->setPosition(0, 0, -2);
	this->localMatrix.setTranslation(this->localPosition);
	InputSystem::get()->addListener(this);
}

Camera::~Camera()
{
	InputSystem::get()->removeListener(this);
	AGameObject::~AGameObject();
}

void Camera::update(float deltaTime)
{
	if (isActive)
	{
		// keu input for camerae
		if (InputSystem::get()->isKeyDown('W'))
		{
			forward = 1; //forward
		}
		else if (InputSystem::get()->isKeyDown('S'))
		{
			forward = -1; //backwards
		}
		else if (InputSystem::get()->isKeyDown('A'))
		{
			rightward = -1; //sideward (left)
		}
		else if (InputSystem::get()->isKeyDown('D'))
		{
			rightward = 1; //sidewards (right)
		}
		else if (InputSystem::get()->isKeyDown('E'))
		{
			upward = 1; //upwards
		}
		else if (InputSystem::get()->isKeyDown('Q'))
		{
			upward = -1;//downwards
		}

		updateViewMatrix();
	}
	else
	{
		if (InputSystem::get()->isKeyDown('I'))
		{
			forward = 1; //forward
		}
		else if (InputSystem::get()->isKeyDown('K'))
		{
			forward = -1; //backwards
		}
		else if (InputSystem::get()->isKeyDown('J'))
		{
			rightward = -1; //sideward (left)
		}
		else if (InputSystem::get()->isKeyDown('L'))
		{
			rightward = 1; //sidewards (right)
		}
		else if (InputSystem::get()->isKeyDown('O'))
		{
			upward = 1; //upwards
		}
		else if (InputSystem::get()->isKeyDown('U'))
		{
			upward = -1;//downwards
		}

		updateViewMatrix();
	}
}

Matrix4x4 Camera::getVMatrix()
{
	return this->localMatrix;
}

Matrix4x4 Camera::getViewMatrix()
{
	return this->world_cam;
}

void Camera::setCameraStatus(bool flag)
{
	isActive = flag;
}

bool Camera::getCameraStatus()
{
	return isActive;
}

float Camera::getForward()
{
	return forward;
}

float Camera::getRightward()
{
	return rightward;
}

float Camera::getUpward()
{
	return upward;
}

float Camera::getFOV()
{
	return this->FOV;
}

float Camera::getNearZ()
{
	return this->nearZ;
}

float Camera::getFarZ()
{
	return this->farZ;
}

float Camera::getAspectRatio()
{
	return aspectRatio;
}

void Camera::setFOV(float fov)
{
	this->FOV = fov;
}

void Camera::setNearZ(float nz)
{
	this->nearZ = nz;
}

void Camera::setFarZ(float fz)
{
	this->farZ = fz;
}

void Camera::setAspect(float aspect)
{
	this->aspectRatio = aspect;
}

void Camera::onKeyDown(int key)
{

}

void Camera::onKeyUp(int key)
{
	forward = 0;
	rightward = 0;
	upward = 0;
}

void Camera::onMouseMove(const Point mouse_pos)
{
	if(this->mouseDown && this->isActive)
	{
		Vector3D v = this->getLocalRotation();

		v.m_x += (mouse_pos.m_y * EngineTime::getDeltaTime() * 0.1f);
		v.m_y += (mouse_pos.m_x * EngineTime::getDeltaTime() * 0.1f);

		this->setRotation(v);
	}
}

void Camera::onLeftMouseDown(const Point delta_mouse_pos)
{
}

void Camera::onLeftMouseUp(const Point delta_mouse_pos)
{
}

void Camera::onRightMouseDown(const Point delta_mouse_pos)
{
	this->mouseDown = true;
}

void Camera::onRightMouseUp(const Point delta_mouse_pos)
{
	this->mouseDown = false;
}

void Camera::updateViewMatrix()
{
	constant cc;
	Matrix4x4 temp;

	world_cam.setIdentity();
	temp.setIdentity();
	temp.setRotationX(this->getLocalRotation().m_x);
	world_cam *= temp;

	temp.setIdentity();
	temp.setRotationY(this->getLocalRotation().m_y);
	world_cam *= temp;

	Vector3D new_pos = this->localMatrix.getTranslation() + (world_cam.getZDirection() * (this->forward * 0.1f));
	new_pos = new_pos + (world_cam.getYDirection() * (this->upward * 0.1f));
	new_pos = new_pos + (world_cam.getXDirection() * (this->rightward * 0.1f));

	this->setPosition(new_pos);

	world_cam.setTranslation(new_pos);

	this->localMatrix = world_cam;

	world_cam.inverse();
}

void Camera::draw(int width, int height)
{

}
