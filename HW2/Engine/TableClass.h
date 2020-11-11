#pragma once
#include "GameObject.h"
class TableClass :public GameObject
{
public:
	TableClass();
	TableClass(TableClass&);
	virtual ~TableClass();

	void Init();
	virtual bool Frame();
	void Shutdown();

private:
	D3DXVECTOR3 m_vPos;
	D3DXVECTOR3 m_vSize;
};

