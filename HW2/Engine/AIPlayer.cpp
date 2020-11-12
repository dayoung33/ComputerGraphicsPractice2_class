#include "AIPlayer.h"

AIPlayer::AIPlayer()
{
	m_vPos = { -90.f, 0.f, 5.f };
	m_vOriginPos = m_vPos;
	IsMoveOn = false;
	IsMoveUp = false;
	m_iScore = 0;
	m_bWin = false;
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
	if (m_iScore >= 10)
		m_bWin = true;

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

void AIPlayer::SetMoveON(bool moveOn)
{
	IsMoveOn = moveOn;
}

void AIPlayer::SetMoveUp(bool moveUp)
{
	IsMoveUp = moveUp;
}

void AIPlayer::Move()
{
	if (m_vPos.y > 40.f)
		SetMoveUp(false);
	if (m_vPos.y < -50.f)
		SetMoveUp(true);

	if (IsMoveOn)
	{
		if (IsMoveUp)
		{
			m_vPos.y += 1.f;
		}
		else if(!IsMoveUp)
		{
			m_vPos.y -= 1.f;
		}
	}
}

void AIPlayer::Reset()
{
	m_vPos = m_vOriginPos;
}
void AIPlayer::ReStart()
{
	m_iScore = 0;
	m_bWin = false;
	Reset();
}