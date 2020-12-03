#include <d3d11.h>
#include <list>

#include "d3dclass.h"
#include "GameSystem.h"
#include "cameraclass.h"
#include "textureshaderclass.h"
using namespace std;

class GameSystemMgr
{

public:
	GameSystemMgr();
	GameSystemMgr(const GameSystemMgr&);
	~GameSystemMgr();

public:
	bool PushGameObject(GameSystem* pGameObject);

	bool Frame();
	void Render(ID3D11DeviceContext *deviceContext, TextureShaderClass *pTextureShader, D3DXMATRIX viewMatrix, D3DXMATRIX worldMatrix, D3DXMATRIX baseViewMatrix, D3DXMATRIX orthoMatrix, D3DXVECTOR3 cameraLook);

	void EraseGameObject(GameSystem* pGameObject);
	void Shutdown();

	int Get_Size() { return m_GameObjectLst.size(); }

private:
	list<GameSystem*> m_GameObjectLst;
};

