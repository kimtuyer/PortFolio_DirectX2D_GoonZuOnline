#include "stdafx.h"
#include "MapUnit_Summon.h"
#include "MFCToolView.h"

MapUnit_Summon::MapUnit_Summon()
{
}

MapUnit_Summon::~MapUnit_Summon()
{
}

HRESULT MapUnit_Summon::Ready_MapUnit_Summon()
{
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Summon/summon_%d.bmp", L"MapUnit_Summon", L"Summon", 26)))
		//L"../Texture/Stage/Terrain/Tile/Tile%d.png
		//L"../Texture/Stage/Object/Tile/Tile%d.bmp
		return E_FAIL;

	return S_OK;


}

void MapUnit_Summon::Update_MapUnit_Summon(D3DXVECTOR3 vMouse)
{
}

void MapUnit_Summon::Render_MapUnit_Summon()
{
	D3DXMATRIX matScale, matTrans, matWorld;
	DWORD dwSize = m_vecMapObject.size();
	TCHAR szBuf[32]{};
	//m_vecTile[31]->byDrawID = 0; 
	for (size_t i = 0; i < dwSize; ++i)
	{
		const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo_Manager(L"MapUnit_Summon", L"Summon", m_vecMapObject[i]->byDrawID);
		if (nullptr == pTexInfo)
			return;
		float fCenterX = float(pTexInfo->tImageInfo.Width >> 1);
		float fCenterY = float(pTexInfo->tImageInfo.Height >> 1);

		D3DXMatrixScaling(&matScale, m_vecMapObject[i]->vSize.x, m_vecMapObject[i]->vSize.y, 0.f);
		D3DXMatrixTranslation(&matTrans, m_vecMapObject[i]->vPos.x - m_pView->GetScrollPos(SB_HORZ), m_vecMapObject[i]->vPos.y - m_pView->GetScrollPos(SB_VERT), 0.f);
		matWorld = matScale * matTrans;

		CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
		CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void MapUnit_Summon::MiniRender_MapUnit_Summon()
{
}

void MapUnit_Summon::Release_MapUnit_Summon()
{
	for (auto& pTile : m_vecMapObject)
		Safe_Delete(pTile);
	m_vecMapObject.clear();
	m_vecMapObject.shrink_to_fit();
}

void MapUnit_Summon::Change_MapUnit_Summon(const D3DXVECTOR3 & vPos, const BYTE & byDrawID, const BYTE & byOption)
{
	INFO* pMap = new INFO;
	pMap->vPos = vPos;
	pMap->byDrawID = byDrawID;
	pMap->byOption = byOption;
	pMap->vSize.x = 1;
	pMap->vSize.y = 1;

	m_vecMapObject.push_back(pMap);
}

int MapUnit_Summon::Get_Index(const D3DXVECTOR3 & vPos)
{
	int iSize = m_vecMapObject.size();
	for (int i = 0; i < iSize; ++i)
	{
		if (IsPicking(vPos, i))
			return i;
	}

	return -1;
}

bool MapUnit_Summon::IsPicking(const D3DXVECTOR3 & vPos, const int iIndex)
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
