#pragma once

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

/////////////
// GLOBALS //
/////////////
//const bool FULL_SCREEN = false;
//const bool VSYNC_ENABLED = true;
//const float SCREEN_DEPTH = 1000.0f;
//const float SCREEN_NEAR = 0.1f;


////////////////////////////////////////////////////////////////////////////////
// Class name: OpeningScene
////////////////////////////////////////////////////////////////////////////////
class OpeningScene
{
public:
	OpeningScene();
	OpeningScene(const OpeningScene&);
	~OpeningScene();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame(int, int);

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
	BitmapClass* m_Bitmap;
	InputClass* m_Input;

	int m_SceneNum;

};

