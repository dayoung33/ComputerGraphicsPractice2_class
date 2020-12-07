#pragma once
#include "GameObject.h"
#include "inputclass.h"

class MovingTree :
	public GameObject
{
public:
	MovingTree();
	MovingTree(MovingTree&);
	virtual ~MovingTree();
public:
	void Init();
	void Init(InputClass * _input);
	virtual bool Frame();
	void Shutdown();
	void SetMoveON(bool moveOn);
	void SetMoveUp(bool moveUp);
	bool GetMoveUP() { return IsMoveUp; }
	void LevelUp() { m_iLevel++; }
//	int GetScore() { return m_iLevel; }
	void Reset();
	void ReStart();
	bool GetWin() { return m_bWin; }
	void GameOver(bool over) { m_bOver = over; }

private:
	void Move();

private:
	D3DXVECTOR3 m_vOriginPos;
	D3DXVECTOR3 m_vSize;
	bool IsMoveOn;
	bool IsMoveUp;

	int m_iLevel;
	bool m_bOver;
	bool m_bWin;

	bool m_bInitBT;

	InputClass* m_pInput;

};

