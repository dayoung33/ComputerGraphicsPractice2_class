#pragma once

#include <d3d11.h>
#include <list>

#include "d3dclass.h"
#include "GameObject.h"
#include "cameraclass.h"
#include "lightclass.h"
#include "lightshaderclass.h"
#include "textureshaderclass.h"
using namespace std;

class D3DClass;
class GameObject;
class CameraClass;
class LightClass;
class LightShaderClass;
class TextureShaderClass;

class GameObjectMgr
{
public:
	GameObjectMgr();
	GameObjectMgr(const GameObjectMgr&);
	~GameObjectMgr();

public:
	bool PushGameObject(GameObject* pGameObject);

	bool Frame();
	void Render(ID3D11DeviceContext * deviceContext, LightShaderClass * pLightShader, D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix, CameraClass * pCamera, LightClass * pLight, D3DXVECTOR4 vDiffusecolor[], D3DXVECTOR4 vLightPosition[]);
	
	void EraseGameObject(GameObject* pGameObject);
	void Shutdown();

	int Get_PolySize();

	int Get_Size() { return m_GameObjectLst.size(); }

private:
	list<GameObject*> m_GameObjectLst;
};