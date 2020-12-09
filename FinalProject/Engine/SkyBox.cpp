#include "SkyBox.h"
#include "modelclass.h"
#include "textureshaderclass.h"
#include "cameraclass.h"

enum DIR { FT, LF, BK, RT, UP, DN };
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
	result = m_plane[FT]->InitializePlane(device, L"./data/plane01.txt",L"./data/skybox/blue_ft.png");
	if (!result)
		return false;
	m_plane[LF] = new ModelClass;
	if (!m_plane[LF])
		return false;
	result = m_plane[LF]->InitializePlane(device, L"./data/plane01.txt", L"./data/skybox/blue_lf.png");
	if (!result)
		return false;
	m_plane[BK] = new ModelClass;
	if (!m_plane[BK])
		return false;
	result = m_plane[BK]->InitializePlane(device, L"./data/plane01.txt", L"./data/skybox/blue_bk.png");
	if (!result)
		return false;
	m_plane[RT] = new ModelClass;
	if (!m_plane[RT])
		return false;
	result = m_plane[RT]->InitializePlane(device, L"./data/plane01.txt", L"./data/skybox/blue_rt.png");
	if (!result)
		return false;
	m_plane[UP] = new ModelClass;
	if (!m_plane[UP])
		return false;
	result = m_plane[UP]->InitializePlane(device, L"./data/plane01.txt", L"./data/skybox/blue_up.png");
	if (!result)
		return false;
	m_plane[DN] = new ModelClass;
	if (!m_plane[DN])
		return false;
	result = m_plane[DN]->InitializePlane(device, L"./data/plane01.txt", L"./data/skybox/blue_dn.png");
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
	D3DXMatrixScaling(&matScale, 100.0f, 100.0f, 100.0f);
	D3DXMatrixRotationX(&matRotX, D3DXToRadian(-90.f));

	worldMatrix = matScale* matRotX * matTans;

	m_plane[FT]->Render(deviceContext);
	pTextuarShader->Render(deviceContext, m_plane[FT]->GetIndexCount(),
		worldMatrix, viewMatrix, projectionMatrix, m_plane[FT]->GetTexture());

	D3DXMatrixTranslation(&matTans, cPos.x+500.f, cPos.y, cPos.z);
	D3DXMatrixRotationZ(&matRotX, D3DXToRadian(90.f));

	worldMatrix = matScale * matRotX *matTans;

	m_plane[LF]->Render(deviceContext);
	pTextuarShader->Render(deviceContext, m_plane[LF]->GetIndexCount(),
		worldMatrix, viewMatrix, projectionMatrix, m_plane[LF]->GetTexture());

	D3DXMatrixTranslation(&matTans, cPos.x, cPos.y, cPos.z-500.f);
	D3DXMatrixRotationX(&matRotX, D3DXToRadian(90.f));

	worldMatrix = matScale * matRotX *matTans;

	m_plane[BK]->Render(deviceContext);
	pTextuarShader->Render(deviceContext, m_plane[BK]->GetIndexCount(),
		worldMatrix, viewMatrix, projectionMatrix, m_plane[BK]->GetTexture());

	D3DXMatrixTranslation(&matTans, cPos.x-500.f, cPos.y, cPos.z);
	D3DXMatrixRotationZ(&matRotX, D3DXToRadian(-90.f));

	worldMatrix = matScale * matRotX *matTans;

	m_plane[RT]->Render(deviceContext);
	pTextuarShader->Render(deviceContext, m_plane[RT]->GetIndexCount(),
		worldMatrix, viewMatrix, projectionMatrix, m_plane[RT]->GetTexture());

	D3DXMatrixTranslation(&matTans, cPos.x, cPos.y - 500.f, cPos.z);
	worldMatrix = matScale * matTans;

	m_plane[DN]->Render(deviceContext);
	pTextuarShader->Render(deviceContext, m_plane[DN]->GetIndexCount(),
		worldMatrix, viewMatrix, projectionMatrix, m_plane[DN]->GetTexture());

	D3DXMatrixTranslation(&matTans, cPos.x, cPos.y + 500.f, cPos.z);
	D3DXMatrixRotationZ(&matRotX, D3DXToRadian(180.f));

	worldMatrix = matScale * matRotX *matTans;

	m_plane[UP]->Render(deviceContext);
	pTextuarShader->Render(deviceContext, m_plane[UP]->GetIndexCount(),
		worldMatrix, viewMatrix, projectionMatrix, m_plane[UP]->GetTexture());

}
