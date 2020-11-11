#include "Player.h"

Player::Player()
{
	m_vPos = { 90.f, 0.f, 5.f };
	m_vOriginPos = m_vPos;
}

Player::Player(Player &)
{
}

Player::~Player()
{
}

void Player::Init()
{
}

void Player::Init(InputClass * _input)
{
	m_pInput = _input;
}

bool Player::Frame()
{
	Move();
	D3DXMATRIX matTans, matRotX, matScale;
	// x  5 ~ 55 몸 가로 길이가 10정도인듯
	// y : -30 ~ 60 세로 15
	D3DXMatrixTranslation(&matTans, m_vPos.x, m_vPos.y, m_vPos.z);
	D3DXMatrixScaling(&matScale, 0.5f, 0.5f, 0.5f);
	D3DXMatrixRotationX(&matRotX, D3DXToRadian(90.f));

	m_matWorld = matScale * matTans * matRotX;
	return true;
}

void Player::Shutdown()
{
}

void Player::Move()
{
	//if (m_pInput->IsKeyPressed(DIK_RIGHT))
	//	m_vPos.x += 1.f;
	//if (m_pInput->IsKeyPressed(DIK_LEFT))
	//	m_vPos.x -= 1.f;
	if (m_pInput->IsKeyPressed(DIK_UP))
		m_vPos.y += 1.f;
	if (m_pInput->IsKeyPressed(DIK_DOWN))
		m_vPos.y -= 1.f;
}

void Player::Reset()
{
	m_vPos = m_vOriginPos;
}
