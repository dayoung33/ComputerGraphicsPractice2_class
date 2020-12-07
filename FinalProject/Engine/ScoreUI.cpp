#include "ScoreUI.h"
#include "Dart.h"
#include "DartBoard.h"
#include "MovingTree.h"

ScoreUI::ScoreUI()
{
	m_totalscore = 0;
	m_levelscore = 0;
	m_curLevel = 1;
	m_scoreCheck = false;
	m_goalScore = 20;
	for (int i = 0; i < 11; i++)
		m_scoreEffect[i] = 0;

	m_backScore = 0;
	m_scoreBar = 0;
}

ScoreUI::ScoreUI(const ScoreUI &)
{
}

ScoreUI::~ScoreUI()
{
}

void ScoreUI::Init()
{
}

void ScoreUI::Init(ID3D11Device* device, ID3D11DeviceContext* deviceContext, float screenWidth, float screenHeight, HWND hwnd, D3DMATRIX baseViewMatrix)
{
	// Create the bitmap object.
	m_deviceContext = deviceContext;
	m_backBoard = new BitmapClass;
	if (!m_backBoard)
	{
		return;
	}
	// Initialize the bitmap object.
	m_backBoard->Initialize(device, screenWidth, screenHeight, L"../Engine/data/BackBoard.png", 550, 100);
	
	m_countDart = new BitmapClass;
	if (!m_countDart)
	{
		return;
	}
	// Initialize the bitmap object.
	m_countDart->Initialize(device, screenWidth, screenHeight, L"../Engine/data/dartcount.jpg", 300, 60);
	
	m_backScore = new BitmapClass;
	if (!m_backScore)
	{
		return;
	}
	// Initialize the bitmap object.
	m_backScore->Initialize(device, screenWidth, screenHeight, L"../Engine/data/scoreback.png", 200, 30);
	
	m_scoreBar = new BitmapClass;
	if (!m_scoreBar)
	{
		return;
	}
	// Initialize the bitmap object.
	m_scoreBar->Initialize(device, screenWidth, screenHeight, L"../Engine/data/red.png", 196, 26);

	for (int i = 0; i < 10; i++)
	{
		m_scoreEffect[i] = new BitmapClass;
		if (!m_scoreEffect[i])
			return;
	}
	m_scoreEffect[0]->Initialize(device, screenWidth, screenHeight, L"../Engine/data/score/0.png", 10, 20);
	m_scoreEffect[1]->Initialize(device, screenWidth, screenHeight, L"../Engine/data/score/1.png", 10, 20);
	m_scoreEffect[2]->Initialize(device, screenWidth, screenHeight, L"../Engine/data/score/2.png", 20, 20);
	m_scoreEffect[3]->Initialize(device, screenWidth, screenHeight, L"../Engine/data/score/3.png", 20, 20);
	m_scoreEffect[4]->Initialize(device, screenWidth, screenHeight, L"../Engine/data/score/4.png", 20, 20);
	m_scoreEffect[5]->Initialize(device, screenWidth, screenHeight, L"../Engine/data/score/5.png", 20, 20);
	m_scoreEffect[6]->Initialize(device, screenWidth, screenHeight, L"../Engine/data/score/6.png", 20, 20);
	m_scoreEffect[7]->Initialize(device, screenWidth, screenHeight, L"../Engine/data/score/7.png", 20, 20);
	m_scoreEffect[8]->Initialize(device, screenWidth, screenHeight, L"../Engine/data/score/8.png", 20, 20);
	m_scoreEffect[9]->Initialize(device, screenWidth, screenHeight, L"../Engine/data/score/9.png", 20, 20);


	m_UsedDart = new BitmapClass;
	if (!m_UsedDart)
	{
		return;
	}
	// Initialize the bitmap object.
	m_UsedDart->Initialize(device, screenWidth, screenHeight, L"../Engine/data/usedDart.jpg", 60, 60);

	// Create the text object.
	m_scoreText = new TextClass;

	// Initialize the text object.
	m_scoreText->Initialize(device, deviceContext, hwnd, screenWidth,
		screenHeight, baseViewMatrix);

	m_scoreText->SetTotalScore(m_totalscore, deviceContext);
	m_scoreText->SetLevelScore(m_curLevel,m_levelscore,m_goalScore, deviceContext);


}

bool ScoreUI::Frame()
{
	if (m_Dart->GetPos().z > 100.f)
	{
		m_Dart->Reset();
		m_DartBoard->Reset();
	}

	if (checkCollision()) {
		checkScore();
		m_Dart->Reset();
		m_DartBoard->Reset();
		m_scoreCheck = false;
	}
	LevelUp();
	m_scoreText->SetTotalScore(m_totalscore, m_deviceContext);
	m_scoreText->SetLevelScore(m_curLevel, m_levelscore, m_goalScore, m_deviceContext);
	return true;
}

