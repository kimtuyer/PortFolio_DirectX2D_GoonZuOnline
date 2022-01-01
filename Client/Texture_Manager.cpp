#include "stdafx.h"
#include "Texture_Manager.h"
#include "Single_Texture.h"
#include "Multi_Texture.h"

IMPLEMENT_SINGLETON(CTexture_Manager)
CTexture_Manager::CTexture_Manager()
{
}


CTexture_Manager::~CTexture_Manager()
{
	Release_Texture_Manager(); 
}
//L"../Texture/Stage/Player/Attack/AKIHA_AKI01_00%d.png",L"Player", L"Attack", 6
//		L"../Texture/Stage/Player/Dash/AKIHA_AKI13_00%d.png",L"Player", L"Dash", 11
//// L"../Texture/Cube.png", L"Cube"
HRESULT CTexture_Manager::Insert_Texture_Manager(TEX_ID eID, const wstring & wstrFilePath, const wstring & wstrObjectKey, int rgb[], const wstring & wstrStateKey, const DWORD & dwCount)
{
	map<wstring, CTexture*>::iterator iter_find = m_mapTexture.find(wstrObjectKey);
	CTexture* pTexture = nullptr; 
	if (m_mapTexture.end() == iter_find)
	{
		switch (eID)
		{
		case CTexture_Manager::TEX_SINGLE:
			pTexture = new CSingle_Texture;
			break;
		case CTexture_Manager::TEX_MULTI:
			pTexture = new CMulti_Texture; 
			break;
		default:
			break;
		}
		if (FAILED(pTexture->Insert_Texture(wstrFilePath, rgb, wstrStateKey, dwCount)))
			goto ERR; 

		m_mapTexture.emplace(wstrObjectKey, pTexture);
	}
	else if (TEX_MULTI == eID)
	{
		//m_mapTexture[wstrObjectKey] - 여기까지가 CMulti_Texture 
		if (FAILED(m_mapTexture[wstrObjectKey]->Insert_Texture(wstrFilePath, rgb, wstrStateKey, dwCount)))
			goto ERR; 
	}

	return S_OK;
ERR:
	ERR_MSG(L"Texture Insert Failed"); 
	return E_FAIL; 
}

 TEXINFO * CTexture_Manager::Get_TexInfo_Manager(const wstring & wstrOjbectKey, const wstring & wstrStateKey, const DWORD & dwIndex)
{
	auto& iter_find = m_mapTexture.find(wstrOjbectKey);
	if(m_mapTexture.end() == iter_find)
		return nullptr;
	return iter_find->second->Get_TexInfo(wstrStateKey, dwIndex);
	//return m_mapTexture[wstrOjbectKey]->Get_TexInfo(wstrStateKey, dwIndex); 
}

void CTexture_Manager::Release_Texture_Manager()
{
	for (auto& rPair : m_mapTexture)
		Safe_Delete(rPair.second); 
	m_mapTexture.clear(); 
}
