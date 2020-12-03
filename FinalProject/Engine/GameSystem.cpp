#include "GameSystem.h"

GameSystem::GameSystem()
{
}

GameSystem::GameSystem(const GameSystem &)
{
}

GameSystem::~GameSystem()
{
}

void GameSystem::Init()
{
}

bool GameSystem::Frame()
{
	return false;
}

void GameSystem::Render(ID3D11DeviceContext *deviceContext, TextureShaderClass *pTextureShader, D3DXMATRIX viewMatrix, D3DXMATRIX worldMatrix, D3DXMATRIX baseViewMatrix, D3DXMATRIX orthoMatrix, D3DXVECTOR3 cameraLook)
{
}

void GameSystem::Shutdown()
{
}
