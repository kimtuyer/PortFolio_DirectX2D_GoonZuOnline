#include "stdafx.h"
#include "GameObject_Manager.h"
//#include "GameObject.h"
#include "Collison_Manager.h"

IMPLEMENT_SINGLETON(CGameObject_Manager)

CGameObject_Manager::CGameObject_Manager()

{
}


CGameObject_Manager::~CGameObject_Manager()
{
	Release_GameObject_Manager(); 
}

HRESULT CGameObject_Manager::Add_GameObject_Manager(ID eID, CGameObject * pObject)
{
	if (eID >= END || nullptr == pObject)
		return E_FAIL; 
	m_listGameObject[eID].emplace_back(pObject); 
	return S_OK;
}

void CGameObject_Manager::Update_GameObject_Manager()
{
	for (int i = 0 ; i < END ; ++i)
	{
		for (auto& iter = m_listGameObject[i].begin(); iter != m_listGameObject[i].end();)
		{
			if ((*iter)->Get_State() != OBJ_DEAD)
			{
				int iEvent = (*iter)->Update_GameObject();

				if (OBJ_DEAD == iEvent)
				{
					if ((*iter)->Get_Info().ID == ID::Bullet)
					{
						(*iter)->Set_State();
					}
					else
					{
						
						//(*iter)->Set_State();
						Safe_Delete(*iter);
						iter = m_listGameObject[i].erase(iter);
					}
				}
				else if ((*iter)->Get_Life() == OBJ_DEAD)
				{
					Safe_Delete(*iter);
					iter = m_listGameObject[i].erase(iter);
				}

				else
					++iter;
			}
			else
				++iter;
			
			
		}
		for (auto& pGameObject : m_listGameObject[i])
		{
			if (pGameObject->Get_State() != OBJ_DEAD)
			{
			pGameObject->Late_Update_GameObject(); 
			}

			

		}
		//Collison_Manager::Collision_Rect(&m_listGameObject[ID::Mouse],

		//	&m_listGameObject[ID::MONSTER]);
		//Collison_Manager::Collision_Rect(&m_listGameObject[ID::PLAYER],
		//	&m_listGameObject[ID::MAP]);

		//Collison_Manager::Get_Instance()->
		Collison_Manager::Get_Instance()->Collision_Rect(&m_listGameObject[ID::PlayerBullet],
			&m_listGameObject[ID::MONSTER]);

		if(!m_listGameObject[ID::BossMonster].empty())
		Collison_Manager::Get_Instance()->Collision_PlayerAttackBoss(&m_listGameObject[ID::PlayerBullet],
			&m_listGameObject[ID::BossMonster]);



		//Collison_Manager::Get_Instance()->Collision_Rect(&m_listGameObject[ID::PLAYER],
		//	&m_listGameObject[ID::Bullet]);

		Collison_Manager::Get_Instance()->Collision_Melee(&m_listGameObject[ID::MONSTER],
			&m_listGameObject[ID::PLAYER]);


		//Collison_Manager::Get_Instance()->Collision_Melee(&m_listGameObject[ID::MonsterBulletEffect],
		//	&m_listGameObject[ID::Bulding]);

		if (!m_listGameObject[ID::Bulding].empty())
		Collison_Manager::Get_Instance()->Collision_BuldingAttack(&m_listGameObject[ID::Bulding],
			&m_listGameObject[ID::MONSTER]);



		if(!m_listGameObject[ID::BOSS].empty())
		Collison_Manager::Get_Instance()->Collision_Skill(&m_listGameObject[ID::BOSS],
			&m_listGameObject[ID::PLAYER]);



		if (!m_listGameObject[ID::Heal].empty())
			Collison_Manager::Get_Instance()->Collision_PlayerHeal(&m_listGameObject[ID::Heal],
				&m_listGameObject[ID::PLAYER]);




		if(!m_listGameObject[ID::MonsterBulletEffect].empty())
		Collison_Manager::Get_Instance()->Collision_MonstervsPlayer(&m_listGameObject[ID::PLAYER],
			&m_listGameObject[ID::MonsterBulletEffect]);







		Collison_Manager::Get_Instance()->Collision_Melee(&m_listGameObject[ID::ChoSun],
			&m_listGameObject[ID::MONSTER]);


		//Collison_Manager::Get_Instance()->Collision_Rect(&m_listGameObject[ID::MONSTER],
		//	&m_listGameObject[ID::PLAYER]);

		if(!m_bQuest && !m_listGameObject[ID::NPC].empty())
		if(Collison_Manager::Get_Instance()->Collision_RectQuest(m_listGameObject[ID::Mouse].front(),
			m_listGameObject[ID::NPC].front(),scenenumber))
		{
			
			return;
		}


		if (m_bQuest)
		{

		if (Collison_Manager::Get_Instance()->Collision_RectQuest2(m_listGameObject[ID::Mouse].front(),
			m_listGameObject[ID::Quest].front(), scenenumber))
		{

			return;
		}
		}

		if (!m_listGameObject[ID::MAP].empty())
		{

		if (Collison_Manager::Get_Instance()->Collision_RectEx(m_listGameObject[ID::PLAYER].front(),
			m_listGameObject[ID::MAP].front()))
		{
			return;
		}

		}
		//if(!m_listGameObject[ID::Turtleship].empty())
		//if (Collison_Manager::Get_Instance()->Collision_PlayerNPC(m_listGameObject[ID::PLAYER].front(),
		//	m_listGameObject[ID::Turtleship].front())) //플레이어,접촉시 플레이어 거북선 변신!
		//{
		//	return;
		//}

		
		
		

	}
}

void CGameObject_Manager::Render_GameObject_Manager()
{
	for (int i = 0 ; i < END ; ++i)
	{
		for (auto& pGameObject : m_listGameObject[i])
		{
			if (pGameObject->Get_State() != OBJ_DEAD)
			pGameObject->Render_GameObject(); 
		}
	}
}

void CGameObject_Manager::Release_GameObject_Manager()
{
	for (int i = 0 ; i < END ; ++i)
	{
		for (auto& pGameObject : m_listGameObject[i])
		{
			Safe_Delete(pGameObject); 
		}
		m_listGameObject[i].clear(); 
	}
}
