#pragma once
#include "GameObject.h"
class AIPlayer :
	public GameObject
{
public:
	AIPlayer();
	AIPlayer(AIPlayer&);
	virtual ~AIPlayer();
public:
	void Init();
	virtual bool Frame();
	void Shutdown();

private:
	void Move();

private:
	D3DXVECTOR3 m_vPos;
	D3DXVECTOR3 m_vSize;
};

