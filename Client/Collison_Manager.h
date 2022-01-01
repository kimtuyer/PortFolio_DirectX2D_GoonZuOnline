#pragma once

class CGameObject;

class CGameObject_Manager;
class Collison_Manager
{
DECLARE_SINGLETON(Collison_Manager)
private:
	Collison_Manager();
	~Collison_Manager();
public:
	 bool Collision_RectEx(CGameObject* plistDest, CGameObject* plistSrc);
	 bool Collision_RectQuest(CGameObject* plistDest, CGameObject* plistSrc, int scene);
	 bool Collision_RectQuest2(CGameObject* plistDest, CGameObject* plistSrc,int scene);




	 void Collision_Rect(list<CGameObject*>* plistDest, list<CGameObject*>* plistSrc); //화살 vs 몬스터

	 void Collision_PlayerAttackBoss(list<CGameObject*>* plistDest, list<CGameObject*>* plistSrc); 






	//몬스터가 top 공격 충돌판정!
	 void Collision_BuldingAttack(list<CGameObject*>* plistDest, list<CGameObject*>* plistSrc);

	 void Collision_Melee(list<CGameObject*>* plistDest, list<CGameObject*>* plistSrc);



	 void Collision_Skill(list<CGameObject*>* plistDest, list<CGameObject*>* plistSrc); //보스가 플레이어에게 스킬 공격

	 void Collision_PlayerHeal(list<CGameObject*>* plistDest, list<CGameObject*>* plistSrc);// 장금이 플레이어에게 힐 



	// void Collision_MonstervsPlayer(list<CGameObject*>* plistDest, list<CGameObject*>* plistSrc);

	 void Collision_MonstervsPlayer(list<CGameObject*>* plistDest, list<CGameObject*>* plistSrc);


	 bool Collision_PlayerNPC(CGameObject* plistDest, CGameObject* plistSrc);




	 void Collision_Sphere(list<CGameObject*>* plistDest, list<CGameObject*>* plistSrc);
	 bool Collision_Line(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3* pos2, D3DXVECTOR3 size2, int Monster_id);
private:
	 bool Check_Sphere(const INFO* pDstInfo, const INFO* pSrcInfo);
	 bool Check_Rect(const INFO* pDstInfo, const INFO* pSrcInfo, float* pOutX, float* pOutY);
private:
	static int m_collisionCount;
	int m_iAttackCount = 0;
	int QuestOrder = 0;

	static float m_fMeleeFPSTime;

	static float m_fBulletFPSTime;
	static float m_fUpdateFPSTime;

	static float m_fMonBulletFPSTime;


	D3DXVECTOR2 m_ColliderInfo[5];

	CGameObject* pCriticalEffect;
	CGameObject* pFirearrowEffect;
	CGameObject* pDmgNumber;
	CGameObject* pCDmgNumber;
	CGameObject* pObject;

	list<CGameObject*> m_listGameObject[END];

	CGameObject_Manager* m_pGameObject_Manager;


};

