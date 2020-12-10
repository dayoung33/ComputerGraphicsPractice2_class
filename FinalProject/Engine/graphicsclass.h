////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_

//////////////
// INCLUDES //
//////////////
#include <dinput.h>


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "d3dclass.h"
#include "cameraclass.h"
#include "modelclass.h"
#include "lightshaderclass.h"
#include "lightclass.h"
#include "textureshaderclass.h"
#include "bitmapclass.h"
#include "textclass.h"
#include "GameObjectMgr.h"
#include "inputclass.h"
#include "GameObject.h"
#include "FpsClass.h"
#include "CpuClass.h"
#include "GameSystemMgr.h"
#include "GameSystem.h"
#include "SkyBox.h"

/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;


////////////////////////////////////////////////////////////////////////////////
// Class name: GraphicsClass
////////////////////////////////////////////////////////////////////////////////
class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame(int, int);


	void CamMoveLR(float x);
	void CamMoveBF(float z);
	void CamLookRotate(DIMOUSESTATE& curMouse, DIMOUSESTATE& nextMouse);
	void SetInput(InputClass* _Input);
private:
	bool Render();

private:
	D3DClass* m_D3D;
	CameraClass* m_Camera;
	LightShaderClass* m_LightShader;
	LightShaderClass* m_PointLightShader;
	LightClass* m_Light;
	LightClass *m_Light1, *m_Light2, *m_Light3;
	TextureShaderClass* m_TextureShader;
	TextClass* m_Text;
	BitmapClass* m_Bitmap;
	InputClass* m_Input;
	GameObjectMgr* m_pGameObjectMgr;
	GameObject* m_pPlayer;
	GameObject* m_pMovingTree;
	GameObject* m_pDart;
	GameObject* m_pDartBoard;
	GameSystemMgr* m_pGameSystemMgr;

	FpsClass* m_pFps;
	CpuClass* m_pCpu;

	D3DXMATRIX baseViewMatrix;

	SkyBox* m_pSkyBox;

	bool m_bCameraMode;
	bool m_bIsPressed;
};

#endif