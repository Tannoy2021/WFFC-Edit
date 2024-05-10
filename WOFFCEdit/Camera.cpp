
#include "Camera.h"

Camera::Camera()
{
	////functional
	//m_movespeed = 0.30;
	//m_camRotRate = 3.0;

	////camera
	//m_camPosition.x = 0.0f;
	//m_camPosition.y = 3.7f;
	//m_camPosition.z = -3.5f;

	//m_camOrientation.x = 0;
	//m_camOrientation.y = 0;
	//m_camOrientation.z = 0;

	//m_camLookAt.x = 0.0f;
	//m_camLookAt.y = 0.0f;
	//m_camLookAt.z = 0.0f;

	//m_camLookDirection.x = 0.0f;
	//m_camLookDirection.y = 0.0f;
	//m_camLookDirection.z = 0.0f;

	//m_camRight.x = 0.0f;
	//m_camRight.y = 0.0f;
	//m_camRight.z = 0.0f;

	//m_camOrientation.x = 0.0f;
	//m_camOrientation.y = 0.0f;
	//m_camOrientation.z = 0.0f;
}

Camera::Camera(float camerasped, float camerarotation, DirectX::SimpleMath::Vector3 cameraPos, DirectX::SimpleMath::Vector3 cameraOrientation, int width, int height)
{
	//functional
	m_movespeed = camerasped;
	m_camRotRate = camerarotation;

	//camera
	m_camPosition = cameraPos;
	m_camOrientation = cameraOrientation;


	m_camLookAt.x = 0.0f;
	m_camLookAt.y = 0.0f;
	m_camLookAt.z = 0.0f;

	m_camLookDirection.x = 0.0f;
	m_camLookDirection.y = 0.0f;
	m_camLookDirection.z = 0.0f;

	m_camRight.x = 0.0f;
	m_camRight.y = 0.0f;
	m_camRight.z = 0.0f;

	middleX = height / 2;
	middleY = width / 2;

	int ID = -1;

	HandleInput(InputCommands());
}

Camera::~Camera()
{

}

void Camera::HandleInput(InputCommands m_InputCommands)
{

	DirectX::SimpleMath::Vector3 planarMotionVector = m_camLookDirection;
	planarMotionVector.y = 0.0;
	planarMotionVector.Normalize();
	// 89 to avoid a wrap around the x axis
	m_camOrientation.x = std::min(std::max(m_camOrientation.x, -89.f), 89.f);
	//m_camOrientation.y = std::min(std::max(m_camOrientation.y, -179.f), 179.f);

	if (!m_InputCommands.mouseLDown)
	{
		m_oldMousePos = DirectX::SimpleMath::Vector2(m_InputCommands.mouseX, m_InputCommands.mouseY);
	}
	m_newMousePos = DirectX::SimpleMath::Vector2(m_InputCommands.mouseX, m_InputCommands.mouseY) - m_oldMousePos;


	m_camOrientation.y += m_newMousePos.x * m_camRotRate / 100;
	m_camOrientation.x -= m_newMousePos.y * m_camRotRate / 100;




	//	//create look direction from Euler angles in m_camOrientation
	//	m_camLookDirection.x = sin((m_camOrientation.y) * 3.1415 / 180);
	//	m_camLookDirection.z = cos((m_camOrientation.y) * 3.1415 / 180);
	//	m_camLookDirection.Normalize();

		//create look direction from Euler angles in m_camOrientation
	m_camLookDirection.x = cos((m_camOrientation.y) * 3.1415 / 180) * cos((m_camOrientation.x) * 3.1415 / 180.0f);
	m_camLookDirection.y = sin((m_camOrientation.x) * 3.1415 / 180);
	m_camLookDirection.z = sin((m_camOrientation.y) * 3.1415 / 180) * cos((m_camOrientation.x) * 3.1415 / 180.0f);
	m_camLookDirection.Normalize();

	//create right vector from look Direction
	m_camLookDirection.Cross(DirectX::SimpleMath::Vector3::UnitY, m_camRight);
	// this section is to rotate up down left right 
	if (m_InputCommands.rotRight)
	{
		m_camOrientation.y += m_camRotRate * (m_movespeed / 24.f);
	}
	if (m_InputCommands.rotLeft)
	{
		m_camOrientation.y -= m_camRotRate * (m_movespeed / 24.f);
	}
	/*if (m_InputCommands.Up)
	{
		m_camOrientation.x += m_camRotRate * (m_movespeed / 24.f);

	}
	if (m_InputCommands.Down)
	{
		m_camOrientation.x -= m_camRotRate * (m_movespeed / 24.f);
	}*/

	//process input and update stuff for keyboard
	if (m_InputCommands.forward)
	{
		m_camPosition += m_camLookDirection * m_movespeed;
	}
	if (m_InputCommands.back)
	{
		m_camPosition -= m_camLookDirection * m_movespeed;
	}
	if (m_InputCommands.right)
	{
		m_camPosition += m_camRight * m_movespeed;
	}
	if (m_InputCommands.left)
	{
		m_camPosition -= m_camRight * m_movespeed;
	}
	if (m_InputCommands.Up)
	{
		m_camPosition.y += m_movespeed;
	}
	if (m_InputCommands.Down)
	{
		m_camPosition.y -= m_movespeed;
	}


	//update lookat point
	m_camLookAt = m_camPosition + m_camLookDirection;

	//apply camera vectors
	//m_view = DirectX::SimpleMath::Matrix::CreateLookAt(m_camPosition, m_camLookAt, DirectX::SimpleMath::Vector3::UnitY);
	m_oldMousePos = DirectX::SimpleMath::Vector2(m_InputCommands.mouseX, m_InputCommands.mouseY);

}

