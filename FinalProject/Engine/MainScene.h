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



////////////////////////////////////////////////////////////////////////////////
// Class name: GraphicsClass
////////////////////////////////////////////////////////////////////////////////
class MainScene
	{
	public:
		MainScene();
		MainScene(const MainScene&);
		~MainScene();

		bool Initialize(int, int, HWND);
		void Shutdown();
		bool Frame(int, int);

		void CamMoveLR(float x);
		void CamMoveBF(float z);
		void CamLookRotate(DIMOUSESTATE& curMouse, DIMOUSESTATE& nextMouse);
		void SetInput(InputClass* _Input);
	private:
		bool Render(float);

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
		GameObjectMgr* m_pGameObjectMgr[3];
		GameObject* m_pPlayer;
		GameObject* m_pAIPlayer;

		FpsClass* m_pFps;
		CpuClass* m_pCpu;

		int m_SceneNum;

};

