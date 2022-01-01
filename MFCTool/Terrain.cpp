#include "stdafx.h"
#include "Terrain.h"
#include "MFCToolView.h"

CTerrain::CTerrain()
	:m_pView(nullptr)
{
}


CTerrain::~CTerrain()
{
	Release_Terrain(); 
}

HRESULT CTerrain::Ready_Terrain()
{
	


	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Terrain/TILEMAP/TILE0%d.png", L"Terrain", L"Tile", 4)))
		return E_FAIL;
	
	
	m_vecTile.reserve(TILEX * TILEY);
	TILE* pTile = nullptr; 
	float fX = 0.f, fY = 0.f; 
	for (int i = 0 ; i < TILEY ; ++i)
	{
		for (int j = 0 ;  j < TILEX ; ++j  )
		{
			fX = float((j * TILECX) + ((i % 2) * (TILECX >> 1))); 
			fY = float(i * (TILECY >> 1));
			pTile = new TILE; 
			pTile->vPos = { fX, fY, 0.f }; 
			pTile->vSize = { 1.f, 1.f, 0.f }; 
			pTile->iIndex = j + (i * TILEX);
			pTile->iParentIndex = 0;
			pTile->byDrawID = 0;
			pTile->byOption = 0; 
			m_vecTile.emplace_back(pTile); 
		}
	}
	return S_OK;
}

void CTerrain::Update_Terrain()
{
}

void CTerrain::Render_Terrain()
{


	D3DXMATRIX matScale, matTrans, matWorld; 
	DWORD dwSize = m_vecTile.size(); 
	TCHAR szBuf[32]{}; 
	//m_vecTile[31]->byDrawID = 0; 
	for (size_t i = 0 ; i < dwSize; ++i)
	{
		const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo_Manager(L"Terrain", L"Tile", m_vecTile[i]->byDrawID);
		if (nullptr == pTexInfo)
			return; 
		float fCenterX = float(pTexInfo->tImageInfo.Width >> 1); 
		float fCenterY = float(pTexInfo->tImageInfo.Height >> 1); 

		D3DXMatrixScaling(&matScale, m_vecTile[i]->vSize.x, m_vecTile[i]->vSize.y, 0.f); 
		D3DXMatrixTranslation(&matTrans, m_vecTile[i]->vPos.x - m_pView->GetScrollPos(SB_HORZ), m_vecTile[i]->vPos.y - m_pView->GetScrollPos(SB_VERT), 0.f); 
		matWorld = matScale * matTrans; 

		CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld); 
		CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255)); 

		swprintf_s(szBuf, L"%d", i); 
		CGraphic_Device::Get_Instance()->Get_Font()->DrawTextW(CGraphic_Device::Get_Instance()->Get_Sprite(), szBuf, lstrlen(szBuf), nullptr, 0, D3DCOLOR_ARGB(255, 0, 0, 0));

	}
}

void CTerrain::MiniRender_Terrain()
{
	D3DXMATRIX matScale, matTrans, matWorld;
	D3DXMATRIX matRatio;
	D3DXMatrixScaling(&matRatio, 0.3f, 0.3f, 0.f); 
	DWORD dwSize = m_vecTile.size();
	for (size_t i = 0; i < dwSize; ++i)
	{
		const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo_Manager(L"Terrain", L"Tile", m_vecTile[i]->byDrawID);
		if (nullptr == pTexInfo)
			return;
		float fCenterX = float(pTexInfo->tImageInfo.Width >> 1);
		float fCenterY = float(pTexInfo->tImageInfo.Height >> 1);

		D3DXMatrixScaling(&matScale, m_vecTile[i]->vSize.x , m_vecTile[i]->vSize.y , 0.f);
		D3DXMatrixTranslation(&matTrans, m_vecTile[i]->vPos.x , m_vecTile[i]->vPos.y, 0.f);
		matWorld = matScale * matTrans;
		matWorld *= matRatio; 
		CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
		CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	}

}

void CTerrain::Release_Terrain()
{
	for (auto& pTile : m_vecTile)
		Safe_Delete(pTile);
	m_vecTile.clear();
	m_vecTile.shrink_to_fit();
}

void CTerrain::Tile_Change_Terrain(const D3DXVECTOR3 & vPos, const BYTE & byDrawID, const BYTE & byOption)
{
	int iIndex = Get_TileIndex(vPos); 

	if (-1 == iIndex)
		return; 

	m_vecTile[iIndex]->byDrawID = byDrawID; 
	m_vecTile[iIndex]->byOption = byOption;
}

int CTerrain::Get_TileIndex(const D3DXVECTOR3 & vPos)
{
	int iSize = m_vecTile.size(); 
	for (int i = 0 ; i < iSize ; ++i)
	{
		if (IsPicking(vPos, i))
			return i; 
	}

	return -1;
}

bool CTerrain::IsPicking(const D3DXVECTOR3 & vPos, const int iIndex)
{
	// 내적을 이용해서 타일 픽킹 ㄱㄱ. 
	// 일단 마름모꼴 타일의 각 꼭지점을 구하자. 

	D3DXVECTOR3 vVertex[4] = 
	{
		{ m_vecTile[iIndex]->vPos.x ,m_vecTile[iIndex]->vPos.y + (TILECY >> 1), 0.f },
		{ m_vecTile[iIndex]->vPos.x + (TILECX >> 1),m_vecTile[iIndex]->vPos.y , 0.f },
		{ m_vecTile[iIndex]->vPos.x ,m_vecTile[iIndex]->vPos.y - (TILECY >> 1), 0.f },
		{ m_vecTile[iIndex]->vPos.x - (TILECX >> 1) ,m_vecTile[iIndex]->vPos.y , 0.f }
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

	for (int i = 0 ; i < 4; ++i)
	{
		if (0 < D3DXVec3Dot(&vMouseDir[i], &vNormal[i]))
			return false;
	}
	return true;
}
