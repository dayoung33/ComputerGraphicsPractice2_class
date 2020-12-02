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
	virtual void Render(ID3D11DeviceContext*, TextureShaderClass*, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX );
	void Shutdown();
};

