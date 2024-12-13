#include "stdafx.h"
#include "West_Boss.h"
#include "Terrain.h"
#include "CCamera.h"
#include "M_AStar_Manager.h"
#include "GameObject_Manager.h"
#include "Player.h"
#include "CMapObject.h"
#include "West_Bullet.h"
West_Boss::West_Boss()
	: m_tFrame({}),m_fFPSTime(0), m_fShotFPSTime(0), m_szFPS(L""),
	m_fSpeed(0), pTerrain(nullptr), m_pGameObject_Manager(CGameObject_Manager::Get_Instance())
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	m_fAttack_Range = float(TILECX * 5);
	m_fShortDist = m_fAttack_Range;

}

West_Boss::~West_Boss()
{
	Release_GameObject();

}

void West_Boss::FrameMove(float fSpeed)
{
	m_tFrame.fFrameStart += m_tFrame.fFrameEnd * CTime_Manager::Get_Instance()->Get_DeltaTime() * fSpeed;
	if (m_tFrame.fFrameEnd < m_tFrame.fFrameStart)
		m_tFrame.fFrameStart = 0.f;
}

HRESULT West_Boss::Ready_GameObject()
{
	m_tInfo.vDir = { 1.f, 1.f, 0.f };
	m_tInfo.vSize = { 1.f, 1.f, 0.f };
	m_tFrame = { 0.f, 7.f };
	m_fSpeed = 200.f;
	StateKey = L"Stand";

	D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);

	//INFO *pObject = nullptr;
	//LoadTileData_MapObject(L"../Data/Start_ObjectData2.dat");
	//LoadData_Object(L"../Data/NamHanCastle_UnitData4.dat");

	//처음 초기 목표지점 설정
	m_listGameObject[MAP] = m_pGameObject_Manager->Get_ObjectList()[MAP];
	m_listGameObject[PLAYER] = m_pGameObject_Manager->Get_ObjectList()[PLAYER];

	D3DXVECTOR3 tPos; //탑의 위치
	for (auto p : m_listGameObject[MAP])
	{
		for (auto n : static_cast<CMapObject*>(p)->Get_VecTile())
			if (n->byDrawID == 34 || n->byDrawID == 26) //탑 id
				tPos = n->vPos;
	}

	//DWORD dwSize = m_vecMonster.size();
	//for (size_t i = 0; i < dwSize; ++i)
	{
		m_listRoute.emplace_back(new M_AStar_Manager(m_tInfo.vPos, tPos));
		m_tInfo.iAttack_Target = ID::END;
	}

	pBullet = new West_Bullet;
	m_pGameObject_Manager->Add_GameObject_Manager(ID::Bullet, pBullet);

	//Kwanghwa_ObjectData

	return S_OK;
}

