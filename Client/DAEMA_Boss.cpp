#include "stdafx.h"
#include "DAEMA_Boss.h"
#include "Terrain.h"
#include "CCamera.h"
#include "M_AStar_Manager.h"
#include "GameObject_Manager.h"
#include "Player.h"
#include "West_Bullet.h"
#include "CMapObject.h"
#include "Frame_Manager.h"
#include "Time_Manager.h"
#include "DAEMA_Dash.h"
#include "DAEMA_Skill.h"
#include "DAEMA_Shield.h"
#include "CFireBoom_Skill.h"
DAEMA_Boss::DAEMA_Boss() : m_tFrame({}), m_fFPSTime(0.f), m_fShotFPSTime(0), m_szFPS(L"")
,
m_fSpeed(0), pTerrain(nullptr), pBullet(nullptr), m_pGameObject_Manager(CGameObject_Manager::Get_Instance())
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	m_fAttack_Range = float(TILECX * 2);
	m_fShortDist = m_fAttack_Range;



}

DAEMA_Boss::~DAEMA_Boss()
{
	Release_GameObject();

}
HRESULT DAEMA_Boss::Ready_GameObject()
{
	m_tInfo.vPos = { 1472, 640, 0.f };
	m_HP = 1500;
	m_tInfo.ID = ID::BOSS;
	m_tInfo.vDir = { 1.f, 1.f, 0.f };
	m_tInfo.vSize = { 1.f, 1.f, 0.f };
	m_tFrame = { 0.f, 10.f };
	m_fSpeed = 600.f;
	StateKey = L"Stand";

	D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);

	//INFO *pObject = nullptr;
	//LoadTileData_MapObject(L"../Data/Start_ObjectData2.dat");
	//LoadData_Object(L"../Data/NamHanCastle_UnitData4.dat");

	//처음 초기 목표지점 설정
	m_listGameObject[MAP] = m_pGameObject_Manager->Get_ObjectList()[MAP];
	m_listGameObject[PLAYER] = m_pGameObject_Manager->Get_ObjectList()[PLAYER];
	m_listGameObject[ChoSun] = m_pGameObject_Manager->Get_ChoSun();

	D3DXVECTOR3 tPos; //탑의 위치
	for (auto p : m_listGameObject[PLAYER])
	{
		tPos=p->Get_Info().vPos;
		//for (auto n : dynamic_cast<CMapObject*>(p)->Get_VecTile())
		//	if (n->byDrawID == 34) //탑 id
		//		tPos = n->vPos;
	}

	//DWORD dwSize = m_vecMonster.size();
	//for (size_t i = 0; i < dwSize; ++i)
	{
		//m_pM_AStar = new M_AStar_Manager(m_vecMonster[i]->vPos, tPos);

		m_listRoute.emplace_back(new M_AStar_Manager(m_tInfo.vPos, m_tInfo.vPos));
		////M_AStar_Manager::Get_Instance()->StartAStar_Manager(m_vecMonster[i]->vPos, tPos);
		//m_tInfo.iAttack_Target = ID::PLAYER;
	}

	//pBullet = new West_Bullet;
	//m_pGameObject_Manager->Add_GameObject_Manager(ID::Bullet, pBullet);



	//Kwanghwa_ObjectData

	return S_OK;
}



void DAEMA_Boss::FrameMove(float fSpeed)
{
	m_tFrame.fFrameStart += m_tFrame.fFrameEnd * CTime_Manager::Get_Instance()->Get_DeltaTime() * fSpeed;
	
	 if (m_tFrame.fFrameEnd < m_tFrame.fFrameStart &&m_bDead)
	{
		m_bAttackState = false;
		m_tFrame.fFrameStart = 0.f;
		m_State = OBJ_DEAD;
		return;
	}
	 else if (m_tFrame.fFrameEnd < m_tFrame.fFrameStart )
	 {
		 m_tFrame.fFrameStart = 0.f;
		 m_bAttackState = false;

	 }

}

