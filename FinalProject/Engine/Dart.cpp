#include "Dart.h"
#include "inputclass.h"

Dart::Dart()
{
	m_vPos = { 0.f, 0.f, -100.f };
	m_vOriginPos = m_vPos;
	isMove = false;
	mouseButtonUp = false;
}

Dart::Dart(Dart &)
{
}

Dart::~Dart()
{
}

void Dart::Init()
{
}

void Dart::Init(InputClass * _input)
{
	m_pInput = _input;
}

bool Dart::Frame()
{
	Move();
	D3DXMATRIX matTans, matRotX, matScale;
	D3DXMatrixTranslation(&matTans, m_vPos.x, m_vPos.y, m_vPos.z);
	D3DXMatrixScaling(&matScale, 2.0f, 2.0f, 2.0f);
	D3DXMatrixRotationY(&matRotX, D3DXToRadian(90.f));

	m_matWorld = matScale * matRotX * matTans ;
	return true;
}

void Dart::Shutdown()
{
}

void Dart::Reset()
{
	//m_vPos = m_vOriginPos;
	mouseButtonUp = false;
	isMove = false;
}

void Dart::ReStart()
{
	
}

void Dart::Move()
{
	if(m_pInput->IsKeyPressed(DIK_SPACE)){
	//if (m_pInput->GetMouseState().rgbButtons[0] & 0x80) {
		
		mouseButtonUp = true;
	}
	else
	{
		if(mouseButtonUp)
			isMove = true;

		if (m_vPos.z > 100.f)
			isMove = false;

		if (isMove)
		{
			m_vPos.z += 2.f;
		}
	}


}
