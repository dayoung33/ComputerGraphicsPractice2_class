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
	void SetMoveON(bool moveOn);
	void SetMoveUp(bool moveUp);
	bool GetMoveUP() { return IsMoveUp; }
	void UpScore() { m_iScore++; }
	int GetScore() { return m_iScore; }
	void Reset();
	void ReStart();
	bool GetWin() { return m_bWin; }

private:
	void Move();

private:
	D3DXVECTOR3 m_vOriginPos;
	D3DXVECTOR3 m_vSize;
	bool IsMoveOn;
	bool IsMoveUp;
	int m_iScore;
	bool m_bWin;

};

