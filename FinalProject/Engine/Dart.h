#pragma once
#include "GameObject.h"
class InputClass;
class Dart : public GameObject
{
public:
	Dart();
	Dart(Dart&);
	virtual ~Dart();
public:
	void Init();
	void Init(InputClass* _input);
	virtual bool Frame();
	void Shutdown();
	void Reset();
	void ReStart();

private:
	void Move();

private:
	D3DXVECTOR3 m_vOriginPos;
	D3DXVECTOR3 m_vSize;
	InputClass* m_pInput;

	bool isMove;
	bool mouseButtonUp;

};

