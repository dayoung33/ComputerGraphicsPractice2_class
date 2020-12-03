#include "SkyBox.h"
#include "modelclass.h"
#include "textureshaderclass.h"
#include "cameraclass.h"

enum DIR { FT, LF, BK, LT, UP, DN };
SkyBox::SkyBox()
{
	for (int i = 0; i < 6; i++)
		m_plane[i] = 0;
}

SkyBox::SkyBox(const SkyBox &)
{
}

SkyBox::~SkyBox()
{
}

bool SkyBox::Initialize(ID3D11Device* device, CameraClass* pCamera)
{
	m_camera = pCamera;
	bool result;
	m_plane[FT] = new ModelClass;
	if (!m_plane[FT])
		return false;

	result = m_plane[FT]->InitializePlane(device, L"./data/skybox/Skybox.png");
	if (!result)
		return false;
	
	return true;;
}

void SkyBox::Shutdown()
{
}

void SkyBox::Render(ID3D11DeviceContext* deviceContext,TextureShaderClass* pTextuarShader ,D3DMATRIX worldMatrix, D3DMATRIX viewMatrix,D3DMATRIX projectionMatrix)
{
	D3DXVECTOR3 cPos = m_camera->GetPosition();
	D3DXMATRIX matTans, matRotX, matScale;
	D3DXMatrixTranslation(&matTans, cPos.x, cPos.y, cPos.z+500.f);
	D3DXMatrixScaling(&matScale, 700.0f, 700.0f, 700.0f);
	//D3DXMatrixRotationY(&matRotX, D3DXToRadian(90.f));

	worldMatrix = matScale* matTans;

	m_plane[FT]->Render(deviceContext);
	// Render the model using the texture shader.
	pTextuarShader->Render(deviceContext, m_plane[0]->GetIndexCount(),
		worldMatrix, viewMatrix, projectionMatrix, m_plane[0]->GetTexture());
}
