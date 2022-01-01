#pragma once
#include "GameObject.h"
class Collison_Manager;

class CGameObject_Manager
{
	DECLARE_SINGLETON(CGameObject_Manager)
public:
	//enum ID {TERRAIN, MAP,PLAYER,ChoSun, MONSTER, BOSS, UI, END};
private:
	CGameObject_Manager();
	~CGameObject_Manager();
public:
	CGameObject* Get_Terrain() { return m_listGameObject[ID::TERRAIN].front(); }
	CGameObject* Get_Mouse() { return m_listGameObject[ID::Mouse].front(); }
	CGameObject* Get_Player_Skill1() { return m_listGameObject[ID::Effect].front(); }
	bool Is_Player_Skill1() { return m_listGameObject[ID::Effect].empty(); }





	HRESULT Add_GameObject_Manager(ID eID, CGameObject* pObject); 
	void Update_GameObject_Manager(); 
	void Render_GameObject_Manager(); 
	void Release_GameObject_Manager(); 

	CGameObject* Get_Player() { return m_listGameObject[PLAYER].front(); }
	CGameObject* Get_PlayerBullet() { return m_listGameObject[ID::Bullet].front(); }

	list<CGameObject*> Get_MonsterList() { return m_listGameObject[ID::MONSTER]; }

	list<CGameObject*> Get_ChoSun() { return m_listGameObject[ChoSun]; }
	list<CGameObject*> Get_NPC() { return m_listGameObject[NPC]; }
	list<CGameObject*> Get_Leewonik() { return m_listGameObject[Turtleship]; }


	CGameObject* Get_Boss() { return m_listGameObject[BossMonster].front(); }

//	list<CGameObject*> Get_Boss() { return m_listGameObject[ID::BOSS]; }



	CGameObject* Get_PlayerHP() { return m_listGameObject[ID::PlayerHP].front(); }



	list<CGameObject*> Get_UI() { return m_listGameObject[ID::UI]; }

	list<CGameObject*> Get_listMouse() { return m_listGameObject[Mouse]; }

	list<CGameObject*> Get_listTop() { return m_listGameObject[Bulding]; }

	list<CGameObject*> Get_listTopHP() { return m_listGameObject[tophp]; }



	list<CGameObject*>* Get_ObjectList() { return m_listGameObject; }

	
	void Release_Quest() {
		
		for (auto& p : m_listGameObject[ID::Quest])
			if (p->Get_Info().ID == ID::UI)
				Safe_Delete(p);
		
		m_listGameObject[Quest].pop_back(); }


	//퀘스트 생성 유무 체크
	void Set_QuestOFF() { m_bQuest = false; }

	void Set_QuestOn() { m_bQuest = true; }
	bool Get_Quest() { return m_bQuest; }

	int scenenumber = 0;
private:
	list<CGameObject*> m_listGameObject[END];
	Collison_Manager* m_Collison_Manager;

	bool m_bQuest = false;

};

