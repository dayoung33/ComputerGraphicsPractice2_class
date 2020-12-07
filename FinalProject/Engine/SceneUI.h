#pragma once
#include "GameSystem.h"
class InputClass;
class SceneUI : public GameSystem
{
public:
	SceneUI();
	SceneUI(const SceneUI&);
	virtual ~SceneUI();
public:
	void Init();
	void Init(InputClass* input, ID3D11Device * device, ID3D11DeviceContext * deviceContext, float screenWidth, float screenHeight, HWND hwnd, D3DMATRIX baseViewMatrix);
	virtual bool Frame();
	virtual void Render(ID3D11DeviceContext*, TextureShaderClass*, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, D3DXVECTOR3);
	void Shutdown();
	void SetScoreUI(GameSystem* scoreUI) { m_scoreUI = scoreUI; }

private:
	void SetTotalScore();
private:
	InputClass* m_input;
	BitmapClass* m_openBoard;
	BitmapClass* m_score[10];
	BitmapClass* m_keyBoard;
	BitmapClass* m_EndingBoard;
	GameSystem* m_scoreUI;

	int SceneNum;
	bool KeyUp;
	int m_iScore[4];


};

