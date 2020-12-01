#include "Player.h"

Player::Player()
{
	m_vPos = { 0.f, -120.f, 70.f };
	m_vOriginPos = m_vPos;
	m_iScore = 0;
	m_bWin = false;
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
	if (m_iScore >= 5)
		m_bWin = true;

	Move();
	D3DXMATRIX matTans, matRotX, matScale;
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
	if (m_pInput->IsKeyPressed(DIK_UP)&&m_vPos.y <= 40.f)
		m_vPos.y += 1.f;
	if (m_pInput->IsKeyPressed(DIK_DOWN)&&m_vPos.y >= -50.f)
		m_vPos.y -= 1.f;
}

void Player::Reset()
{
	m_vPos = m_vOriginPos;
}

void Player::ReStart()
{
	m_iScore = 0;
	m_bWin = false;
	Reset();
}
