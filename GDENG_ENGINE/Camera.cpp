#include "Camera.h"
#include "InputSystem.h"

Camera::Camera(string name):AGameObject(name)
{
	this->forwardDirection = Vector3D(1.0f, 0.0f, 1.0f);
	this->backwardDirection = Vector3D(-1.0f, 0.0f, -1.0f);

	this->setPosition(0.0f, 0.0f, -4.0f);
	this->updateViewMatrix();
	InputSystem::get()->addListener(this);
}

Camera::~Camera()
{
	InputSystem::get()->removeListener(this);
}

void Camera::update(float deltaTime)
{
	AGameObject::update(deltaTime);
}

Matrix4x4 Camera::getViewMatrix()
{
}

void Camera::onKeyDown(int key)
{
}

void Camera::onKeyUp(int key)
{
}

void Camera::onMouseMove(const Point& mouse_pos)
{
}

void Camera::onLeftMouseDown(const Point& delta_mouse_pos)
{
}

void Camera::onLeftMouseUp(const Point& delta_mouse_pos)
{
}

void Camera::onRightMouseDown(const Point& delta_mouse_pos)
{
}

void Camera::onRightMouseUp(const Point& delta_mouse_pos)
{
}

void Camera::updateViewMatrix()
{
}
