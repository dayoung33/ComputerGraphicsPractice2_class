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
	void UpScore() { m_iScore++; }
	int GetScore() { return m_iScore; }
	void Reset();
	bool GetWin() { return m_bWin; }
	void ReStart();

private:
	void Move();

private:
	D3DXVECTOR3 m_vOriginPos;
	D3DXVECTOR3 m_vSize;
	InputClass* m_pInput;
	int m_iScore;
	bool m_bWin;
};

