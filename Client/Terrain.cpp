#include "stdafx.h"
#include "Terrain.h"
#include "CCamera.h"

CTerrain::CTerrain()
{
}


CTerrain::~CTerrain()
{
	Release_GameObject(); 
}

HRESULT CTerrain::Create_PlayerGraph_Terrain()
{
	m_vecGraph.resize(TILEX * TILEY); 





	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			int iIndex = j + (i * TILEX);
			// 일단 좌 상단
			if (0 != i && iIndex % (TILEX * 2) != 0)
			{
				if (i % 2 != 0 && 0 == m_vecTile[iIndex - TILEX]->byOption)  //LU   29일때 1 LU
					m_vecGraph[iIndex].emplace_back(m_vecTile[iIndex - TILEX]);
				else if (i % 2 == 0 && 0 == m_vecTile[iIndex - (TILEX + 1)]->byOption)  //LU
					m_vecGraph[iIndex].emplace_back(m_vecTile[iIndex - (TILEX + 1)]);

				//위
				if (i != 0 && i != 1 && j != TILEX - 1 && 0 == m_vecTile[iIndex - (TILEX * 2)]->byOption)
					m_vecGraph[iIndex].emplace_back(m_vecTile[iIndex - (TILEX * 2)]);

				//아래
				if (i < TILEY-2  && j != TILEX - 1 && 0 == m_vecTile[iIndex + (TILEX * 2)]->byOption)
					m_vecGraph[iIndex].emplace_back(m_vecTile[iIndex + (TILEX * 2)]);

				//좌
				//하단
				if (i >=1 && j >0 && 0 == m_vecTile[iIndex - 1]->byOption)  //왼쪽 
					m_vecGraph[iIndex].emplace_back(m_vecTile[iIndex -1]);


				//우
				if (j < TILEX - 2 && 0 == m_vecTile[iIndex + 1]->byOption)  //Right
					m_vecGraph[iIndex].emplace_back(m_vecTile[iIndex +1]);

			}
			
			//위ㅣ
			/*
			위=플레이어-28*2	-x,-y
			아래=플레이어+28*2    -x ,y
			좌=플레이어-1	       x,-y
			우=플레이어+1		x,y
			
			//타일 뒤로 왼쪽가로줄 검사 빠져있음
			*/



			// 우상단 .
			if (0 != i && ((TILEX * 2) - 1) != iIndex % (TILEX * 2))
			{
				if (i % 2 != 0 && 0 == m_vecTile[iIndex - (TILEX - 1)]->byOption) //LU 29일때 1
					m_vecGraph[iIndex].emplace_back(m_vecTile[iIndex - (TILEX - 1)]);
				else if (i % 2 == 0 && 0 == m_vecTile[iIndex - (TILEX)]->byOption)
					m_vecGraph[iIndex].emplace_back(m_vecTile[iIndex - (TILEX)]);
			}

			// 일단 좌 하단
			if ((TILEY - 1) != i && iIndex % (TILEX * 2) != 0)
			{
				if (i % 2 != 0 && 0 == m_vecTile[iIndex + TILEX]->byOption)  //LD 28일때 56 LD
					m_vecGraph[iIndex].emplace_back(m_vecTile[iIndex + TILEX]);
				else if (i % 2 == 0 && 0 == m_vecTile[iIndex + (TILEX - 1)]->byOption)  //LD
					m_vecGraph[iIndex].emplace_back(m_vecTile[iIndex + (TILEX - 1)]);
			}

			// 우하단 .
			if ((TILEY - 1) != i && ((TILEX * 2) - 1) != iIndex % (TILEX * 2))
			{
				if (i % 2 != 0 && 0 == m_vecTile[iIndex + (TILEX + 1)]->byOption)   //28일때 29 RD , 29일때 58
					m_vecGraph[iIndex].emplace_back(m_vecTile[iIndex + (TILEX + 1)]);
				else if (i % 2 == 0 && 0 == m_vecTile[iIndex + (TILEX)]->byOption) //28번  RD
					m_vecGraph[iIndex].emplace_back(m_vecTile[iIndex + (TILEX)]);
			}

			//아래


			// 좌 방향


			//우 방향











		}
	}
	return S_OK;
}

