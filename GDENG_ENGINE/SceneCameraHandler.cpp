#include "SceneCameraHandler.h"
#include "EngineTime.h"

SceneCameraHandler* SceneCameraHandler::sharedInstance = NULL;

SceneCameraHandler* SceneCameraHandler::getInstance()
{
    return sharedInstance;
}

void SceneCameraHandler::initialize()
{
    sharedInstance = new SceneCameraHandler();
}

void SceneCameraHandler::destroy()
{
    delete sharedInstance;
}

void SceneCameraHandler::update()
{
    this->activeCamera->update(EngineTime::getDeltaTime());
}

Matrix4x4 SceneCameraHandler::getActiveCameraViewMatrix()
{
    return this->activeCamera->getVMatrix();
}

Matrix4x4 SceneCameraHandler::getActiveCameraWorldCamMatrix()
{
    return this->activeCamera->getViewMatrix();
}

Matrix4x4 SceneCameraHandler::getCameraWorldCamMatrix()
{
    return this->camera->getViewMatrix();
}

Camera* SceneCameraHandler::getActiveCamera()
{
    return this->activeCamera;
}

Camera* SceneCameraHandler::getCamera()
{
    return this->camera;
}

void SceneCameraHandler::SetActiveCamera(Camera* cameraObject)
{
    if (activeCamera)
        this->activeCamera->setCameraStatus(false);
    this->activeCamera = cameraObject;
    this->activeCamera->setCameraStatus(true);
}

void SceneCameraHandler::SetCamera(Camera* camera)
{
    this->camera = camera;
}

SceneCameraHandler::SceneCameraHandler()
{
    this->activeCamera = new Camera("ActiveCamera");

}

SceneCameraHandler::~SceneCameraHandler()
{
    delete this->activeCamera;
}
