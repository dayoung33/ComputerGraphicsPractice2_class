#pragma once
#include "GameObject.h"
#include "inputclass.h"

#include <cstdlib>
#include <ctime>

class DartBoard :
	public GameObject
{
public:
	DartBoard();
	DartBoard(DartBoard&);
	virtual ~DartBoard();

	void Init();
	virtual bool Frame();
	void Shutdown();

	virtual void Reset();
	D3DXVECTOR3 getPos() { return m_vPos; }
	D3DXVECTOR3 getDir() { return m_vDir; }
	void SetPlayer(GameObject* _pPlayer);
	void SetAIPlayer(GameObject* _pPlayer);


private:
	GameObject* m_pPlayer;
	GameObject* m_pTree;
	D3DXVECTOR3 m_vOriginPos;
	D3DXVECTOR3 m_vDir;
	D3DXVECTOR3 m_vSize;

	bool gameStart;

};

