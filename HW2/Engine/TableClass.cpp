#include "TableClass.h"

TableClass::TableClass()
{
	m_vPos = { 0.f,0.f,0.f };
}

TableClass::TableClass(TableClass &)
{
}

TableClass::~TableClass()
{
}

void TableClass::Init()
{
}

bool TableClass::Frame()
{

	D3DXMATRIX matTans, matRotX, matRotY, matScale;

	D3DXMatrixTranslation(&matTans, 0.f, 0.f, 80.f);
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixRotationX(&matRotX, D3DXToRadian(90.f));
	D3DXMatrixRotationZ(&matRotY, D3DXToRadian(90.f));

	m_matWorld = matScale* matRotY* matTans * matRotX;
	return true;
}

void TableClass::Shutdown()
{
}
