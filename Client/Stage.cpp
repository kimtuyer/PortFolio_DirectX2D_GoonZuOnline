#include "stdafx.h"
#include "Stage.h"
#include "GameObject_Manager.h"
#include "Terrain.h"
#include "CMapObject.h"
#include "Player.h"
#include "West_Rifleman.h"
#include "West_Boss.h"
#include "West_infantry.h"
#include "CCamera.h"
#include "Bullet_Player.h"
#include "CMouse.h"
#include"Japan_Boss.h"
#include "Japan_infantry.h"
#include "CGageBar.h"
#include "Summon_Kimsimin.h"
#include "Summon_Janggum.h"
#include "Summon_GwonYool.h"
#include "SummonName.h"

#include "CHPBar_Player.h"
#include "CMPBar_Player.h"
#include "CExPBar_Player.h"
#include "TopHP.h"
#include "TopHPbar.h"


#include "JangGumIName.h"
#include "RoyalGuard.h"
#include "RoyalGuardName.h"
CStage::CStage()
	:m_pGameObject_Manager(CGameObject_Manager::Get_Instance())
{
}


CStage::~CStage()
{
	Release_Scene();
}

HRESULT CStage::LoadData_MAPObject(const wstring & wstrFilePath)
{
	HANDLE hFile = CreateFile(wstrFilePath.c_str(), GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (INVALID_HANDLE_VALUE == hFile)
		return E_FAIL;

	DWORD dwbyte = 0;

	MAPOBJECT* pObject = nullptr;
	CGameObject* pMap = new CMapObject;
	CGameObject* pTile = new CMapObject;
	CGameObject* pBulding = new CMapObject;

	if (FAILED(pMap->Ready_GameObject()))
		return E_FAIL;

	if (FAILED(pTile->Ready_GameObject()))
		return E_FAIL;

	//TILE* pTile = nullptr; 
	while (true)
	{
		//pTile = new TILE; 
		//안에서 
		pObject = new MAPOBJECT;

		ReadFile(hFile, pObject, sizeof(MAPOBJECT), &dwbyte, nullptr);
		if (0 == dwbyte)
		{
			Safe_Delete(pObject);
			break;
		}
		//오브젝트가 유닛보다 먼저, 즉 유닛먼저 깔려야 되는
		//23 ,27,28 29 46 47 48 49 52  54 55 56 57 63 
		if (pObject->byDrawID == 23 || pObject->byDrawID == 27 || pObject->byDrawID == 28 || pObject->byDrawID == 29 || pObject->byDrawID == 46 || pObject->byDrawID == 47 ||
			pObject->byDrawID == 48 || pObject->byDrawID == 49 || pObject->byDrawID == 52 || pObject->byDrawID == 54 || pObject->byDrawID == 55 || pObject->byDrawID == 56 ||
			pObject->byDrawID == 57 || pObject->byDrawID == 63)
		{
			dynamic_cast<CMapObject*>(pTile)->Set_VecMap(pObject);

		}
		else if (pObject->byDrawID == 34)
		{

			dynamic_cast<CMapObject*>(pBulding)->Set_VecMap(pObject);
			pBulding->Set_HP(10000);

		}
		else if (pObject->byDrawID == 26)
		{
			dynamic_cast<CMapObject*>(pBulding)->Set_VecMap(pObject);

		}
		else
			dynamic_cast<CMapObject*>(pMap)->Set_VecMap(pObject);





	}
	m_pGameObject_Manager->Add_GameObject_Manager(ID::Bulding, pBulding);

	m_pGameObject_Manager->Add_GameObject_Manager(ID::MAP, pMap);
	m_pGameObject_Manager->Add_GameObject_Manager(ID::TERRAIN, pTile);

	CloseHandle(hFile);
	return S_OK;
}

HRESULT CStage::LoadData_TILEObject(const wstring & wstrFilePath)
{
	HANDLE hFile = CreateFile(wstrFilePath.c_str(), GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (INVALID_HANDLE_VALUE == hFile)
		return E_FAIL;

	CGameObject* pTerrain = new CTerrain;
	
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
		dynamic_cast<CTerrain*>(pTerrain)->Set_vecTile(pTile);
	}
	if (FAILED(pTerrain->Ready_GameObject()))
		return E_FAIL;
	m_pGameObject_Manager->Add_GameObject_Manager(ID::TERRAIN, pTerrain);


	CloseHandle(hFile);
	return S_OK;
}

HRESULT CStage::LoadData_Object(const wstring & wstrFilePath)
{
	HANDLE hFile = CreateFile(wstrFilePath.c_str(), GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (INVALID_HANDLE_VALUE == hFile)
		return E_FAIL;

	DWORD dwbyte = 0;

	INFO* pObject = nullptr;
	//TILE* pTile = nullptr; 
	while (true)
	{
		//pTile = new TILE; 
		//안에서 
		pObject = new INFO;

		ReadFile(hFile, pObject, sizeof(INFO), &dwbyte, nullptr);
		if (0 == dwbyte)
		{
			Safe_Delete(pObject);
			break;
		}
		//wcscpy_s(pObject->StateKey, L"Stand");
		if (pObject->byDrawID == 8)
		{
			CGameObject* pMonster = new West_Rifleman;
			pMonster->Set_Info(pObject);

			if (FAILED(pMonster->Ready_GameObject()))
				return E_FAIL;
			//CCamera::Get_Instance()->SetTarget(pObject);
			m_pGameObject_Manager->Add_GameObject_Manager(ID::MONSTER, pMonster);

		}

		if (pObject->byDrawID == 5)
		{
			CGameObject* pMonster = new Japan_Boss;
			pMonster->Set_Info(pObject);

			if (FAILED(pMonster->Ready_GameObject()))
				return E_FAIL;
			//CCamera::Get_Instance()->SetTarget(pObject);
			m_pGameObject_Manager->Add_GameObject_Manager(ID::MONSTER, pMonster);

		}
		if (pObject->byDrawID == 7)
		{
			CGameObject* pMonster = new Japan_infantry;
			pMonster->Set_Info(pObject);

			if (FAILED(pMonster->Ready_GameObject()))
				return E_FAIL;
			//CCamera::Get_Instance()->SetTarget(pObject);
			m_pGameObject_Manager->Add_GameObject_Manager(ID::MONSTER, pMonster);

		}
		//if (pObject->byDrawID == 9)
		//{
		//	CGameObject* pMonster = new West_Boss;
		//	pMonster->Set_Info(pObject);
		//
		//	if (FAILED(pMonster->Ready_GameObject()))
		//		return E_FAIL;
		//	//CCamera::Get_Instance()->SetTarget(pObject);
		//	m_pGameObject_Manager->Add_GameObject_Manager(ID::MONSTER, pMonster);
		//
		//}
		if (pObject->byDrawID == 24)
		{
			CGameObject* pMonster = new West_infantry;
			pMonster->Set_Info(pObject);

			if (FAILED(pMonster->Ready_GameObject()))
				return E_FAIL;
			//CCamera::Get_Instance()->SetTarget(pObject);
			m_pGameObject_Manager->Add_GameObject_Manager(ID::MONSTER, pMonster);

		}



			//m_vecMonster.emplace_back(pObject);
		//m_vecTile.emplace_back(pTile); 
	}
	CloseHandle(hFile);
	return S_OK;
}

HRESULT CStage::Ready_Scene()
{
	CSoundMgr::Get_Instance()->StopAll();
	CSoundMgr::Get_Instance()->PlayBGM(L"Music_MuhanBattle.ogg");
	number = 4;
	CGameObject* pObject = nullptr;
	LoadData_TILEObject(L"../Data/NamHanCastle_TileData.dat");


	LoadData_MAPObject(L"../Data/NamHanCastle_ObjectData.dat");


	pObject = new TopHPbar;
	if (FAILED(pObject->Ready_GameObject()))
		return E_FAIL;
	pObject->Set_StateKey(L"NamhanHP");


	m_pGameObject_Manager->Add_GameObject_Manager(ID::UI, pObject);



	pObject = new TopHP;
	if (FAILED(pObject->Ready_GameObject()))
		return E_FAIL;
	pObject->Set_StateKey(L"TopHP");


	m_pGameObject_Manager->Add_GameObject_Manager(ID::tophp, pObject);

	pObject = new CGageBar;
	if (FAILED(pObject->Ready_GameObject()))
		return E_FAIL;

	m_pGameObject_Manager->Add_GameObject_Manager(ID::UI, pObject);


	pObject = new CHPBar_Player;
	if (FAILED(pObject->Ready_GameObject()))
		return E_FAIL;

	m_pGameObject_Manager->Add_GameObject_Manager(ID::PlayerHP, pObject);


	pObject = new CMPBar_Player;
	if (FAILED(pObject->Ready_GameObject()))
		return E_FAIL;

	m_pGameObject_Manager->Add_GameObject_Manager(ID::PlayerMP, pObject);

	pObject = new CExPBar_Player;
	if (FAILED(pObject->Ready_GameObject()))
		return E_FAIL;

	m_pGameObject_Manager->Add_GameObject_Manager(ID::PlayerEXP, pObject);




	pObject = new SummonName;
	if (FAILED(pObject->Ready_GameObject()))
		return E_FAIL;

	m_pGameObject_Manager->Add_GameObject_Manager(ID::UI, pObject);

	pObject = new JangGumIName;
	if (FAILED(pObject->Ready_GameObject()))
		return E_FAIL;

	m_pGameObject_Manager->Add_GameObject_Manager(ID::UI, pObject);




	//pObject = new Bullet_Player;
	//if (FAILED(pObject->Ready_GameObject()))
	//	return E_FAIL;
	//
	//m_pGameObject_Manager->Add_GameObject_Manager(ID::Bullet, pObject);

	pObject = new CMouse;
	
	if (FAILED(pObject->Ready_GameObject()))
		return E_FAIL;
	//CCamera::Get_Instance()->SetTarget(pObject);
	m_pGameObject_Manager->Add_GameObject_Manager(ID::Mouse, pObject);





	pObject = new CPlayer; 
	
	if (FAILED(pObject->Ready_GameObject()))
		return E_FAIL; 
	CCamera::Get_Instance()->SetTarget(pObject);
	m_pGameObject_Manager->Add_GameObject_Manager(ID::PLAYER, pObject);



	pObject = new Summon_Kimsimin;

	if (FAILED(pObject->Ready_GameObject()))
		return E_FAIL;
	//CCamera::Get_Instance()->SetTarget(pObject);
	m_pGameObject_Manager->Add_GameObject_Manager(ID::ChoSun, pObject);



	pObject = new Summon_Janggum;
	if (FAILED(pObject->Ready_GameObject()))
		return E_FAIL;
	//CCamera::Get_Instance()->SetTarget(pObject);
	m_pGameObject_Manager->Add_GameObject_Manager(ID::ChoSun, pObject);


	pObject = new RoyalGuard;

	if (FAILED(pObject->Ready_GameObject()))
		return E_FAIL;
	//Pos = { 1412,269,0 };  //1412 269
   //pObject->Set_Pos(Pos);
	pObject->Set_State();
	m_pGameObject_Manager->Add_GameObject_Manager(ID::NPC, pObject);


	pObject = new RoyalGuardName;
	if (FAILED(pObject->Ready_GameObject()))
		return E_FAIL;
	pObject->Set_State();

	m_pGameObject_Manager->Add_GameObject_Manager(ID::UI, pObject);

	//pObject = new CMapObject;
	//if (FAILED(pObject->Ready_GameObject()))
	//	return E_FAIL;
	//
	//m_pGameObject_Manager->Add_GameObject_Manager(ID::MAP, pObject);
	//

	LoadData_Object(L"../Data/NamHanCastle_UnitData22.dat");

	//pObject = new West_Rifleman;
	//
	//if (FAILED(pObject->Ready_GameObject()))
	//	return E_FAIL;
	////CCamera::Get_Instance()->SetTarget(pObject);
	//m_pGameObject_Manager->Add_GameObject_Manager(ID::MONSTER, pObject);
	//

	//pObject = new West_Boss;
	//
	//if (FAILED(pObject->Ready_GameObject()))
	//	return E_FAIL;
	////CCamera::Get_Instance()->SetTarget(pObject);
	//m_pGameObject_Manager->Add_GameObject_Manager(ID::MONSTER, pObject);
	//
	//
	//pObject = new West_infantry;
	//
	//if (FAILED(pObject->Ready_GameObject()))
	//	return E_FAIL;
	////CCamera::Get_Instance()->SetTarget(pObject);
	//m_pGameObject_Manager->Add_GameObject_Manager(ID::MONSTER, pObject);
	//

	



	return S_OK;
}

void CStage::Update_Scene()
{
	m_pGameObject_Manager->Update_GameObject_Manager();

	//몬스터 다 처치시, 다음 퀘스트 발동!
	if (
		m_pGameObject_Manager->Get_MonsterList().empty())
	{
		if (!m_pGameObject_Manager->Get_NPC().empty() && !m_pGameObject_Manager->Get_UI().empty())
		{

		m_pGameObject_Manager->Get_NPC().front()->Set_StateON();
		m_pGameObject_Manager->Get_UI().back()->Set_StateON();
		m_pGameObject_Manager->scenenumber = 4;
		}

	}


}

void CStage::Render_Scene()
{
	//SeaMap1
	//const TEXINFO* pTexInfo2 = CTexture_Manager::Get_Instance()->Get_TexInfo_Manager(L"SeaMap2", L"Sea2");

	const TEXINFO* pTexInfo2 = CTexture_Manager::Get_Instance()->Get_TexInfo_Manager(L"StartMap", L"Map");
	if (nullptr == pTexInfo2)
		return;
	D3DXMATRIX matScale, matTrans, matWorld;
	D3DXMatrixScaling(&matScale, 0.5f, 0.5f, 0.f); //기본 StartMap. 0.5 세팅 되어있음! Sea는 1.5

	//D3DXMatrixTranslation(&matTrans, 0 ,, 0.f);

	D3DXVECTOR3 tPos = {0,0,0};// * m_tPivot;

	tPos -= CCamera::Get_Instance()->GetPos();

	//if(tPos.y)
	D3DXMatrixTranslation(&matTrans, tPos.x, tPos.y, 0.f);

	//D3DXMatrixTranslation(&matTrans, 0 + CScroll_Manager::Get_Instance()->Get_Scroll(CScroll_Manager::eSB_HORZ), CScroll_Manager::Get_Instance()->Get_Scroll(CScroll_Manager::eSB_VERT), 0.f);
	matWorld = matScale* matTrans;

	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
	CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo2->pTexture, nullptr, nullptr, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	m_pGameObject_Manager->Render_GameObject_Manager();
}

void CStage::Release_Scene()
{
	m_pGameObject_Manager->Destroy_Instance(); 
}
