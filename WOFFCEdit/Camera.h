#pragma once

//#include <d3d12.h>
//#include <SimpleMath.h>
#include "InputCommands.h"
//#include "StepTimer.h"
#include "pch.h"

class Camera
{
public:

	Camera();
	Camera(float cameraSpeed, float cameraRotation,DirectX::SimpleMath::Vector3 cameraPos, DirectX::SimpleMath::Vector3 cameraOrientation, int width , int height);
	~Camera();
	//camera
	DirectX::SimpleMath::Vector3		m_camPosition;
	DirectX::SimpleMath::Vector3		m_camOrientation;
	DirectX::SimpleMath::Vector3		m_camLookAt;
	DirectX::SimpleMath::Vector3		m_camLookDirection;
	DirectX::SimpleMath::Vector3		m_camRight;
	DirectX::SimpleMath::Matrix			m_view;
	//InputCommands* m_InputCommands;
	float m_camRotRate;
	float m_movespeed;
	int middleX;
	int middleY;
	float m_oldX;
	float m_oldY;
	DirectX::SimpleMath::Vector2		m_oldMousePos;
	DirectX::SimpleMath::Vector2		m_newMousePos;
	//void Update(DX::StepTimer const& timer, InputCommands m_InputCommands);
	void HandleInput(InputCommands m_InputCommands);
	DirectX::SimpleMath::Matrix GetLookAt();
};

