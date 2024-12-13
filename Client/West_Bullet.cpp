#include "stdafx.h"
#include "West_Bullet.h"
#include "CCamera.h"
#include "Terrain.h"
West_Bullet::West_Bullet() : m_tFrame({}),
m_fSpeed(0), pTerrain(nullptr)
{
	m_life = 1;
	ZeroMemory(&m_tInfo, sizeof(INFO));
	Ready_GameObject();

}

West_Bullet::~West_Bullet()
{
	Release_GameObject();

}

void West_Bullet::FrameMove(float fSpeed)
{
	m_tFrame.fFrameStart += m_tFrame.fFrameEnd * CTime_Manager::Get_Instance()->Get_DeltaTime() * fSpeed;
	if (m_tFrame.fFrameEnd < m_tFrame.fFrameStart)
		m_tFrame.fFrameStart = 0.f;
}


void West_Bullet::Move()
{
}

HRESULT West_Bullet::Ready_GameObject()
{

	m_tInfo.ID = ID::Bullet;
	m_State = OBJ_DEAD;

	m_tInfo.vDir = { 1.f, 1.f, 0.f };
	m_tInfo.vSize = { 1.f, 1.f, 0.f };
	m_tFrame = { 0.f, 1.f };
	m_fSpeed = 300.f;
	StateKey = L"WestBullet";
	D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);

	pTerrain = static_cast<CTerrain*>(CGameObject_Manager::Get_Instance()->Get_Terrain());
	return S_OK;
}

int West_Bullet::Update_GameObject()
{
	if (m_State != OBJ_DEAD)
	{


	m_tInfo.vDir = m_vGoalPos - m_tInfo.vPos;

	int index = pTerrain->Get_TileIndex(m_vGoalPos);

	float fDist = D3DXVec3Length(&m_tInfo.vDir);
	m_fTargetDist = fDist;
	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);

	if (fDist <= 3)
	{
		//m_life = OBJ_DEAD;
		return OBJ_DEAD;
	}
	}
	return 0;
}

void West_Bullet::Late_Update_GameObject()
{
	if (m_State != OBJ_DEAD)
	{


		int index = pTerrain->Get_TileIndex(m_tInfo.vPos);
		int Targetindex = pTerrain->Get_TileIndex(m_vGoalPos);

		//if (abs(Targetindex - index) % (TILEX * 2) == 0 && m_tInfo.vDir.y > 0)
		//{
		//	//StateKey = L"PlayerBulletDown"; //Down
		//
		//	D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
		//
		//}
		//else if (abs(Targetindex - index) % (TILEX * 2) == 0 && m_tInfo.vDir.y < 0) //up
		//{
		//	//StateKey = L"PlayerBulletUp";
		//
		//	D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
		//
		//
		//
		//}
		//else if (m_tInfo.vDir.x < 0 && abs((Targetindex - index)) < 10)
		//{
		//	//StateKey = L"PlayerBulletLeft";
		//
		//	D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
		//
		//}
		//else if (m_tInfo.vDir.x > 0 && abs((Targetindex - index)) < 10)
		//{
		//	//tateKey = L"PlayerBulletLeft";
		//
		//	D3DXMatrixScaling(&matScale, -m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
		//
		//}
		////왼쪽 대각선 LU
		//else if (m_tInfo.vDir.x < 0 && m_tInfo.vDir.y >0)
		//{
		//	//StateKey = L"PlayerBulletLD";
		//
		//	D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
		//
		//}
		////왼쪽 대각선 LD
		//
		//else if (m_tInfo.vDir.x < 0 && m_tInfo.vDir.y < 0)
		//{
		//	//StateKey = L"PlayerBulletLU";
		//	D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
		//
		//
		//}
		//
		////오른 대각선 LU
		//else if (m_tInfo.vDir.x > 0 && m_tInfo.vDir.y > 0)
		//{
		//	//StateKey = L"PlayerBulletLD";
		//
		//	D3DXMatrixScaling(&matScale, -m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
		//
		//}
		////오른 대각선 LD
		//
		//else if (m_tInfo.vDir.x > 0 && m_tInfo.vDir.y < 0)
		//{
		//	//StateKey = L"PlayerBulletLU";
		//
		//	D3DXMatrixScaling(&matScale, -m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
		//
		//
		//}
		//
		//if (pTexInfo == nullptr)
		//	return OBJ_DEAD;


		D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);


		m_tInfo.vPos += m_tInfo.vDir * CTime_Manager::Get_Instance()->Get_DeltaTime() * m_fSpeed;


	}

	FrameMove(0.5f);
}

void West_Bullet::Render_GameObject()
{
	if (m_State !=OBJ_DEAD)
	{
		m_tInfo.vDir = m_vGoalPos - m_tInfo.vPos;
		int Bulletindex = pTerrain->Get_TileIndex(m_tInfo.vPos);

		int index = pTerrain->Get_TileIndex(m_vGoalPos);

		float fDist = D3DXVec3Length(&m_tInfo.vDir);
		D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);

		//if (fDist <= 1.5)
		//{
		//	m_life = 0;
		//	//return OBJ_DEAD;
		//}



		//int index = pTerrain->Get_TileIndex(m_vGoalPos);
		pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo_Manager(L"WestBullet", StateKey, (DWORD)m_tFrame.fFrameStart);
		//if(pTexInfo=nullptr)
		{


			//return;
		}
		//else
		{


			fCenterX = pTexInfo->tImageInfo.Width >> 1;
			fCenterY = pTexInfo->tImageInfo.Height >> 1;

			D3DXVECTOR3 tPos = m_tInfo.vPos; //- m_tInfo.vSize;// * m_tPivot;
			tPos -= CCamera::Get_Instance()->GetPos();

			m_ColliderInfo[0] = { tPos.x-4  ,tPos.y  };
			m_ColliderInfo[1] = { m_ColliderInfo[0].x + 8,tPos.y  };
			m_ColliderInfo[2] = { m_ColliderInfo[1].x,m_ColliderInfo[1].y +8 };
			m_ColliderInfo[3] = { m_ColliderInfo[0].x,m_ColliderInfo[2].y };
			m_ColliderInfo[4] = { tPos.x-4 ,tPos.y  };

			D3DXMatrixTranslation(&matTrans, tPos.x, tPos.y, 0.f);

			matWorld = matScale * matTrans;

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

void West_Bullet::Release_GameObject()
{
}
