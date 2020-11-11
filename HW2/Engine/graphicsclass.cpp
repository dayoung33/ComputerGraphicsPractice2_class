////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"
#include "TableClass.h"
#include "Player.h"
#include "Ball.h"
#include "AIPlayer.h"

GraphicsClass::GraphicsClass()
{
	m_D3D = 0;
	m_Camera = 0;
	m_LightShader = 0;
	m_PointLightShader = 0;
	m_Light1 = 0;
	m_Light2 = 0;
	m_Light3 = 0;
	m_Light = 0;
	m_TextureShader = 0;
	m_Bitmap = 0;
	m_Text = 0;
	m_SkyBoxShader = 0;
	m_pGameObjectMgr = 0;
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;
	D3DXMATRIX baseViewMatrix;

	// Create the Direct3D object.
	m_D3D = new D3DClass;
	if(!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	// Create the camera object.
	m_Camera = new CameraClass;
	if(!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera.
	m_Camera->SetPosition(0.0f, 100.0f, -150.0f);
	m_Camera->SetRotation(0.0f, 0.0f, 0.0f);

	m_Camera->Render();
	m_Camera->GetViewMatrix(baseViewMatrix);


	// Create the text object.
	m_Text = new TextClass;
	if (!m_Text)
	{
		return false;
	}

	// Create the texture shader object.
	m_TextureShader = new TextureShaderClass;
	if (!m_TextureShader)
	{
		return false;
	}
	// Initialize the texture shader object.
	result = m_TextureShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the texture shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the bitmap object.
	m_Bitmap = new BitmapClass;
	if (!m_Bitmap)
	{
		return false;
	}
	// Initialize the bitmap object.
	result = m_Bitmap->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight,
		L"../Engine/data/seafloor.dds", 256, 256);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the bitmap object.", L"Error", MB_OK);
		return false;
	}

	// Initialize the text object.
	result = m_Text->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), hwnd, screenWidth,
		screenHeight, baseViewMatrix);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the text object.", L"Error", MB_OK);
		return false;
	}

	//m_SkyBoxShader = new SkyboxShaderClass;
	//if (!m_SkyBoxShader)
	//	return false;

	//result = m_SkyBoxShader->Initialize(m_D3D->GetDevice(), hwnd);
	//if (!result)
	//{
	//	MessageBox(hwnd, L"Could not initialize the SkyBox object.", L"Error", MB_OK);
	//	return false;
	//}

	m_pGameObjectMgr = new GameObjectMgr;
	if (!m_pGameObjectMgr)
		return false;

	GameObject* pGameObject = nullptr;

	// Create the model object.
	pGameObject = new TableClass;
	if (!pGameObject)
		return false;
	result = pGameObject->Initialize(m_D3D->GetDevice(), L"./data/10450_Rectangular_Grass_Patch_v1_iterations-2.obj", L"./data/pingpong.png");
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	m_pGameObjectMgr->PushGameObject(pGameObject);

	GameObject* pPlayer = nullptr;
	pPlayer = new Player;
	result = pPlayer->Initialize(m_D3D->GetDevice(), L"./data/12221_Cat_v1_l3.obj", L"./data/Cat_diffuse.jpg");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	dynamic_cast<Player*>(pPlayer)->Init(m_Input);
	m_pGameObjectMgr->PushGameObject(pPlayer);

	GameObject* pAIPlayer = nullptr;
	pAIPlayer = new AIPlayer;
	result = pAIPlayer->Initialize(m_D3D->GetDevice(), L"./data/12221_Cat_v1_l3.obj", L"./data/Cat_diffuse.jpg");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	m_pGameObjectMgr->PushGameObject(pAIPlayer);

		pGameObject = new Ball;
	if (!pGameObject)
		return false;
	result = pGameObject->Initialize(m_D3D->GetDevice(), L"./data/12190_Heart_v1_L3.obj", L"./data/red.png");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	dynamic_cast<Ball*>(pGameObject)->SetPlayer(pPlayer);
	dynamic_cast<Ball*>(pGameObject)->SetAIPlayer(pAIPlayer);
	m_pGameObjectMgr->PushGameObject(pGameObject);

	// Create the light shader object.
	m_LightShader = new LightShaderClass;
	if(!m_LightShader)
	{
		return false;
	}

	// Initialize the light shader object.
	result = m_LightShader->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false;
	}
	m_PointLightShader = new LightShaderClass;
	if (!m_PointLightShader)
	{
		return false;
	}

	// Initialize the light shader object.
	result = m_PointLightShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the light object.
	m_Light = new LightClass;
	if(!m_Light)
	{
		return false;
	}

	// Initialize the light object.
	m_Light->SetAmbientColor(0.3f, 0.3f, 0.3f, 0.3f);
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetDirection(0.0f, 0.0f, 1.0f);
	m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetSpecularPower(32.0f);

	// Create the first light object.
	m_Light1 = new LightClass;
	if (!m_Light1)
	{
		return false;
	}

	// Initialize the first light object.
	m_Light1->SetDiffuseColor(1.0f, 0.0f, 0.0f, 1.0f);
	m_Light1->SetPosition(30.0f, 1.0f, -20.0f);


	// Create the second light object.
	m_Light2 = new LightClass;
	if (!m_Light2)
	{
		return false;
	}

	// Initialize the second light object.
	m_Light2->SetDiffuseColor(0.0f, 1.0f, 0.0f, 1.0f);
	m_Light2->SetPosition(0.0f, 1.0f, -20.0f);


	// Create the third light object.
	m_Light3 = new LightClass;
	if (!m_Light3)
	{
		return false;
	}

	// Initialize the third light object.
	m_Light3->SetDiffuseColor(0.0f, 0.0f, 1.0f, 1.0f);
	m_Light3->SetPosition(-30.0f, 1.0f, -20.0f);

	return true;
}


