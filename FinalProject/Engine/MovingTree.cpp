#include "MovingTree.h"

MovingTree::MovingTree()
{
	m_vPos = { -50.f, 50.f, 70.f };
	m_vOriginPos = m_vPos;
	IsMoveOn = false;
	IsMoveUp = false;
	m_iLevel = 1;
	m_bWin = false;
	m_pInput = 0;
	m_bOver = false;
}

MovingTree::MovingTree(MovingTree &)
{
}

MovingTree::~MovingTree()
{
}

void MovingTree::Init()
{
}

void MovingTree::Init(InputClass * _input)
{
	m_pInput = _input;
}

bool MovingTree::Frame()
{
	if (!m_bOver) {
		if (m_pInput->IsKeyPressed(DIK_SPACE)) //if (m_pInput->GetMouseState().rgbButtons[0] & 0x80)
			IsMoveOn = true;
		//else
		//	IsMoveOn = false;
		Move();
	}
	D3DXMATRIX matTans, matRotX, matScale;

	D3DXMatrixTranslation(&matTans, m_vPos.x, m_vPos.y, m_vPos.z);
	D3DXMatrixScaling(&matScale, 0.3f, 0.3f, 0.3f);
	D3DXMatrixRotationX(&matRotX, D3DXToRadian(90.f));

	m_matWorld = matScale * matTans * matRotX;
	return true;
}

void MovingTree::Shutdown()
{
}

void MovingTree::SetMoveON(bool moveOn)
{
	IsMoveOn = moveOn;
}

void MovingTree::SetMoveUp(bool moveUp)
{
	IsMoveUp = moveUp;
}

void MovingTree::Move()
{
	if (m_vPos.x > 180.f)
		SetMoveUp(false);
	if (m_vPos.x < -50.f)
		SetMoveUp(true);

	if (IsMoveOn)
	{
		if (IsMoveUp)
		{
			m_vPos.x += 0.5f * m_iLevel;
		}
		else if(!IsMoveUp)
		{
			m_vPos.x -= 0.5f * m_iLevel;
		}
	}
}

void MovingTree::Reset()
{
	m_vPos = m_vOriginPos;
	IsMoveOn = false;
}
void MovingTree::ReStart()
{
	m_bWin = false;
	Reset();
}