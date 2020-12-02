#include "ScoreUI.h"
#include "Dart.h"
#include "DartBoard.h"

ScoreUI::ScoreUI()
{
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

bool ScoreUI::Frame()
{
	return false;
}

void ScoreUI::Render(ID3D11DeviceContext *, TextureShaderClass *, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX)
{
}

void ScoreUI::Shutdown()
{
}

void ScoreUI::SetObject(Dart * pDart, DartBoard * pBoard)
{
}

bool ScoreUI::checkCollision()
{
	return false;
}
