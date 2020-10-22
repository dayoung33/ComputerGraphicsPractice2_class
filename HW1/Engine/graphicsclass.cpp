////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"


GraphicsClass::GraphicsClass()
{
	m_D3D = 0;
	m_Camera = 0;
	m_Model = 0;
	m_Model2 = 0;
	m_Model3 = 0;
	m_Ground = 0;
	m_LightShader = 0;
	m_PointLightShader = 0;
	m_Light1 = 0;
	m_Light2 = 0;
	m_Light3 = 0;
	m_Light = 0;
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
	m_Camera->SetPosition(0.0f, 2.0f, -100.0f);
//	m_Camera->SetPosition(0.0f, 0.5f, -3.0f);
	//m_Camera->SetPosition(0.0f, 2.0f, -12.0f);


	// Create the model object.
	m_Model = new ModelClass;
	if(!m_Model)	
		return false;
	
	m_Model2 = new ModelClass;
	if (!m_Model2)
		return false;

	m_Model3 = new ModelClass;
	if (!m_Model3)
		return false;

	m_Ground = new ModelClass;
	if (!m_Ground)
		return false;
	

	// Initialize the model object.
	result = m_Model->Initialize(m_D3D->GetDevice(), L"./data/10436_Cactus_v1_max2010_it2.obj", L"./data/10436_Cactus_v1_Diffuse.dds");
	result = m_Model2->Initialize(m_D3D->GetDevice(), L"./data/12330_Statue_v1_L2.obj", L"./data/DavidFixedDiff.jpg");
	result = m_Model3->Initialize(m_D3D->GetDevice(), L"./data/12221_Cat_v1_l3.obj", L"./data/Cat_diffuse.jpg");
	result = m_Ground->Initialize(m_D3D->GetDevice(), L"./data/10450_Rectangular_Grass_Patch_v1_iterations-2.obj", L"./data/stone01.dds");
//	result = m_Model->Initialize(m_D3D->GetDevice(), "./data/chair.txt", L"./data/chair_d.dds");

	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

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

	// Release the model object.
	if(m_Model)
	{
		m_Model->Shutdown();
		delete m_Model;
		m_Model = 0;
	}
	if (m_Model2)
	{
		m_Model2->Shutdown();
		delete m_Model2;
		m_Model2 = 0;
	}
	if (m_Model3)
	{
		m_Model3->Shutdown();
		delete m_Model3;
		m_Model3 = 0;
	}
	if (m_Ground)
	{
		m_Ground->Shutdown();
		delete m_Ground;
		m_Ground = 0;
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


bool GraphicsClass::Frame()
{
	bool result;
	static float rotation = 0.0f;


	// Update the rotation variable each frame.
	rotation += (float)D3DX_PI * 0.005f;
	if(rotation > 360.0f)
	{
		rotation -= 360.0f;
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
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix;
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

	// Rotate the world matrix by the rotation value so that the triangle will spin.
	D3DXMATRIX matTans, matRot, matRotX, matScale;

	D3DXMatrixTranslation(&matTans, -27.f, 0.f, -10.f);
	D3DXMatrixScaling(&matScale, 0.1f, 0.1f, 0.1f);
	D3DXMatrixRotationX(&matRotX, 0.f);
	D3DXMatrixRotationY(&matRot, rotation);

	worldMatrix = matScale * matRot * matTans * matRotX;
	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_Model->Render(m_D3D->GetDeviceContext());
	// Render the model using the light shader.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
								   m_Model->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), 
								   m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower(), diffuseColor, lightPosition);
	if (!result)
	{
		return false;
	}

	D3DXMatrixTranslation(&matTans, 0.f, 0.f, -1.f);
	D3DXMatrixScaling(&matScale, 0.05f, 0.05f, 0.05f);
	D3DXMatrixRotationX(&matRotX, -150.f);
	D3DXMatrixRotationZ(&matRot, rotation);

	worldMatrix = matScale * matRot * matTans * matRotX;
	m_Model2->Render(m_D3D->GetDeviceContext());

	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model2->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Model2->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower(), diffuseColor, lightPosition);

	if (!result)
	{
		return false;
	}

	D3DXMatrixTranslation(&matTans, 27.f, 0.f, -2.f);
	D3DXMatrixScaling(&matScale, 0.2f, 0.2f, 0.2f);
	D3DXMatrixRotationX(&matRotX, -150.f);
	D3DXMatrixRotationX(&matRot, rotation);

	worldMatrix = matScale * matRot * matTans * matRotX;
	m_Model3->Render(m_D3D->GetDeviceContext());

	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model3->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Model3->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower(), diffuseColor, lightPosition);
	if (!result)
	{
		return false;
	}
	D3DXMatrixTranslation(&matTans, 0.f, 20.f, 10.f);
	D3DXMatrixScaling(&matScale, 0.4f, 0.4f, 0.4f);
	D3DXMatrixRotationX(&matRotX, D3DXToRadian(65.f));

	worldMatrix = matScale * matTans * matRotX;
	m_Ground->Render(m_D3D->GetDeviceContext());	

	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Ground->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Ground->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower(), diffuseColor, lightPosition);
	if (!result)
	{
		return false;
	}


	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}