////////////////////////////////////////////////////////////////////////////////
// Filename: fontclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _FONTCLASS_H_
#define _FONTCLASS_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <d3dx10math.h>
#include <fstream>
using namespace std;


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "textureclass.h"


////////////////////////////////////////////////////////////////////////////////
// Class name: FontClass
////////////////////////////////////////////////////////////////////////////////
class FontClass
{
private:
	struct FontType
	{
		float left, right;
		int size;
	};

	struct VertexType
	{
		D3DXVECTOR3 position;
	    D3DXVECTOR2 texture;
	};

public:
	FontClass();
	FontClass(const FontClass&);
	~FontClass();

	bool Initialize(ID3D11Device*, const wchar_t*, const wchar_t*);
	void Shutdown();

	ID3D11ShaderResourceView* GetTexture();

	void BuildVertexArray(void*, const char*, float, float);

private:
	bool LoadFontData(const wchar_t*);
	void ReleaseFontData();
	bool LoadTexture(ID3D11Device*, const wchar_t*);
	void ReleaseTexture();

private:
	FontType* m_Font;
	TextureClass* m_Texture;
};

#endif