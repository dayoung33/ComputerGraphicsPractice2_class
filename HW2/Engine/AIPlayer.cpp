#include "AIPlayer.h"

AIPlayer::AIPlayer()
{
	m_vPos = { -90.f, 0.f, 5.f };
	m_vOriginPos = m_vPos;
}

AIPlayer::AIPlayer(AIPlayer &)
{
}

AIPlayer::~AIPlayer()
{
}

void AIPlayer::Init()
{
}

bool AIPlayer::Frame()
{
	Move();
	D3DXMATRIX matTans, matRotX, matScale;

	D3DXMatrixTranslation(&matTans, m_vPos.x, m_vPos.y, m_vPos.z);
	D3DXMatrixScaling(&matScale, 0.5f, 0.5f, 0.5f);
	D3DXMatrixRotationX(&matRotX, D3DXToRadian(90.f));

	m_matWorld = matScale * matTans * matRotX;
	return true;
}

void AIPlayer::Shutdown()
{
}

void AIPlayer::Move()
{
}

void AIPlayer::Reset()
{
	m_vPos = m_vOriginPos;
}
