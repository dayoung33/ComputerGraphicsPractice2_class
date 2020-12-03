////////////////////////////////////////////////////////////////////////////////
// Filename: cameraclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "cameraclass.h"


CameraClass::CameraClass()
{
	m_moveSpeed = 1.0f;
	m_position = { 0.0f, 0.0f ,0.0f };
	m_rotation = { 0.0f, 0.0f ,0.0f };
	// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
	pitch = 0.0f;
	yaw = 0.0f;
	roll = 0.0f;

	// Setup the vector that points upwards.
	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	// Setup where the camera is looking by default.
	lookAt.x = 0.0f;
	lookAt.y = 0.0f;
	lookAt.z = 1.0f;
}


CameraClass::CameraClass(const CameraClass& other)
{
}


CameraClass::~CameraClass()
{
}


void CameraClass::SetPosition(float x, float y, float z)
{
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;
	return;
}


void CameraClass::SetRotation(float x, float y, float z)
{
	m_rotation.x = x;
	m_rotation.y = y;
	m_rotation.z = z;
	return;
}


D3DXVECTOR3 CameraClass::GetPosition()
{
	return D3DXVECTOR3(m_position.x, m_position.y, m_position.z);
}


D3DXVECTOR3 CameraClass::GetRotation()
{
	return D3DXVECTOR3(m_rotation.x, m_rotation.y, m_rotation.z);
}


void CameraClass::Render()
{
	D3DXMATRIX rotationMatrix;

	D3DXVECTOR3 DefaultForward = { 0.0f, 0.0f, 1.0f };
	D3DXVECTOR3 DefaultRight = { 1.0f, 0.0f, 0.0f };
	D3DXVECTOR3 camForward = { 0.0f, 0.0f, 1.0f };
	D3DXVECTOR3 camRight = { 1.0f, 0.0f, 0.0f };
	
	D3DXMatrixRotationYawPitchRoll(&rotationMatrix, yaw, pitch, 0);

	D3DXVec3TransformCoord(&lookAt, &DefaultForward, &rotationMatrix);
	D3DXVec3Normalize(&lookAt, &lookAt);

	D3DXMATRIX RotateYTempMatrix;
	D3DXMatrixRotationY(&RotateYTempMatrix, yaw);

	D3DXVec3TransformCoord(&camRight, &DefaultRight, &RotateYTempMatrix);
	D3DXVec3TransformCoord(&up, &up, &RotateYTempMatrix);
	D3DXVec3TransformCoord(&camForward, &DefaultForward, &RotateYTempMatrix);

	m_position += moveLeftRight * camRight;
	m_position += moveBackForward * camForward;

	moveLeftRight = 0.0f;
	moveBackForward = 0.0f;

	lookAt = m_position + lookAt;

	D3DXMatrixLookAtLH(&m_viewMatrix, &m_position, &lookAt, &up);
	return;
}


void CameraClass::GetViewMatrix(D3DXMATRIX& viewMatrix)
{
	viewMatrix = m_viewMatrix;
	return;
}

void CameraClass::GetLookAt(D3DXVECTOR3 &lookAt)
{
	lookAt = this->lookAt;
}

void CameraClass::MoveLeftRight(float x)
{
	moveLeftRight += x * m_moveSpeed;
}

void CameraClass::MoveBackForward(float z)
{
	moveBackForward += z * m_moveSpeed;
}

void CameraClass::LookRotation(DIMOUSESTATE& curMouse, DIMOUSESTATE& nextMouse)
{
	yaw += nextMouse.lX * 0.001f;
	pitch += curMouse.lY * 0.001f;
}
