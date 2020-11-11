#pragma once
#include "GameObject.h"
#include <cstdlib>
#include <ctime>
enum eDir {STOP, LEFT, LEFTUP, LEFTDOWN, RIGHT, RIGHTUP ,RIGHTDOWN};
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

	void Reset();
	void ChangeDir(eDir _dir);
	D3DXVECTOR3 getPos() { return m_vPos; }
	D3DXVECTOR3 getDir() { return m_vDir; }
	void Move();
	void RandomDir();
	bool CheckPlayerCol(D3DXVECTOR3 plyerPos);
	void SetPlayer(GameObject* _pPlayer);
	void SetAIPlayer(GameObject* _pPlayer);

private:
	GameObject* m_pPlayer;
	GameObject* m_pAIPlayer;
	D3DXVECTOR3 m_vOriginPos;
	D3DXVECTOR3 m_vDir;
	D3DXVECTOR3 m_vSize;


	D3DXVECTOR3 Stop =		{ 0.f,0.f,0.f };
	D3DXVECTOR3 Left =		{ -1.f,0.f,0.f };
	D3DXVECTOR3 LeftUp =	{ -1.f,1.f,0.f };
	D3DXVECTOR3 LeftDown =	{ -1.f,-1.f,0.f };
	D3DXVECTOR3 Right =		{ 1.f,0.f,0.f };
	D3DXVECTOR3 RightUp =	{ 1.f,1.f,0.f };
	D3DXVECTOR3 RightDown = { 1.f,-1.f,0.f };

};

