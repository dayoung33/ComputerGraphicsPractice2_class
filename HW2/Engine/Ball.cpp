#include "Ball.h"
#include "AIPlayer.h"
#include "Player.h"

Ball::Ball()
{
	srand(time(unsigned int(NULL)));
	m_vPos = { 0.f, 0.f, 0.f };
	m_vOriginPos = m_vPos;
	m_vDir = { 0.0f, 0.0f, 0.0f };
	m_eDir = STOP;
	gameStart = false;

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

void Ball::Init(InputClass * _input)
{
	m_pInput = _input;
}

bool Ball::Frame()
{
	if (!gameStart&&m_pInput->IsKeyPressed(DIK_SPACE))
		gameStart = true;

	if(gameStart)
		if (m_vDir == Stop)
			RandomDir();


	if (m_vPos.x > 95.f) {
		Reset();
		m_pAIPlayer->Reset();
		m_pPlayer->Reset();
		dynamic_cast<AIPlayer*>(m_pAIPlayer)->UpScore();
	}
	if (m_vPos.x < -95.f)
	{
		Reset();
		m_pAIPlayer->Reset();
		m_pPlayer->Reset();
		dynamic_cast<Player*>(m_pPlayer)->UpScore();
	}

	if (!dynamic_cast<Player*>(m_pPlayer)->GetWin() && !dynamic_cast<AIPlayer*>(m_pAIPlayer)->GetWin()) {
		Move();
		SetAIMove();
	}
	else
	{
		if (m_pInput->IsKeyPressed(DIK_SPACE))
		{
			Reset();
			dynamic_cast<AIPlayer*>(m_pAIPlayer)->ReStart();
			dynamic_cast<Player*>(m_pPlayer)->ReStart();

		}
	}

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
	m_eDir = STOP;
}

void Ball::ChangeDir(eDir _dir)
{
	switch (_dir)
	{
	case STOP:
		m_vDir = Stop;
		m_eDir = STOP;
		break;
	case LEFT:
		m_vDir = Left;
		m_eDir = LEFT;
		break;
	case LEFTUP:
		m_vDir = LeftUp;
		m_eDir = LEFTUP;
		break;
	case LEFTDOWN:
		m_vDir = LeftDown;
		m_eDir = LEFTDOWN;
		break;
	case RIGHT:
		m_vDir = Right;
		m_eDir = RIGHT;
		break;
	case RIGHTUP:
		m_vDir = RightUp;
		m_eDir = RIGHTUP;
		break;
	case RIGHTDOWN:
		m_vDir = RightDown;
		m_eDir = RIGHTDOWN;
		break;
	default:
		break;
	}
}

void Ball::Move()
{
	if (m_vPos.y >= 55.f)
		ChangeDir(m_eDir == RIGHTUP ? RIGHTDOWN : LEFTDOWN);
	if (m_vPos.y <= -55.f)
		ChangeDir(m_eDir == RIGHTDOWN ? RIGHTUP : LEFTUP);

	if(CheckPlayerCol(m_pPlayer->GetPos()))
		ChangeDir((eDir)(rand() % 3 + 1));
	if(CheckPlayerCol(m_pAIPlayer->GetPos()))
		ChangeDir((eDir)(rand() % 3 + 4));

	D3DXVec3Normalize(&m_vDir, &m_vDir);
	m_vPos += m_vDir * (2.5f);
}

void Ball::RandomDir()
{
	int randomNum = rand()%6 + 1;
	switch (randomNum)
	{
	case STOP:
		m_vDir = Stop;
		m_eDir = STOP;
		break;
	case LEFT:
		m_vDir = Left;
		m_eDir = LEFT;
		break;
	case LEFTUP:
		m_vDir = LeftUp;
		m_eDir = LEFTUP;
		break;
	case LEFTDOWN:
		m_vDir = LeftDown;
		m_eDir = LEFTDOWN;
		break;
	case RIGHT:
		m_vDir = Right;
		m_eDir = RIGHT;
		break;
	case RIGHTUP:
		m_vDir = RightUp;
		m_eDir = RIGHTUP;
		break;
	case RIGHTDOWN:
		m_vDir = RightDown;
		m_eDir = RIGHTDOWN;
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

void Ball::SetAIMove()
{	
	if (m_eDir >= RIGHT)
	{
		dynamic_cast<AIPlayer*>(m_pAIPlayer)->SetMoveON(false);
	}
	else {
		dynamic_cast<AIPlayer*>(m_pAIPlayer)->SetMoveON(true);
		float aPosY = m_pAIPlayer->GetPos().y;
		if(aPosY-10.f>m_vPos.y)
			dynamic_cast<AIPlayer*>(m_pAIPlayer)->SetMoveUp(false);
		else if(aPosY+10.f < m_vPos.y)
			dynamic_cast<AIPlayer*>(m_pAIPlayer)->SetMoveUp(true);
		else if(aPosY - 10.f < m_vPos.y && aPosY + 10.f > m_vPos.y)
			dynamic_cast<AIPlayer*>(m_pAIPlayer)->SetMoveON(false);
		}
}
