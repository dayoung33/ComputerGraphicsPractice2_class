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
	void Init(ID3D11Device * device, ID3D11DeviceContext * deviceContext, float screenWidth, float screenHeight, HWND hwnd, D3DMATRIX baseViewMatrix);
	virtual bool Frame();
	virtual void Render(ID3D11DeviceContext*, TextureShaderClass*, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, D3DXVECTOR3);
	void Shutdown();

	void SetObject(GameObject* pDart, GameObject* pBoard, GameObject* pTree);

private:
	bool checkCollision();
	int checkScore();
	void LevelUp();

private:
	BitmapClass* m_backBoard;
	BitmapClass* m_countDart;
	BitmapClass* m_UsedDart;
	BitmapClass* m_scoreEffect[11];
	BitmapClass* m_backScore;
	BitmapClass* m_scoreBar;
	TextClass*	 m_scoreText;
	GameObject*	 m_Dart;
	GameObject*	 m_DartBoard;
	GameObject*  m_pTree;
	ID3D11DeviceContext* m_deviceContext;

	int m_totalscore;
	int m_levelscore;
	int m_curLevel;
	int m_goalScore;
	
	bool m_scoreCheck;
};

