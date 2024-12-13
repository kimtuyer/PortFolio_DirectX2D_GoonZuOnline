#include "stdafx.h"
#include "Bullet_Player.h"
#include "CCamera.h"
#include "Terrain.h"
Bullet_Player::Bullet_Player() : m_tFrame({}),
m_fSpeed(0), pTerrain(nullptr)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));

}

Bullet_Player::~Bullet_Player()
{
	Release_GameObject();

}

void Bullet_Player::FrameMove(float fSpeed)
{
	m_tFrame.fFrameStart += m_tFrame.fFrameEnd * CTime_Manager::Get_Instance()->Get_DeltaTime() * fSpeed;
	if (m_tFrame.fFrameEnd < m_tFrame.fFrameStart)
		m_tFrame.fFrameStart = 0.f;
}

void Bullet_Player::Move()
{
}

HRESULT Bullet_Player::Ready_GameObject()
{
	//m_tInfo.vPos = { 850.f, 420.f, 0.f };

	m_ebullet = Bullet_ID::default;
	m_bAttackState = true;
	m_Damage = 30;
	m_tInfo.ID = ID::PlayerBullet;
	m_tInfo.vDir = { 1.f, 1.f, 0.f };
	m_tInfo.vSize = { 0.5f, 0.5f, 0.f };
	m_tFrame = { 0.f, 10.f };
	m_fSpeed = 400.f;
	StateKey = L"PlayerBulletDown";
	D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);

	pTerrain = static_cast<CTerrain*>(CGameObject_Manager::Get_Instance()->Get_Terrain());
	Set_Dir();
	return S_OK;
}

int Bullet_Player::Update_GameObject()
{
	m_tInfo.vDir = m_vGoalPos - m_tInfo.vPos;

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

void Bullet_Player::Late_Update_GameObject()
{

	

		//if (pTexInfo == nullptr)
		//	return OBJ_DEAD;


		

		m_tInfo.vPos += m_tInfo.vDir * CTime_Manager::Get_Instance()->Get_DeltaTime() * m_fSpeed;


	

	FrameMove(0.5f);
}

void Bullet_Player::Render_GameObject()
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
	pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo_Manager(L"PlayerBullet", StateKey, (DWORD)m_tFrame.fFrameStart);
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


	m_ColliderInfo[0] = { tPos.x-35  ,tPos.y-35 };
	m_ColliderInfo[1] = { m_ColliderInfo[0].x + 75,tPos.y-35 };
	m_ColliderInfo[2] = { m_ColliderInfo[1].x,m_ColliderInfo[1].y + 75 };
	m_ColliderInfo[3] = { m_ColliderInfo[0].x,m_ColliderInfo[2].y };
	m_ColliderInfo[4] = { tPos.x-35 ,tPos.y-35 };

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

void Bullet_Player::Release_GameObject()
{
}

void Bullet_Player::Set_Dir()
{
	if (m_life != 0)
	{
		m_tInfo.vDir = m_vGoalPos - m_tInfo.vPos;


		int index = pTerrain->Get_TileIndex(m_tInfo.vPos);
		int Targetindex = pTerrain->Get_TileIndex(m_vGoalPos);

		if (abs(Targetindex - index) % (TILEX * 2) == 0 && m_tInfo.vDir.y > 0)
		{
			StateKey = L"PlayerBulletDown"; //Down

			D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);

		}
		else if (abs(Targetindex - index) % (TILEX * 2) == 0 && m_tInfo.vDir.y < 0) //up
		{
			StateKey = L"PlayerBulletUp";

			D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);



		}
		else if (m_tInfo.vDir.x < 0 && abs((Targetindex - index)) < 10)
		{
			StateKey = L"PlayerBulletLeft";

			D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);

		}
		else if (m_tInfo.vDir.x > 0 && abs((Targetindex - index)) < 10)
		{
			StateKey = L"PlayerBulletLeft";

			D3DXMatrixScaling(&matScale, -m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);

		}
		//왼쪽 대각선 LU
		else if (m_tInfo.vDir.x < 0 && m_tInfo.vDir.y >0)
		{
			StateKey = L"PlayerBulletLD";

			D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);

		}
		//왼쪽 대각선 LD

		else if (m_tInfo.vDir.x < 0 && m_tInfo.vDir.y < 0)
		{
			StateKey = L"PlayerBulletLU";
			D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);


		}

		//오른 대각선 LU
		else if (m_tInfo.vDir.x > 0 && m_tInfo.vDir.y > 0)
		{
			StateKey = L"PlayerBulletLD";

			D3DXMatrixScaling(&matScale, -m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);

		}
		//오른 대각선 LD

		else if (m_tInfo.vDir.x > 0 && m_tInfo.vDir.y < 0)
		{
			StateKey = L"PlayerBulletLU";

			D3DXMatrixScaling(&matScale, -m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);


		}
	}
}
