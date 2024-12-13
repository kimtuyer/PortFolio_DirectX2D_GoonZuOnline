#include "stdafx.h"
#include "Japan_infantry.h"
#include "Terrain.h"
#include "CCamera.h"
#include "M_AStar_Manager.h"
#include "GameObject_Manager.h"
#include "Player.h"
#include "West_Bullet.h"
#include "CMapObject.h"
#include "Frame_Manager.h"
#include "Time_Manager.h"

Japan_infantry::Japan_infantry() : m_tFrame({}), m_fFPSTime(0.f), m_fShotFPSTime(0), m_szFPS(L"")
,
m_fSpeed(0), pTerrain(nullptr), pBullet(nullptr), m_pGameObject_Manager(CGameObject_Manager::Get_Instance())
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	m_fAttack_Range = float(TILECX * 2);
	m_fShortDist = m_fAttack_Range;



}

Japan_infantry::~Japan_infantry()
{
	Release_GameObject();

}

HRESULT Japan_infantry::Ready_GameObject()
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

	//ó�� �ʱ� ��ǥ���� ����
	m_listGameObject[Bulding] = m_pGameObject_Manager->Get_listTop();
	m_listGameObject[PLAYER] = m_pGameObject_Manager->Get_ObjectList()[PLAYER];
	m_listGameObject[ChoSun] = m_pGameObject_Manager->Get_ChoSun();


	D3DXVECTOR3 tPos; //ž�� ��ġ
	for (auto p : m_listGameObject[ID::Bulding])
	{
		for (auto n : static_cast<CMapObject*>(p)->Get_VecTile())
			if (n->byDrawID == 34 ) //ž id
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



void Japan_infantry::FrameMove(float fSpeed)
{
	m_tFrame.fFrameStart += m_tFrame.fFrameEnd * CTime_Manager::Get_Instance()->Get_DeltaTime() * fSpeed;
	if (m_tFrame.fFrameEnd < m_tFrame.fFrameStart)
	{
		m_tFrame.fFrameStart = 0.f;
		m_bAttackState = false;

	}
}

void Japan_infantry::Move()
{
	/*�ʱ� ž ��ġ �ε��� ��ǥ�� �̵�

		���� �ε����� �ƴϱ� ��ġ�� �޾ƿ� �Ÿ� ���� �Ÿ�������
		�Ѻ��� ����or���� Ÿ�ϱ��� 3�� �Ÿ��� �����Ÿ��� ��Ƽ�
		Ÿ�� �ε������� �Ÿ��� �����Ÿ��̳��� �ִ��� �˻�
		>> �ִٸ� �ش� ��ǥ ��ġ�� �������� �ִϸ� �����ϸ鼭 �̵�!

		�켱 �� �����Ÿ� �ε��� ����Ʈ�� �̾ƿ� �´� �ε����ִ��� �˻�!
	>

		������� ��ü�� ��ġ�� 8������ �ش���⿡ �´� ���� ������� ����!
		�̶� ���ݴ�� Target ������� �������� �����ؾ��� /
		���ݹ��� Target ���� �ڽ��� ���ݹ��� ���� On�� �Ǿ���!
	*/

	/*
	����Ÿ���� ����������� �̵��� ���߰�  �ڽ��� ��ġ�� Ÿ�� �ε����� �ٸ� ������Ʈ�� �ִ��� �˻�!
	�ִٸ� �ش� Ÿ���߽� 8���� �ƹ����� �̵�!

	*/




	//list<TILE*>& BestList = M_AStar_Manager::Get_Instance()->Get_BestList();
	//if (BestList.empty())
	//	return;
	pTerrain = static_cast<CTerrain*>(CGameObject_Manager::Get_Instance()->Get_Terrain());


	{

		list<TILE*>& BestList = m_listRoute.front()->Get_BestList();
		if (BestList.empty())
			return;


		//if (m_tInfo.iAttack_Target == ID::END)//����Ÿ���� �ʱ��ǥ ž�϶��� �̵�!
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
			//���� �밢�� LU
			else if (m_tInfo.vDir.x < 0 && m_tInfo.vDir.y >0)
			{
				wcscpy_s(m_tInfo.StateKey, L"WalkLD");

				StateKey = L"WalkLD";
				D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);

				//				D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);

			}
			//���� �밢�� LD

			else if (m_tInfo.vDir.x < 0 && m_tInfo.vDir.y < 0)
			{
				wcscpy_s(m_tInfo.StateKey, L"WalkLU");

				StateKey = L"WalkLU";
				//				D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
				D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);



			}

			//���� �밢�� LU
			else if (m_tInfo.vDir.x > 0 && m_tInfo.vDir.y > 0)
			{
				wcscpy_s(m_tInfo.StateKey, L"WalkLD");

				StateKey = L"WalkLD";

				//D3DXMatrixScaling(&matScale, -m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
				D3DXMatrixScaling(&matScale, -m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);


			}
			//���� �밢�� LD

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
		//else if (m_vecMonster[i]->iAttack_Target == ID::PLAYER)//����Ÿ���� �÷��̾�� ���� ������
		//
		//{/ }
		//
		//else //
		{

			if (m_tInfo.iAttack_Target == MAP)

			{
				//m_vecMonster[i]->iAttack_Target = ID::MONSTER; //�����ؼ� ���ݸ�� ���ϱ� ���ؼ�
				//���� ��ǥ �������
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


int Japan_infantry::Update_GameObject()
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
	//D3DXVECTOR3 tPos; //ž�� ��ġ
	//for (auto p : m_listGameObject[MAP])
	//{
	//	for (auto n : static_cast<CMapObject*>(p)->Get_VecTile())
	//		if (n->byDrawID == 34) //ž id
	//			tPos = n->vPos;
	//}
	//
	//DWORD dwSize = m_vecMonster.size();
	//for (size_t i = 0; i < dwSize; ++i)
	//{
	//
	//	M_AStar_Manager::Get_Instance()->StartAStar_Manager(m_vecMonster[i]->vPos, tPos);
	//}


	//����Ÿ���� �׾������ �ٽ� Ÿ�ټ��� �ʱ� ��ǥ�� �ٲٱ�
	//float bTime = CTime_Manager::Get_Instance()->Get_DeltaTime();
	m_fUpdateFPSTime += CTime_Manager::Get_Instance()->Get_DeltaTime();
	//if (m_listBullet.empty())




	if (0.1f <= m_fUpdateFPSTime) //0.035 ������ 6���� ~50fps ,4������ 6~7fps  //8�������� �������̻�����߻�
	{

		m_fUpdateFPSTime = 0.f;
		Search_Enemy();
	}
	//float eTime = CTime_Manager::Get_Instance()->Get_DeltaTime();

	m_fFPSTime += CTime_Manager::Get_Instance()->Get_DeltaTime();

	if (0.1f <= m_fFPSTime)
	{
		if (!m_bAttackState)
			Move();

		m_fFPSTime = 0.f;
	}



	/*
���� ��ġ�� Ÿ�� �ε����� ������ �����Ÿ���
�� �ִ��� �˻�

�ش� ���������� �����ϴ� ������Ʈ ��������
������Ʈ Ÿ���ε����� �����ؾ���
�ϴ� ���⼱ Archer,Cannon,�÷��̾�,ž �� �ش�

�ε��� �� ������, �� �ڽ���ġ���� ex
------------------------------------------
�Ѻ��� ���߽� 8���� 3ĭ �̳����� �����Ÿ�,
��ǥ�� �� 3ĭ�̳� �ε��� �����ȿ� �ִ��� �˻�
or
�ʱ� ž ��ġ �ε��� ��ǥ�� �̵�

���� �ε����� �ƴϱ� ��ġ�� �޾ƿ� �Ÿ� ���� �Ÿ�������
�Ѻ��� ����or���� Ÿ�ϱ��� 3�� �Ÿ��� �����Ÿ��� ��Ƽ�
Ÿ�� �ε������� �Ÿ��� �����Ÿ��̳��� �ִ��� �˻�
>>�ִٸ� �ش� ��ǥ ��ġ�� �������� �ִϸ� �����ϸ鼭 �̵�!

�켱 �� �����Ÿ� �ε��� ����Ʈ�� �̾ƿ� �´� �ε����ִ��� �˻�!
>






������� ��ü�� ��ġ�� 8������ �ش���⿡ �´� ���� ������� ����!
�̶� ���ݴ�� Target ������� �������� �����ؾ���/
���ݹ��� Target ���� �ڽ��� ���ݹ��� ���� On�� �Ǿ���!






*/
//m_pGameObject_Manager=




//Move();
	return 0;

}

void Japan_infantry::Search_Enemy()
{
	pTerrain = static_cast<CTerrain*>(CGameObject_Manager::Get_Instance()->Get_Terrain());


	if (!m_beAttacked)
	{
	
		//���� Ÿ���� ������!
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
								//���� Ÿ���� ��ġ �ε����� ����!
								m_tInfo.GoalIndex = pTerrain->Get_TileIndex((*iter)->Get_Info().vPos);
								m_bAttackState = true;
								Change_Animation(&m_tInfo, (*iter)->Get_Info().vPos);

								//m_fShotFPSTime += CTime_Manager::Get_Instance()->Get_DeltaTime();
								//if (4.0f <= m_fShotFPSTime) //0.035 ������ 6���� ~50fps ,4������ 6~7fps  //8�������� �������̻�����߻�
								{

									//m_fShotFPSTime = 0.f;
									Shot(m_tInfo.vPos, (*iter)->Get_Info().vPos);
								}


							}
						}
						else
						{
							//m_tInfo.iAttack_Target = ID::PLAYER;
							//���� Ÿ���� ��ġ �ε����� ����!
							//m_tInfo.GoalIndex = pTerrain->Get_TileIndex((*iter)->Get_Info().vPos);
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
								//���� Ÿ���� ��ġ �ε����� ����!
								m_tInfo.GoalIndex = pTerrain->Get_TileIndex((*iter)->Get_Info().vPos);
								Change_Animation(&m_tInfo, (*iter)->Get_Info().vPos);

								//m_fShotFPSTime += CTime_Manager::Get_Instance()->Get_DeltaTime();
								//if (1.0f <= m_fShotFPSTime) //0.035 ������ 6���� ~50fps ,4������ 6~7fps  //8�������� �������̻�����߻�
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
										//���� Ÿ���� ��ġ �ε����� ����!
										m_tInfo.GoalIndex = pTerrain->Get_TileIndex(vPos);
										Change_Animation(&m_tInfo, vPos);
					
					
										//m_fShotFPSTime += CTime_Manager::Get_Instance()->Get_DeltaTime();
										//if (1.0f <= m_fShotFPSTime) //0.035 ������ 6���� ~50fps ,4������ 6~7fps  //8�������� �������̻�����߻�
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
		else //����Ÿ���� �̹� �ִ°��
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
						//���� Ÿ���� ��ġ �ε����� ����!
						m_tInfo.GoalIndex = pTerrain->Get_TileIndex(vPos);
						m_bAttackState = true;
						Change_Animation(&m_tInfo, vPos);
						//m_fShotFPSTime += CTime_Manager::Get_Instance()->Get_DeltaTime();
						//if (0.5f <= m_fShotFPSTime) //0.035 ������ 6���� ~50fps ,4������ 6~7fps  //8�������� �������̻�����߻�
						{

							//m_fShotFPSTime = 0.f;
							Shot(m_tInfo.vPos, vPos);
						}

					}
				}
				else
				{
					//���� Ÿ���� �÷��̾�or ��ȯ�������� �������� �������Ÿ���� ��������� �����Ӻ���x,���⼱ �÷��̾�
					//������ �Ű澲�� �ɵ�!
					m_bAttackState = false;
					//m_tInfo.iAttack_Target = ID::PLAYER; //���� ������ Ÿ�꺯��
					m_listRoute.front()->StartAStar_Manager(m_tInfo.vPos,
						vPos);
					//M_AStar_Manager::Get_Instance()->StartAStar_Manager(m_vecMonster[i]->vPos, 
					//	vPos);

					//�÷��̾ ���� ��ǥ ��� �̵�����!


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
						//���� Ÿ���� ��ġ �ε����� ����!
						m_tInfo.GoalIndex = pTerrain->Get_TileIndex(vPos);
						m_bAttackState = true;
						Change_Animation(&m_tInfo, vPos);
				
				
				
					}
				}
				else
				{
					m_bAttackState = false;
					//m_tInfo.iAttack_Target = ID::PLAYER; //���� ������ Ÿ�꺯��
					m_listRoute.front()->StartAStar_Manager(m_tInfo.vPos,
						vPos);
				}
			}
			//else if (m_tInfo.iAttack_Target == ID::Bulding)
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
			//	//if (1.0f <= m_fShotFPSTime) //0.035 ������ 6���� ~50fps ,4������ 6~7fps  //8�������� �������̻�����߻�
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

			//����Ÿ�� ������� �ش�Ÿ���� ���ݹ��� ����� ��� üũ!

		}
	}
	else //���ݹ޾��� ���
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
				//���� Ÿ���� ��ġ �ε����� ����!
				m_tInfo.GoalIndex = pTerrain->Get_TileIndex(vPos);
				m_bAttackState = true;
				Change_Animation(&m_tInfo, vPos);
				//m_fShotFPSTime += CTime_Manager::Get_Instance()->Get_DeltaTime();
				//if (0.5f <= m_fShotFPSTime) //0.035 ������ 6���� ~50fps ,4������ 6~7fps  //8�������� �������̻�����߻�
				{

					//m_fShotFPSTime = 0.f;
					Shot(m_tInfo.vPos, vPos);
				}

			}
		}
		else
		{
			//���� Ÿ���� �÷��̾�or ��ȯ�������� �������� �������Ÿ���� ��������� �����Ӻ���x,���⼱ �÷��̾�
			//������ �Ű澲�� �ɵ�!
			m_bAttackState = false;
			m_tInfo.iAttack_Target = ID::PLAYER; //���� ������ Ÿ�꺯��
			m_listRoute.front()->StartAStar_Manager(m_tInfo.vPos,
				vPos);
			//M_AStar_Manager::Get_Instance()->StartAStar_Manager(m_vecMonster[i]->vPos, 
			//	vPos);

			//�÷��̾ ���� ��ǥ ��� �̵�����!


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
				//���� Ÿ���� ��ġ �ε����� ����!
				m_tInfo.GoalIndex = pTerrain->Get_TileIndex(vPos);
				m_bAttackState = true;
				Change_Animation(&m_tInfo, vPos);
				//m_fShotFPSTime += CTime_Manager::Get_Instance()->Get_DeltaTime();
				//if (0.5f <= m_fShotFPSTime) //0.035 ������ 6���� ~50fps ,4������ 6~7fps  //8�������� �������̻�����߻�
				{

					//m_fShotFPSTime = 0.f;
					Shot(m_tInfo.vPos, vPos);
				}

			}
		}
		else
		{
			//���� Ÿ���� �÷��̾�or ��ȯ�������� �������� �������Ÿ���� ��������� �����Ӻ���x,���⼱ �÷��̾�
			//������ �Ű澲�� �ɵ�!
			m_bAttackState = false;
			m_tInfo.iAttack_Target = ID::ChoSun; //���� ������ Ÿ�꺯��
			m_listRoute.front()->StartAStar_Manager(m_tInfo.vPos,
				vPos);
			//M_AStar_Manager::Get_Instance()->StartAStar_Manager(m_vecMonster[i]->vPos, 
			//	vPos);

			//�÷��̾ ���� ��ǥ ��� �̵�����!


		}


	}

	 }

}


