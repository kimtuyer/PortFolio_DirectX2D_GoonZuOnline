#include "stdafx.h"
#include "West_Rifleman.h"
#include "Terrain.h"
#include "CCamera.h"
#include "M_AStar_Manager.h"
#include "GameObject_Manager.h"
#include "Player.h"
#include "West_Bullet.h"
#include "CMapObject.h"
#include "Frame_Manager.h"
#include "Time_Manager.h"
#include "BulletEffect.h"

West_Rifleman::West_Rifleman() : m_tFrame({}),  m_fFPSTime(0.f), m_fShotFPSTime(0), m_szFPS(L"")
,
m_fSpeed(0),pTerrain(nullptr), pBullet(nullptr),m_pGameObject_Manager(CGameObject_Manager::Get_Instance())
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	m_fAttack_Range = float(TILECX * 5);
	m_fShortDist = m_fAttack_Range;
	

	
}

West_Rifleman::~West_Rifleman()
{
	Release_GameObject();

}

HRESULT West_Rifleman::Ready_GameObject()
{
	m_tInfo.vDir = { 1.f, 1.f, 0.f };
	m_tInfo.vSize = { 1.f, 1.f, 0.f };
	m_tFrame = { 0.f, 7.f };
	m_fSpeed = 600.f;
	StateKey = L"Stand";

	D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);

	//INFO *pObject = nullptr;
	//LoadTileData_MapObject(L"../Data/Start_ObjectData2.dat");
	//LoadData_Object(L"../Data/NamHanCastle_UnitData4.dat");

	//처음 초기 목표지점 설정
	m_listGameObject[Bulding] = m_pGameObject_Manager->Get_listTop();
	m_listGameObject[PLAYER] = m_pGameObject_Manager->Get_ObjectList()[PLAYER];
	m_listGameObject[ChoSun] = m_pGameObject_Manager->Get_ObjectList()[ChoSun];

	D3DXVECTOR3 tPos; //탑의 위치
	for (auto p : m_listGameObject[Bulding])
	{
		for (auto n : static_cast<CMapObject*>(p)->Get_VecTile())
			if (n->byDrawID == 34 ) //탑 id
				tPos = n->vPos;
	}

	//DWORD dwSize = m_vecMonster.size();
	//for (size_t i = 0; i < dwSize; ++i)
	{
		//m_pM_AStar = new M_AStar_Manager(m_vecMonster[i]->vPos, tPos);

		m_listRoute.emplace_back(new M_AStar_Manager(m_tInfo.vPos, tPos));
		//M_AStar_Manager::Get_Instance()->StartAStar_Manager(m_vecMonster[i]->vPos, tPos);
		m_tInfo.iAttack_Target = ID::Bulding;
	}

	pBullet = new West_Bullet;
	m_pGameObject_Manager->Add_GameObject_Manager(ID::Bullet, pBullet);



	//Kwanghwa_ObjectData

	return S_OK;
}



void West_Rifleman::FrameMove(float fSpeed)
{
	m_tFrame.fFrameStart += m_tFrame.fFrameEnd * CTime_Manager::Get_Instance()->Get_DeltaTime() * fSpeed;
	if (m_tFrame.fFrameEnd < m_tFrame.fFrameStart)
	{
		m_tFrame.fFrameStart = 0.f;
		m_bAttackState = false;

	}
}

