#include "stdafx.h"
#include "Scene_Manager.h"
#include "Stage.h"
#include "Start_Scene.h"
#include "HanYang_Scene.h"
#include "KwangHwa_Scene.h"
#include "CLoading.h"
#include "KwangHwa_Scene2.h"
#include "DAEMADO_Scene.h"

IMPLEMENT_SINGLETON(CScene_Manager)
CScene_Manager::CScene_Manager()
	:m_eCurScene(END)
	, m_eNextScene(END)
	, m_pScene(nullptr)
{
}


CScene_Manager::~CScene_Manager()
{
	Release_Scene_Manager(); 
}


HRESULT CScene_Manager::Change_Scene_Manager(ID eNextScene)
{
	m_eNextScene = eNextScene; 
	if (m_eNextScene != m_eCurScene)
	{
		Safe_Delete(m_pScene); 
		switch (m_eNextScene)
		{
		case CScene_Manager::LOADING:
			m_pScene = new CLoading;
			break;
		case CScene_Manager::Start:
			m_pScene = new Start_Scene;
			break;
		case CScene_Manager::HanYang:
			m_pScene = new HanYang_Scene;
			break;
		case CScene_Manager::KwangHwa:
			m_pScene = new KwangHwa_Scene;
			break;
		case CScene_Manager::STAGE:
			m_pScene = new CStage; 
			break;
		case CScene_Manager::KwangHwa2:
			m_pScene = new KwangHwa_Scene2;
			break;
		case CScene_Manager::DAEMA:
			m_pScene = new DAEMADO_Scene;
			break;
		case CScene_Manager::END:
			break;
		default:
			break;
		}
		if (FAILED(m_pScene->Ready_Scene()))
		{
			Safe_Delete(m_pScene); 
			return E_FAIL;
		}

		m_eCurScene = m_eNextScene; 
	}
	return S_OK;
}

void CScene_Manager::Update_Scene_Manager()
{
	m_pScene->Update_Scene(); 
}

void CScene_Manager::Render_Scene_Manager()
{
	m_pScene->Render_Scene(); 
}

void CScene_Manager::Release_Scene_Manager()
{
	Safe_Delete(m_pScene); 
}
