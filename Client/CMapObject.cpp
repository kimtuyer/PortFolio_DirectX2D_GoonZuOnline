#include "stdafx.h"
#include "CMapObject.h"
#include "CCamera.h"

CMapObject::CMapObject()
{
}

CMapObject::~CMapObject()
{
	Release_GameObject();

}

HRESULT CMapObject::Create_Graph_Terrain()
{
	return E_NOTIMPL;
}

HRESULT CMapObject::LoadTileData_Terrain(const wstring & wstrFilePath)
{
	return E_NOTIMPL;
}

HRESULT CMapObject::LoadTileData_MapObject(const wstring & wstrFilePath)
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

HRESULT CMapObject::Ready_GameObject()
{
	MAPOBJECT *pMap = nullptr;
	//LoadTileData_MapObject(L"../Data/Start_ObjectData2.dat");
	//LoadTileData_MapObject(L"../Data/NamHanCastle_ObjectData2.dat");

	m_tInfo.ID = ID::MAP;
	//Kwanghwa_ObjectData

	return S_OK;
}

int CMapObject::Update_GameObject()
{
	return 0;
}

void CMapObject::Late_Update_GameObject()
{
}

void CMapObject::Render_GameObject()
{
	D3DXMATRIX matScale, matTrans, matWorld;
	DWORD dwSize = m_vecMap.size();

	for (size_t i = 0; i < dwSize; ++i)
	{
		//const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo_Manager(L"Terrain", L"Tile", m_vecTile[i]->byDrawID);
		const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo_Manager(L"MapObject", L"Gate", m_vecMap[i]->byDrawID);
		if (nullptr == pTexInfo)
			return;
		float fCenterX = float(pTexInfo->tImageInfo.Width >> 1);
		float fCenterY = float(pTexInfo->tImageInfo.Height >> 1);

		D3DXVECTOR3 tPos = m_vecMap[i]->vPos - m_vecMap[i]->vSize;// * m_tPivot;

		tPos -= CCamera::Get_Instance()->GetPos();
		D3DXMatrixTranslation(&matTrans, tPos.x, tPos.y, 0.f);

		D3DXMatrixScaling(&matScale, m_vecMap[i]->vSize.x, m_vecMap[i]->vSize.y, 0.f);
		//D3DXMatrixTranslation(&matTrans, m_vecMap[i]->vPos.x + CScroll_Manager::Get_Instance()->Get_Scroll(CScroll_Manager::eSB_HORZ), m_vecMap[i]->vPos.y + CScroll_Manager::Get_Instance()->Get_Scroll(CScroll_Manager::eSB_VERT), 0.f);
		matWorld = matScale * matTrans;

		if (m_vecMap[i]->byDrawID == 2)
		{
			m_ColliderInfo[MAP_Object::id_2][0] = { tPos.x - 80 ,tPos.y - 80 };
			m_ColliderInfo[MAP_Object::id_2][1] = { m_ColliderInfo[MAP_Object::id_2][0].x + 160,tPos.y - 80 };
			m_ColliderInfo[MAP_Object::id_2][2] = { m_ColliderInfo[MAP_Object::id_2][1].x,m_ColliderInfo[MAP_Object::id_2][1].y + 160 };
			m_ColliderInfo[MAP_Object::id_2][3] = { m_ColliderInfo[MAP_Object::id_2][0].x,m_ColliderInfo[MAP_Object::id_2][2].y };
			m_ColliderInfo[MAP_Object::id_2][4] = { tPos.x - 80 ,tPos.y - 80 };

		}
		if (m_vecMap[i]->byDrawID == 34)
		{
			D3DXMatrixScaling(&matScale, 1.25, 1.25, 0.f);
			matWorld = matScale * matTrans;


			m_ColliderInfo[MAP_Object::id_34][0] = { tPos.x - 90 ,tPos.y - 140 };
			m_ColliderInfo[MAP_Object::id_34][1] = { m_ColliderInfo[MAP_Object::id_34][0].x + 180,tPos.y - 140 };
			m_ColliderInfo[MAP_Object::id_34][2] = { m_ColliderInfo[MAP_Object::id_34][1].x,m_ColliderInfo[MAP_Object::id_34][1].y + 280 };
			m_ColliderInfo[MAP_Object::id_34][3] = { m_ColliderInfo[MAP_Object::id_34][0].x,m_ColliderInfo[MAP_Object::id_34][2].y };
			m_ColliderInfo[MAP_Object::id_34][4] = { tPos.x - 90 ,tPos.y - 140 };

		}



		if (m_vecMap[i]->byDrawID == 26)
		{
			m_ColliderInfo[MAP_Object::id_26][0] = { tPos.x - 250 ,tPos.y - 220 };
			m_ColliderInfo[MAP_Object::id_26][1] = { m_ColliderInfo[MAP_Object::id_26][0].x + 500,tPos.y - 220 };
			m_ColliderInfo[MAP_Object::id_26][2] = { m_ColliderInfo[MAP_Object::id_26][1].x,m_ColliderInfo[MAP_Object::id_26][1].y + 440 };
			m_ColliderInfo[MAP_Object::id_26][3] = { m_ColliderInfo[MAP_Object::id_26][0].x,m_ColliderInfo[MAP_Object::id_26][2].y };
			m_ColliderInfo[MAP_Object::id_26][4] = { tPos.x - 250 ,tPos.y - 220 };

		}
		if (m_vecMap[i]->byDrawID == 31)
		{
			m_ColliderInfo[MAP_Object::id_31][0] = { tPos.x - 130 ,tPos.y - 130 };
			m_ColliderInfo[MAP_Object::id_31][1] = { m_ColliderInfo[MAP_Object::id_31][0].x + 260,tPos.y - 130 };
			m_ColliderInfo[MAP_Object::id_31][2] = { m_ColliderInfo[MAP_Object::id_31][1].x,m_ColliderInfo[MAP_Object::id_31][1].y + 260 };
			m_ColliderInfo[MAP_Object::id_31][3] = { m_ColliderInfo[MAP_Object::id_31][0].x,m_ColliderInfo[MAP_Object::id_31][2].y };
			m_ColliderInfo[MAP_Object::id_31][4] = { tPos.x - 130 ,tPos.y - 130 };

		}
		if (m_vecMap[i]->byDrawID == 33)
		{
			m_ColliderInfo[MAP_Object::id_33][0] = { tPos.x - 200 ,tPos.y - 110 };
			m_ColliderInfo[MAP_Object::id_33][1] = { m_ColliderInfo[MAP_Object::id_33][0].x + 200,tPos.y - 110 };
			m_ColliderInfo[MAP_Object::id_33][2] = { m_ColliderInfo[MAP_Object::id_33][1].x,m_ColliderInfo[MAP_Object::id_33][1].y + 200 };
			m_ColliderInfo[MAP_Object::id_33][3] = { m_ColliderInfo[MAP_Object::id_33][0].x,m_ColliderInfo[MAP_Object::id_33][2].y };
			m_ColliderInfo[MAP_Object::id_33][4] = { tPos.x - 200 ,tPos.y - 110 };

		}
		if (m_vecMap[i]->byDrawID == 39)
		{
			m_ColliderInfo[MAP_Object::id_39][0] = { tPos.x - 110 ,tPos.y - 110 };
			m_ColliderInfo[MAP_Object::id_39][1] = { m_ColliderInfo[MAP_Object::id_39][0].x + 220,tPos.y - 110 };
			m_ColliderInfo[MAP_Object::id_39][2] = { m_ColliderInfo[MAP_Object::id_39][1].x,m_ColliderInfo[MAP_Object::id_39][1].y + 130 };
			m_ColliderInfo[MAP_Object::id_39][3] = { m_ColliderInfo[MAP_Object::id_39][0].x,m_ColliderInfo[MAP_Object::id_39][2].y };
			m_ColliderInfo[MAP_Object::id_39][4] = { tPos.x - 110 ,tPos.y - 50 };

		}
		if (m_vecMap[i]->byDrawID == 68) //미완성
		{
			m_ColliderInfo[MAP_Object::id_68][0] = { tPos.x - 75 ,tPos.y - 50 };
			m_ColliderInfo[MAP_Object::id_68][1] = { m_ColliderInfo[MAP_Object::id_68][0].x + 150,tPos.y - 50 };
			m_ColliderInfo[MAP_Object::id_68][2] = { m_ColliderInfo[MAP_Object::id_68][1].x,m_ColliderInfo[MAP_Object::id_68][1].y + 120 };
			m_ColliderInfo[MAP_Object::id_68][3] = { m_ColliderInfo[MAP_Object::id_68][0].x,m_ColliderInfo[MAP_Object::id_68][2].y };
			m_ColliderInfo[MAP_Object::id_68][4] = { tPos.x - 75 ,tPos.y - 50 };

		}
		if (m_vecMap[i]->byDrawID == 66) //미완성
		{
			m_ColliderInfo[MAP_Object::id_66][0] = { tPos.x - 40 ,tPos.y - 35 };
			m_ColliderInfo[MAP_Object::id_66][1] = { m_ColliderInfo[MAP_Object::id_66][0].x + 80,tPos.y - 35 };
			m_ColliderInfo[MAP_Object::id_66][2] = { m_ColliderInfo[MAP_Object::id_66][1].x,m_ColliderInfo[MAP_Object::id_66][1].y + 100 };
			m_ColliderInfo[MAP_Object::id_66][3] = { m_ColliderInfo[MAP_Object::id_66][0].x,m_ColliderInfo[MAP_Object::id_66][2].y };
			m_ColliderInfo[MAP_Object::id_66][4] = { tPos.x - 40 ,tPos.y - 35 };

		}
		


		CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
		CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void CMapObject::Release_GameObject()
{
	for (auto& pTile : m_vecMap)
		Safe_Delete(pTile);
	m_vecMap.clear();
	m_vecMap.shrink_to_fit();
}
