#include "stdafx.h"
#include "TopHP.h"
#include "CCamera.h"
#include "GameObject_Manager.h"
TopHP::TopHP() : m_tFrame({})
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	pTophpbar = CGameObject_Manager::Get_Instance()->Get_UI().front();


}

TopHP::~TopHP()
{
	Release_GameObject();

}

int TopHP::FrameMove(float fSpeed)
{
	m_tFrame.fFrameStart += m_tFrame.fFrameEnd * CTime_Manager::Get_Instance()->Get_DeltaTime() * fSpeed;
	if (m_tFrame.fFrameEnd < m_tFrame.fFrameStart)
	{
		m_tFrame.fFrameStart = 0.f;
		//m_bFrameEnd = true;
		return OBJ_DEAD;
	}
	else
		return 0;
}

HRESULT TopHP::Ready_GameObject()
{
	pTophpbar = CGameObject_Manager::Get_Instance()->Get_UI().front();
	
	
	
	//m_vecInfo.resize(196);
	//m_vecInfo[0]->vPos.x = pTophpbar->Get_Info().vPos.x - 194;
	//m_vecInfo[0]->vPos.y = pTophpbar->Get_Info().vPos.y - 170;
	//
	//for (int i = 1; i < 196; ++i)
	//{
	//	m_vecInfo[i]->vPos.x = m_vecInfo[i]->vPos.x + 2;
	//	m_vecInfo[i]->vPos.y = pTophpbar->Get_Info().vPos.y - 170;
	//
	//}
	



	//m_tInfo.vPos = pTophpbar->Get_Info().vPos;
	m_tInfo.vPos = { pTophpbar->Get_Info().vPos.x - 197,pTophpbar->Get_Info().vPos.y - 36,0 };
	m_tInfo.vDir = { 1.f, 1.f, 0.f };
	m_tInfo.vSize = { 1.f, 1.f, 0.f };
	//m_tInfo.vPos = { 100,30,0 };
	m_tFrame = { 0.f, 1.f };
	//m_fSpeed = 300.f;
	StateKey = L"TopHP";




	//pTerrain = dynamic_cast<CTerrain*>(CGameObject_Manager::Get_Instance()->Get_Terrain());
	//Set_Dir();
	return S_OK;
}

int TopHP::Update_GameObject()
{
	FrameMove(0.5f);

	return 0;
}

void TopHP::Late_Update_GameObject()
{
}

void TopHP::Render_GameObject()
{
	m_tInfo.vPos = { pTophpbar->Get_Info().vPos.x ,pTophpbar->Get_Info().vPos.y - 170 ,0 };
	//for (int i = 0; i < 196; ++i)
	{


	//m_tInfo.vPos = { pTophpbar->Get_Info().vPos.x-194 ,pTophpbar->Get_Info().vPos.y-170 ,0 };

	D3DXMatrixScaling(&matScale, 1, 3, 0.f);

	///pTophpbar = CGameObject_Manager::Get_Instance()->Get_NPC().front();
	pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo_Manager(L"TopHP", StateKey, (DWORD)m_tFrame.fFrameStart);
	fCenterX = pTexInfo->tImageInfo.Width >> 1;
	fCenterY = pTexInfo->tImageInfo.Height >> 1;

	D3DXVECTOR3 tPos;
	tPos = m_tInfo.vPos;//m_vecInfo[i]->vPos;


	tPos -= CCamera::Get_Instance()->GetPos();

	D3DXMatrixTranslation(&matTrans, tPos.x, tPos.y, 0.f);
	matWorld = matScale * matTrans;

	

	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
	CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, &HP, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	}

}

void TopHP::Release_GameObject()
{
	for (auto& pTile : m_vecInfo)
		Safe_Delete(pTile);
	m_vecInfo.clear();
	m_vecInfo.shrink_to_fit();
}
