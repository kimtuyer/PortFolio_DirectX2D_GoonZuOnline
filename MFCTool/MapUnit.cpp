#include "stdafx.h"
#include "MapUnit.h"
#include "MFCToolView.h"

MapUnit::MapUnit()
{
}

MapUnit::~MapUnit()
{
	Release_MapUnit();
}

HRESULT MapUnit::Ready_MapUnit()
{
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Object/gate_%d.bmp", L"MapObject", L"Gate",74)))
		//L"../Texture/Stage/Terrain/Tile/Tile%d.png
		//L"../Texture/Stage/Object/Tile/Tile%d.bmp
		return E_FAIL;

	//MAPOBJECT* pMap = nullptr;
	//
	//m_vecMapObject.emplace_back(pMap);
	//
	//m_vecMapObject.reserve(23);
	////TILE* pTile = nullptr;
	//float fX = 0.f, fY = 0.f;
	//for (int i = 1; i < m_vecMapObject.size(); ++i)
	//{
	//		pMap = new MAPOBJECT;
	//		//pMap->vPos = { fX, fY, 0.f };
	//		pMap->vSize = { 1.f, 1.f, 0.f };
	//		pMap->iIndex = i;
	//		pMap->iParentIndex = 0;
	//		pMap->byDrawID = i;
	//		pMap->byOption = 0;
	//		m_vecMapObject.emplace_back(pMap);
	//	
	//}
	return S_OK;

}

void MapUnit::Update_MapUnit(D3DXVECTOR3 vMouse)
{




}

void MapUnit::Render_MapUnit()
{
	D3DXMATRIX matScale, matTrans, matWorld;
	DWORD dwSize = m_vecMapObject.size();
	TCHAR szBuf[32]{};
	//m_vecTile[31]->byDrawID = 0; 
	for (size_t i = 0; i < dwSize; ++i)
	{	
		const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo_Manager(L"MapObject", L"Gate", m_vecMapObject[i]->byDrawID);
		if (nullptr == pTexInfo)
			return;
		float fCenterX = float(pTexInfo->tImageInfo.Width >> 1);
		float fCenterY = float(pTexInfo->tImageInfo.Height >> 1);

		D3DXMatrixScaling(&matScale, m_vecMapObject[i]->vSize.x, m_vecMapObject[i]->vSize.y, 0.f);
		D3DXMatrixTranslation(&matTrans, m_vecMapObject[i]->vPos.x - m_pView->GetScrollPos(SB_HORZ), m_vecMapObject[i]->vPos.y - m_pView->GetScrollPos(SB_VERT), 0.f);
		matWorld = matScale * matTrans;

		CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
		CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

		//swprintf_s(szBuf, L"%d", i);
		//CGraphic_Device::Get_Instance()->Get_Font()->DrawTextW(CGraphic_Device::Get_Instance()->Get_Sprite(), szBuf, lstrlen(szBuf), nullptr, 0, D3DCOLOR_ARGB(255, 0, 0, 0));
	
	}
}

void MapUnit::MiniRender_MapUnit()
{
}

void MapUnit::Release_MapUnit()
{
	for (auto& pTile : m_vecMapObject)
		Safe_Delete(pTile);
	m_vecMapObject.clear();
	m_vecMapObject.shrink_to_fit();
}

void MapUnit::Change_MapUnit(const D3DXVECTOR3 & vPos, const BYTE & byDrawID, const BYTE & byOption)
{
	//int iIndex = Get_Index(vPos);
	//
	//if (-1 == iIndex)
	//	return;

	MAPOBJECT* pMap = new MAPOBJECT;
	pMap->vPos = vPos;
	pMap->byDrawID = byDrawID;
	pMap->byOption = byOption;
	pMap->vSize.x = 1;
	pMap->vSize.y = 1;

	m_vecMapObject.push_back(pMap);

}

int MapUnit::Get_Index(const D3DXVECTOR3 & vPos)
{
	int iSize = m_vecMapObject.size();
	for (int i = 0; i < iSize; ++i)
	{
		if (IsPicking(vPos, i))
			return i;
	}

	return -1;
}

bool MapUnit::IsPicking(const D3DXVECTOR3 & vPos, const int iIndex)
{

	D3DXVECTOR3 vVertex[4] =
	{
		{ m_vecMapObject[iIndex]->vPos.x ,m_vecMapObject[iIndex]->vPos.y + (TILECY >> 1), 0.f },
		{ m_vecMapObject[iIndex]->vPos.x + (TILECX >> 1),m_vecMapObject[iIndex]->vPos.y , 0.f },
		{ m_vecMapObject[iIndex]->vPos.x ,m_vecMapObject[iIndex]->vPos.y - (TILECY >> 1), 0.f },
		{ m_vecMapObject[iIndex]->vPos.x - (TILECX >> 1) ,m_vecMapObject[iIndex]->vPos.y , 0.f }
	};

	// 챕터 2. 각 꼭지점에서 방향벡터를 구하자! 0 ->1 1 ->2 ...
	D3DXVECTOR3 vVertexDir[4] =
	{
		vVertex[1] - vVertex[0],
		vVertex[2] - vVertex[1],
		vVertex[3] - vVertex[2],
		vVertex[0] - vVertex[3]
	};
	// 챕터3. 법선백터를 뽑아내자!!! 
	D3DXVECTOR3 vNormal[4] =
	{
		{-vVertexDir[0].y, vVertexDir[0].x, 0.f },
		{ -vVertexDir[1].y, vVertexDir[1].x, 0.f },
		{ -vVertexDir[2].y, vVertexDir[2].x, 0.f },
		{ -vVertexDir[3].y, vVertexDir[3].x, 0.f },
	};

	//챕터 4. 각 꼭지점에서 마우스를 바라보는 방향벡터를 구해라!!!! 
	D3DXVECTOR3 vMouseDir[4] =
	{
		// 마우스 - 꼭지점 영번째 
		vPos - vVertex[0],
		vPos - vVertex[1],
		vPos - vVertex[2],
		vPos - vVertex[3],
	};

	// 이제 나 다 구했다!!! 

	for (int i = 0; i < 4; ++i)
	{
		if (0 < D3DXVec3Dot(&vMouseDir[i], &vNormal[i]))
			return false;
	}
	return true;
}
