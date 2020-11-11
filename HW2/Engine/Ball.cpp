#include "Ball.h"

Ball::Ball()
{
	srand(time(unsigned int(NULL)));
	m_vPos = { 0.f, 0.f, 5.f };
	m_vOriginPos = m_vPos;
	m_vDir = { 0.0f, 0.0f, 0.0f };

	D3DXVec3Normalize(&Left, &Left);
	D3DXVec3Normalize(&LeftUp, &LeftUp);
	D3DXVec3Normalize(&LeftDown, &LeftDown);
	D3DXVec3Normalize(&Right, &Right);
	D3DXVec3Normalize(&RightUp, &RightUp);
	D3DXVec3Normalize(&RightDown, &RightDown);


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
	if (m_vDir == Stop)
		RandomDir();

	if (m_vPos.x > 95.f || m_vPos.x < -95.f)
		Reset();

	Move();
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

void Ball::Reset()
{
	m_vPos = m_vOriginPos;
	m_vDir = Stop;
}

void Ball::ChangeDir(eDir _dir)
{
	switch (_dir)
	{
	case STOP:
		m_vDir = Stop;
		break;
	case LEFT:
		m_vDir = Left;
		break;
	case LEFTUP:
		m_vDir = LeftUp;
		break;
	case LEFTDOWN:
		m_vDir = LeftDown;
		break;
	case RIGHT:
		m_vDir = Right;
		break;
	case RIGHTUP:
		m_vDir = RightUp;
		break;
	case RIGHTDOWN:
		m_vDir = RightDown;
		break;
	default:
		break;
	}
}

void Ball::Move()
{
	if (m_vPos.y >= 55.f)
		ChangeDir(m_vDir == RightUp ? RIGHTDOWN : LEFTDOWN);
	if (m_vPos.y <= -55.f)
		ChangeDir(m_vDir == RightDown ? RIGHTUP : LEFTUP);

	if(CheckPlayerCol(m_pPlayer->GetPos()))
		ChangeDir((eDir)(rand() % 3 + 1));
	if(CheckPlayerCol(m_pAIPlayer->GetPos()))
		ChangeDir((eDir)(rand() % 3 + 4));

	D3DXVec3Normalize(&m_vDir, &m_vDir);
	m_vPos += m_vDir * (0.5f);
}

void Ball::RandomDir()
{
	int randomNum = rand()%6 + 1;
	switch (randomNum)
	{
	case STOP:
		break;
	case LEFT:
		m_vDir = Left;
		break;
	case LEFTUP:
		m_vDir = LeftUp;
		break;
	case LEFTDOWN:
		m_vDir = LeftDown;
		break;
	case RIGHT:
		m_vDir = Right;
		break;
	case RIGHTUP:
		m_vDir = RightUp;
		break;
	case RIGHTDOWN:
		m_vDir = RightDown;
		break;
	default:
		break;
	}
}

bool Ball::CheckPlayerCol(D3DXVECTOR3 plyerPos)
{
	if (plyerPos.x > 0) { //player
		if (m_vPos.x > 85.f)
			if (m_vPos.y <plyerPos.y + 10.f&&m_vPos.y > plyerPos.y - 10.f)
				return true;
	}
			
	else {//AI
		if (m_vPos.x < -85.f)
			if (m_vPos.y <plyerPos.y + 10.f&&m_vPos.y > plyerPos.y - 10.f)
				return true;
	}

	return false;
}

void Ball::SetPlayer(GameObject * _pPlayer)
{
	m_pPlayer = _pPlayer;
}

void Ball::SetAIPlayer(GameObject * _pPlayer)
{
	m_pAIPlayer = _pPlayer;
}