void West_Boss::Move()
{
	
	pTerrain = static_cast<CTerrain*>(CGameObject_Manager::Get_Instance()->Get_Terrain());

	DWORD dwSize = m_vecMonster.size();

	//for (size_t i = 0; i < dwSize; ++i)
	{
		list<TILE*>& BestList = m_listRoute.front()->Get_BestList();
		if (BestList.empty())
			return;


		if (m_tInfo.iAttack_Target == ID::END)//공격타겟이 초기목표 탑일때만 이동!
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
		else //
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
				//switch (i % 8)
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


int West_Boss::Update_GameObject()
{
	m_fUpdateFPSTime += CTime_Manager::Get_Instance()->Get_DeltaTime();
	//if (m_listBullet.empty())




	if (0.1f <= m_fUpdateFPSTime) //0.035 설정시 6마리 ~50fps ,4마리는 6~7fps  //8마리부턴 움직임이상현상발생
	{

		m_fUpdateFPSTime = 0.f;
		Search_Enemy();
	}
	float eTime = CTime_Manager::Get_Instance()->Get_DeltaTime();
	return 0;
}

void West_Boss::Late_Update_GameObject()
{
	FrameMove(0.5f);
	m_fFPSTime += CTime_Manager::Get_Instance()->Get_DeltaTime();
	if (0.1f <= m_fFPSTime)
	{
		Move();

		m_fFPSTime = 0.f;
	}
}

void West_Boss::Render_GameObject()
{//D3DXMATRIX matScale, matTrans, matWorld;
	//DWORD dwSize = m_vecMonster.size();

	//for (size_t i = 0; i < dwSize; ++i)
	{
		//const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo_Manager(L"Terrain", L"Tile", m_vecTile[i]->byDrawID);
		pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo_Manager(L"West_Boss", m_tInfo.StateKey, (DWORD)m_tFrame.fFrameStart);
		if (nullptr == pTexInfo)
			return;
		float fCenterX = float(pTexInfo->tImageInfo.Width >> 1);
		float fCenterY = float(pTexInfo->tImageInfo.Height >> 1);

		D3DXVECTOR3 tPos = m_tInfo.vPos - m_tInfo.vSize;// * m_tPivot;

		tPos -= CCamera::Get_Instance()->GetPos();



		m_ColliderInfo[0] = { tPos.x - 75 ,tPos.y - 50 };
		m_ColliderInfo[1] = { m_ColliderInfo[0].x + 150,tPos.y - 50 };
		m_ColliderInfo[2] = { m_ColliderInfo[1].x,m_ColliderInfo[1].y + 120 };
		m_ColliderInfo[3] = { m_ColliderInfo[0].x,m_ColliderInfo[2].y };
		m_ColliderInfo[4] = { tPos.x - 75 ,tPos.y - 50 };


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
		{
			swprintf_s(m_szFPS, L"HP : %d", m_HP);
			//m_iFPS = 0;
			//m_fFPSTime = 0.f;
		}
		//SetWindowText(g_hWND, m_szFPS); 
		D3DXMATRIX matTrans1;
		D3DXMatrixTranslation(&matTrans1, m_ColliderInfo[0].x, m_ColliderInfo[0].y, 0.f);

		CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matTrans1);
		CGraphic_Device::Get_Instance()->Get_Font()->DrawTextW(CGraphic_Device::Get_Instance()->Get_Sprite(), m_szFPS, lstrlen(m_szFPS), nullptr, 0, D3DCOLOR_ARGB(255, 0, 0, 0));
		//CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);

	}
}

void West_Boss::Release_GameObject()
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

void West_Boss::Change_Animation(INFO * pObject, D3DXVECTOR3 vPos)
{//현재 라이플병이 위치한 인덱스값
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

void West_Boss::Set_GoalTarget()
{
	//{
	//	m_listGameObject[MAP] = m_pGameObject_Manager->Get_ObjectList()[MAP];
	//	D3DXVECTOR3 tPos; //탑의 위치
	//	for (auto p : m_listGameObject[MAP])
	//	{
	//		for (auto n : static_cast<CMapObject*>(p)->Get_VecTile())
	//			if (n->byDrawID == 34) //탑 id
	//				tPos = n->vPos;
	//	}
	//
	//	DWORD dwSize = m_vecMonster.size();
	//	for (size_t i = 0; i < dwSize; ++i)
	//	{
	//
	//		M_AStar_Manager::Get_Instance()->StartAStar_Manager(m_vecMonster[i]->vPos, tPos);
	//	}
	//}
}

void West_Boss::Search_Enemy()
{
	pTerrain = static_cast<CTerrain*>(CGameObject_Manager::Get_Instance()->Get_Terrain());

	DWORD dwSize = m_vecMonster.size();

	for (size_t i = 0; i < dwSize; ++i)
	{
		//공격 타깃이 없을때!
		if (m_vecMonster[i]->iAttack_Target == END)
		{


			for (int j = 0; j < ID::END; j++)
			{

				for (auto& iter = m_listGameObject[j].begin(); iter != m_listGameObject[j].end(); ++iter)
				{
					if (j == ID::PLAYER)
					{
						m_Dist = (*iter)->Get_Info().vPos - m_vecMonster[i]->vPos;
						m_fDist = sqrtf(m_Dist.x*m_Dist.x + m_Dist.y*+m_Dist.y);

						if (m_fAttack_Range > m_fDist)
						{
							if (m_fShortDist > m_fDist)
							{
								m_fShortDist = m_fDist;
								m_vecMonster[i]->iAttack_Target = ID::PLAYER;
								//공격 타겟의 위치 인덱스값 저장!
								m_vecMonster[i]->GoalIndex = pTerrain->Get_TileIndex((*iter)->Get_Info().vPos);
								Change_Animation(m_vecMonster[i], (*iter)->Get_Info().vPos);

							}
						}
						//else
						//{
						//	m_vecMonster[i]->iAttack_Target = ID::MAP;
						//}




					}
					else if (j == ID::ChoSun)
					{
						m_Dist = (*iter)->Get_Info().vPos - m_vecMonster[i]->vPos;
						m_fDist = sqrtf(m_Dist.x*m_Dist.x + m_Dist.y*+m_Dist.y);

						if (m_fAttack_Range > m_fDist)
						{
							if (m_fShortDist > m_fDist)
							{
								m_fShortDist = m_fDist;
								m_vecMonster[i]->iAttack_Target = ID::ChoSun;
								//공격 타겟의 위치 인덱스값 저장!
								m_vecMonster[i]->GoalIndex = pTerrain->Get_TileIndex((*iter)->Get_Info().vPos);
								Change_Animation(m_vecMonster[i], (*iter)->Get_Info().vPos);



							}
						}
						//else
						//{
						//	m_vecMonster[i]->iAttack_Target = ID::MAP;
						//}
					}

					else if (j == ID::MAP)
					{
						int size = static_cast<CMapObject*>(*iter)->Get_VecTile().size();
						for (int k = 0; k < size; k++)
						{
							if (static_cast<CMapObject*>(*iter)->Get_VecTile()[k]->byDrawID == 34)
							{
								D3DXVECTOR3 vPos = static_cast<CMapObject*>(*iter)->Get_VecTile()[k]->vPos;

								m_Dist = vPos - m_vecMonster[i]->vPos;
								m_fDist = sqrtf(m_Dist.x*m_Dist.x + m_Dist.y*+m_Dist.y);

								if (m_fAttack_Range > m_fDist)
								{
									if (m_fShortDist >= m_fDist)
									{
										m_fShortDist = m_fDist;
										m_vecMonster[i]->iAttack_Target = ID::MAP;
										//공격 타겟의 위치 인덱스값 저장!
										m_vecMonster[i]->GoalIndex = pTerrain->Get_TileIndex(vPos);
										Change_Animation(m_vecMonster[i], vPos);
										//return;

									}
								}
								//return;

							}
						}
						//int size= 



						//else
						//{
						//	m_vecMonster[i]->iAttack_Target = ID::MAP;
						//}




					}




					//else
					//	++iter;
				}


			}
		}
		else //공격타겟이 이미 있는경우
		{
			if (m_vecMonster[i]->iAttack_Target == ID::PLAYER)
			{
				D3DXVECTOR3 vPos = m_listGameObject[ID::PLAYER].front()->Get_Info().vPos;
				m_Dist = vPos - m_vecMonster[i]->vPos;
				m_fDist = sqrtf(m_Dist.x*m_Dist.x + m_Dist.y*+m_Dist.y);

				if (m_fAttack_Range > m_fDist)
				{
					if (m_fShortDist > m_fDist)
					{
						m_fShortDist = m_fDist;
						m_vecMonster[i]->iAttack_Target = ID::PLAYER;
						//공격 타겟의 위치 인덱스값 저장!
						m_vecMonster[i]->GoalIndex = pTerrain->Get_TileIndex(vPos);
						Change_Animation(m_vecMonster[i], vPos);

					}
				}
				else
				{
					//공격 타겟이 플레이어or 소환영웅내지 조선군은 현재공격타겟이 죽을대까지 움직임변경x,여기선 플레이어
					//추적만 신경쓰면 될듯!
					m_vecMonster[i]->iAttack_Target = ID::END; //새로 추적할 타깃변경
					m_listRoute[i]->StartAStar_Manager(m_vecMonster[i]->vPos,
						vPos);
					

					//플레이어를 추적 목표 잡고 이동시작!


				}




			}
			else if (m_vecMonster[i]->iAttack_Target == ID::ChoSun)
			{
				//m_Dist = (*iter)->Get_Info().vPos - m_vecMonster[i]->vPos;
				//m_fDist = sqrtf(m_Dist.x*m_Dist.x + m_Dist.y*+m_Dist.y);
				//
				//if (m_fAttack_Range > m_fDist)
				//{
				//	if (m_fShortDist > m_fDist)
				//	{
				//		m_fShortDist = m_fDist;
				//		m_vecMonster[i]->iAttack_Target = ID::ChoSun;
				//		//공격 타겟의 위치 인덱스값 저장!
				//		m_vecMonster[i]->GoalIndex = pTerrain->Get_TileIndex((*iter)->Get_Info().vPos);
				//		Change_Animation(m_vecMonster[i], (*iter)->Get_Info().vPos);
				//
				//
				//
				//	}
				//}
				////else
				//{
				//	m_vecMonster[i]->iAttack_Target = ID::MAP;
				//}
			}
			else if (m_vecMonster[i]->iAttack_Target == ID::MAP)
			{




			}




		}

		//공격타겟 있을경우 해당타깃이 공격범위 벗어났을 경우 체크!


	}
}

HRESULT West_Boss::Shot(D3DXVECTOR3 & vPos, D3DXVECTOR3 & GoalPos)
{
	return E_NOTIMPL;
}

HRESULT West_Boss::LoadData_Object(const wstring & wstrFilePath)
{
	HANDLE hFile = CreateFile(wstrFilePath.c_str(), GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (INVALID_HANDLE_VALUE == hFile)
		return E_FAIL;

	DWORD dwbyte = 0;

	INFO* pObject = nullptr;
	//TILE* pTile = nullptr; 
	while (true)
	{
		//pTile = new TILE; 
		//안에서 
		pObject = new INFO;

		ReadFile(hFile, pObject, sizeof(INFO), &dwbyte, nullptr);
		if (0 == dwbyte)
		{
			Safe_Delete(pObject);
			break;
		}
		wcscpy_s(pObject->StateKey, L"Stand");
		if (pObject->byDrawID == 9)
			m_vecMonster.emplace_back(pObject);
		//m_vecTile.emplace_back(pTile); 
	}
	CloseHandle(hFile);
	return S_OK;
}
