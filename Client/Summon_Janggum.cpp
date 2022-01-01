#include "stdafx.h"
#include "Summon_Janggum.h"
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
#include "Janggum_Skill.h"

#include "CHPBar_Player.h"

Summon_Janggum::Summon_Janggum() : m_tFrame({}), m_fFPSTime(0.f), m_fShotFPSTime(0), m_szFPS(L"")
,
m_fSpeed(0), pTerrain(nullptr), pPlayer(nullptr), m_pGameObject_Manager(CGameObject_Manager::Get_Instance())
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	m_fAttack_Range = float(TILECX * 5);
	m_fShortDist = m_fAttack_Range;
	



}

Summon_Janggum::~Summon_Janggum()
{
	Release_GameObject();

}
HRESULT Summon_Janggum::Ready_GameObject()
{
	m_tInfo.vDir = { 1.f, 1.f, 0.f };
	m_tInfo.vSize = { 1.f, 1.f, 0.f };
	m_tFrame = { 0.f, 8.f };
	m_fSpeed = 500.f;
	StateKey = L"Stand";
	m_tInfo.ID = ID::ChoSun;
	m_Damage = 10;

	vMouse = { 0, 0, 0.f };


	D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);

	//INFO *pObject = nullptr;
	//LoadTileData_MapObject(L"../Data/Start_ObjectData2.dat");
	//LoadData_Object(L"../Data/NamHanCastle_UnitData4.dat");

	//처음 초기 목표지점 설정
	//m_listGameObject[MAP] = m_pGameObject_Manager->Get_ObjectList()[MAP];


	m_listGameObject[PLAYER] = m_pGameObject_Manager->Get_ObjectList()[PLAYER];
	PlayerPos = m_listGameObject[PLAYER].front()->Get_Info().vPos;
	m_tInfo.vPos = { PlayerPos.x + TILECX * 2, PlayerPos.y - TILECY * 2,0 };


	//for (auto p : m_listGameObject[MAP])
	//{
	//	for (auto n : dynamic_cast<CMapObject*>(p)->Get_VecTile())
	//		if (n->byDrawID == 34) //탑 id
	//			tPos = n->vPos;
	//}

	//DWORD dwSize = m_vecMonster.size();
	//for (size_t i = 0; i < dwSize; ++i)
	{
		//m_pM_AStar = new M_AStar_Manager(m_vecMonster[i]->vPos, tPos);

		//m_listRoute.emplace_back(new M_AStar_Manager(m_tInfo.vPos, PlayerPos));
		//M_AStar_Manager::Get_Instance()->StartAStar_Manager(m_vecMonster[i]->vPos, tPos);
		m_tInfo.iAttack_Target = ID::END;
	}





	//Kwanghwa_ObjectData

	return S_OK;
}

void Summon_Janggum::FrameMove(float fSpeed)
{
	m_tFrame.fFrameStart += m_tFrame.fFrameEnd * CTime_Manager::Get_Instance()->Get_DeltaTime() * fSpeed;
	if (m_tFrame.fFrameEnd < m_tFrame.fFrameStart)
		m_tFrame.fFrameStart = 0.f;
}

void Summon_Janggum::Move()
{
	pTerrain = dynamic_cast<CTerrain*>(CGameObject_Manager::Get_Instance()->Get_Terrain());



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
			//PlayerPos = m_listGameObject[PLAYER].front()->Get_Info().vPos;
			//D3DXVECTOR3 vPos = { PlayerPos.x - TILECX * 2, PlayerPos.y - TILECY * 2,0 };
			m_listRoute.pop_back();
			//플레이어에게 도착했을때 멈췄다가 이동시 다시 경로 받아 이동
			//m_listRoute.emplace_back(new M_AStar_Manager(m_tInfo.vPos, vPos));
		}

		m_tInfo.vPos += m_tInfo.vDir * CTime_Manager::Get_Instance()->Get_DeltaTime() * m_fSpeed;


	}
	//else if (m_vecMonster[i]->iAttack_Target == ID::PLAYER)//공격타겟이 플레이어로 새로 설정시
	//
	//{/ }
	//
	//else //
	


	
}