DirectX::SimpleMath::Matrix Camera::GetLookAt()
{
	//apply camera vectors
	return DirectX::SimpleMath::Matrix::CreateLookAt(m_camPosition, m_camLookAt, DirectX::SimpleMath::Vector3::UnitY);
}

void Camera::SetCameraPosition(const DirectX::SimpleMath::Vector3& position)
{
	m_camPosition = position;
}

void Camera::SetCameraOrientation(const DirectX::SimpleMath::Vector3& orientation)
{
	m_camOrientation = orientation;
}


//void Camera::Update(DX::StepTimer const& timer, InputCommands m_InputCommands)
//{
//	//TODO  any more complex than this, and the camera should be abstracted out to somewhere else
//	//camera motion is on a plane, so kill the 7 component of the look direction
//	DirectX::SimpleMath::Vector3 planarMotionVector = m_camLookDirection;
//	planarMotionVector.y = 0.0;
//
//	if (m_InputCommands.rotRight)
//	{
//		m_camOrientation.y -= m_camRotRate;
//	}
//	if (m_InputCommands.rotLeft)
//	{
//		m_camOrientation.y += m_camRotRate;
//	}
//
//	//create look direction from Euler angles in m_camOrientation
//	m_camLookDirection.x = sin((m_camOrientation.y) * 3.1415 / 180);
//	m_camLookDirection.z = cos((m_camOrientation.y) * 3.1415 / 180);
//	m_camLookDirection.Normalize();
//
//	//create right vector from look Direction
//	m_camLookDirection.Cross(DirectX::SimpleMath::Vector3::UnitY, m_camRight);
//
//	//process input and update stuff
//	if (m_InputCommands.forward)
//	{
//		m_camPosition += m_camLookDirection * m_movespeed;
//	}
//	if (m_InputCommands.back)
//	{
//		m_camPosition -= m_camLookDirection * m_movespeed;
//	}
//	if (m_InputCommands.right)
//	{
//		m_camPosition += m_camRight * m_movespeed;
//	}
//	if (m_InputCommands.left)
//	{
//		m_camPosition -= m_camRight * m_movespeed;
//	}
//
//	//update lookat point
//	m_camLookAt = m_camPosition + m_camLookDirection;
//
//	//apply camera vectors
//	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(m_camPosition, m_camLookAt, DirectX::SimpleMath::Vector3::UnitY);
//}
