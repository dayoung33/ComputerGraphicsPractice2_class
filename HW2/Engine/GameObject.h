#pragma once
#include "modelclass.h"
class GameObject :
	public ModelClass
{
public:
	GameObject();
	GameObject(const GameObject&);
	virtual ~GameObject();

public:
	const D3DXMATRIX GetWorld() const { return m_matWorld; }
	void SetWorld(D3DXMATRIX matWorld) { m_matWorld = matWorld; }
	void SetPos(D3DXVECTOR3 vPos);
	const D3DXVECTOR3& GetPos() { return m_vPos; }

public:
	void Init();
	virtual bool Frame();
	void Shutdown();

protected:
	D3DXMATRIX m_matWorld;
	D3DXVECTOR3 m_vPos;

};

