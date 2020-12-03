#pragma once

#include "d3dclass.h"
#include "textureshaderclass.h"
#include "textclass.h"
#include "bitmapclass.h"

class GameSystem
{
public:
	GameSystem();
	GameSystem(const GameSystem&);
	virtual ~GameSystem();

public:
	void Init();
	virtual bool Frame();
	virtual void Render(ID3D11DeviceContext *deviceContext, TextureShaderClass *pTextureShader, D3DXMATRIX viewMatrix, D3DXMATRIX worldMatrix, D3DXMATRIX baseViewMatrix, D3DXMATRIX orthoMatrix, D3DXVECTOR3 cameraLook);
	void Shutdown();
};

