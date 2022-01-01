#include "stdafx.h"
#include "MainApp.h"
#include "Scene_Manager.h"
#include "GameObject_Manager.h"
#include "Frame_Manager.h"
#include "CCamera.h"
CMainApp::CMainApp()
	:m_pGraphic_Device(CGraphic_Device::Get_Instance())
	, m_pScene_Manager(CScene_Manager::Get_Instance())
{
}


CMainApp::~CMainApp()
{
	Release_MainApp(); 
}

HRESULT CMainApp::Ready_MainApp()
{
	m_tRS.iH = 720;
	m_tRS.iW = 1280;


	CTime_Manager::Get_Instance()->Ready_Time_Manager(); 
	if (FAILED(m_pGraphic_Device->Ready_Graphic_Device(CGraphic_Device::MODE_WIN)))
		return E_FAIL; 


	//카메라관리자 초기화
	//CCamera::Get_Instance()->Init(D3DXVECTOR3(0,0,0),
	if (!CCamera::Get_Instance()->Init(D3DXVECTOR3(0.f, 0.f,0),
		m_tRS, RESOLUTION(3500/2, 2048/2)))//RESOLUTION은 출력할 전체 맵이미지크기
		return false;


	rgb[0] = 255;
	rgb[1] = 247;
	rgb[2] = 0;
	rgb[3] = 255;


	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_SINGLE,
		L"../Texture/StartUI1.bmp", L"Loading",rgb)))
		return E_FAIL;

	//TileTexture
	//if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
	//	L"../Texture/Stage/Terrain/TILEMAP/TILE0%d.png", L"Terrain",rgb, L"Tile", 4)))
	//	return E_FAIL;
	//
	//if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
	//	L"../Texture/Stage/Object/gate_%d.bmp", L"MapObject", rgb, L"Gate", 23)))
	//	return E_FAIL;
	//
	//
	//if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_SINGLE,
	//	L"../Texture/Stage/Tile/Town.png", L"StartMap", rgb,L"Map", 1)))
	//	return E_FAIL;
	//
	////Player-Attack Texture 
	//rgb[0] = 255;
	//rgb[1] = 247;
	//rgb[2] = 0;
	//rgb[3] = 255;
	//
	//if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
	//	L"../Texture/Stage/Player/Stand/%d.bmp", L"Player", rgb, L"Attack", 20)))
	//	return E_FAIL;
	CSoundMgr::Get_Instance()->Initialize();



	m_pScene_Manager->Change_Scene_Manager(CScene_Manager::LOADING); 
	return S_OK;
}

void CMainApp::Update_MainApp()
{
	CTime_Manager::Get_Instance()->Update_Time_Manager(); 
	float fTime = CTime_Manager::Get_Instance()->Get_DeltaTime();
	CCamera* Object = CCamera::Get_Instance();//->Update(fTime);
	dynamic_cast<CCamera*>(Object)->Update(fTime);
	//Object->Update(fTime);
	//CCamera::Get_Instance()->Update(CTime_Manager::Get_Instance()->Get_DeltaTime());
	m_pScene_Manager->Update_Scene_Manager(); 
}

void CMainApp::Render_MainApp(CFrame_Manager* pFrame_Manager)
{
	m_pGraphic_Device->Render_Begin(); 

	//const TEXINFO* pTexInfo2 = CTexture_Manager::Get_Instance()->Get_TexInfo_Manager(L"StartMap", L"Map");
	//if (nullptr == pTexInfo2)
	//	return;
	//D3DXMATRIX matScale, matTrans, matWorld;
	//D3DXMatrixScaling(&matScale, 0.5f, 0.5f, 0.f);
	//
	//D3DXMatrixTranslation(&matTrans, 0+CScroll_Manager::Get_Instance()->Get_Scroll(CScroll_Manager::eSB_HORZ), CScroll_Manager::Get_Instance()->Get_Scroll(CScroll_Manager::eSB_VERT), 0.f);
	//matWorld = matScale * matTrans;
	//
	//CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
	//m_pGraphic_Device->Get_Sprite()->Draw(pTexInfo2->pTexture, nullptr, nullptr, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	m_pScene_Manager->Render_Scene_Manager(); 
	pFrame_Manager->Render_Frame_Manager(); 
	CCamera::Get_Instance()->Render(CTime_Manager::Get_Instance()->Get_DeltaTime());

	m_pGraphic_Device->Render_End(); 
}

void CMainApp::Release_MainApp()
{
	CTime_Manager::Destroy_Instance(); 
	CScroll_Manager::Destroy_Instance(); 
	CGameObject_Manager::Destroy_Instance(); 
	CCamera::Destroy_Instance();
	m_pScene_Manager->Destroy_Instance(); 
	m_pGraphic_Device->Destroy_Instance(); 
	
}