void DAEMA_Boss::Move()
{
	pTerrain = dynamic_cast<CTerrain*>(CGameObject_Manager::Get_Instance()->Get_Terrain());


	{

		if(m_listRoute.empty())
		{
			return;
		}

		list<TILE*>& BestList = m_listRoute.front()->Get_BestList();
		if (BestList.empty())
			return;


		//if (m_tInfo.iAttack_Target == ID::END)//공격타겟이 초기목표 탑일때만 이동!
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


			if (nullptr == pTexInfo)
				return;


			float fDist = D3DXVec3Length(&m_tInfo.vDir);
			D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);

			if (4.f > fDist)
				BestList.pop_front();
			m_tInfo.vPos += m_tInfo.vDir * CTime_Manager::Get_Instance()->Get_DeltaTime() * m_fSpeed;


		}
		//else if (m_vecMonster[i]->iAttack_Target == ID::PLAYER)//공격타겟이 플레이어로 새로 설정시
		//
		//{/ }
		//
		//else //
		{

			if (m_tInfo.iAttack_Target == MAP)

			{
				//m_vecMonster[i]->iAttack_Target = ID::MONSTER; //정지해서 공격모션 취하기 위해서
				//공격 목표 있을경우
				int index = pTerrain->Get_TileIndex(m_tInfo.vPos);
				m_tInfo.vDir = BestList.front()->vPos - m_tInfo.vPos;
				m_tInfo.vDir2 = BestList.back()->vPos - m_tInfo.vPos;
				//m_tInfo.vDir = BestList.front()->vPos - m_vecMonster[i]->vPos;
				//m_tInfo.vDir2 = BestList.back()->vPos - m_vecMonster[i]->vPos;

				Direct8 dir;
				//switch (i%8)
				//{
				//case Up:
				//	m_vecMonster[i]->vPos.x += dir.Direct[Up].x * CTime_Manager::Get_Instance()->Get_DeltaTime()* m_fSpeed;
				//	m_vecMonster[i]->vPos.y += dir.Direct[Up].y * CTime_Manager::Get_Instance()->Get_DeltaTime()* m_fSpeed;
				//	break;
				//case Down:
				//	m_vecMonster[i]->vPos.x += dir.Direct[Down].x * CTime_Manager::Get_Instance()->Get_DeltaTime()* m_fSpeed;
				//	m_vecMonster[i]->vPos.y += dir.Direct[Down].y * CTime_Manager::Get_Instance()->Get_DeltaTime()* m_fSpeed;
				//	break;
				//case Left:
				//	m_vecMonster[i]->vPos.x += dir.Direct[Left].x * CTime_Manager::Get_Instance()->Get_DeltaTime()* m_fSpeed;
				//	m_vecMonster[i]->vPos.y += dir.Direct[Left].y * CTime_Manager::Get_Instance()->Get_DeltaTime()* m_fSpeed;
				//	break;
				//case LD:
				//	m_vecMonster[i]->vPos.x += dir.Direct[LD].x * CTime_Manager::Get_Instance()->Get_DeltaTime()* m_fSpeed;
				//	m_vecMonster[i]->vPos.y += dir.Direct[LD].y * CTime_Manager::Get_Instance()->Get_DeltaTime()* m_fSpeed;
				//	break;
				//case LU:
				//	m_vecMonster[i]->vPos.x += dir.Direct[LU].x * CTime_Manager::Get_Instance()->Get_DeltaTime()* m_fSpeed;
				//	m_vecMonster[i]->vPos.y += dir.Direct[LU].y * CTime_Manager::Get_Instance()->Get_DeltaTime()* m_fSpeed;
				//	break;
				//case Right:
				//	m_vecMonster[i]->vPos.x += dir.Direct[Right].x * CTime_Manager::Get_Instance()->Get_DeltaTime()* m_fSpeed;
				//	m_vecMonster[i]->vPos.y += dir.Direct[Right].y * CTime_Manager::Get_Instance()->Get_DeltaTime()* m_fSpeed;
				//	break;
				//case RD:
				//	m_vecMonster[i]->vPos.x += dir.Direct[RD].x * CTime_Manager::Get_Instance()->Get_DeltaTime()* m_fSpeed;
				//	m_vecMonster[i]->vPos.y += dir.Direct[RD].y * CTime_Manager::Get_Instance()->Get_DeltaTime()* m_fSpeed;
				//	break;
				//case RU:
				//	m_vecMonster[i]->vPos.x += dir.Direct[RU].x * CTime_Manager::Get_Instance()->Get_DeltaTime()* m_fSpeed;
				//	m_vecMonster[i]->vPos.y += dir.Direct[RU].y * CTime_Manager::Get_Instance()->Get_DeltaTime()* m_fSpeed;
				//	break;
				//default:
				//	break;
				//}


				//if (i == 0)
				//	m_vecMonster[i]->vPos.y += TILECY * CTime_Manager::Get_Instance()->Get_DeltaTime()* m_fSpeed;
				//
				//else if (i == 1)
				//	m_vecMonster[i]->vPos.y -= TILECY * CTime_Manager::Get_Instance()->Get_DeltaTime()* m_fSpeed;
				//
				//else if (i == 2)
				//{
				//
				//	m_vecMonster[i]->vPos.x -= TILECX* CTime_Manager::Get_Instance()->Get_DeltaTime()* m_fSpeed;
				//    m_vecMonster[i]->vPos.y -= TILECY* CTime_Manager::Get_Instance()->Get_DeltaTime()* m_fSpeed;
				//
				//}
				//
				//else if (i == 3)
				//	m_vecMonster[i]->vPos.x -= TILECX * CTime_Manager::Get_Instance()->Get_DeltaTime()* m_fSpeed;
				//


			}


			//m_vecMonster[i]->vPos += m_vecMonster[i]->vDir * CTime_Manager::Get_Instance()->Get_DeltaTime() * m_fSpeed;

			//if (abs((BestList.back()->iIndex - index)) % (TILEX * 2) == 0 && m_vecMonster[i]->vDir.y > 0)
			//{
			//	StateKey = L"Walk"; //Down
			//
			//
			//
			//}



		}

	}
}


