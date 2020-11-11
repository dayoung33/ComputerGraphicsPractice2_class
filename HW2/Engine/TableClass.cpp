#include "TableClass.h"

TableClass::TableClass()
{
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

	D3DXMATRIX matTans, matRotX, matScale;

	D3DXMatrixTranslation(&matTans, 0.f, 20.f, 10.f);
	D3DXMatrixScaling(&matScale, 0.8f, 0.4f, 0.1f);
	D3DXMatrixRotationX(&matRotX, D3DXToRadian(90.f));

	m_matWorld = matScale * matTans * matRotX;
	return true;
}

void TableClass::Shutdown()
{
}