void ScoreUI::Render(ID3D11DeviceContext *deviceContext, TextureShaderClass *pTextureShader, D3DXMATRIX viewMatrix, D3DXMATRIX worldMatrix, D3DXMATRIX baseViewMatrix, D3DXMATRIX orthoMatrix,D3DXVECTOR3 cameraLook)
{
	m_backBoard->Render(deviceContext, 250, 0);
	pTextureShader->Render(deviceContext, m_backBoard->GetIndexCount(),
		worldMatrix, baseViewMatrix, orthoMatrix, m_backBoard->GetTexture());

	m_backScore->Render(deviceContext, 270, 60);
	pTextureShader->Render(deviceContext, m_backScore->GetIndexCount(),
		worldMatrix, baseViewMatrix, orthoMatrix, m_backScore->GetTexture());

	m_scoreBar->Render(deviceContext, 272, 62);
	pTextureShader->Render(deviceContext, m_scoreBar->GetIndexCount(),
		worldMatrix, baseViewMatrix, orthoMatrix, m_scoreBar->GetTexture());

	m_countDart->Render(deviceContext, 490, 20);
	pTextureShader->Render(deviceContext, m_countDart->GetIndexCount(),
		worldMatrix, baseViewMatrix, orthoMatrix, m_countDart->GetTexture());

	int cnt = dynamic_cast<Dart*>(m_Dart)->GetDartCount();
	for (int i = cnt; i >= 1; i--) {
		m_UsedDart->Render(deviceContext, 790 - (i*60), 20);
		pTextureShader->Render(deviceContext, m_UsedDart->GetIndexCount(),
			worldMatrix, baseViewMatrix, orthoMatrix, m_UsedDart->GetTexture());
	}

	m_scoreText->Render(deviceContext, worldMatrix, orthoMatrix);

	for (int i = 0; i < 10; i++) {
		m_scoreEffect[i]->Render(deviceContext, 400 + (20*i), 200);
		pTextureShader->Render(deviceContext, m_scoreEffect[i]->GetIndexCount(),
			worldMatrix, baseViewMatrix, orthoMatrix, m_scoreEffect[i]->GetTexture());
	}
}

void ScoreUI::Shutdown()
{
	if (m_backBoard)
	{
		m_backBoard->Shutdown();
		delete m_backBoard;
		m_backBoard = 0;
	}

	if (m_countDart)
	{
		m_countDart->Shutdown();
		delete m_countDart;
		m_countDart = 0;
	}
	if (m_UsedDart)
	{
		m_UsedDart->Shutdown();
		delete m_UsedDart;
		m_UsedDart = 0;
	}

	if (m_backScore)
	{
		m_backScore->Shutdown();
		delete m_backScore;
		m_backScore = 0;
	}

	if (m_scoreBar)
	{
		m_scoreBar->Shutdown();
		delete m_scoreBar;
		m_scoreBar = 0;
	}

	for (int i = 0; i < 10; i++)
	{
		if (m_scoreEffect[i])
		{
			m_scoreEffect[i]->Shutdown();
			delete m_scoreEffect[i];
			m_scoreEffect[i] = 0;
		}
	}
	
	// Release the text object.
	if (m_scoreText)
	{
		m_scoreText->Shutdown();
		delete m_scoreText;
		m_scoreText = 0;
	}
}

void ScoreUI::SetObject(GameObject * pDart, GameObject * pBoard, GameObject* pTree)
{
	m_Dart = pDart;
	m_DartBoard = pBoard;
	m_pTree = pTree;
}

bool ScoreUI::checkCollision()
{
	D3DXVECTOR2 dPos = { m_Dart->GetPos().x,m_Dart->GetPos().y };
	D3DXVECTOR2 bPos = { m_DartBoard->GetPos().x,m_DartBoard->GetPos().y };

	if (abs(m_DartBoard->GetPos().z - m_Dart->GetPos().z) < 8 && 
		 D3DXVec2Length(&(dPos-bPos)) <26.f)
		return true;

	return false;
}

int ScoreUI::checkScore()
{
	if (m_scoreCheck) return 0;
	m_scoreCheck = true;
	D3DXVECTOR2 dPos = { m_Dart->GetPos().x,m_Dart->GetPos().y };
	D3DXVECTOR2 bPos = { m_DartBoard->GetPos().x,m_DartBoard->GetPos().y };

	if (D3DXVec2Length(&(dPos - bPos)) < 2.5f) {
		m_levelscore += 10;
		m_totalscore += 100 * m_curLevel;
	}
	else if (D3DXVec2Length(&(dPos - bPos)) < 5.5f) {
		m_levelscore += 9;
		m_totalscore += 90 * m_curLevel;
	}
	else if (D3DXVec2Length(&(dPos - bPos)) < 8.f) {
		m_levelscore += 8;
		m_totalscore += 80 * m_curLevel;
	}
	else if (D3DXVec2Length(&(dPos - bPos)) < 10.5f) {
		m_levelscore += 7;
		m_totalscore += 70 * m_curLevel;
	}
	else if (D3DXVec2Length(&(dPos - bPos)) < 13.5f) {
		m_levelscore += 6;
		m_totalscore += 60 * m_curLevel;
	}
	else if (D3DXVec2Length(&(dPos - bPos)) < 16.f) {
	
		m_levelscore += 5;
		m_totalscore += 50 * m_curLevel;
	}
	else if (D3DXVec2Length(&(dPos - bPos)) < 18.5f) {
		m_levelscore += 4;
		m_totalscore += 40 * m_curLevel;
	}
	else if (D3DXVec2Length(&(dPos - bPos)) < 21.5f) {
		m_levelscore += 3;
		m_totalscore += 30 * m_curLevel;
	}
	else if (D3DXVec2Length(&(dPos - bPos)) < 24.5f) {
		m_levelscore += 2;
		m_totalscore += 20 * m_curLevel;
	}
	else{
		m_levelscore += 1;
		m_totalscore += 10 * m_curLevel;
	}



	return 0;
}

void ScoreUI::LevelUp()
{
	int cnt = dynamic_cast<Dart*>(m_Dart)->GetDartCount();
	if (cnt > 0) return;
	if (cnt == 0 && m_levelscore >= m_goalScore)
	{
		m_curLevel++;
		m_levelscore = 0;
		m_goalScore += 2;
		dynamic_cast<Dart*>(m_Dart)->ResetDartCount();
		dynamic_cast<MovingTree*>(m_pTree)->LevelUp();
	}
	else
		dynamic_cast<MovingTree*>(m_pTree)->GameOver(true);
	
}
