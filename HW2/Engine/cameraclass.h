////////////////////////////////////////////////////////////////////////////////
// Filename: cameraclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _CAMERACLASS_H_
#define _CAMERACLASS_H_


//////////////
// INCLUDES //
//////////////
#include <d3dx10math.h>
#include <dinput.h>

////////////////////////////////////////////////////////////////////////////////
// Class name: CameraClass
////////////////////////////////////////////////////////////////////////////////
class CameraClass
{
public:
	CameraClass();
	CameraClass(const CameraClass&);
	~CameraClass();

	void SetPosition(float, float, float);
	void SetRotation(float, float, float);

	D3DXVECTOR3 GetPosition();
	D3DXVECTOR3 GetRotation();

	void Render();
	void GetViewMatrix(D3DXMATRIX&);

	void MoveLeftRight(float x);
	void MoveBackForward(float z);
	void LookRotation(DIMOUSESTATE&, DIMOUSESTATE&);

private:
	D3DXVECTOR3 m_position;
	D3DXVECTOR3 m_rotation;
	float moveLeftRight = 0.0f;
	float moveBackForward = 0.0f;
	D3DXMATRIX m_viewMatrix;
	float m_moveSpeed;
	float yaw, pitch, roll;
	D3DXVECTOR3 up, lookAt;

};

#endif