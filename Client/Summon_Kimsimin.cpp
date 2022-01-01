#include "stdafx.h"
#include "Summon_Kimsimin.h"
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
Summon_Kimsimin::Summon_Kimsimin() : m_tFrame({}), m_fFPSTime(0.f), m_fShotFPSTime(0), m_szFPS(L"")
,
m_fSpeed(0), pTerrain(nullptr), pPlayer(nullptr), m_pGameObject_Manager(CGameObject_Manager::Get_Instance())
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	m_fAttack_Range = float(TILECX * 1.5);
	m_fShortDist = m_fAttack_Range;



}

Summon_Kimsimin::~Summon_Kimsimin()
{
	Release_GameObject();

}
HRESULT Summon_Kimsimin::Ready_GameObject()
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

	//ó�� �ʱ� ��ǥ���� ����
	//m_listGameObject[MAP] = m_pGameObject_Manager->Get_ObjectList()[MAP];
	

	m_listGameObject[PLAYER] = m_pGameObject_Manager->Get_ObjectList()[PLAYER];
	 PlayerPos = m_listGameObject[PLAYER].front()->Get_Info().vPos;
	m_tInfo.vPos = { PlayerPos.x - TILECX * 2, PlayerPos.y - TILECY * 2,0 };


	//for (auto p : m_listGameObject[MAP])
	//{
	//	for (auto n : dynamic_cast<CMapObject*>(p)->Get_VecTile())
	//		if (n->byDrawID == 34) //ž id
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

void Summon_Kimsimin::FrameMove(float fSpeed)
{
	m_tFrame.fFrameStart += m_tFrame.fFrameEnd * CTime_Manager::Get_Instance()->Get_DeltaTime() * fSpeed;
	if (m_tFrame.fFrameEnd < m_tFrame.fFrameStart)
	{
		m_tFrame.fFrameStart = 0.f;
		m_bAttackState = false;
	}
}

void Summon_Kimsimin::Move()
{
	pTerrain = dynamic_cast<CTerrain*>(CGameObject_Manager::Get_Instance()->Get_Terrain());


	
	//list<TILE*>& BestList = CAStar_Manager::Get_Instance()->Get_BestList();

	list<TILE*>& BestList = m_listRoute.front()->Get_BestList();
		if (BestList.empty())
			return;


		//if (m_tInfo.iAttack_Target == ID::END)//����Ÿ�� ������ �÷��̾ ����
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
				//�÷��̾�� ���������� ����ٰ� �̵��� �ٽ� ��� �޾� �̵�
				//m_listRoute.emplace_back(new M_AStar_Manager(m_tInfo.vPos, vPos));
			}

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


int Summon_Kimsimin::Update_GameObject()
{

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
		//�÷��̾ ������ǥ���� ī�޶��ǹ� �̻� �̵���
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

		D3DXVECTOR3 vPos = { vMouse.x - TILECX * 2, vMouse.y - TILECY * 2,0 };


		m_listRoute.emplace_back(new M_AStar_Manager(m_tInfo.vPos, vPos));


		//CAStar_Manager::Get_Instance()->StartAStar_Manager(m_tInfo.vPos, vPos);

		

	}
	else if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
	{
	
		m_fUpdateFPSTime += CTime_Manager::Get_Instance()->Get_DeltaTime();

		if (0.1f <= m_fUpdateFPSTime) //0.035 ������ 6���� ~50fps ,4������ 6~7fps  //8�������� �������̻�����߻�
		{
			m_listGameObject[MONSTER] = m_pGameObject_Manager->Get_ObjectList()[MONSTER];

			if (!m_listGameObject[MONSTER].empty())
			{

			Search_Enemy();
			}
			m_fUpdateFPSTime = 0.f;
		}

	}
	if (0.1f <= m_fFPSTime)
	{
		//m_bAttackState = false;
		if (!m_bAttackState &&!m_listRoute.empty())
			Move();

		m_fFPSTime = 0.f;
	}



	return 0;
}

