#include "Dart.h"
#include "inputclass.h"

Dart::Dart()
{
	m_vPos = { 0.f, 0.f, -100.f };
	m_vOriginPos = m_vPos;
	isMove = false;
	mouseButtonUp = false;
	m_dartCount = 5;
	checkInit = false;
	gameStart = false;

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
	if (gameStart) {
		Move();
		D3DXMATRIX matTans, matRotY, matScale;
		D3DXMatrixTranslation(&matTans, m_vPos.x, m_vPos.y, m_vPos.z);
		D3DXMatrixScaling(&matScale, 2.0f, 2.0f, 2.0f);
		D3DXMatrixRotationY(&matRotY, D3DXToRadian(90.f));

		m_matWorld = matScale * matRotY * matTans;
	}
	return true;
}

void Dart::Shutdown()
{
}

void Dart::Reset()
{
	
	mouseButtonUp = false;
	isMove = false;
	checkInit = false;
}

void Dart::ReStart()
{
	
}

void Dart::Move()
{
	if(m_pInput->IsKeyPressed(DIK_SPACE)&&m_dartCount > 0){
	//if (m_pInput->GetMouseState().rgbButtons[0] & 0x80) {
		m_vPos = m_vOriginPos;
		mouseButtonUp = true;	
	}
	else
	{
		if (mouseButtonUp) {
			if (!checkInit) {
				isMove = true;
				m_dartCount--;
				checkInit = true;
			}
		}

		if (isMove)
		{
			m_vPos.z += 4.f;
		}
	}


}