void Japan_infantry::Late_Update_GameObject()
{
	//FrameMove(0.5f);
	FrameMove(0.5f);

	/*
	//0.035 ������ 6���� ~50fps ,4������ 6~7fps  //8�������� �������̻�����߻�
	0.07�� �ø��� ���ڸ� ���ݽ� ����fps 20�뿡�� 50��� �ö�
	������������� ������ ���� �ø��鼭, ������ ���ǵ尪�� �ø���
	������ ���ڸ����� ��Ÿ�鼭 ������ �̵����� ����
	*/

	


	//CFrame_Manager::Frame_Lock();

}

void Japan_infantry::Render_GameObject()
{
	//D3DXMATRIX matScale, matTrans, matWorld;

	{
		//const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo_Manager(L"Terrain", L"Tile", m_vecTile[i]->byDrawID);
		pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo_Manager(L"Japan_infantry", m_tInfo.StateKey, (DWORD)m_tFrame.fFrameStart);
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
		D3DXMatrixTranslation(&matTrans1, m_ColliderInfo[0].x, m_ColliderInfo[0].y, 0.f);

		CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matTrans1);
		CGraphic_Device::Get_Instance()->Get_Font()->DrawTextW(CGraphic_Device::Get_Instance()->Get_Sprite(), m_szFPS, lstrlen(m_szFPS), nullptr, 0, D3DCOLOR_ARGB(255, 0, 0, 0));
		//CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);



	}
}

