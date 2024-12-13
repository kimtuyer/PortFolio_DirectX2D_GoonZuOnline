#include "stdafx.h"
#include "DAEMA_Shield.h"
#include "CCamera.h"

DAEMA_Shield::DAEMA_Shield() : m_tFrame({}),
m_fSpeed(0)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));

}

DAEMA_Shield::~DAEMA_Shield()
{
	Release_GameObject();

}

int DAEMA_Shield::FrameMove(float fSpeed)
{
	m_tFrame.fFrameStart += m_tFrame.fFrameEnd * CTime_Manager::Get_Instance()->Get_DeltaTime() * fSpeed;
	if (m_tFrame.fFrameEnd < m_tFrame.fFrameStart)
	{
		m_tFrame.fFrameStart = 0.f;
		m_bFrameEnd = true;
		return OBJ_DEAD;
	}
	else
		return 0;
}

void DAEMA_Shield::Move()
{
}

HRESULT DAEMA_Shield::Ready_GameObject()
{
	m_Damage = 0;

	m_tInfo.vDir = { 1.f, 1.f, 0.f };
	m_tInfo.vSize = { 1.f, 1.f, 0.f };
	m_tFrame = { 0.f, 16.f };
	m_fSpeed = 300.f;
	StateKey = L"Shield";
	D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);

	//pTerrain = static_cast<CTerrain*>(CGameObject_Manager::Get_Instance()->Get_Terrain());
	//Set_Dir();
	return S_OK;
}

int DAEMA_Shield::Update_GameObject()
{
	if (FrameMove(1.2f) == OBJ_DEAD)
	{
		m_life = 0;
		return OBJ_DEAD;
	}
	return 0;
}

void DAEMA_Shield::Late_Update_GameObject()
{
}

void DAEMA_Shield::Render_GameObject()
{
	if (m_life != 0)
	{
		//m_tInfo.vDir = m_vGoalPos - m_tInfo.vPos;
		//int Bulletindex = pTerrain->Get_TileIndex(m_tInfo.vPos);
		//
		//int index = pTerrain->Get_TileIndex(m_vGoalPos);
		//
		//float fDist = D3DXVec3Length(&m_tInfo.vDir);
		//D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);



		//int index = pTerrain->Get_TileIndex(m_vGoalPos);
		pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo_Manager(L"CheonGu", StateKey, (DWORD)m_tFrame.fFrameStart);
		//if(pTexInfo=nullptr)
		{


			//return;
		}
		//else
		{


			fCenterX = pTexInfo->tImageInfo.Width >> 1;
			fCenterY = pTexInfo->tImageInfo.Height >> 1;

			D3DXVECTOR3 tPos = m_tInfo.vPos; //- m_tInfo.vSize;// * m_tPivot;
			//if (CCamera::Get_Instance()->GetLoc() > 0)
			tPos -= CCamera::Get_Instance()->GetPos();
			//else
			//	tPos -= CCamera::Get_Instance()->GetPos();


			m_ColliderInfo[0] = { tPos.x - 200  ,tPos.y - 160 };
			m_ColliderInfo[1] = { m_ColliderInfo[0].x + 400,tPos.y - 160 };
			m_ColliderInfo[2] = { m_ColliderInfo[1].x,m_ColliderInfo[1].y + 320 };
			m_ColliderInfo[3] = { m_ColliderInfo[0].x,m_ColliderInfo[2].y };
			m_ColliderInfo[4] = { tPos.x - 200 ,tPos.y - 160 };

			D3DXMatrixTranslation(&matTrans, tPos.x, tPos.y, 0.f);
			//D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);

			//D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x + CScroll_Manager::Get_Instance()->Get_Scroll(CScroll_Manager::eSB_HORZ), m_tInfo.vPos.y + CScroll_Manager::Get_Instance()->Get_Scroll(CScroll_Manager::eSB_VERT), 0.f);
			matWorld = matScale * matTrans;
			//pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo_Manager(L"Player", L"Stand", (DWORD)m_tFrame.fFrameStart);
			 //fCenterX = pTexInfo->tImageInfo.Width >> 1; 
			 //fCenterY = pTexInfo->tImageInfo.Height >> 1; 



			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

			//CGraphic_Device::Get_Instance()->Get_Sprite()->End();
			////D3DXVECTOR2 vLine[5]{ {m_ColliderInfo.left,}, {200.f, 100.f},{ 200.f, 200.f },{ 100.f, 200.f },{ 100.f, 100.f }, };
			////CGraphic_Device::Get_Instance()->Get_Line()->SetWidth(20); 
			//
			//CGraphic_Device::Get_Instance()->Get_Line()->Draw(m_ColliderInfo, 5, D3DCOLOR_ARGB(255, 0, 0, 0));
			//CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);

		}
	}
}

void DAEMA_Shield::Release_GameObject()
{
}

void DAEMA_Shield::Set_Dir()
{
}
