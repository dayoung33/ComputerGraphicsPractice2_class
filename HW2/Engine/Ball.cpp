#include "Ball.h"

Ball::Ball()
{
	m_vPos = { 0.f, 0.f, 5.f };
}

Ball::Ball(Ball &)
{
}

Ball::~Ball()
{
}

void Ball::Init()
{
}

bool Ball::Frame()
{
	D3DXMATRIX matTans, matRotX, matScale;
	D3DXMatrixTranslation(&matTans, m_vPos.x, m_vPos.y, m_vPos.z);
	D3DXMatrixScaling(&matScale, 0.5f, 0.5f, 0.5f);
	D3DXMatrixRotationX(&matRotX, D3DXToRadian(90.f));

	m_matWorld = matScale * matTans * matRotX;
	return true;
}

void Ball::Shutdown()
{
}
