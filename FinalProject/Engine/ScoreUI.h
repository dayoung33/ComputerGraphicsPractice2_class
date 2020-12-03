#pragma once
#include "GameSystem.h"
class GameObject;
class ScoreUI : public GameSystem
{
public:
	ScoreUI();
	ScoreUI(const ScoreUI&);
	virtual ~ScoreUI();

	

public:
	void Init(); 
	void Init(ID3D11Device * device, float screenWidth, float screenHeight);
	virtual bool Frame();
	virtual void Render(ID3D11DeviceContext*, TextureShaderClass*, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, D3DXVECTOR3);
	void Shutdown();

	void SetObject(GameObject* pDart, GameObject* pBoard);

private:
	bool checkCollision();
	int checkScore();

private:
	BitmapClass* m_backBoard;
	TextClass* m_scoreText;
	GameObject* m_Dart;
	GameObject* m_DartBoard;

	int m_totalscore;
	int m_levelscore;
};

