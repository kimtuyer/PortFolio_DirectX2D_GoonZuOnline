#include "stdafx.h"
#include "PowerBullet_Player.h"
#include "CSkill1_Player.h"
#include "CCamera.h"
#include "Terrain.h"
PowerBullet_Player::PowerBullet_Player() : m_tFrame({}),
m_fSpeed(0), pTerrain(nullptr)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	//Ready_GameObject();
}
PowerBullet_Player::~PowerBullet_Player()
{
	Release_GameObject();

}

void PowerBullet_Player::FrameMove(float fSpeed)
{
	m_tFrame.fFrameStart += m_tFrame.fFrameEnd * CTime_Manager::Get_Instance()->Get_DeltaTime() * fSpeed;
	if (m_tFrame.fFrameEnd < m_tFrame.fFrameStart)
		m_tFrame.fFrameStart = 0.f;
}

void PowerBullet_Player::Move()
{
}

HRESULT PowerBullet_Player::Ready_GameObject()
{
	m_ebullet = Bullet_ID::power;

	m_Damage = 100;
	m_bAttackState = true;

	m_tInfo.ID = ID::PlayerPowerBullet;
	m_tInfo.vDir = { 1.f, 1.f, 0.f };
	m_tInfo.vSize = { 0.7f, 0.7f, 0.f };
	m_tFrame = { 0.f, 10.f };
	m_fSpeed = 400.f;
	StateKey = L"Powerbullet_Player";
	D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);

	pTerrain = dynamic_cast<CTerrain*>(CGameObject_Manager::Get_Instance()->Get_Terrain());
	//pSkill1 = dynamic_cast<CSkill1_Player*>(CGameObject_Manager::Get_Instance()->Get_ObjectList);

	Set_Dir();

	return S_OK;
}

int PowerBullet_Player::Update_GameObject()
{
	
	m_tInfo.vDir = m_vGoalPos - m_tInfo.vPos;

	if (CGameObject_Manager::Get_Instance()->Is_Player_Skill1())//스킬이펙트 발동 삭제되었으면 발사

	{



	int index = pTerrain->Get_TileIndex(m_vGoalPos);

	float fDist = D3DXVec3Length(&m_tInfo.vDir);
	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);

	if (fDist <= 3)
	{
		m_life = 0;
		return OBJ_DEAD;
	}
		return 0;
	}
	
}

void PowerBullet_Player::Late_Update_GameObject()
{
	if (CGameObject_Manager::Get_Instance()->Is_Player_Skill1())//삭제되었으면
	{

	m_tInfo.vPos += m_tInfo.vDir * CTime_Manager::Get_Instance()->Get_DeltaTime() * m_fSpeed;
	FrameMove(0.5f);

	}
}

void PowerBullet_Player::Render_GameObject()
{
	if (m_life != 0)
	{
		m_tInfo.vDir = m_vGoalPos - m_tInfo.vPos;
		int Bulletindex = pTerrain->Get_TileIndex(m_tInfo.vPos);

		int index = pTerrain->Get_TileIndex(m_vGoalPos);

		float fDist = D3DXVec3Length(&m_tInfo.vDir);
		D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);

		if (fDist <= 1.5)
		{
			m_life = 0;
			//return OBJ_DEAD;
		}



		//int index = pTerrain->Get_TileIndex(m_vGoalPos);
		pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo_Manager(L"Powerbullet_Player", StateKey, (DWORD)m_tFrame.fFrameStart);
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


			m_ColliderInfo[0] = { tPos.x - 35  ,tPos.y - 35 };
			m_ColliderInfo[1] = { m_ColliderInfo[0].x + 75,tPos.y - 35 };
			m_ColliderInfo[2] = { m_ColliderInfo[1].x,m_ColliderInfo[1].y + 75 };
			m_ColliderInfo[3] = { m_ColliderInfo[0].x,m_ColliderInfo[2].y };
			m_ColliderInfo[4] = { tPos.x - 35 ,tPos.y - 35 };

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

void PowerBullet_Player::Release_GameObject()
{
}

void PowerBullet_Player::Set_Dir()
{
	D3DXVECTOR3 Dirpos= { 10,10,0 };
	if (m_life != 0)
	{
		m_tInfo.vDir = m_vGoalPos - m_tInfo.vPos;
		if(m_tInfo.vDir.x>=0)
		{ 
			Dirpos.x = 50;
		}
		else
		{
			Dirpos.x = -50;

		}

		if (m_tInfo.vDir.y >= 0)
		{
			Dirpos.y = 50;

		}
		else
		{
			Dirpos.y = -50;

		}

		//D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);
		//D3DXVec3Length()
		//Dirpos += m_tInfo.vDir;


		int index = pTerrain->Get_TileIndex(m_tInfo.vPos);
		int Targetindex = pTerrain->Get_TileIndex(m_vGoalPos);

		if (abs(Targetindex - index) % (TILEX * 2) == 0 && m_tInfo.vDir.y > 0)
		{
			StateKey = L"Powerbullet_Player"; //Down

			D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
			Dirpos.x = 0;
		}
		else if (abs(Targetindex - index) % (TILEX * 2) == 0 && m_tInfo.vDir.y < 0) //up
		{
			StateKey = L"Powerbullet_PlayerUp";

			D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);

			Dirpos.x = 0;


		}
		else if (m_tInfo.vDir.x < 0 && abs((Targetindex - index)) < 10)
		{
			StateKey = L"Powerbullet_PlayerLeft";

			D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);

			Dirpos.y = 0;

		}
		else if (m_tInfo.vDir.x > 0 && abs((Targetindex - index)) < 10)
		{
			StateKey = L"Powerbullet_PlayerLeft";

			D3DXMatrixScaling(&matScale, -m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
			Dirpos.y = 0;

		}
		//왼쪽 대각선 LU
		else if (m_tInfo.vDir.x < 0 && m_tInfo.vDir.y >0)
		{
			StateKey = L"Powerbullet_PlayerLD2";

			D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);

		}
		//왼쪽 대각선 LD

		else if (m_tInfo.vDir.x < 0 && m_tInfo.vDir.y < 0)
		{
			StateKey = L"Powerbullet_PlayerLU2";
			D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);


		}

		//오른 대각선 LU
		else if (m_tInfo.vDir.x > 0 && m_tInfo.vDir.y > 0)
		{
			StateKey = L"Powerbullet_PlayerLD2";

			D3DXMatrixScaling(&matScale, -m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);

		}
		//오른 대각선 LD

		else if (m_tInfo.vDir.x > 0 && m_tInfo.vDir.y < 0)
		{
			StateKey = L"Powerbullet_PlayerLU2";

			D3DXMatrixScaling(&matScale, -m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);


		}

		m_tInfo.vPos += Dirpos;

	}
}
