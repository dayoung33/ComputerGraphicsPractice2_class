#include "GameSystemMgr.h"

GameSystemMgr::GameSystemMgr()
{
}

GameSystemMgr::GameSystemMgr(const GameSystemMgr &)
{
}

GameSystemMgr::~GameSystemMgr()
{
	Shutdown();
}

bool GameSystemMgr::PushGameObject(GameSystem * pGameObject)
{
	m_GameObjectLst.push_back(pGameObject);

	return true;
}

bool GameSystemMgr::Frame()
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

void GameSystemMgr::Render(ID3D11DeviceContext * deviceContext, TextureShaderClass * pTextureShader, D3DXMATRIX viewMatrix, D3DXMATRIX worldMatrix, D3DXMATRIX orthoMatrix)
{
	if (m_GameObjectLst.size() == 0)
		return;

	for (auto iter : m_GameObjectLst)
	{
		iter->Render(deviceContext,pTextureShader,viewMatrix,worldMatrix, orthoMatrix);
	}
}


void GameSystemMgr::EraseGameObject(GameSystem * pGameObject)
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

void GameSystemMgr::Shutdown()
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
