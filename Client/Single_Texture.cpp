#include "stdafx.h"
#include "Single_Texture.h"


CSingle_Texture::CSingle_Texture()
	:m_tTexInfo({})
{
}


CSingle_Texture::~CSingle_Texture()
{
	Release_Texture(); 
}

HRESULT CSingle_Texture::Insert_Texture(const wstring & wstrFilePath, int rgb[] ,const wstring & wstrStateKey /*= L""*/, const DWORD & dwCount /*= 0*/)
{
	D3DCOLOR color = D3DCOLOR_ARGB(rgb[0], rgb[1], rgb[2], rgb[3]);

	// 이미지에 대한 정보를 불러와서 D3DXIMAGE_INFO에 집어넣어줄꺼야. 
	if (FAILED(D3DXGetImageInfoFromFile(wstrFilePath.c_str(), &m_tTexInfo.tImageInfo)))
		goto ERR; 
	if (FAILED(D3DXCreateTextureFromFileEx(CGraphic_Device::Get_Instance()->Get_Device(),
		wstrFilePath.c_str(),
		m_tTexInfo.tImageInfo.Width,
		m_tTexInfo.tImageInfo.Height,
		m_tTexInfo.tImageInfo.MipLevels,
		0,
		m_tTexInfo.tImageInfo.Format,
		D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		color,
		nullptr,
		nullptr,
		&m_tTexInfo.pTexture)))
		goto ERR;
	//8000X1200; 
	return S_OK; 
ERR:
	ERR_MSG(L"Single_Texture Error"); 
	return E_FAIL;
}

 TEXINFO * CSingle_Texture::Get_TexInfo(const wstring & wstrStateKey/* = L""*/, const DWORD & dwIndex /*= 0*/)
{
	return &m_tTexInfo;
}

void CSingle_Texture::Release_Texture()
{
	if (m_tTexInfo.pTexture)
		m_tTexInfo.pTexture->Release(); 
}
