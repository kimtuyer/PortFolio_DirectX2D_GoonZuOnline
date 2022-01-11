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
			// �ϴ� �� ���
			if (0 != i && iIndex % (TILEX * 2) != 0)
			{
				if (i % 2 != 0 && 0 == m_vecTile[iIndex - TILEX]->byOption)  //LU   29�϶� 1 LU
					m_vecGraph[iIndex].emplace_back(m_vecTile[iIndex - TILEX]);
				else if (i % 2 == 0 && 0 == m_vecTile[iIndex - (TILEX + 1)]->byOption)  //LU
					m_vecGraph[iIndex].emplace_back(m_vecTile[iIndex - (TILEX + 1)]);

				//��
				if (i != 0 && i != 1 && j != TILEX - 1 && 0 == m_vecTile[iIndex - (TILEX * 2)]->byOption)
					m_vecGraph[iIndex].emplace_back(m_vecTile[iIndex - (TILEX * 2)]);

				//�Ʒ�
				if (i < TILEY-2  && j != TILEX - 1 && 0 == m_vecTile[iIndex + (TILEX * 2)]->byOption)
					m_vecGraph[iIndex].emplace_back(m_vecTile[iIndex + (TILEX * 2)]);

				//��
				//�ϴ�
				if (i >=1 && j >0 && 0 == m_vecTile[iIndex - 1]->byOption)  //���� 
					m_vecGraph[iIndex].emplace_back(m_vecTile[iIndex -1]);


				//��
				if (j < TILEX - 2 && 0 == m_vecTile[iIndex + 1]->byOption)  //Right
					m_vecGraph[iIndex].emplace_back(m_vecTile[iIndex +1]);

			}
			
			//����
			/*
			��=�÷��̾�-28*2	-x,-y
			�Ʒ�=�÷��̾�+28*2    -x ,y
			��=�÷��̾�-1	       x,-y
			��=�÷��̾�+1		x,y
			
			//Ÿ�� �ڷ� ���ʰ����� �˻� ��������
			*/



			// ���� .
			if (0 != i && ((TILEX * 2) - 1) != iIndex % (TILEX * 2))
			{
				if (i % 2 != 0 && 0 == m_vecTile[iIndex - (TILEX - 1)]->byOption) //LU 29�϶� 1
					m_vecGraph[iIndex].emplace_back(m_vecTile[iIndex - (TILEX - 1)]);
				else if (i % 2 == 0 && 0 == m_vecTile[iIndex - (TILEX)]->byOption)
					m_vecGraph[iIndex].emplace_back(m_vecTile[iIndex - (TILEX)]);
			}

			// �ϴ� �� �ϴ�
			if ((TILEY - 1) != i && iIndex % (TILEX * 2) != 0)
			{
				if (i % 2 != 0 && 0 == m_vecTile[iIndex + TILEX]->byOption)  //LD 28�϶� 56 LD
					m_vecGraph[iIndex].emplace_back(m_vecTile[iIndex + TILEX]);
				else if (i % 2 == 0 && 0 == m_vecTile[iIndex + (TILEX - 1)]->byOption)  //LD
					m_vecGraph[iIndex].emplace_back(m_vecTile[iIndex + (TILEX - 1)]);
			}

			// ���ϴ� .
			if ((TILEY - 1) != i && ((TILEX * 2) - 1) != iIndex % (TILEX * 2))
			{
				if (i % 2 != 0 && 0 == m_vecTile[iIndex + (TILEX + 1)]->byOption)   //28�϶� 29 RD , 29�϶� 58
					m_vecGraph[iIndex].emplace_back(m_vecTile[iIndex + (TILEX + 1)]);
				else if (i % 2 == 0 && 0 == m_vecTile[iIndex + (TILEX)]->byOption) //28��  RD
					m_vecGraph[iIndex].emplace_back(m_vecTile[iIndex + (TILEX)]);
			}

			//�Ʒ�


			// �� ����


			//�� ����











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


			// �ϴ� �� ���
			if (0 != i && iIndex % (TILEX * 2) != 0)
			{
				if (i % 2 != 0 && 0 == m_vecTile[iIndex - TILEX]->byOption) //��ó���� ���ܽ�Ű��
					m_vecMonsterGraph[iIndex].emplace_back(m_vecTile[iIndex - TILEX]);
				else if (i % 2 == 0 && 0 == m_vecTile[iIndex - (TILEX + 1)]->byOption)
					m_vecMonsterGraph[iIndex].emplace_back(m_vecTile[iIndex - (TILEX + 1)]);
				

				////��
				
				if (i != 0 && i != 1 && j != TILEX - 1 && 0 == m_vecTile[iIndex - (TILEX * 2)]->byOption)
					m_vecMonsterGraph[iIndex].emplace_back(m_vecTile[iIndex - (TILEX * 2)]);
				
				
				//�Ʒ�
				if (i < TILEY - 2 && j != TILEX - 1 && 0 == m_vecTile[iIndex + (TILEX * 2)]->byOption)
					m_vecMonsterGraph[iIndex].emplace_back(m_vecTile[iIndex + (TILEX * 2)]);
				
				//��
				//
				if (i >= 2 && j > 0 && 0 == m_vecTile[iIndex - 1]->byOption)
					m_vecMonsterGraph[iIndex].emplace_back(m_vecTile[iIndex - 1]);
				
				
				//��
				if (j < TILEX - 2 && 0 == m_vecTile[iIndex + 1]->byOption)
					m_vecMonsterGraph[iIndex].emplace_back(m_vecTile[iIndex + 1]);

			}

			//����
			/*
			��=�÷��̾�-28*2	-x,-y
			�Ʒ�=�÷��̾�+28*2    -x ,y
			��=�÷��̾�-1	       x,-y
			��=�÷��̾�+1		x,y
			*/



			//// ���� .
			if (0 != i && ((TILEX * 2) - 1) != iIndex % (TILEX * 2))
			{
				if (i % 2 != 0 && 0 == m_vecTile[iIndex - (TILEX - 1)]->byOption)
					m_vecMonsterGraph[iIndex].emplace_back(m_vecTile[iIndex - (TILEX - 1)]);
				else if (i % 2 == 0 && 0 == m_vecTile[iIndex - (TILEX)]->byOption)
					m_vecMonsterGraph[iIndex].emplace_back(m_vecTile[iIndex - (TILEX)]);
			}
			
			
			
			
			//// �ϴ� �� �ϴ�
			if ((TILEY - 1) != i && iIndex % (TILEX * 2) != 0)
			{
				if (i % 2 != 0 && 0 == m_vecTile[iIndex + TILEX]->byOption)
					m_vecMonsterGraph[iIndex].emplace_back(m_vecTile[iIndex + TILEX]);
				else if (i % 2 == 0 && 0 == m_vecTile[iIndex + (TILEX - 1)]->byOption)
					m_vecMonsterGraph[iIndex].emplace_back(m_vecTile[iIndex + (TILEX - 1)]);
			}
			
			// ���ϴ� .
			if ((TILEY - 1) != i && ((TILEX * 2) - 1) != iIndex % (TILEX * 2))
			{
				if (i % 2 != 0 && 0 == m_vecTile[iIndex + (TILEX + 1)]->byOption)
					m_vecMonsterGraph[iIndex].emplace_back(m_vecTile[iIndex + (TILEX + 1)]);
				else if (i % 2 == 0 && 0 == m_vecTile[iIndex + (TILEX)]->byOption)
					m_vecMonsterGraph[iIndex].emplace_back(m_vecTile[iIndex + (TILEX)]);
			}
			
			//�Ʒ�


			// �� ����


			//�� ����











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
	//� Stage���� ȣ���Ѱ��� ���ڷ� �޾Ƽ� �ش��ϴ� Stage�� �´� Ÿ�ϰ� ��ƾ�!
	//ex int��=0�� default��, �� �ʸ��� 1,2 �� ���ؼ� ����!
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

	// ���� �����ؿ�����. 3����. 
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
