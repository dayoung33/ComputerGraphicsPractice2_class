#pragma once
#include <d3d11.h>
#include <d3dx10math.h>

class ModelClass;
class TextureShaderClass;
class CameraClass;
class SkyBox 
{
public:
	SkyBox();
	SkyBox(const SkyBox&);
	~SkyBox();

	bool Initialize(ID3D11Device*,CameraClass*);
	void Shutdown();
	void Render(ID3D11DeviceContext * deviceContext, TextureShaderClass * pTextuarShader, D3DMATRIX worldMatrix, D3DMATRIX viewMatrix, D3DMATRIX projectionMatrix);

private:
	ModelClass* m_plane[6];
	CameraClass* m_camera;

};

