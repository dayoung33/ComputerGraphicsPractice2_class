#include "ScoreUI.h"
#include "Dart.h"
#include "DartBoard.h"

ScoreUI::ScoreUI()
{
	m_totalscore = 0;
	m_levelscore = 0;
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

void ScoreUI::Init(ID3D11Device* device, float screenWidth, float screenHeight)
{
	// Create the bitmap object.
	m_backBoard = new BitmapClass;
	if (!m_backBoard)
	{
		return;
	}
	// Initialize the bitmap object.
	m_backBoard->Initialize(device, screenWidth, screenHeight, L"../Engine/data/BackBoard.png", 200, 200);

}

bool ScoreUI::Frame()
{
	if (checkCollision()) {
		m_Dart->Reset();
		m_DartBoard->Reset();
	}
	return true;
}

void ScoreUI::Render(ID3D11DeviceContext *deviceContext, TextureShaderClass *pTextureShader, D3DXMATRIX viewMatrix, D3DXMATRIX worldMatrix, D3DXMATRIX baseViewMatrix, D3DXMATRIX orthoMatrix,D3DXVECTOR3 cameraLook)
{
	m_backBoard->Render(deviceContext, 250, 0);

	// Render the bitmap with the texture shader.
	pTextureShader->Render(deviceContext, m_backBoard->GetIndexCount(),
		worldMatrix, baseViewMatrix, orthoMatrix, m_backBoard->GetTexture());

}

void ScoreUI::Shutdown()
{
	if (m_backBoard)
	{
		m_backBoard->Shutdown();
		delete m_backBoard;
		m_backBoard = 0;
	}
}

void ScoreUI::SetObject(GameObject * pDart, GameObject * pBoard)
{
	m_Dart = pDart;
	m_DartBoard = pBoard;
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
	D3DXVECTOR2 dPos = { m_Dart->GetPos().x,m_Dart->GetPos().y };
	D3DXVECTOR2 bPos = { m_DartBoard->GetPos().x,m_DartBoard->GetPos().y };


	return 0;
}
