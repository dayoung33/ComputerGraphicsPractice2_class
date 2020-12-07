#include "SceneUI.h"
#include "inputclass.h"
#include "ScoreUI.h"
enum SCENE {OPEN, KEY, MAIN, END};
SceneUI::SceneUI()
{
	m_openBoard = 0;
	m_keyBoard = 0;
	m_EndingBoard = 0;
	SceneNum = 0;
	m_input = 0;
	KeyUp = false;
	for (int i = 0; i < 4; i++)
		m_iScore[i] = 0;
	for (int i = 0; i < 10; i++)
		m_score[i] = 0;
}

SceneUI::SceneUI(const SceneUI &)
{
}

SceneUI::~SceneUI()
{
}

void SceneUI::Init()
{
}

void SceneUI::Init(InputClass * input, ID3D11Device * device, ID3D11DeviceContext * deviceContext, float screenWidth, float screenHeight, HWND hwnd, D3DMATRIX baseViewMatrix)
{
	m_input = input;

	m_openBoard = new BitmapClass;
	if (!m_openBoard)	return;
	m_openBoard->Initialize(device, screenWidth, screenHeight, L"../Engine/data/scene/Open.png", 800, 600);

	m_keyBoard = new BitmapClass;
	if (!m_keyBoard)	return;
	m_keyBoard->Initialize(device, screenWidth, screenHeight, L"../Engine/data/scene/Key.png", 800, 600);

	m_EndingBoard = new BitmapClass;
	if (!m_EndingBoard)	return;
	m_EndingBoard->Initialize(device, screenWidth, screenHeight, L"../Engine/data/scene/End.png", 800, 600);

	for (int i = 0; i < 10; i++)
	{
		m_score[i] = new BitmapClass;
		if (!m_score[i])	return;
	}
	m_score[0]->Initialize(device, screenWidth, screenHeight, L"../Engine/data/totalscore/0.jpg", 37, 57);
	m_score[1]->Initialize(device, screenWidth, screenHeight, L"../Engine/data/totalscore/1.jpg", 37, 57);
	m_score[2]->Initialize(device, screenWidth, screenHeight, L"../Engine/data/totalscore/2.jpg", 37, 57);
	m_score[3]->Initialize(device, screenWidth, screenHeight, L"../Engine/data/totalscore/3.jpg", 37, 57);
	m_score[4]->Initialize(device, screenWidth, screenHeight, L"../Engine/data/totalscore/4.jpg", 37, 57);
	m_score[5]->Initialize(device, screenWidth, screenHeight, L"../Engine/data/totalscore/5.jpg", 37, 57);
	m_score[6]->Initialize(device, screenWidth, screenHeight, L"../Engine/data/totalscore/6.jpg", 37, 57);
	m_score[7]->Initialize(device, screenWidth, screenHeight, L"../Engine/data/totalscore/7.jpg", 37, 57);
	m_score[8]->Initialize(device, screenWidth, screenHeight, L"../Engine/data/totalscore/8.jpg", 37, 57);
	m_score[9]->Initialize(device, screenWidth, screenHeight, L"../Engine/data/totalscore/9.jpg", 37, 57);

}

bool SceneUI::Frame()
{
	if (m_input->IsKeyPressed(DIK_RETURN))
	{
		KeyUp = true;
	}
	else
	{
		if (KeyUp) {
			if (SceneNum < 2) {
				SceneNum++;
				if (SceneNum == 2)
					dynamic_cast<ScoreUI*>(m_scoreUI)->SetGame(true);
			}
			KeyUp = false;
		}
	}

	if (dynamic_cast<ScoreUI*>(m_scoreUI)->GetOver()) {
		SetTotalScore();
		SceneNum = 3;
	}
	return true;
}

void SceneUI::Render(ID3D11DeviceContext *deviceContext, TextureShaderClass *pTextureShader, D3DXMATRIX viewMatrix, D3DXMATRIX worldMatrix, D3DXMATRIX baseViewMatrix, D3DXMATRIX orthoMatrix, D3DXVECTOR3 cameraLook)
{
	switch (SceneNum)
	{
	case OPEN:
		m_openBoard->Render(deviceContext, 0, 0);
		pTextureShader->Render(deviceContext, m_openBoard->GetIndexCount(),
				worldMatrix, baseViewMatrix, orthoMatrix, m_openBoard->GetTexture());
		break;
	case KEY:
		m_keyBoard->Render(deviceContext, 0, 0);
		pTextureShader->Render(deviceContext, m_keyBoard->GetIndexCount(),
			worldMatrix, baseViewMatrix, orthoMatrix, m_keyBoard->GetTexture());
		break;
	case MAIN:
		break;
	case END:
		m_EndingBoard->Render(deviceContext, 0, 0);
		pTextureShader->Render(deviceContext, m_EndingBoard->GetIndexCount(),
			worldMatrix, baseViewMatrix, orthoMatrix, m_EndingBoard->GetTexture());
		for (int i = 0; i < 4; i++) {
			m_score[m_iScore[i]]->Render(deviceContext, 470 +(i*37), 375);
			pTextureShader->Render(deviceContext, m_score[m_iScore[i]]->GetIndexCount(),
				worldMatrix, baseViewMatrix, orthoMatrix, m_score[m_iScore[i]]->GetTexture());
		}
		break;
	default:
		break;
	}
		
}

void SceneUI::Shutdown()
{
	for (int i = 0; i < 10; i++)
	{
		if (m_score[i])
		{
			m_score[i]->Shutdown();
			delete m_score[i];
			m_score[i] = 0;
		}
	}

	if (m_openBoard)
	{
		m_openBoard->Shutdown();
		delete m_openBoard;
		m_openBoard = 0;
	}
	if (m_keyBoard)
	{
		m_keyBoard->Shutdown();
		delete m_keyBoard;
		m_keyBoard = 0;
	}
	if (m_EndingBoard)
	{
		m_EndingBoard->Shutdown();
		delete m_EndingBoard;
		m_EndingBoard = 0;
	}
}

void SceneUI::SetTotalScore()
{
	int score = dynamic_cast<ScoreUI*>(m_scoreUI)->GetTotalScore();
	if (score > 1000) {
		m_iScore[0] = score / 1000;
		score -= m_iScore[0] * 1000;
	}
	if (score > 100) {
		m_iScore[1] = score / 100;
		score -= m_iScore[1] * 100;
	}
	if (score > 10) {
		m_iScore[2] = score / 10;
		score -= m_iScore[2] * 10;
	}
	m_iScore[3] = score;
}