int DAEMA_Boss::Update_GameObject()
{
	m_fUpdateFPSTime += CTime_Manager::Get_Instance()->Get_DeltaTime();
	//if (m_listBullet.empty())




	if (0.1f <= m_fUpdateFPSTime) //0.035 설정시 6마리 ~50fps ,4마리는 6~7fps  //8마리부턴 움직임이상현상발생
	{
		if(!m_bDead)
		m_fUpdateFPSTime = 0.f;
		Search_Enemy();
	}
	//float eTime = CTime_Manager::Get_Instance()->Get_DeltaTime();

	m_fFPSTime += CTime_Manager::Get_Instance()->Get_DeltaTime();

	if (0.1f <= m_fFPSTime)
	{
		if (!m_bAttackState && !m_bDead)
			Move();

		m_fFPSTime = 0.f;
	}



	/*
현재 위치한 타일 인덱스값 가져와 사정거리내
적 있는지 검사

해당 스테이지에 존재하는 오브젝트 돌려가며
오브젝트 타일인덱스값 조사해야함
일단 여기선 Archer,Cannon,플레이어,탑 이 해당

인덱스 값 가져와, 내 자신위치에서 ex
------------------------------------------
총병은 내중심 8방향 3칸 이내까지 사정거리,
목표가 내 3칸이내 인덱스 범위안에 있는지 검사
or
초기 탑 위치 인덱스 목표로 이동

서로 인덱스값 아니까 위치값 받아와 거리 구해 거리값으로
총병은 가로or세로 타일기준 3개 거리를 사정거리로 잡아서
타겟 인덱스와의 거리가 사정거리이내에 있는지 검사
>>있다면 해당 목표 위치한 방향으로 애니메 변경하면서 이동!

우선 내 사정거리 인덱스 리스트를 뽑아와 맞는 인덱스있는지 검사!
>






있을경우 물체가 위치한 8방향중 해당방향에 맞는 공격 모션으로 변경!
이때 공격대상 Target 잡아준후 데미지값 전달해야함/
공격받은 Target 역시 자신이 공격받은 상태 On이 되야함!






*/
//m_pGameObject_Manager=




//Move();
	return 0;
}

