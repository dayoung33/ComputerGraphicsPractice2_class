#include "DartBoard.h"
#include "MovingTree.h"
#include "Player.h"

DartBoard::DartBoard()
{
	srand(time(unsigned int(NULL)));
	m_vPos = { 0.f, 0.f, 75.f };
	m_vOriginPos = m_vPos;
	m_vDir = { 0.0f, 0.0f, 0.0f };

}

DartBoard::DartBoard(DartBoard &)
{
}

DartBoard::~DartBoard()
{
}

void DartBoard::Init()
{
}

bool DartBoard::Frame()
{
	m_vPos = D3DXVECTOR3(m_pTree->GetPos().x - 60.f, m_vPos.y, m_vPos.z);
	D3DXMATRIX matTans, matRotX, matScale;
	D3DXMatrixTranslation(&matTans, m_vPos.x, m_vPos.y+3.3f, m_vPos.z);
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	//D3DXMatrixRotationX(&matRotX, D3DXToRadian(90.f));

	m_matWorld = matScale * matTans ;
	return true;
}

void DartBoard::Shutdown()
{
}

void DartBoard::Reset()
{
	//m_vPos = m_vOriginPos;
	m_pTree->Reset();
}

void DartBoard::SetPlayer(GameObject * _pPlayer)
{
	m_pPlayer = _pPlayer;
}

void DartBoard::SetTree(GameObject * _pPlayer)
{
	m_pTree = _pPlayer;
}


