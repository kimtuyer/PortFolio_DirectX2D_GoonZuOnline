#include "stdafx.h"
#include "DAEMA_Dash.h"
#include "CCamera.h"
#include "Terrain.h"
DAEMA_Dash::DAEMA_Dash() : m_tFrame({}),
m_fSpeed(0), pTerrain(nullptr)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));

}

DAEMA_Dash::~DAEMA_Dash()
{
	Release_GameObject();

}

int DAEMA_Dash::FrameMove(float fSpeed)
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

void DAEMA_Dash::Move()
{
}

HRESULT DAEMA_Dash::Ready_GameObject()
{
	m_Damage = 30;

	m_tInfo.vDir = { 1.f, 1.f, 0.f };
	m_tInfo.vSize = { 1.f, 1.f, 0.f };
	m_tFrame = { 0.f, 7.f };
	m_fSpeed = 300.f;
	StateKey = L"DashEffect";
	D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);

	pTerrain = static_cast<CTerrain*>(CGameObject_Manager::Get_Instance()->Get_Terrain());
	Set_Dir();
	return S_OK;
}

int DAEMA_Dash::Update_GameObject()
{
	m_tInfo.vDir = m_vGoalPos - m_tInfo.vPos;

	int index = pTerrain->Get_TileIndex(m_vGoalPos);

	float fDist = D3DXVec3Length(&m_tInfo.vDir);
	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);



	if (FrameMove(0.5f) == OBJ_DEAD)
	{
		m_life = 0;
		return OBJ_DEAD;
	}
	return 0;
}

void DAEMA_Dash::Late_Update_GameObject()
{
}

void DAEMA_Dash::Render_GameObject()
{
	if (m_life != 0)
	{
		m_tInfo.vDir = m_vGoalPos - m_tInfo.vPos;
		int Bulletindex = pTerrain->Get_TileIndex(m_tInfo.vPos);

		int index = pTerrain->Get_TileIndex(m_vGoalPos);

		float fDist = D3DXVec3Length(&m_tInfo.vDir);
		D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);



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


			m_ColliderInfo[0] = { tPos.x - 267  ,tPos.y - 260 };
			m_ColliderInfo[1] = { m_ColliderInfo[0].x +520,tPos.y - 260 };
			m_ColliderInfo[2] = { m_ColliderInfo[1].x,m_ColliderInfo[1].y + 520 };
			m_ColliderInfo[3] = { m_ColliderInfo[0].x,m_ColliderInfo[2].y };
			m_ColliderInfo[4] = { tPos.x - 267 ,tPos.y - 260 };

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

void DAEMA_Dash::Release_GameObject()
{
}

void DAEMA_Dash::Set_Dir()
{
	if (m_life != 0)
	{
		m_tInfo.vDir = m_vGoalPos - m_tInfo.vPos;


		int index = pTerrain->Get_TileIndex(m_tInfo.vPos);
		int Targetindex = pTerrain->Get_TileIndex(m_vGoalPos);

		if (abs(Targetindex - index) % (TILEX * 2) == 0 && m_tInfo.vDir.y > 0)
		{
			StateKey = L"DashEffect"; //Down

			D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);

		}
		else if (abs(Targetindex - index) % (TILEX * 2) == 0 && m_tInfo.vDir.y < 0) //up
		{
			StateKey = L"DashEffectUp";

			D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);



		}
		else if (m_tInfo.vDir.x < 0 && abs((Targetindex - index)) < 10)
		{
			StateKey = L"DashEffectLeft";

			D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);

		}
		else if (m_tInfo.vDir.x > 0 && abs((Targetindex - index)) < 10)
		{
			StateKey = L"DashEffectLeft";

			D3DXMatrixScaling(&matScale, -m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);

		}
		//���� �밢�� LU
		else if (m_tInfo.vDir.x < 0 && m_tInfo.vDir.y >0)
		{
			StateKey = L"DashEffectLD";

			D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);

		}
		//���� �밢�� LD

		else if (m_tInfo.vDir.x < 0 && m_tInfo.vDir.y < 0)
		{
			StateKey = L"DashEffectLU";
			D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);


		}

		//���� �밢�� LU
		else if (m_tInfo.vDir.x > 0 && m_tInfo.vDir.y > 0)
		{
			StateKey = L"DashEffectLD";

			D3DXMatrixScaling(&matScale, -m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);

		}
		//���� �밢�� LD

		else if (m_tInfo.vDir.x > 0 && m_tInfo.vDir.y < 0)
		{
			StateKey = L"DashEffectLU";

			D3DXMatrixScaling(&matScale, -m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);


		}
	}
}
