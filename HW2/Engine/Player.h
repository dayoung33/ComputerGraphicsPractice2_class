#pragma once
#include "GameObject.h"
#include "inputclass.h"
class Player :
	public GameObject
{
public:
	Player();
	Player(Player&);
	virtual ~Player();
public:
	void Init();
	void Init(InputClass* _input);
	virtual bool Frame();
	void Shutdown();

private:
	void Move();
	void Reset();

private:
	D3DXVECTOR3 m_vOriginPos;
	D3DXVECTOR3 m_vSize;
	InputClass* m_pInput;
};

