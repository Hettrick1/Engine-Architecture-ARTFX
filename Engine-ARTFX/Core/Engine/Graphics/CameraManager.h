#pragma once

#include <vector>

class CameraComponent;

class CameraManager
{
public:
	static CameraManager& Instance();
	~CameraManager();

	void AddCamera(CameraComponent* pCameraToAdd);
	void RemoveCamera(CameraComponent* pCameraToRemove);

	void UpdateCurrentCamera();

	void SetCurrentCamera(int pIndex);
	void SetCurrentCamera(CameraComponent* pCameraToActivate);
private:
	CameraManager();
	CameraComponent* mActiveCamera;
	std::vector<CameraComponent*> mCameras;
};