void DAEMA_Boss::Late_Update_GameObject()
{

	if (m_bAttackState)
		m_tFrame.fFrameEnd = 10;
	else
		m_tFrame.fFrameEnd = 7;

	if (m_bDead)
	{
		m_tFrame.fFrameEnd = 25;
		m_bDead = true;
		StateKey == L"Dead";

	}

	//if (m_DAEMA_State == DAEMASTATE_Attack)
	//	m_tFrame.fFrameEnd = DAEMASTATE_Attack;
	//
	//else if (m_DAEMA_State == DAEMASTATE_Dash)
	//	m_tFrame.fFrameEnd = DAEMASTATE_Dash;
	//
	//else if (m_DAEMA_State == DAEMASTATE_Skill)
	//	m_tFrame.fFrameEnd = DAEMASTATE_Skill;

	FrameMove(0.5f);

}

void DAEMA_Boss::Render_GameObject()
{
	if (StateKey == L"Dead")
	{
		m_tFrame.fFrameEnd = 25;
	}

	{
		//const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo_Manager(L"Terrain", L"Tile", m_vecTile[i]->byDrawID);
		pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo_Manager(L"CheonGu", StateKey, (DWORD)m_tFrame.fFrameStart);
		if (nullptr == pTexInfo)
			return;
		float fCenterX = float(pTexInfo->tImageInfo.Width >> 1);
		float fCenterY = float(pTexInfo->tImageInfo.Height >> 1);

		D3DXVECTOR3 tPos = m_tInfo.vPos - m_tInfo.vSize;// * m_tPivot;

		tPos -= CCamera::Get_Instance()->GetPos();



		m_ColliderInfo[0] = { tPos.x - 180 ,tPos.y - 150 };
		m_ColliderInfo[1] = { m_ColliderInfo[0].x + 360,tPos.y - 150 };
		m_ColliderInfo[2] = { m_ColliderInfo[1].x,m_ColliderInfo[1].y + 300 };
		m_ColliderInfo[3] = { m_ColliderInfo[0].x,m_ColliderInfo[2].y };
		m_ColliderInfo[4] = { m_ColliderInfo[0].x ,tPos.y - 150 };


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
		//if (1.f <= m_fFPSTime)
		{
			//swprintf_s(m_szFPS, L"HP : %d", m_HP);
			//m_iFPS = 0;
			//m_fFPSTime = 0.f;
		}
		//SetWindowText(g_hWND, m_szFPS); 
		//D3DXMATRIX matTrans1;
		//D3DXMatrixTranslation(&matTrans1, m_ColliderInfo[0].x, m_ColliderInfo[0].y, 0.f);
		//
		//CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matTrans1);
		//CGraphic_Device::Get_Instance()->Get_Font()->DrawTextW(CGraphic_Device::Get_Instance()->Get_Sprite(), m_szFPS, lstrlen(m_szFPS), nullptr, 0, D3DCOLOR_ARGB(255, 0, 0, 0));
		////CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);



	}
}

void DAEMA_Boss::Release_GameObject()
{
	for (auto& pTile : m_vecMonster)
		Safe_Delete(pTile);
	m_vecMonster.clear();
	m_vecMonster.shrink_to_fit();

	for (auto& pTile : m_listRoute)
		Safe_Delete(pTile);
	m_listRoute.clear();
	m_listRoute.shrink_to_fit();
}

