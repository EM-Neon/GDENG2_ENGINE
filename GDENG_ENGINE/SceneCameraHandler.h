#pragma once
#include "Camera.h"

class SceneCameraHandler
{
public:
	static SceneCameraHandler* getInstance();
	static void initialize();
	static void destroy();

	void update();

	Matrix4x4 getActiveCameraViewMatrix();
	Matrix4x4 getActiveCameraWorldCamMatrix();

	Matrix4x4 getCameraWorldCamMatrix();

	Camera* getActiveCamera();
	Camera* getCamera();

	void SetActiveCamera(Camera* objCamera);
	void SetCamera(Camera* camera);

private:
	SceneCameraHandler();
	~SceneCameraHandler();
	SceneCameraHandler(SceneCameraHandler const&) {};
	SceneCameraHandler& operator = (SceneCameraHandler const&){};
	static SceneCameraHandler* sharedInstance;

	Camera* activeCamera;
	Camera* camera;
};