void Summon_Kimsimin::Late_Update_GameObject()
{
	

	m_fFPSTime += CTime_Manager::Get_Instance()->Get_DeltaTime();
	/*
	//0.035 ������ 6���� ~50fps ,4������ 6~7fps  //8�������� �������̻�����߻�
	0.07�� �ø��� ���ڸ� ���ݽ� ����fps 20�뿡�� 50��� �ö�
	������������� ������ ���� �ø��鼭, ������ ���ǵ尪�� �ø���
	������ ���ڸ����� ��Ÿ�鼭 ������ �̵����� ����
	*/

	

	

	//�ϱ��� ���͸���Ʈ�� hp 0�ΰ͵��� ����Ʈ���� ����
	if (!m_listGameObject[MONSTER].empty() &&m_listGameObject[MONSTER].front()->Get_Hp() <= 0)
		m_listGameObject[MONSTER].pop_front();

	if (!m_listGameObject[MONSTER].empty())
	{

	Search_Enemy();
	}
	else
	{
		m_tInfo.iAttack_Target = ID::END;
		m_bAttackState = false;
	}

	if (!m_bAttackState&&!m_listRoute.empty()&&m_listRoute.front()->Get_BestList().empty())
		StateKey = L"Stand";


	
	if (m_bAttackState)
	{
		m_tFrame.fFrameEnd = 12.f;

	}
	else
		m_tFrame.fFrameEnd = 8.f;


	FrameMove(0.5f);

}

