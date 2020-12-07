#pragma once
#include "GameObject.h"
class GameSystem;
class Particle : public GameObject
{
public:
	Particle();
	Particle(Particle&);
	virtual ~Particle();
public:
	void Init();
	void Init(D3DXVECTOR3 vPos, bool MR, GameSystem* ScoreUI);
	virtual bool Frame();
	void Shutdown();
	bool GetisHidden() { return m_isHidden; }
	void SetisHidden(bool isHidden) { m_isHidden = isHidden; }
private:
	void Move();
private:
	GameSystem* m_ScoreUI;
	D3DXVECTOR3 m_vOriginPos;
	bool m_isHidden;
	bool m_moveR;
};

