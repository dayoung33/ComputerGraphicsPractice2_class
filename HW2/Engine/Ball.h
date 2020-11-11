#pragma once
#include "GameObject.h"
class Ball :
	public GameObject
{
public:
	Ball();
	Ball(Ball&);
	virtual ~Ball();

	void Init();
	virtual bool Frame();
	void Shutdown();

private:
	D3DXVECTOR3 m_vPos;
	D3DXVECTOR3 m_vSize;
};

