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
	m_Text = 0;
	m_pGameObjectMgr = 0;
	m_pPlayer = 0;
	m_pAIPlayer = 0;
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
	m_Camera->SetPosition(0.0f, 100.0f, -250.0f);
	m_Camera->SetRotation(0.0f, 0.0f, 0.0f);

	m_Camera->Render();
	m_Camera->GetViewMatrix(baseViewMatrix);


	// Create the text object.
	m_Text = new TextClass;
	if (!m_Text)
	{
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

	m_pGameObjectMgr = new GameObjectMgr;
	if (!m_pGameObjectMgr)
		return false;

	GameObject* pGameObject = nullptr;

	// Create the model object.
	pGameObject = new TableClass;
	if (!pGameObject)
		return false;
	result = pGameObject->Initialize(m_D3D->GetDevice(), L"./data/10233_Kitchen_Table_v2_max2011_it2.obj", L"./data/10233_Kitchen_Table_v1_Diffuse.jpg");
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	m_pGameObjectMgr->PushGameObject(pGameObject);

	m_pPlayer = new Player;
	result = m_pPlayer->Initialize(m_D3D->GetDevice(), L"./data/12221_Cat_v1_l3.obj", L"./data/Cat_diffuse.jpg");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	dynamic_cast<Player*>(m_pPlayer)->Init(m_Input);
	m_pGameObjectMgr->PushGameObject(m_pPlayer);

	m_pAIPlayer = new AIPlayer;
	result = m_pAIPlayer->Initialize(m_D3D->GetDevice(), L"./data/12221_Cat_v1_l3.obj", L"./data/Cat_diffuse.jpg");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	m_pGameObjectMgr->PushGameObject(m_pAIPlayer);

		pGameObject = new Ball;
	if (!pGameObject)
		return false;
	result = pGameObject->Initialize(m_D3D->GetDevice(), L"./data/12190_Heart_v1_L3.obj", L"./data/red.png");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	dynamic_cast<Ball*>(pGameObject)->Init(m_Input);
	dynamic_cast<Ball*>(pGameObject)->SetPlayer(m_pPlayer);
	dynamic_cast<Ball*>(pGameObject)->SetAIPlayer(m_pAIPlayer);
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
	m_Light1->SetDiffuseColor(1.0f, 1.0f, 0.0f, 1.0f);
	m_Light1->SetPosition(90.0f, 1.0f, 0.0f);


	// Create the second light object.
	m_Light2 = new LightClass;
	if (!m_Light2)
	{
		return false;
	}

	// Initialize the second light object.
	m_Light2->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light2->SetPosition(0.0f, 1.0f, 0.0f);


	// Create the third light object.
	m_Light3 = new LightClass;
	if (!m_Light3)
	{
		return false;
	}

	// Initialize the third light object.
	m_Light3->SetDiffuseColor(1.0f, 0.0f, 0.0f, 1.0f);
	m_Light3->SetPosition(-90.0f, 1.0f, 0.0f);

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
	m_Text->SetScore(dynamic_cast<AIPlayer*>(m_pAIPlayer)->GetScore(), dynamic_cast<Player*>(m_pPlayer)->GetScore(), m_D3D->GetDeviceContext());
	m_Text->SetWin(dynamic_cast<AIPlayer*>(m_pAIPlayer)->GetWin(), dynamic_cast<Player*>(m_pPlayer)->GetWin(), m_D3D->GetDeviceContext());
	// Update the rotation variable each frame.
	if(dynamic_cast<AIPlayer*>(m_pAIPlayer)->GetWin())
		m_Light2->SetDiffuseColor(1.0f, 0.0f, 0.0f, 1.0f);
	if(dynamic_cast<Player*>(m_pPlayer)->GetWin())
		m_Light2->SetDiffuseColor(1.0f, 1.0f, 0.0f, 1.0f);

	m_Light1->SetPosition(90.0f, 1.0f, m_pPlayer->GetPos().y);
	m_Light3->SetPosition(-90.0f, 1.0f, m_pAIPlayer->GetPos().y);

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
