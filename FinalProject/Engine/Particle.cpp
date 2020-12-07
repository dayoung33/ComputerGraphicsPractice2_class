#include "Particle.h"
#include "ScoreUI.h"
Particle::Particle()
{
	m_vPos = { 0.f, 30.f, 80.f };
	m_vOriginPos = m_vPos;
	m_isHidden = true;
	m_moveR = false;
}

Particle::Particle(Particle &)
{
}

Particle::~Particle()
{
}

void Particle::Init()
{
}

void Particle::Init(D3DXVECTOR3 vPos, bool MR, GameSystem* ScoreUI)
{
	m_ScoreUI = ScoreUI;
	m_vPos = vPos;
	m_vOriginPos = m_vPos;
	m_moveR = MR;
}

bool Particle::Frame()
{
	if (dynamic_cast<ScoreUI*>(m_ScoreUI)->GetisColl())
		SetisHidden(false);
	else
		SetisHidden(true);
	Move();
	D3DXMATRIX matTans, matScale;
	D3DXMatrixTranslation(&matTans, m_vPos.x, m_vPos.y, m_vPos.z);
	D3DXMatrixScaling(&matScale, 0.5f, 0.5f, 0.5f);
	//D3DXMatrixRotationX(&matRotX, D3DXToRadian(90.f));

	m_matWorld = matScale * matTans ;
	return true;
}

void Particle::Shutdown()
{
}

void Particle::Move()
{
	if (m_vPos.x > m_vOriginPos.x + 20.f)
		m_moveR = false;
	if (m_vPos.x < m_vOriginPos.x - 10.f)
		m_moveR = true;
	if (m_vPos.y < -70.f)
		m_vPos = m_vOriginPos;

	if (m_moveR)
	{
		m_vPos.x += 0.3f;
	}
	else if (!m_moveR)
	{
		m_vPos.x -= 0.3f;
	}

	m_vPos.y -= 0.2f;
}