void GraphicsClass::Shutdown()
{
	if (m_pGameObjectMgr)
	{
		delete m_pGameObjectMgr;
		m_pGameObjectMgr = 0;
	}

	// Release the light object.
	if(m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}
	if (m_Light1)
	{
		delete m_Light1;
		m_Light1 = 0;
	}

	if (m_Light2)
	{
		delete m_Light2;
		m_Light2 = 0;
	}

	if (m_Light3)
	{
		delete m_Light3;
		m_Light3 = 0;
	}

	// Release the light shader object.
	if(m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
	}
	if (m_PointLightShader)
	{
		m_PointLightShader->Shutdown();
		delete m_PointLightShader;
		m_PointLightShader = 0;
	}

	// Release the text object.
	if (m_Text)
	{
		m_Text->Shutdown();
		delete m_Text;
		m_Text = 0;
	}

	// Release the bitmap object.
	if (m_Bitmap)
	{
		m_Bitmap->Shutdown();
		delete m_Bitmap;
		m_Bitmap = 0;
	}

	// Release the texture shader object.
	if (m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}

	if (m_SkyBoxShader)
	{
		m_SkyBoxShader->Shutdown();
		delete m_SkyBoxShader;
		m_SkyBoxShader = 0;
	}

	// Release the camera object.
	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the D3D object.
	if(m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	return;
}


bool GraphicsClass::Frame(int mouseX, int mouseY)
{
	bool result;
	static float rotation = 0.0f;

	// Update the rotation variable each frame.
	rotation += (float)D3DX_PI * 0.005f;
	if(rotation > 360.0f)
	{
		rotation -= 360.0f;
	}
	result = m_pGameObjectMgr->Frame();
	if (!result)
	{
		return false;
	}
	// Render the graphics scene.
	result = Render(rotation);
	if(!result)
	{
		return false;
	}

	return true;
}

void GraphicsClass::OffAmbient()
{
	m_Light->SetAmbientColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void GraphicsClass::OffDiffuse()
{
	m_Light->SetDiffuseColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void GraphicsClass::OffSpecular()
{
	m_Light->SetSpecularColor(0.0f, 0.0f, 0.0f, 0.0f);
	m_Light->SetSpecularPower(32000.0f);
}

void GraphicsClass::OffPointLight()
{
	m_Light1->SetDiffuseColor(0.0f, 0.0f, 0.0f, 0.0f);
	m_Light2->SetDiffuseColor(0.0f, 0.0f, 0.0f, 0.0f);
	m_Light3->SetDiffuseColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void GraphicsClass::OnLight()
{
	m_Light->SetAmbientColor(0.15f, 0.15f, 0.15f, 0.15f);
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetSpecularPower(32.0f);

	m_Light1->SetDiffuseColor(1.0f, 0.0f, 0.0f, 1.0f);
	m_Light2->SetDiffuseColor(0.0f, 1.0f, 0.0f, 1.0f);
	m_Light3->SetDiffuseColor(0.0f, 0.0f, 1.0f, 1.0f);


}


bool GraphicsClass::Render(float rotation)
{
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix;
	bool result;
	D3DXVECTOR4 diffuseColor[4];
	D3DXVECTOR4 lightPosition[4];

	// Create the diffuse color array from the four light colors.
	diffuseColor[0] = m_Light1->GetDiffuseColor();
	diffuseColor[1] = m_Light2->GetDiffuseColor();
	diffuseColor[2] = m_Light3->GetDiffuseColor();

	// Create the light position array from the four light positions.
	lightPosition[0] = m_Light1->GetPosition();
	lightPosition[1] = m_Light2->GetPosition();
	lightPosition[2] = m_Light3->GetPosition();

	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	m_D3D->GetOrthoMatrix(orthoMatrix);
	
	m_pGameObjectMgr->Render(m_D3D->GetDeviceContext(), m_LightShader, viewMatrix, projectionMatrix, m_Camera, m_Light, diffuseColor, lightPosition);

	// Turn off the Z buffer to begin all 2D rendering.
	m_D3D->TurnZBufferOff();

	// Put the bitmap vertex and index buffers on the graphics pipeline to prepare them for drawing.
	//result = m_Bitmap->Render(m_D3D->GetDeviceContext(), 200, 200);
	//if (!result)
	//{
	//	return false;
	//}

	// Render the bitmap with the texture shader.
	//result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Bitmap->GetIndexCount(),
	//	worldMatrix, viewMatrix, orthoMatrix, m_Bitmap->GetTexture());
	//if (!result)
	//{
	//	return false;
	//}
	// Turn on the alpha blending before rendering the text.
	m_D3D->TurnOnAlphaBlending();

	// Render the text strings.
	result = m_Text->Render(m_D3D->GetDeviceContext(), worldMatrix, orthoMatrix);
	if (!result)
	{
		return false;
	}
	// Turn off alpha blending after rendering the text.
	m_D3D->TurnOffAlphaBlending();

	// Turn the Z buffer back on now that all 2D rendering has completed.
	m_D3D->TurnZBufferOn();

	/*result = m_SkyBoxShader->Render(m_D3D->GetDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, m_Camera->GetPosition());
	if (!result)
	{
		return false;
	}*/


	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}

void GraphicsClass::CamMoveLR(float x)
{
	m_Camera->MoveLeftRight(x);
}

void GraphicsClass::CamMoveBF(float z)
{
	m_Camera->MoveBackForward(z);
}

void GraphicsClass::CamLookRotate(DIMOUSESTATE & curMouse, DIMOUSESTATE & nextMouse)
{
	m_Camera->LookRotation(curMouse, nextMouse);
}

void GraphicsClass::SetInput(InputClass * _Input)
{
	m_Input = _Input;
}