int Summon_Janggum::Update_GameObject()
{
	pPlayerHP = CGameObject_Manager::Get_Instance()->Get_PlayerHP();

	

	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		if (!m_listRoute.empty())
		{
			//vector<M_AStar_Manager*>::iterator iter = m_listRoute.begin();
			for (auto&p : m_listRoute)
				Safe_Delete(p);
			m_listRoute.clear();
		}
		//m_listRoute.pop_back();
		//m_AttackState = 0;

		//pMouse->Set_StateKey(L"MouseClick");
		//m_AttackState = 1;
		D3DXVECTOR3 vpos = CCamera::Get_Instance()->GetPos();
		D3DXVECTOR3 vPivot = CCamera::Get_Instance()->Get_Pivoit();

		//D3DXVECTOR3 vCamera = { vpos.x*vPivot.x, vpos.y*vPivot.y, 0 };
		D3DXVECTOR3 vCamera = { vpos.x, vpos.y, 0 };

		POINT pt{};
		GetCursorPos(&pt);
		ScreenToClient(g_hWND, &pt);

		//Screento
		pTerrain = dynamic_cast<CTerrain*>(CGameObject_Manager::Get_Instance()->Get_Terrain());

		D3DXVECTOR3 vPt = { float(pt.x),float(pt.y),0 };
		vMouse = { float(pt.x) + vCamera.x, float(pt.y) + vCamera.y, 0.f };

		//D3DXVECTOR3 vMouse{ float(pt.x)- vpos.x , float(pt.y)- vpos.y  , 0.f };
		//플레이어가 월드좌표에서 카메라피벗 이상 이동시
		if (m_tInfo.vPos.x >= CCamera::Get_Instance()->GetWorld().x*vPivot.x
			&& m_tInfo.vPos.y <= CCamera::Get_Instance()->GetWorld().y*vPivot.y

			)
			vMouse = { float(pt.x) + (vCamera.x*vPivot.x) + float(pTexInfo->tImageInfo.Width)*(0.45f)
		   , float(pt.y) + (vCamera.y*vPivot.y), 0.f };



		else if (m_tInfo.vPos.y >= CCamera::Get_Instance()->GetWorld().y*vPivot.y
			&& m_tInfo.vPos.x <= CCamera::Get_Instance()->GetWorld().x*vPivot.x)
			vMouse = { float(pt.x) + (vCamera.x*vPivot.x)
		   , float(pt.y) + (vCamera.y*vPivot.y) + float(pTexInfo->tImageInfo.Height)*(0.55f), 0.f };



		else if (m_tInfo.vPos.x >= CCamera::Get_Instance()->GetWorld().x*vPivot.x
			&&m_tInfo.vPos.y >= CCamera::Get_Instance()->GetWorld().y*vPivot.y)
			vMouse = { float(pt.x) + (vCamera.x*vPivot.x) + float(pTexInfo->tImageInfo.Width)*(0.45f)
		   , float(pt.y) + (vCamera.y*vPivot.y) + float(pTexInfo->tImageInfo.Height)*(0.45f), 0.f };




		else
		{
			vMouse = { float(pt.x) + vCamera.x
	   , float(pt.y) + vCamera.y, 0.f };
		}



		//pMouse->Set_Pos(vMouse);



		int PlayerIndex = pTerrain->Get_TileIndex(m_tInfo.vPos);
		int index = pTerrain->Get_TileIndex(vPt);
		int Mouseindex = pTerrain->Get_TileIndex(vMouse);
		//D3DXVECTOR3 vMouse{ float(pt.x) - vScroll.x, float(pt.y) - vScroll.y , 0.f };

		D3DXVECTOR3 vPos = { vMouse.x + TILECX * 2, vMouse.y - TILECY * 2,0 };


		m_listRoute.emplace_back(new M_AStar_Manager(m_tInfo.vPos, vPos));


		//CAStar_Manager::Get_Instance()->StartAStar_Manager(m_tInfo.vPos, vPos);



	}
	else if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
	{

		m_fUpdateFPSTime += CTime_Manager::Get_Instance()->Get_DeltaTime();

		if (0.1f <= m_fUpdateFPSTime) //0.035 설정시 6마리 ~50fps ,4마리는 6~7fps  //8마리부턴 움직임이상현상발생
		{
			//m_listGameObject[MONSTER] = m_pGameObject_Manager->Get_ObjectList()[MONSTER];

			//if (!m_listGameObject[MONSTER].empty())
			{

				Search_Enemy();
			m_fUpdateFPSTime = 0.f;
			}
		}

	}
	if (0.1f <= m_fFPSTime)
	{
		//m_bAttackState = false;
		if (!m_bAttackState && !m_listRoute.empty())
			Move();

		m_fFPSTime = 0.f;
	}



	return 0;
}