int West_Rifleman::Update_GameObject()
{
	//Get_DeltaTime
	//if (!m_listBullet.empty() &&static_cast<West_Bullet*>(m_listBullet.front())->Get_State()== OBJ_DEAD)
	//{
	//	list<CGameObject*>::iterator iter = m_listBullet.begin();
	//	//for(; iter!= m_listBullet.end(); ++iter)
	//		
	//
	//	m_listBullet.pop_front();
	//}


	//m_listGameObject[MAP] = m_pGameObject_Manager->Get_ObjectList()[MAP];
	//D3DXVECTOR3 tPos; //탑의 위치
	//for (auto p : m_listGameObject[MAP])
	//{
	//	for (auto n : static_cast<CMapObject*>(p)->Get_VecTile())
	//		if (n->byDrawID == 34) //탑 id
	//			tPos = n->vPos;
	//}
	//
	//DWORD dwSize = m_vecMonster.size();
	//for (size_t i = 0; i < dwSize; ++i)
	//{
	//
	//	M_AStar_Manager::Get_Instance()->StartAStar_Manager(m_vecMonster[i]->vPos, tPos);
	//}


	//공격타겟이 죽었을경우 다시 타겟설정 초기 목표로 바꾸기
	//float bTime = CTime_Manager::Get_Instance()->Get_DeltaTime();
	 m_fUpdateFPSTime += CTime_Manager::Get_Instance()->Get_DeltaTime();
	//if (m_listBullet.empty())

	


	if (0.1f <= m_fUpdateFPSTime) //0.035 설정시 6마리 ~50fps ,4마리는 6~7fps  //8마리부턴 움직임이상현상발생
	{

		 m_fUpdateFPSTime = 0.f;
			Search_Enemy();
		}
	float eTime = CTime_Manager::Get_Instance()->Get_DeltaTime();

	m_fFPSTime += CTime_Manager::Get_Instance()->Get_DeltaTime();


	if (0.1f <= m_fFPSTime)
	{
		if (!m_bAttackState)
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
	
	return 0;

}

void West_Rifleman::Search_Enemy()
{
	pTerrain = static_cast<CTerrain*>(CGameObject_Manager::Get_Instance()->Get_Terrain());

	if (!m_beAttacked)

	{
		//공격 타깃이 없을때!
		if (m_tInfo.iAttack_Target == Bulding)
		{

			for (int j = 0; j < ID::END; j++)
			{

				for (auto& iter = m_listGameObject[j].begin(); iter != m_listGameObject[j].end(); ++iter)
				{
					if (j == ID::PLAYER)
					{
						m_Dist = (*iter)->Get_Info().vPos - m_tInfo.vPos;
						m_fDist = sqrtf(m_Dist.x*m_Dist.x + m_Dist.y*+m_Dist.y);

						if (m_fAttack_Range > m_fDist)
						{
							if (m_fShortDist > m_fDist)
							{
								m_fShortDist = m_fDist;
								m_tInfo.iAttack_Target = ID::PLAYER;
								//공격 타겟의 위치 인덱스값 저장!
								m_tInfo.GoalIndex = pTerrain->Get_TileIndex((*iter)->Get_Info().vPos);
								Change_Animation(&m_tInfo, (*iter)->Get_Info().vPos);
								
								//CSoundMgr::Get_Instance()->PlaySound(L"Bullet_Gun_Fire1.wav", CSoundMgr::MONSTER);

								m_bAttackState = true;
								//m_fShotFPSTime += CTime_Manager::Get_Instance()->Get_DeltaTime();
								//if (4.0f <= m_fShotFPSTime) //0.035 설정시 6마리 ~50fps ,4마리는 6~7fps  //8마리부턴 움직임이상현상발생
								{

									//m_fShotFPSTime = 0.f;
									Shot(m_tInfo.vPos, (*iter)->Get_Info().vPos);
								}


							}
						}
						else
						{
							//공격 타겟의 위치 인덱스값 저장!
							//m_vecMonster[i]->iAttack_Target = ID::MAP;
						}




					}
					else if (j == ID::ChoSun)
					{
						m_Dist = (*iter)->Get_Info().vPos - m_tInfo.vPos;
						m_fDist = sqrtf(m_Dist.x*m_Dist.x + m_Dist.y*+m_Dist.y);

						if (m_fAttack_Range > m_fDist)
						{
							if (m_fShortDist > m_fDist)
							{
								m_fShortDist = m_fDist;
								m_tInfo.iAttack_Target = ID::ChoSun;
								//공격 타겟의 위치 인덱스값 저장!
								m_tInfo.GoalIndex = pTerrain->Get_TileIndex((*iter)->Get_Info().vPos);
								Change_Animation(&m_tInfo, (*iter)->Get_Info().vPos);
								//CSoundMgr::Get_Instance()->PlaySound(L"Bullet_Gun_Fire1.wav", CSoundMgr::MONSTER);

								//m_fShotFPSTime += CTime_Manager::Get_Instance()->Get_DeltaTime();
								//if (1.0f <= m_fShotFPSTime) //0.035 설정시 6마리 ~50fps ,4마리는 6~7fps  //8마리부턴 움직임이상현상발생
								{

								//	m_fShotFPSTime = 0.f;
									Shot(m_tInfo.vPos, (*iter)->Get_Info().vPos);
								}

							}
						}
						//else
						//{
						//	m_vecMonster[i]->iAttack_Target = ID::MAP;
						//}
					}

					else if (j == ID::Bulding)
					{
						int size = static_cast<CMapObject*>(*iter)->Get_VecTile().size();
						for (int k = 0; k < size; k++)
						{
							if (static_cast<CMapObject*>(*iter)->Get_VecTile()[k]->byDrawID == 34)
							{
								D3DXVECTOR3 vPos = static_cast<CMapObject*>(*iter)->Get_VecTile()[k]->vPos;

								m_Dist = vPos - m_tInfo.vPos;
								m_fDist = sqrtf(m_Dist.x*m_Dist.x + m_Dist.y*+m_Dist.y);

								if (m_fAttack_Range > m_fDist)
								{
									if (m_fShortDist >= m_fDist)
									{
										m_fShortDist = m_fDist;
										m_tInfo.iAttack_Target = ID::Bulding;
										//공격 타겟의 위치 인덱스값 저장!
										m_tInfo.GoalIndex = pTerrain->Get_TileIndex(vPos);
										Change_Animation(&m_tInfo, vPos);
										//CSoundMgr::Get_Instance()->PlaySound(L"Bullet_Gun_Fire1.wav", CSoundMgr::MONSTER);


										//m_fShotFPSTime += CTime_Manager::Get_Instance()->Get_DeltaTime();
										//if (1.0f <= m_fShotFPSTime) //0.035 설정시 6마리 ~50fps ,4마리는 6~7fps  //8마리부턴 움직임이상현상발생
										{

											//m_fShotFPSTime = 0.f;
											Shot(m_tInfo.vPos, (*iter)->Get_Info().vPos);
										}
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
			if (m_tInfo.iAttack_Target == ID::PLAYER)
			{
				D3DXVECTOR3 vPos = m_listGameObject[ID::PLAYER].front()->Get_Info().vPos;
				m_Dist = vPos - m_tInfo.vPos;
				m_fDist = sqrtf(m_Dist.x*m_Dist.x + m_Dist.y*+m_Dist.y);

				if (m_fAttack_Range > m_fDist)
				{
					if (m_fShortDist >= m_fDist)
					{
						m_fShortDist = m_fDist;
						m_tInfo.iAttack_Target = ID::PLAYER;
						//공격 타겟의 위치 인덱스값 저장!
						m_tInfo.GoalIndex = pTerrain->Get_TileIndex(vPos);
						Change_Animation(&m_tInfo, vPos);
						//CSoundMgr::Get_Instance()->PlaySound(L"Bullet_Gun_Fire1.wav", CSoundMgr::MONSTER);

						//m_fShotFPSTime += CTime_Manager::Get_Instance()->Get_DeltaTime();
						//if (0.5f <= m_fShotFPSTime) //0.035 설정시 6마리 ~50fps ,4마리는 6~7fps  //8마리부턴 움직임이상현상발생
						{

							//m_fShotFPSTime = 0.f;
							Shot(m_tInfo.vPos, vPos);
						}

					}
				}
				else
				{
					//공격 타겟이 플레이어or 소환영웅내지 조선군은 현재공격타겟이 죽을대까지 움직임변경x,여기선 플레이어
					//추적만 신경쓰면 될듯!
					m_bAttackState = false;

					//m_tInfo.iAttack_Target = ID::PLAYER; //새로 추적할 타깃변경
					m_listRoute.front()->StartAStar_Manager(m_tInfo.vPos,
						vPos);
					//M_AStar_Manager::Get_Instance()->StartAStar_Manager(m_vecMonster[i]->vPos, 
					//	vPos);

					//플레이어를 추적 목표 잡고 이동시작!


				}




			}
			else if (m_tInfo.iAttack_Target == ID::ChoSun)
			{
				D3DXVECTOR3 vPos = m_listGameObject[ID::ChoSun].front()->Get_Info().vPos;
				m_Dist = vPos - m_tInfo.vPos;
				m_fDist = sqrtf(m_Dist.x*m_Dist.x + m_Dist.y*+m_Dist.y);


				if (m_fAttack_Range > m_fDist)
				{
					if (m_fShortDist > m_fDist)
					{
						m_fShortDist = m_fDist;
						m_tInfo.iAttack_Target = ID::ChoSun;
						//공격 타겟의 위치 인덱스값 저장!
						m_tInfo.GoalIndex = pTerrain->Get_TileIndex(vPos);
						m_bAttackState = true;
						Change_Animation(&m_tInfo, vPos);



					}
				}
				else
				{
					m_bAttackState = false;
					//m_tInfo.iAttack_Target = ID::PLAYER; //새로 추적할 타깃변경
					m_listRoute.front()->StartAStar_Manager(m_tInfo.vPos,
						vPos);
				}
			}
			//else if (m_tInfo.iAttack_Target == ID::MAP)
			//{
			//	D3DXVECTOR3 vPos;
			//	for (auto& iter = m_listGameObject[MAP].begin(); iter != m_listGameObject[MAP].end(); ++iter)
			//	{
			//
			//		int Mapsize = static_cast<CMapObject*>(*iter)->Get_VecTile().size();
			//		for (int k = 0; k < Mapsize; k++)
			//		{
			//			if (static_cast<CMapObject*>(*iter)->Get_VecTile()[k]->byDrawID == 34)
			//			{
			//				vPos = static_cast<CMapObject*>(*iter)->Get_VecTile()[k]->vPos;
			//				break;
			//			}
			//
			//		}
			//
			//	}
			//	//m_fShotFPSTime += CTime_Manager::Get_Instance()->Get_DeltaTime();
			//	//if (1.0f <= m_fShotFPSTime) //0.035 설정시 6마리 ~50fps ,4마리는 6~7fps  //8마리부턴 움직임이상현상발생
			//	{
			//
			//		//m_fShotFPSTime = 0.f;
			//		Shot(m_tInfo.vPos, vPos);
			//	}
			//
			//
			//
			//
			//
			//
			//
			//}
			//
			////공격타겟 있을경우 해당타깃이 공격범위 벗어났을 경우 체크!

		}
	}
	else
	{

	if (m_beAttackedTarget == ID::PLAYER)

	{
		D3DXVECTOR3 vPos = m_listGameObject[ID::PLAYER].front()->Get_Info().vPos;
		m_Dist = vPos - m_tInfo.vPos;
		m_fDist = sqrtf(m_Dist.x*m_Dist.x + m_Dist.y*+m_Dist.y);

		if (m_fAttack_Range > m_fDist)
		{
			if (m_fShortDist >= m_fDist)
			{
				m_fShortDist = m_fDist;
				m_tInfo.iAttack_Target = ID::PLAYER;
				//공격 타겟의 위치 인덱스값 저장!
				m_tInfo.GoalIndex = pTerrain->Get_TileIndex(vPos);
				m_bAttackState = true;
				Change_Animation(&m_tInfo, vPos);
				//CSoundMgr::Get_Instance()->PlaySound(L"Bullet_Gun_Fire1.wav", CSoundMgr::MONSTER);

				//m_fShotFPSTime += CTime_Manager::Get_Instance()->Get_DeltaTime();
				//if (0.5f <= m_fShotFPSTime) //0.035 설정시 6마리 ~50fps ,4마리는 6~7fps  //8마리부턴 움직임이상현상발생
				{

					//m_fShotFPSTime = 0.f;
					Shot(m_tInfo.vPos, vPos);
				}

			}
		}
		else
		{
			//공격 타겟이 플레이어or 소환영웅내지 조선군은 현재공격타겟이 죽을대까지 움직임변경x,여기선 플레이어
			//추적만 신경쓰면 될듯!
			m_bAttackState = false;
			m_tInfo.iAttack_Target = ID::PLAYER; //새로 추적할 타깃변경
			m_listRoute.front()->StartAStar_Manager(m_tInfo.vPos,
				vPos);
			//M_AStar_Manager::Get_Instance()->StartAStar_Manager(m_vecMonster[i]->vPos, 
			//	vPos);

			//플레이어를 추적 목표 잡고 이동시작!


		}
	}
	else if (m_beAttackedTarget == ID::ChoSun)
	{

		D3DXVECTOR3 vPos = m_listGameObject[ID::ChoSun].front()->Get_Info().vPos;
		m_Dist = vPos - m_tInfo.vPos;
		m_fDist = sqrtf(m_Dist.x*m_Dist.x + m_Dist.y*+m_Dist.y);

		if (m_fAttack_Range > m_fDist)
		{
			if (m_fShortDist >= m_fDist)
			{
				m_fShortDist = m_fDist;
				m_tInfo.iAttack_Target = ID::ChoSun;
				//공격 타겟의 위치 인덱스값 저장!
				m_tInfo.GoalIndex = pTerrain->Get_TileIndex(vPos);
				m_bAttackState = true;
				Change_Animation(&m_tInfo, vPos);
				//CSoundMgr::Get_Instance()->PlaySound(L"Bullet_Gun_Fire1.wav", CSoundMgr::MONSTER);

				//m_fShotFPSTime += CTime_Manager::Get_Instance()->Get_DeltaTime();
				//if (0.5f <= m_fShotFPSTime) //0.035 설정시 6마리 ~50fps ,4마리는 6~7fps  //8마리부턴 움직임이상현상발생
				{

					//m_fShotFPSTime = 0.f;
					Shot(m_tInfo.vPos, vPos);
				}

			}
		}
		else
		{
			//공격 타겟이 플레이어or 소환영웅내지 조선군은 현재공격타겟이 죽을대까지 움직임변경x,여기선 플레이어
			//추적만 신경쓰면 될듯!
			m_bAttackState = false;
			m_tInfo.iAttack_Target = ID::ChoSun; //새로 추적할 타깃변경
			m_listRoute.front()->StartAStar_Manager(m_tInfo.vPos,
				vPos);
			//M_AStar_Manager::Get_Instance()->StartAStar_Manager(m_vecMonster[i]->vPos, 
			//	vPos);

			//플레이어를 추적 목표 잡고 이동시작!


		}


	}

	 }




	 
}

void West_Rifleman::Late_Update_GameObject()
{
	//FrameMove(0.5f);
	FrameMove(0.5f);

	
	

	//CFrame_Manager::Frame_Lock();

}

void West_Rifleman::Move()
{
	/*초기 탑 위치 인덱스 목표로 이동

		서로 인덱스값 아니까 위치값 받아와 거리 구해 거리값으로
		총병은 가로or세로 타일기준 3개 거리를 사정거리로 잡아서
		타겟 인덱스와의 거리가 사정거리이내에 있는지 검사
		>> 있다면 해당 목표 위치한 방향으로 애니메 변경하면서 이동!

		우선 내 사정거리 인덱스 리스트를 뽑아와 맞는 인덱스있는지 검사!
	>

		있을경우 물체가 위치한 8방향중 해당방향에 맞는 공격 모션으로 변경!
		이때 공격대상 Target 잡아준후 데미지값 전달해야함 /
		공격받은 Target 역시 자신이 공격받은 상태 On이 되야함!
	*/
	
	/*
	공격타겟이 정해졌을경우 이동을 멈추고  자신이 위치한 타일 인덱스에 다른 오브젝트가 있는지 검사!
	있다면 해당 타일중심 8방향 아무데나 이동!

	*/




	//list<TILE*>& BestList = M_AStar_Manager::Get_Instance()->Get_BestList();
	//if (BestList.empty())
	//	return;
	pTerrain = static_cast<CTerrain*>(CGameObject_Manager::Get_Instance()->Get_Terrain());


	{

		list<TILE*>& BestList=m_listRoute.front()->Get_BestList();
		if (BestList.empty())
		return;
		

		if (m_tInfo.iAttack_Target == ID::END )//공격타겟이 초기목표 탑일때만 이동!
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


void West_Rifleman::Change_Animation(INFO* pObject, D3DXVECTOR3 vPos)
{
	//현재 라이플병이 위치한 인덱스값
	int index = pTerrain->Get_TileIndex(pObject->vPos);
	m_tInfo.vDir = vPos - pObject->vPos;
	//m_tInfo.vDir2 = BestList.back()->vPos - m_tInfo.vPos;

	if (abs((pObject->GoalIndex - index)) % (TILEX * 2) == 0 && m_tInfo.vDir.y > 0)
	{
		wcscpy_s(pObject->StateKey, L"Attack");

		StateKey = L"Attack"; //Down

		D3DXMatrixScaling(&matScale,pObject->vSize.x, pObject->vSize.y, 0.f);

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

HRESULT West_Rifleman::Shot(D3DXVECTOR3 &vPos,D3DXVECTOR3 &GoalPos)
{

	



	m_fShotFPSTime += CTime_Manager::Get_Instance()->Get_DeltaTime();
	////if (m_listBullet.empty())
	//
	//{
	//	
	//
		if (0.5f <= m_fShotFPSTime) //0.035 설정시 6마리 ~50fps ,4마리는 6~7fps  //8마리부턴 움직임이상현상발생
		{
	//
			m_fShotFPSTime = 0.f;
	//
			pBulletEffect = new BulletEffect;
			pBulletEffect->Ready_GameObject();
			static_cast<BulletEffect*>(pBulletEffect)->Set_target(GoalPos);
			static_cast<BulletEffect*>(pBulletEffect)->Set_Life(1);
			CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(ID::MonsterBulletEffect, pBulletEffect);
	//		{
	//			if (pBullet)
	//			{
	//
	//			pBullet->Set_StateON();
	//			static_cast<West_Bullet*>(pBullet)->Set_targetPos(vPos, GoalPos);
	//			}
	//			//static_cast<West_Bullet*>(pBullet)->Set
	//
	//
	//
	//			//m_listBullet.emplace_back(new West_Bullet);
	//			//m_pGameObject_Manager->Add_GameObject_Manager(ID::Bullet, m_listBullet.front());
	//			////pBullet= m_pGameObject_Manager->Get_PlayerBullet();
	//			//
	//			//static_cast<West_Bullet*>(m_listBullet.front())->Set_targetPos(vPos, GoalPos);
	//
	//
	//
	//			//pBullet->Release_GameObject();
	//		}
	//		//else
	//		{
	//			//D3DXVECTOR3 pos=pBullet->Get_Info().vPos;
	//			//
	//			//
	//			//D3DXVECTOR3 m_Dist = pos - GoalPos;
	//			//m_fDist = sqrtf(m_Dist.x*m_Dist.x + m_Dist.y*+m_Dist.y);
	//			//if (m_fDist <= 3)
	//			//{
	//			//
	//			//}
	//		}
	//
		}
	//}
	////else
	//{
	//	//m_listBullet.pop_front();
	//}
	//
	//
	
	return S_OK;
}


void West_Rifleman::Render_GameObject()
{
	//D3DXMATRIX matScale, matTrans, matWorld;

	{
		//const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo_Manager(L"Terrain", L"Tile", m_vecTile[i]->byDrawID);
		 pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo_Manager(L"West_Rifleman", m_tInfo.StateKey, (DWORD)m_tFrame.fFrameStart);
		if (nullptr == pTexInfo)
			return;
		float fCenterX = float(pTexInfo->tImageInfo.Width >> 1);
		float fCenterY = float(pTexInfo->tImageInfo.Height >> 1);

		D3DXVECTOR3 tPos = m_tInfo.vPos - m_tInfo.vSize;// * m_tPivot;

		tPos -= CCamera::Get_Instance()->GetPos();



		m_ColliderInfo[0] = { tPos.x - 50 ,tPos.y - 50 };
		m_ColliderInfo[1] = { m_ColliderInfo[0].x + 100,tPos.y - 50 };
		m_ColliderInfo[2] = { m_ColliderInfo[1].x,m_ColliderInfo[1].y + 100 };
		m_ColliderInfo[3] = { m_ColliderInfo[0].x,m_ColliderInfo[2].y };
		m_ColliderInfo[4] = { m_ColliderInfo[0].x ,tPos.y - 50 };


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
			swprintf_s(m_szFPS, L"HP : %d", m_HP);
			//m_iFPS = 0;
			//m_fFPSTime = 0.f;
		}
		//SetWindowText(g_hWND, m_szFPS); 
		D3DXMATRIX matTrans1;
		D3DXMatrixTranslation(&matTrans1, m_ColliderInfo[0].x, m_ColliderInfo[0].y,  0.f);

		CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matTrans1);
		CGraphic_Device::Get_Instance()->Get_Font()->DrawTextW(CGraphic_Device::Get_Instance()->Get_Sprite(), m_szFPS, lstrlen(m_szFPS), nullptr, 0, D3DCOLOR_ARGB(255, 0, 0, 0));
		//CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);



	}
}


void West_Rifleman::Set_GoalTarget()
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
void West_Rifleman::Release_GameObject()
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
HRESULT West_Rifleman::LoadData_Object(const wstring & wstrFilePath)
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
		if(pObject->byDrawID==8)
			m_vecMonster.emplace_back(pObject);
		//m_vecTile.emplace_back(pTile); 
	}
	CloseHandle(hFile);
	return S_OK;
}