void DAEMA_Boss::Change_Animation(INFO * pObject, D3DXVECTOR3 vPos)
{
	m_bAttackState = true;
	m_DAEMA_State = DAEMASTATE_Attack;
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

void DAEMA_Boss::Dash_Animation(INFO * pObject, D3DXVECTOR3 vPos)
{
	m_bAttackState = true;
	m_DAEMA_State = DAEMASTATE_Dash;

	//현재 라이플병이 위치한 인덱스값
	int index = pTerrain->Get_TileIndex(pObject->vPos);
	m_tInfo.vDir = vPos - pObject->vPos;
	//m_tInfo.vDir2 = BestList.back()->vPos - m_tInfo.vPos;

	if (abs((pObject->GoalIndex - index)) % (TILEX * 2) == 0 && m_tInfo.vDir.y > 0)
	{
		wcscpy_s(pObject->StateKey, L"Attack");

		StateKey = L"Dash"; //Down

		D3DXMatrixScaling(&matScale, pObject->vSize.x, pObject->vSize.y, 0.f);

	}
	else if (abs((pObject->GoalIndex - index)) % (TILEX * 2) == 0 && m_tInfo.vDir.y < 0) //up
	{
		wcscpy_s(pObject->StateKey, L"AttackUp");

		StateKey = L"DashUp";

		D3DXMatrixScaling(&matScale, pObject->vSize.x, pObject->vSize.y, 0.f);



	}
	else if (m_tInfo.vDir.x < 0 && abs((pObject->GoalIndex - index)) < 10)
	{
		wcscpy_s(pObject->StateKey, L"AttackLeft");

		StateKey = L"DashLeft";

		D3DXMatrixScaling(&matScale, pObject->vSize.x, pObject->vSize.y, 0.f);

	}
	else if (m_tInfo.vDir.x > 0 && abs((pObject->GoalIndex - index)) < 10)
	{
		wcscpy_s(pObject->StateKey, L"AttackLeft");

		StateKey = L"DashLeft";

		D3DXMatrixScaling(&matScale, -pObject->vSize.x, pObject->vSize.y, 0.f);

	}
	//왼쪽 대각선 LU
	else if (m_tInfo.vDir.x < 0 && m_tInfo.vDir.y >0)
	{
		wcscpy_s(pObject->StateKey, L"AttackLD");

		StateKey = L"DashLD";

		D3DXMatrixScaling(&matScale, pObject->vSize.x, pObject->vSize.y, 0.f);

	}
	//왼쪽 대각선 LD

	else if (m_tInfo.vDir.x < 0 && m_tInfo.vDir.y < 0)
	{
		wcscpy_s(pObject->StateKey, L"AttackLU");

		StateKey = L"DashLU";
		D3DXMatrixScaling(&matScale, pObject->vSize.x, pObject->vSize.y, 0.f);


	}

	//오른 대각선 LU
	else if (m_tInfo.vDir.x > 0 && m_tInfo.vDir.y > 0)
	{
		wcscpy_s(pObject->StateKey, L"AttackLD");

		StateKey = L"DashLD";

		D3DXMatrixScaling(&matScale, -pObject->vSize.x, pObject->vSize.y, 0.f);

	}
	//오른 대각선 LD

	else if (m_tInfo.vDir.x > 0 && m_tInfo.vDir.y < 0)
	{
		wcscpy_s(pObject->StateKey, L"AttackLU");

		StateKey = L"DashLU";

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

void DAEMA_Boss::Skill_Animation(INFO * pObject, D3DXVECTOR3 vPos)
{
	m_bAttackState = true;
	m_DAEMA_State = DAEMASTATE_Skill;

	//현재 라이플병이 위치한 인덱스값
	int index = pTerrain->Get_TileIndex(pObject->vPos);
	m_tInfo.vDir = vPos - pObject->vPos;
	//m_tInfo.vDir2 = BestList.back()->vPos - m_tInfo.vPos;

	if (abs((pObject->GoalIndex - index)) % (TILEX * 2) == 0 && m_tInfo.vDir.y > 0)
	{
		wcscpy_s(pObject->StateKey, L"Attack");

		StateKey = L"Skill"; //Down

		D3DXMatrixScaling(&matScale, pObject->vSize.x, pObject->vSize.y, 0.f);

	}
	else if (abs((pObject->GoalIndex - index)) % (TILEX * 2) == 0 && m_tInfo.vDir.y < 0) //up
	{
		wcscpy_s(pObject->StateKey, L"AttackUp");

		StateKey = L"SkillUp";

		D3DXMatrixScaling(&matScale, pObject->vSize.x, pObject->vSize.y, 0.f);



	}
	else if (m_tInfo.vDir.x < 0 && abs((pObject->GoalIndex - index)) < 10)
	{
		wcscpy_s(pObject->StateKey, L"AttackLeft");

		StateKey = L"SkillLeft";

		D3DXMatrixScaling(&matScale, pObject->vSize.x, pObject->vSize.y, 0.f);

	}
	else if (m_tInfo.vDir.x > 0 && abs((pObject->GoalIndex - index)) < 10)
	{
		wcscpy_s(pObject->StateKey, L"AttackLeft");

		StateKey = L"SkillLeft";

		D3DXMatrixScaling(&matScale, -pObject->vSize.x, pObject->vSize.y, 0.f);

	}
	//왼쪽 대각선 LU
	else if (m_tInfo.vDir.x < 0 && m_tInfo.vDir.y >0)
	{
		wcscpy_s(pObject->StateKey, L"AttackLD");

		StateKey = L"SkillLD";

		D3DXMatrixScaling(&matScale, pObject->vSize.x, pObject->vSize.y, 0.f);

	}
	//왼쪽 대각선 LD

	else if (m_tInfo.vDir.x < 0 && m_tInfo.vDir.y < 0)
	{
		wcscpy_s(pObject->StateKey, L"AttackLU");

		StateKey = L"SkillLU";
		D3DXMatrixScaling(&matScale, pObject->vSize.x, pObject->vSize.y, 0.f);


	}

	//오른 대각선 LU
	else if (m_tInfo.vDir.x > 0 && m_tInfo.vDir.y > 0)
	{
		wcscpy_s(pObject->StateKey, L"AttackLD");

		StateKey = L"SkillLD";

		D3DXMatrixScaling(&matScale, -pObject->vSize.x, pObject->vSize.y, 0.f);

	}
	//오른 대각선 LD

	else if (m_tInfo.vDir.x > 0 && m_tInfo.vDir.y < 0)
	{
		wcscpy_s(pObject->StateKey, L"AttackLU");

		StateKey = L"SkillLU";

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

void DAEMA_Boss::Set_GoalTarget()
{
}

HRESULT DAEMA_Boss::Shot(D3DXVECTOR3 & vPos, D3DXVECTOR3 & GoalPos)
{
	return E_NOTIMPL;
}

void DAEMA_Boss::Search_Enemy()
{
	pTerrain = dynamic_cast<CTerrain*>(CGameObject_Manager::Get_Instance()->Get_Terrain());


	if (!m_beAttacked)	Target_Finding(ID::PLAYER);

	
	else //공격받았을 경우
	{

		if (m_beAttackedTarget == ID::PLAYER)

		{
			D3DXVECTOR3 vPos = m_listGameObject[ID::PLAYER].front()->Get_Info().vPos;

			if(Target_Finding(ID::PLAYER)==Target_State::Target_In)
				//CSoundMgr::Get_Instance()->PlaySound(L"KINGYACHA_Attack1.wav", CSoundMgr::MONSTER);


			if(m_fAttack_Range < m_fDist &&  m_fDist <= TILECX*4)
			{
				
			
				Dash_Animation(&m_tInfo, vPos);

				//CSoundMgr::Get_Instance()->PlaySound(L"sura_attack.wav", CSoundMgr::MONSTER);

				m_fDashFPSTime+= CTime_Manager::Get_Instance()->Get_DeltaTime();
				if (0.15f <= m_fDashFPSTime)
				{
					m_fDashFPSTime = 0;
				pDash = new DAEMA_Dash;
				dynamic_cast<DAEMA_Dash*>(pDash)->Set_targetPos(m_tInfo.vPos, vPos);
				dynamic_cast<DAEMA_Dash*>(pDash)->Set_Life(1);
				pDash->Ready_GameObject();
				
				m_pGameObject_Manager->Add_GameObject_Manager(ID::Effect, pDash);
				}


				m_listRoute.front()->StartAStar_Manager(m_tInfo.vPos,
					vPos);
			

			}
			else if (m_fDist > TILECX * 4  && m_fDist <= TILECX * 6)
			{
			
				Skill_Animation(&m_tInfo, vPos);

				//CSoundMgr::Get_Instance()->PlaySound(L"sura_attack1.wav", CSoundMgr::MONSTER);

			
				m_fSkillFPSTime += CTime_Manager::Get_Instance()->Get_DeltaTime();
				if (0.15f <= m_fSkillFPSTime)
				{
					m_fSkillFPSTime = 0;
					pSkill = new DAEMA_Skill;
					dynamic_cast<DAEMA_Skill*>(pSkill)->Set_targetPos(m_tInfo.vPos, vPos);
					dynamic_cast<DAEMA_Skill*>(pSkill)->Set_Life(1);
					pSkill->Ready_GameObject();

					m_pGameObject_Manager->Add_GameObject_Manager(ID::Effect, pSkill);


					pSkill = new CFireBoom_Skill;
					dynamic_cast<CFireBoom_Skill*>(pSkill)->Set_targetPos(m_tInfo.vPos, vPos);
					dynamic_cast<CFireBoom_Skill*>(pSkill)->Set_Life(1);
					pSkill->Ready_GameObject();

					m_pGameObject_Manager->Add_GameObject_Manager(ID::BOSS, pSkill);


					//CFireBoom_Skill




				}
			
				m_listRoute.front()->StartAStar_Manager(m_tInfo.vPos,
					vPos);
			}
			else
			{
				
				
				m_fShieldFPSTime += CTime_Manager::Get_Instance()->Get_DeltaTime();
				if (0.2f <= m_fShieldFPSTime)
				{

				m_fShieldFPSTime = 0;
				pSkill = new DAEMA_Shield;
				dynamic_cast<DAEMA_Shield*>(pSkill)->Set_targetPos(m_tInfo.vPos, vPos);
				dynamic_cast<DAEMA_Shield*>(pSkill)->Set_Life(1);
				pSkill->Ready_GameObject();
				m_pGameObject_Manager->Add_GameObject_Manager(ID::Effect, pSkill);

				}

				m_listRoute.front()->StartAStar_Manager(m_tInfo.vPos,
					vPos);
			}



		}
		else if (m_beAttackedTarget == ID::ChoSun)
		{

			D3DXVECTOR3 vPos = m_listGameObject[ID::ChoSun].front()->Get_Info().vPos;
			Target_Finding(ID::ChoSun);



		}

	}
}

Target_State DAEMA_Boss::Target_Finding(int ObjectID)
{
	
		if (m_listGameObject[ObjectID].empty())	return Target_State::Target_Not;

		for (auto& iter = m_listGameObject[ObjectID].begin(); iter != m_listGameObject[ObjectID].end(); ++iter)
		{

			m_Dist = (*iter)->Get_Info().vPos - m_tInfo.vPos;
			m_fDist = sqrtf(m_Dist.x * m_Dist.x + m_Dist.y * +m_Dist.y);

			if (m_fAttack_Range > m_fDist)
			{
				if (m_fShortDist > m_fDist)
				{
					m_fShortDist = m_fDist;
					m_tInfo.iAttack_Target = ObjectID;
					m_tInfo.GoalIndex = pTerrain->Get_TileIndex((*iter)->Get_Info().vPos);
					m_bAttackState = true;

					Change_Animation(&m_tInfo, (*iter)->Get_Info().vPos);

					Shot(m_tInfo.vPos, (*iter)->Get_Info().vPos);



				}
				return Target_State::Target_In;
			}
			else
				return Target_State::Target_Out;


		}


	
}

HRESULT DAEMA_Boss::LoadData_Object(const wstring & wstrFilePath)
{
	return E_NOTIMPL;
}