void Summon_Janggum::Late_Update_GameObject()
{
	FrameMove(0.5f);

	m_fFPSTime += CTime_Manager::Get_Instance()->Get_DeltaTime();
	/*
	//0.035 설정시 6마리 ~50fps ,4마리는 6~7fps  //8마리부턴 움직임이상현상발생
	0.07로 올리니 제자리 공격시 기존fps 20대에서 50대로 올라감
	프레임잡기위해 프레임 턴을 올리면서, 유닛의 스피드값을 올리면
	유닛이 제자리에서 얼타면서 빠르게 이동하질 못함
	*/



	if (m_bAttackState)
	{
		m_tFrame.fFrameEnd = 17.f;

	}
	else
		m_tFrame.fFrameEnd = 8.f;

	//하기전 몬스터리스트에 hp 0인것들은 리스트에서 삭제
	if (!m_listGameObject[MONSTER].empty() && m_listGameObject[MONSTER].front()->Get_Hp() <= 0)
		m_listGameObject[MONSTER].pop_front();

	if (!m_listGameObject[MONSTER].empty())
		//Search_Enemy();

	if (!m_listRoute.empty() && m_listRoute.front()->Get_BestList().empty())
		StateKey = L"Stand";

}

void Summon_Janggum::Render_GameObject()
{
	pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo_Manager(L"Janggum", StateKey, (DWORD)m_tFrame.fFrameStart);
	if (nullptr == pTexInfo)
		return;
	float fCenterX = float(pTexInfo->tImageInfo.Width >> 1);
	float fCenterY = float(pTexInfo->tImageInfo.Height >> 1);

	D3DXVECTOR3 tPos = m_tInfo.vPos - m_tInfo.vSize;// * m_tPivot;

	tPos -= CCamera::Get_Instance()->GetPos();



	m_ColliderInfo[0] = { tPos.x - 75 ,tPos.y - 50 };
	m_ColliderInfo[1] = { m_ColliderInfo[0].x + 150,tPos.y - 50 };
	m_ColliderInfo[2] = { m_ColliderInfo[1].x,m_ColliderInfo[1].y + 150 };
	m_ColliderInfo[3] = { m_ColliderInfo[0].x,m_ColliderInfo[2].y };
	m_ColliderInfo[4] = { m_ColliderInfo[0].x ,tPos.y - 50 };


	D3DXMatrixTranslation(&matTrans, tPos.x, tPos.y, 0.f);

	//D3DXMatrixScaling(&matScale, m_vecMonster[i]->vSize.x, m_vecMonster[i]->vSize.y, 0.f);
	//D3DXMatrixTranslation(&matTrans, m_vecMap[i]->vPos.x + CScroll_Manager::Get_Instance()->Get_Scroll(CScroll_Manager::eSB_HORZ), m_vecMap[i]->vPos.y + CScroll_Manager::Get_Instance()->Get_Scroll(CScroll_Manager::eSB_VERT), 0.f);
	matWorld = matScale * matTrans;

	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
	CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));




	//CGraphic_Device::Get_Instance()->Get_Line()->Draw(m_ColliderInfo, 5, D3DCOLOR_ARGB(255, 0, 0, 0));
	//CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);
	//if (1.f <= m_fFPSTime)
	{
		swprintf_s(m_szFPS, L"HP : %d", m_HP);
		//m_iFPS = 0;
		//m_fFPSTime = 0.f;
	}
	//SetWindowText(g_hWND, m_szFPS); 
	//D3DXMATRIX matTrans1;
	//D3DXMatrixTranslation(&matTrans1, m_ColliderInfo[0].x, m_ColliderInfo[0].y, 0.f);
	////
	//CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matTrans1);
	//CGraphic_Device::Get_Instance()->Get_Font()->DrawTextW(CGraphic_Device::Get_Instance()->Get_Sprite(), m_szFPS, lstrlen(m_szFPS), nullptr, 0, D3DCOLOR_ARGB(255, 0, 0, 0));
	//CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);

}

void Summon_Janggum::Release_GameObject()
{
}