void Japan_infantry::Release_GameObject()
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

HRESULT Japan_infantry::Shot(D3DXVECTOR3 &vPos, D3DXVECTOR3 &GoalPos)
{




	//m_fShotFPSTime += CTime_Manager::Get_Instance()->Get_DeltaTime();
	////if (m_listBullet.empty())
	//
	//{
	//	
	//
	//	if (1.f <= m_fShotFPSTime) //0.035 ������ 6���� ~50fps ,4������ 6~7fps  //8�������� �������̻�����߻�
	//	{
	//
	//		m_fShotFPSTime = 0.f;
	//
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
	//	}
	//}
	////else
	//{
	//	//m_listBullet.pop_front();
	//}
	//
	//

	return S_OK;
}

void Japan_infantry::Change_Animation(INFO* pObject, D3DXVECTOR3 vPos)
{
	m_bAttackState = true;

	//���� �����ú��� ��ġ�� �ε�����
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
	//���� �밢�� LU
	else if (m_tInfo.vDir.x < 0 && m_tInfo.vDir.y >0)
	{
		wcscpy_s(pObject->StateKey, L"AttackLD");

		StateKey = L"AttackLD";

		D3DXMatrixScaling(&matScale, pObject->vSize.x, pObject->vSize.y, 0.f);

	}
	//���� �밢�� LD

	else if (m_tInfo.vDir.x < 0 && m_tInfo.vDir.y < 0)
	{
		wcscpy_s(pObject->StateKey, L"AttackLU");

		StateKey = L"AttackLU";
		D3DXMatrixScaling(&matScale, pObject->vSize.x, pObject->vSize.y, 0.f);


	}

	//���� �밢�� LU
	else if (m_tInfo.vDir.x > 0 && m_tInfo.vDir.y > 0)
	{
		wcscpy_s(pObject->StateKey, L"AttackLD");

		StateKey = L"AttackLD";

		D3DXMatrixScaling(&matScale, -pObject->vSize.x, pObject->vSize.y, 0.f);

	}
	//���� �밢�� LD

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

void Japan_infantry::Set_GoalTarget()
{
	//{
	//	m_listGameObject[MAP] = m_pGameObject_Manager->Get_ObjectList()[MAP];
	//	D3DXVECTOR3 tPos; //ž�� ��ġ
	//	for (auto p : m_listGameObject[MAP])
	//	{
	//		for (auto n : static_cast<CMapObject*>(p)->Get_VecTile())
	//			if (n->byDrawID == 34) //ž id
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


HRESULT Japan_infantry::LoadData_Object(const wstring & wstrFilePath)
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
		//�ȿ��� 
		pObject = new INFO;

		ReadFile(hFile, pObject, sizeof(INFO), &dwbyte, nullptr);
		if (0 == dwbyte)
		{
			Safe_Delete(pObject);
			break;
		}
		wcscpy_s(pObject->StateKey, L"Stand");
		if (pObject->byDrawID == 8)
			m_vecMonster.emplace_back(pObject);
		//m_vecTile.emplace_back(pTile); 
	}
	CloseHandle(hFile);
	return S_OK;
}
