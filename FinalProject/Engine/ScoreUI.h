#pragma once
#include "GameSystem.h"
class Dart;
class DartBoard;
class ScoreUI : public GameSystem
{
public:
	ScoreUI();
	ScoreUI(const ScoreUI&);
	virtual ~ScoreUI();

public:
	void Init(); 
	virtual bool Frame();
	virtual void Render(ID3D11DeviceContext*, TextureShaderClass*, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX);
	void Shutdown();

	void SetObject(Dart* pDart, DartBoard* pBoard);

private:
	bool checkCollision();

private:
	BitmapClass* m_backBoard;
	TextClass* m_scoreText;
	Dart* m_Dart;
	DartBoard* m_DartBoard;

	int m_totalscore;
	int m_levelscore;
};