void Summon_Janggum::Change_Animation(INFO * pObject, D3DXVECTOR3 vPos)
{

	//현재 라이플병이 위치한 인덱스값
	int index = pTerrain->Get_TileIndex(pObject->vPos);
	m_tInfo.vDir = vPos - pObject->vPos;
	//m_tInfo.vDir2 = BestList.back()->vPos - m_tInfo.vPos;

	if (abs((pObject->GoalIndex - index)) % (TILEX * 2) == 0 && m_tInfo.vDir.y > 0)
	{
		wcscpy_s(pObject->StateKey, L"Attack");

		StateKey = L"Attack"; //Down

		D3DXMatrixScaling(&matScale, pObject->vSize.x, pObject->vSize.y, 0.f);

	}
	else if (abs((pObject->GoalIndex - index)) % (TILEX * 2) == 0 && m_tInfo.vDir.y < 0) //up
	{
		wcscpy_s(pObject->StateKey, L"AttackUp");

		StateKey = L"AttackUp";

		D3DXMatrixScaling(&matScale, pObject->vSize.x, pObject->vSize.y, 0.f);



	}
	else if (m_tInfo.vDir.x < 0 && abs((pObject->GoalIndex - index)) < 10)
	{
		wcscpy_s(pObject->StateKey, L"AttackLeft");

		StateKey = L"AttackLeft";

		D3DXMatrixScaling(&matScale, pObject->vSize.x, pObject->vSize.y, 0.f);

	}
	else if (m_tInfo.vDir.x > 0 && abs((pObject->GoalIndex - index)) < 10)
	{
		wcscpy_s(pObject->StateKey, L"AttackLeft");

		StateKey = L"AttackLeft";

		D3DXMatrixScaling(&matScale, -pObject->vSize.x, pObject->vSize.y, 0.f);

	}
	//왼쪽 대각선 LU
	else if (m_tInfo.vDir.x < 0 && m_tInfo.vDir.y >0)
	{
		wcscpy_s(pObject->StateKey, L"AttackLD");

		StateKey = L"AttackLD";

		D3DXMatrixScaling(&matScale, pObject->vSize.x, pObject->vSize.y, 0.f);

	}
	//왼쪽 대각선 LD

	else if (m_tInfo.vDir.x < 0 && m_tInfo.vDir.y < 0)
	{
		wcscpy_s(pObject->StateKey, L"AttackLU");

		StateKey = L"AttackLU";
		D3DXMatrixScaling(&matScale, pObject->vSize.x, pObject->vSize.y, 0.f);


	}

	//오른 대각선 LU
	else if (m_tInfo.vDir.x > 0 && m_tInfo.vDir.y > 0)
	{
		wcscpy_s(pObject->StateKey, L"AttackLD");

		StateKey = L"AttackLD";

		D3DXMatrixScaling(&matScale, -pObject->vSize.x, pObject->vSize.y, 0.f);

	}
	//오른 대각선 LD

	else if (m_tInfo.vDir.x > 0 && m_tInfo.vDir.y < 0)
	{
		wcscpy_s(pObject->StateKey, L"AttackLU");

		StateKey = L"AttackLU";

		D3DXMatrixScaling(&matScale, -pObject->vSize.x, pObject->vSize.y, 0.f);


	}

	else
	{
		wcscpy_s(pObject->StateKey, L"Stand");

		StateKey = L"Stand";
		D3DXMatrixScaling(&matScale, pObject->vSize.x, pObject->vSize.y, 0.f);

	}

	if (nullptr == pTexInfo)
		return;



}

void Summon_Janggum::Set_GoalTarget()
{
}

HRESULT Summon_Janggum::Shot(D3DXVECTOR3 & vPos, D3DXVECTOR3 & GoalPos)
{
	return E_NOTIMPL;
}

void Summon_Janggum::Search_Enemy()
{
	pPlayer = CGameObject_Manager::Get_Instance()->Get_Player();
	if (dynamic_cast<CHPBar_Player*>(pPlayerHP)->Get_TopHP() < 172)
	{
		m_bAttackState = true;
		m_tFrame.fFrameEnd = 17;
		
		Change_Animation(&m_tInfo, pPlayer->Get_Info().vPos);

		m_fHealFPSTime += CTime_Manager::Get_Instance()->Get_DeltaTime();
		if (0.1f <= m_fHealFPSTime)
		{
			m_fHealFPSTime = 0;
			pSkill = new Janggum_Skill;
			dynamic_cast<Janggum_Skill*>(pSkill)->Set_targetPos(m_tInfo.vPos, pPlayer->Get_Info().vPos);
			dynamic_cast<Janggum_Skill*>(pSkill)->Set_Life(1);
			pSkill->Ready_GameObject();

			m_pGameObject_Manager->Add_GameObject_Manager(ID::Heal, pSkill);
		}





	}
	else
	{
		m_bAttackState = false;
		m_tFrame.fFrameEnd = 8;


	}

}

HRESULT Summon_Janggum::LoadData_Object(const wstring & wstrFilePath)
{
	return E_NOTIMPL;
}