void Summon_Kimsimin::Render_GameObject()
{
	pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo_Manager(L"Kimsimin", StateKey, (DWORD)m_tFrame.fFrameStart);
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

void Summon_Kimsimin::Release_GameObject()
{
}

void Summon_Kimsimin::Change_Animation(INFO * pObject, D3DXVECTOR3 vPos)
{
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

void Summon_Kimsimin::Set_GoalTarget()
{
}

HRESULT Summon_Kimsimin::Shot(D3DXVECTOR3 & vPos, D3DXVECTOR3 & GoalPos)
{
	return E_NOTIMPL;
}

void Summon_Kimsimin::Search_Enemy()
{
	pTerrain = dynamic_cast<CTerrain*>(CGameObject_Manager::Get_Instance()->Get_Terrain());

	//���� Ÿ���� ������!
	if (m_tInfo.iAttack_Target == END) //�÷��̾ ����ٴϴ� ����!
	{

		for (int j = 0; j < ID::END; j++)
		{

			for (auto& iter = m_listGameObject[j].begin(); iter != m_listGameObject[j].end(); ++iter)
			{
				if (j == ID::MONSTER)
				{
					m_Dist = (*iter)->Get_Info().vPos - m_tInfo.vPos;
					m_fDist = sqrtf(m_Dist.x*m_Dist.x + m_Dist.y*+m_Dist.y);

					if (m_fAttack_Range > m_fDist)
					{
						if (m_fShortDist > m_fDist)
						{
							m_fShortDist = m_fDist;
							m_tInfo.iAttack_Target = ID::MONSTER;
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
					{  //route ���� ��� ������ ���� �߻�
						m_tInfo.iAttack_Target = ID::MONSTER;
						m_listRoute.front()->StartAStar_Manager(m_tInfo.vPos,
							(*iter)->Get_Info().vPos);
						//CAStar_Manager::Get_Instance()->StartAStar_Manager(m_tInfo.vPos, (*iter)->Get_Info().vPos);

					}




				}
				//else if (j == ID::PLAYER) //���⼱ ���� �ƴ� �÷��̾� ������
				//{
				//	m_Dist = (*iter)->Get_Info().vPos - m_tInfo.vPos;
				//	m_fDist = sqrtf(m_Dist.x*m_Dist.x + m_Dist.y*+m_Dist.y);
				//
				//	if (m_fAttack_Range > m_fDist)
				//	{
				//		if (m_fShortDist > m_fDist)
				//		{
				//			m_fShortDist = m_fDist;
				//			m_tInfo.iAttack_Target = ID::PLAYER;
				//			//���� Ÿ���� ��ġ �ε����� ����!
				//			m_tInfo.GoalIndex = pTerrain->Get_TileIndex((*iter)->Get_Info().vPos);
				//			//Change_Animation(&m_tInfo, (*iter)->Get_Info().vPos);
				//
				//			//m_fShotFPSTime += CTime_Manager::Get_Instance()->Get_DeltaTime();
				//			//if (1.0f <= m_fShotFPSTime) //0.035 ������ 6���� ~50fps ,4������ 6~7fps  //8�������� �������̻�����߻�
				//			{
				//
				//				//	m_fShotFPSTime = 0.f;
				//				//Shot(m_tInfo.vPos, (*iter)->Get_Info().vPos);
				//			}
				//
				//		}
				//	}
				//	//else
				//	//{
				//	//	m_vecMonster[i]->iAttack_Target = ID::MAP;
				//	//}
				//}

				//else if (j == ID::MAP)
				//{
				//	int size = dynamic_cast<CMapObject*>(*iter)->Get_VecTile().size();
				//	for (int k = 0; k < size; k++)
				//	{
				//		if (dynamic_cast<CMapObject*>(*iter)->Get_VecTile()[k]->byDrawID == 34)
				//		{
				//			D3DXVECTOR3 vPos = dynamic_cast<CMapObject*>(*iter)->Get_VecTile()[k]->vPos;
				//
				//			m_Dist = vPos - m_tInfo.vPos;
				//			m_fDist = sqrtf(m_Dist.x*m_Dist.x + m_Dist.y*+m_Dist.y);
				//
				//			if (m_fAttack_Range > m_fDist)
				//			{
				//				if (m_fShortDist >= m_fDist)
				//				{
				//					m_fShortDist = m_fDist;
				//					m_tInfo.iAttack_Target = ID::MAP;
				//					//���� Ÿ���� ��ġ �ε����� ����!
				//					m_tInfo.GoalIndex = pTerrain->Get_TileIndex(vPos);
				//					Change_Animation(&m_tInfo, vPos);
				//
				//
				//					//m_fShotFPSTime += CTime_Manager::Get_Instance()->Get_DeltaTime();
				//					//if (1.0f <= m_fShotFPSTime) //0.035 ������ 6���� ~50fps ,4������ 6~7fps  //8�������� �������̻�����߻�
				//					{
				//
				//						//m_fShotFPSTime = 0.f;
				//						Shot(m_tInfo.vPos, (*iter)->Get_Info().vPos);
				//					}
				//					//return;
				//
				//				}
				//			}
				//			//return;
				//
				//		}
				//	}
				//	//int size= 
				//
				//
				//
				//	//else
				//	//{
				//	//	m_vecMonster[i]->iAttack_Target = ID::MAP;
				//	//}
				//
				//
				//
				//
				//}




				//else
				//	++iter;
			}


		}
	}
	else //����Ÿ���� �̹� �ִ°�� >>���� �ο�� ���� ��ġ�� or ��������
	{
		if ( m_tInfo.iAttack_Target == ID::MONSTER)
		{

			D3DXVECTOR3 vPos = m_listGameObject[ID::MONSTER].front()->Get_Info().vPos;
			m_Dist = vPos - m_tInfo.vPos;
			m_fDist = sqrtf(m_Dist.x*m_Dist.x + m_Dist.y*+m_Dist.y);
	
			if (m_fAttack_Range > m_fDist)
			{
				if (m_fShortDist >= m_fDist)
				{
					m_fShortDist = m_fDist;
					m_tInfo.iAttack_Target = ID::MONSTER;
					//���� Ÿ���� ��ġ �ε����� ����!
					m_tInfo.GoalIndex = pTerrain->Get_TileIndex(vPos);
					Change_Animation(&m_tInfo, vPos);
					m_bAttackState = true;
	
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
				m_tInfo.iAttack_Target = ID::MONSTER; //���� ������ Ÿ�꺯��
				m_listRoute.front()->StartAStar_Manager(m_tInfo.vPos,
					vPos);
				m_bAttackState = false;
				
				//M_AStar_Manager::Get_Instance()->StartAStar_Manager(m_vecMonster[i]->vPos, 
				//	vPos);
	
				//�÷��̾ ���� ��ǥ ��� �̵�����!
	
	
			}
	
	
	
	
		}
		
		//else if (m_tInfo.iAttack_Target == ID::MAP)
		//{
		//	D3DXVECTOR3 vPos;
		//	for (auto& iter = m_listGameObject[MAP].begin(); iter != m_listGameObject[MAP].end(); ++iter)
		//	{
		//
		//		int Mapsize = dynamic_cast<CMapObject*>(*iter)->Get_VecTile().size();
		//		for (int k = 0; k < Mapsize; k++)
		//		{
		//			if (dynamic_cast<CMapObject*>(*iter)->Get_VecTile()[k]->byDrawID == 34)
		//			{
		//				vPos = dynamic_cast<CMapObject*>(*iter)->Get_VecTile()[k]->vPos;
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



HRESULT Summon_Kimsimin::LoadData_Object(const wstring & wstrFilePath)
{
	return E_NOTIMPL;
}