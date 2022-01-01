#include "stdafx.h"
#include "Multi_Texture.h"


CMulti_Texture::CMulti_Texture()
{
}


CMulti_Texture::~CMulti_Texture()
{
	Release_Texture(); 
}
//D:\박병건\118C\D2D\FrameWork\Texture\Stage\Terrain\Tile\Tile%d.png
//D:\박병건\118C\D2D\FrameWork\Texture\Stage\Player\Stand\AKIHA_AKI00_00%d.png
////		L"../Texture/Stage/Player/Dash/AKIHA_AKI13_00%d.png",L"Player", L"Dash", 11
HRESULT CMulti_Texture::Insert_Texture(const wstring & wstrFilePath, int rgb[], const wstring & wstrStateKey /*= L""*/, const DWORD & dwCount /*= 0*/)
{
	D3DCOLOR color = D3DCOLOR_ARGB(rgb[0], rgb[1], rgb[2], rgb[3]);
	map<wstring, vector<TEXINFO*>>::iterator iter_find = m_mapMultiTex.find(wstrStateKey);
	if (iter_find == m_mapMultiTex.end())
	{
		TCHAR szFilePath[MAX_PATH] = L""; 
		TEXINFO* pTexInfo = nullptr; 
		for (int i = 0 ; i < dwCount; ++i)
		{
			//D:\박병건\118C\D2D\FrameWork\Texture\Stage\Terrain\Tile\Tile0.png
			swprintf_s(szFilePath, wstrFilePath.c_str(), i);
			pTexInfo = new TEXINFO; 
			// 이미지에 대한 정보를 불러와서 D3DXIMAGE_INFO에 집어넣어줄꺼야. 
			if (FAILED(D3DXGetImageInfoFromFile(szFilePath, &pTexInfo->tImageInfo)))
				goto ERR;
			if (FAILED(D3DXCreateTextureFromFileEx(CGraphic_Device::Get_Instance()->Get_Device(),
				szFilePath,
				pTexInfo->tImageInfo.Width,
				pTexInfo->tImageInfo.Height,
				pTexInfo->tImageInfo.MipLevels,
				0,
				pTexInfo->tImageInfo.Format,
				D3DPOOL_MANAGED,
				D3DX_DEFAULT,
				D3DX_DEFAULT,
				color,
				nullptr,
				nullptr,
				&pTexInfo->pTexture)))
				goto ERR;
			
			m_mapMultiTex[wstrStateKey].emplace_back(pTexInfo); 
			//m_mapMultiTex[wstrStateKey].여기까지가 벡터 
			//emplace_back(pTexInfo); 에 원소 삽입. 
		}
	}

	return S_OK;
ERR:
	wstring wstrCombine = wstrFilePath + L" Insert MultiTex Failed";
	ERR_MSG(wstrCombine.c_str());
	return E_FAIL; 
}

 TEXINFO * CMulti_Texture::Get_TexInfo(const wstring & wstrStateKey /*= L""*/, const DWORD & dwIndex /*= 0*/)
{
	map<wstring, vector<TEXINFO*>>::iterator iter_find = m_mapMultiTex.find(wstrStateKey); 
	if(iter_find == m_mapMultiTex.end())
		return nullptr;

	if (iter_find->second.size() <= dwIndex)
		return nullptr; 

	return iter_find->second[dwIndex];
	//return m_mapMultiTex[wstrStateKey][dwIndex];
}

void CMulti_Texture::Release_Texture()
{
	for (auto& rPair : m_mapMultiTex)
	{
		for (auto& pTexInfo : rPair.second)
			Safe_Delete(pTexInfo); 
		
		rPair.second.clear(); 
		rPair.second.shrink_to_fit(); 
	}
	m_mapMultiTex.clear(); 
}
