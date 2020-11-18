#include "GameObjectMgr.h"
GameObjectMgr::GameObjectMgr()
{
}

GameObjectMgr::GameObjectMgr(const GameObjectMgr & other)
{
}

GameObjectMgr::~GameObjectMgr()
{
	Shutdown();
}

bool GameObjectMgr::PushGameObject(GameObject * pGameObject)
{
	m_GameObjectLst.push_back(pGameObject);

	return true;
}

bool GameObjectMgr::Frame()
{
	if (m_GameObjectLst.size() == 0)
		return true;

	for (auto iter : m_GameObjectLst)
	{
		if (!iter->Frame())
		{
			return false;
		}
	}
	return true;
}

void GameObjectMgr::Render(ID3D11DeviceContext* deviceContext, LightShaderClass *pLightShader, D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix,
	CameraClass* pCamera, LightClass* pLight, D3DXVECTOR4 vDiffusecolor[], D3DXVECTOR4 vLightPosition[])
{
	if (m_GameObjectLst.size() == 0)
		return;

	for (auto iter : m_GameObjectLst)
	{
		iter->Render(deviceContext);
		pLightShader->Render(deviceContext, iter, viewMatrix, projectionMatrix, pCamera, pLight, vDiffusecolor, vLightPosition);
	}
}

void GameObjectMgr::EraseGameObject(GameObject * pGameObject)
{
	if (m_GameObjectLst.size() == 0
		|| !pGameObject)
		return;

	for (auto iter = m_GameObjectLst.begin(); iter != m_GameObjectLst.end(); )
	{
		if (*iter == pGameObject)
		{
			delete *iter;
			*iter = 0;
			iter = m_GameObjectLst.erase(iter);
		}
		else
			++iter;
	}
}

void GameObjectMgr::Shutdown()
{
	if (m_GameObjectLst.size() == 0)
	{
		m_GameObjectLst.clear();
		return;
	};

	for (auto iter : m_GameObjectLst)
	{
		if (iter)
		{
			delete iter;
			iter = 0;
		}
	}

	m_GameObjectLst.clear();
}

int GameObjectMgr::Get_PolySize()
{
	int Polycnt = 0;
	for (auto iter : m_GameObjectLst)
	{
		if (iter)
		{
			Polycnt += (iter->GetVertexCount() / 3);
		}
	}

	return Polycnt;
}