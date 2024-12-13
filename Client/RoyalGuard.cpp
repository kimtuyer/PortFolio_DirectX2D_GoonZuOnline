#include "stdafx.h"
#include "RoyalGuard.h"
#include "Terrain.h"
#include "CCamera.h"
#include "CMouse.h"
#include "M_AStar_Manager.h"
#include "CAStar_Manager.h"
#include "GameObject_Manager.h"
#include "Player.h"
#include "CMapObject.h"
#include "Frame_Manager.h"
#include "Time_Manager.h"
RoyalGuard::RoyalGuard() : m_tFrame({}), m_fFPSTime(0.f), m_fShotFPSTime(0), m_szFPS(L"")
,
m_fSpeed(0), pTerrain(nullptr), pPlayer(nullptr), m_pGameObject_Manager(CGameObject_Manager::Get_Instance())
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	m_fAttack_Range = float(TILECX * 2);
	m_fShortDist = m_fAttack_Range;



}

RoyalGuard::~RoyalGuard()
{
	Release_GameObject();

}
HRESULT RoyalGuard::Ready_GameObject()
{
	m_tInfo.vPos = { 1412,269,0 };
	m_tInfo.vDir = { 1.f, 1.f, 0.f };
	m_tInfo.vSize = { 1.f, 1.f, 0.f };
	m_tFrame = { 0.f, 8.f };
	m_fSpeed = 500.f;
	StateKey = L"Stand";
	m_tInfo.ID = ID::ChoSun;
	m_Damage = 10;

	vMouse = { 0, 0, 0.f };


	D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);


	m_listGameObject[PLAYER] = m_pGameObject_Manager->Get_ObjectList()[PLAYER];
	PlayerPos = m_listGameObject[PLAYER].front()->Get_Info().vPos;
	PlayerPos = { PlayerPos.x + TILECX * 2, PlayerPos.y,0 };

		//m_pM_AStar = new M_AStar_Manager(m_vecMonster[i]->vPos, tPos);

	m_listRoute.emplace_back(new M_AStar_Manager(m_tInfo.vPos, PlayerPos));
		//M_AStar_Manager::Get_Instance()->StartAStar_Manager(m_vecMonster[i]->vPos, tPos);
		m_tInfo.iAttack_Target = ID::END;
	



	return S_OK;
}

void RoyalGuard::FrameMove(float fSpeed)
{
	m_tFrame.fFrameStart += m_tFrame.fFrameEnd * CTime_Manager::Get_Instance()->Get_DeltaTime() * fSpeed;
	if (m_tFrame.fFrameEnd < m_tFrame.fFrameStart)
		m_tFrame.fFrameStart = 0.f;
}

void RoyalGuard::Move()
{
	pTerrain = static_cast<CTerrain*>(CGameObject_Manager::Get_Instance()->Get_Terrain());



	//list<TILE*>& BestList = CAStar_Manager::Get_Instance()->Get_BestList();

	list<TILE*>& BestList = m_listRoute.front()->Get_BestList();
	if (BestList.empty())
		return;


	//if (m_tInfo.iAttack_Target == ID::END)//공격타겟 없을땐 플레이어만 추적
	{
		int index = pTerrain->Get_TileIndex(m_tInfo.vPos);

		m_tInfo.vDir = BestList.front()->vPos - m_tInfo.vPos;
		m_tInfo.vDir2 = BestList.back()->vPos - m_tInfo.vPos;
		//m_tInfo.vDir = BestList.front()->vPos - m_vecMonster[i]->vPos;
		//m_tInfo.vDir2 = BestList.back()->vPos - m_vecMonster[i]->vPos;


		if (abs((BestList.back()->iIndex - index)) % (TILEX * 2) == 0 && m_tInfo.vDir.y > 0)
		{
			wcscpy_s(m_tInfo.StateKey, L"Walk");
			StateKey = L"Walk"; //Down

			//D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
			D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);


		}
		else if (abs((BestList.back()->iIndex - index)) % (TILEX * 2) == 0 && m_tInfo.vDir.y < 0) //up
		{
			wcscpy_s(m_tInfo.StateKey, L"WalkUp");

			StateKey = L"WalkUp";

			//D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
			D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);




		}
		else if (m_tInfo.vDir.x < 0 && abs((BestList.back()->iIndex - index)) < 10)
		{
			wcscpy_s(m_tInfo.StateKey, L"WalkLeft");

			StateKey = L"WalkLeft";

			//D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
			D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);


		}
		else if (m_tInfo.vDir.x > 0 && abs((BestList.back()->iIndex - index)) < 10)
		{
			wcscpy_s(m_tInfo.StateKey, L"WalkLeft");

			StateKey = L"WalkLeft";
			D3DXMatrixScaling(&matScale, -m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);

			//				D3DXMatrixScaling(&matScale, -m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);

		}
		//왼쪽 대각선 LU
		else if (m_tInfo.vDir.x < 0 && m_tInfo.vDir.y >0)
		{
			wcscpy_s(m_tInfo.StateKey, L"WalkLD");

			StateKey = L"WalkLD";
			D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);

			//				D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);

		}
		//왼쪽 대각선 LD

		else if (m_tInfo.vDir.x < 0 && m_tInfo.vDir.y < 0)
		{
			wcscpy_s(m_tInfo.StateKey, L"WalkLU");

			StateKey = L"WalkLU";
			//				D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
			D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);



		}

		//오른 대각선 LU
		else if (m_tInfo.vDir.x > 0 && m_tInfo.vDir.y > 0)
		{
			wcscpy_s(m_tInfo.StateKey, L"WalkLD");

			StateKey = L"WalkLD";

			//D3DXMatrixScaling(&matScale, -m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
			D3DXMatrixScaling(&matScale, -m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);


		}
		//오른 대각선 LD

		else if (m_tInfo.vDir.x > 0 && m_tInfo.vDir.y < 0)
		{
			wcscpy_s(m_tInfo.StateKey, L"WalkLU");

			StateKey = L"WalkLU";

			//D3DXMatrixScaling(&matScale, -m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
			D3DXMatrixScaling(&matScale, -m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);


		}

		else
		{
			wcscpy_s(m_tInfo.StateKey, L"Stand");

			StateKey = L"Stand";
			//D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
			D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);


		}


		//if (nullptr == pTexInfo)
		//	return;


		float fDist = D3DXVec3Length(&m_tInfo.vDir);
		D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);

		if (4.f > fDist)
			BestList.pop_front();

		if (BestList.empty())
		{
			StateKey = L"Stand";
			//PlayerPos = m_listGameObject[PLAYER].front()->Get_Info().vPos;
			//D3DXVECTOR3 vPos = { PlayerPos.x - TILECX * 2, PlayerPos.y - TILECY * 2,0 };
			//m_listRoute.pop_back();
			//플레이어에게 도착했을때 멈췄다가 이동시 다시 경로 받아 이동
			//m_listRoute.emplace_back(new M_AStar_Manager(m_tInfo.vPos, vPos));
		}

		m_tInfo.vPos += m_tInfo.vDir * CTime_Manager::Get_Instance()->Get_DeltaTime() * m_fSpeed;


	}
	

}


