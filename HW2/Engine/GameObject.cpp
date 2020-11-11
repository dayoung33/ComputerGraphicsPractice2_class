#include "GameObject.h"
GameObject::GameObject()
{
	Init();
}

GameObject::GameObject(const GameObject & other)
{
}

GameObject::~GameObject()
{
	Shutdown();
}

void GameObject::SetPos(D3DXVECTOR3 vPos)
{
	m_vPos = vPos;
}

void GameObject::Init()
{
	D3DXMatrixIdentity(&m_matWorld);
}

bool GameObject::Frame()
{
	return false;
}

void GameObject::Shutdown()
{

}