HRESULT CTerrain::Create_MonsterGraph_Terrain()
{
	m_vecMonsterGraph.resize(TILEX * TILEY);
	//m_vecGraph[2].emplace_back(TILE*); 

	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			int iIndex = j + (i * TILEX);


			// 일단 좌 상단
			if (0 != i && iIndex % (TILEX * 2) != 0)
			{
				if (i % 2 != 0 && 0 == m_vecTile[iIndex - TILEX]->byOption) //맨처음행 제외시키려
					m_vecMonsterGraph[iIndex].emplace_back(m_vecTile[iIndex - TILEX]);
				else if (i % 2 == 0 && 0 == m_vecTile[iIndex - (TILEX + 1)]->byOption)
					m_vecMonsterGraph[iIndex].emplace_back(m_vecTile[iIndex - (TILEX + 1)]);
				

				////위
				
				if (i != 0 && i != 1 && j != TILEX - 1 && 0 == m_vecTile[iIndex - (TILEX * 2)]->byOption)
					m_vecMonsterGraph[iIndex].emplace_back(m_vecTile[iIndex - (TILEX * 2)]);
				
				
				//아래
				if (i < TILEY - 2 && j != TILEX - 1 && 0 == m_vecTile[iIndex + (TILEX * 2)]->byOption)
					m_vecMonsterGraph[iIndex].emplace_back(m_vecTile[iIndex + (TILEX * 2)]);
				
				//좌
				//
				if (i >= 2 && j > 0 && 0 == m_vecTile[iIndex - 1]->byOption)
					m_vecMonsterGraph[iIndex].emplace_back(m_vecTile[iIndex - 1]);
				
				
				//우
				if (j < TILEX - 2 && 0 == m_vecTile[iIndex + 1]->byOption)
					m_vecMonsterGraph[iIndex].emplace_back(m_vecTile[iIndex + 1]);

			}

			//위ㅣ
			/*
			위=플레이어-28*2	-x,-y
			아래=플레이어+28*2    -x ,y
			좌=플레이어-1	       x,-y
			우=플레이어+1		x,y
			*/



			//// 우상단 .
			if (0 != i && ((TILEX * 2) - 1) != iIndex % (TILEX * 2))
			{
				if (i % 2 != 0 && 0 == m_vecTile[iIndex - (TILEX - 1)]->byOption)
					m_vecMonsterGraph[iIndex].emplace_back(m_vecTile[iIndex - (TILEX - 1)]);
				else if (i % 2 == 0 && 0 == m_vecTile[iIndex - (TILEX)]->byOption)
					m_vecMonsterGraph[iIndex].emplace_back(m_vecTile[iIndex - (TILEX)]);
			}
			
			
			
			
			//// 일단 좌 하단
			if ((TILEY - 1) != i && iIndex % (TILEX * 2) != 0)
			{
				if (i % 2 != 0 && 0 == m_vecTile[iIndex + TILEX]->byOption)
					m_vecMonsterGraph[iIndex].emplace_back(m_vecTile[iIndex + TILEX]);
				else if (i % 2 == 0 && 0 == m_vecTile[iIndex + (TILEX - 1)]->byOption)
					m_vecMonsterGraph[iIndex].emplace_back(m_vecTile[iIndex + (TILEX - 1)]);
			}
			
			// 우하단 .
			if ((TILEY - 1) != i && ((TILEX * 2) - 1) != iIndex % (TILEX * 2))
			{
				if (i % 2 != 0 && 0 == m_vecTile[iIndex + (TILEX + 1)]->byOption)
					m_vecMonsterGraph[iIndex].emplace_back(m_vecTile[iIndex + (TILEX + 1)]);
				else if (i % 2 == 0 && 0 == m_vecTile[iIndex + (TILEX)]->byOption)
					m_vecMonsterGraph[iIndex].emplace_back(m_vecTile[iIndex + (TILEX)]);
			}
			
			//아래


			// 좌 방향


			//우 방향











		}
	}
	return S_OK;
}

HRESULT CTerrain::LoadTileData_Terrain(const wstring & wstrFilePath)
{
	HANDLE hFile = CreateFile(wstrFilePath.c_str(), GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr); 
	if (INVALID_HANDLE_VALUE == hFile)
		return E_FAIL; 

	DWORD dwbyte = 0; 
	TILE* pTile = nullptr; 
	while (true)
	{
		//pTile = new TILE; 
		pTile = new TILE;
		ReadFile(hFile, pTile, sizeof(TILE), &dwbyte, nullptr);
		if (0 == dwbyte)
		{
			Safe_Delete(pTile);
			break; 
		}
		m_vecTile.emplace_back(pTile); 
	}
	CloseHandle(hFile); 
	return S_OK;
}