int RoyalGuard::Update_GameObject()
{
	return 0;
}

void RoyalGuard::Late_Update_GameObject()
{
	FrameMove(0.5f);
	m_fFPSTime += CTime_Manager::Get_Instance()->Get_DeltaTime();
	if (0.1f <= m_fFPSTime)
	{
		Move();

		m_fFPSTime = 0.f;
	}
}

void RoyalGuard::Render_GameObject()
{
	pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo_Manager(L"RoyalGuard", StateKey, (DWORD)m_tFrame.fFrameStart);
	if (nullptr == pTexInfo)
		return;
	float fCenterX = float(pTexInfo->tImageInfo.Width >> 1);
	float fCenterY = float(pTexInfo->tImageInfo.Height >> 1);

	D3DXVECTOR3 tPos = m_tInfo.vPos - m_tInfo.vSize;// * m_tPivot;

	tPos -= CCamera::Get_Instance()->GetPos();



	m_ColliderInfo[0] = { tPos.x - 52 ,tPos.y - 50 };
	m_ColliderInfo[1] = { m_ColliderInfo[0].x + 104,tPos.y - 50 };
	m_ColliderInfo[2] = { m_ColliderInfo[1].x,m_ColliderInfo[1].y + 100 };
	m_ColliderInfo[3] = { m_ColliderInfo[0].x,m_ColliderInfo[2].y };
	m_ColliderInfo[4] = { tPos.x - 52 ,tPos.y - 50 };


	D3DXMatrixTranslation(&matTrans, tPos.x, tPos.y, 0.f);

	//D3DXMatrixScaling(&matScale, m_vecMonster[i]->vSize.x, m_vecMonster[i]->vSize.y, 0.f);
	//D3DXMatrixTranslation(&matTrans, m_vecMap[i]->vPos.x + CScroll_Manager::Get_Instance()->Get_Scroll(CScroll_Manager::eSB_HORZ), m_vecMap[i]->vPos.y + CScroll_Manager::Get_Instance()->Get_Scroll(CScroll_Manager::eSB_VERT), 0.f);
	matWorld = matScale * matTrans;

	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
	CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	//CGraphic_Device::Get_Instance()->Get_Sprite()->End();
	//
	//CGraphic_Device::Get_Instance()->Get_Line()->Draw(m_ColliderInfo, 5, D3DCOLOR_ARGB(255, 0, 0, 0));
	//CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);
	
	


}

void RoyalGuard::Release_GameObject()
{
}

void RoyalGuard::Change_Animation(INFO * pObject, D3DXVECTOR3 vPos)
{
}

void RoyalGuard::Set_GoalTarget()
{
}

HRESULT RoyalGuard::Shot(D3DXVECTOR3 & vPos, D3DXVECTOR3 & GoalPos)
{
	return E_NOTIMPL;
}

void RoyalGuard::Search_Enemy()
{
}

HRESULT RoyalGuard::LoadData_Object(const wstring & wstrFilePath)
{
	return E_NOTIMPL;
}