HRESULT CTerrain::LoadTileData_MapObject(const wstring & wstrFilePath)
{
	HANDLE hFile = CreateFile(wstrFilePath.c_str(), GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (INVALID_HANDLE_VALUE == hFile)
		return E_FAIL;

	DWORD dwbyte = 0;
	MAPOBJECT* pMap = nullptr;
	//TILE* pTile = nullptr; 
	while (true)
	{
		//pTile = new TILE; 
		pMap = new MAPOBJECT;
		ReadFile(hFile, pMap, sizeof(MAPOBJECT), &dwbyte, nullptr);
		if (0 == dwbyte)
		{
			Safe_Delete(pMap);
			break;
		}
		//m_vecTile.emplace_back(pTile); 
		m_vecMap.emplace_back(pMap);
	}
	CloseHandle(hFile);
	return S_OK;
}

HRESULT CTerrain::Ready_GameObject()
{
	//어떤 Stage에서 호출한건지 인자로 받아서 해당하는 Stage에 맞는 타일값 깔아야!
	//ex int값=0을 default로, 각 맵마다 1,2 값 정해서 삽입!
	MAPOBJECT *pMap = nullptr;
	TILE* pTile = nullptr;

	//LoadTileData_Terrain(L"../Data/NamHanCastle_TileData.dat");
	Create_PlayerGraph_Terrain();
	Create_MonsterGraph_Terrain();

	return S_OK;
}



int CTerrain::Update_GameObject()
{
	//float fSpeed = 300.f * CTime_Manager::Get_Instance()->Get_DeltaTime(); 
	//
	//if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	//	CScroll_Manager::Get_Instance()->Set_Scroll({ fSpeed, 0.f, 0.f });
	//if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	//	CScroll_Manager::Get_Instance()->Set_Scroll({ -fSpeed, 0.f, 0.f });
	//if (GetAsyncKeyState(VK_UP) & 0x8000)
	//	CScroll_Manager::Get_Instance()->Set_Scroll({ 0.f,fSpeed,  0.f });
	//if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	//	CScroll_Manager::Get_Instance()->Set_Scroll({ 0.f,-fSpeed,  0.f });

	// 게임 선정해오세요. 3가지. 
	// 
	return 0;
}

void CTerrain::Late_Update_GameObject()
{
}

void CTerrain::Render_GameObject()
{
	D3DXMATRIX matScale, matTrans, matWorld;
	DWORD dwSize = m_vecTile.size();
	
	D3DXVECTOR3 tPos;
	//for (size_t i = 0; i < dwSize; ++i)
	//{
	//	if (m_vecTile[i]->byDrawID == 1)
	//	{
	//
	//	const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo_Manager(L"Terrain", L"Tile", m_vecTile[i]->byDrawID);
	//	//const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo_Manager(L"MapObject", L"Gate", m_vecMap[i]->byDrawID);
	//	if (nullptr == pTexInfo)
	//		return;
	//	float fCenterX = float(pTexInfo->tImageInfo.Width >> 1);
	//	float fCenterY = float(pTexInfo->tImageInfo.Height >> 1);
	//	tPos = m_vecTile[i]->vPos;
	//	tPos -= CCamera::Get_Instance()->GetPos();
	//	
	//
	//
	//	D3DXMatrixScaling(&matScale, m_vecTile[i]->vSize.x, m_vecTile[i]->vSize.y, 0.f);
	//	D3DXMatrixTranslation(&matTrans, tPos.x, tPos.y, 0.f);
	//
	//	//D3DXMatrixTranslation(&matTrans, m_vecTile[i]->vPos.x , m_vecTile[i]->vPos.y , 0.f);
	//	matWorld = matScale * matTrans;
	//
	//	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
	//	CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	//	}
	//}
}

void CTerrain::Release_GameObject()
{
	for (auto& pTile : m_vecTile)
		Safe_Delete(pTile);
	m_vecTile.clear();
	m_vecTile.shrink_to_fit();
}
