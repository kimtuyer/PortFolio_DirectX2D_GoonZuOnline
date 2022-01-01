#include "stdafx.h"
#include "Collison_Manager.h"
#include "GameObject.h"
#include "CMapObject.h"
//#include "CRectangle.h"
#include"CriticalEffect.h"
#include "FireArrowSkill.h"
#include"DmgNumber.h"
#include "CTDmgNumber.h"
#include "CdmgNumber2.h"
#include "TopHP.h"
#include "CBossHPbar.h"
#include "DAEMA_Boss.h"
#include "CQuest.h"
#include "Player.h"
#include "Scene_Manager.h"
#include "GameObject_Manager.h"
#include "CHPBar_Player.h"


int Collison_Manager::m_collisionCount = 0;

float Collison_Manager::m_fMonBulletFPSTime = 0;
float Collison_Manager::m_fBulletFPSTime = 0;
float Collison_Manager::m_fMeleeFPSTime = 0;
float Collison_Manager::m_fUpdateFPSTime = 0.f;

IMPLEMENT_SINGLETON(Collison_Manager)

Collison_Manager::Collison_Manager(): m_pGameObject_Manager(CGameObject_Manager::Get_Instance())
{



}

Collison_Manager::~Collison_Manager()
{
}

void Collison_Manager::Collision_Rect(list<CGameObject*>* plistDest, list<CGameObject*>* plistSrc)
{



	RECT rc = {};
	RECT rPlayer = {};
	RECT rMonster = {};
	list<CGameObject*>::iterator iter = plistSrc->begin();

	for (auto& pDstObject : *plistDest)
	{
		int player_Collider = pDstObject->Get_Current_Collider();
		rPlayer = { LONG((pDstObject)->Get_Collider()[0].x), LONG((pDstObject)->Get_Collider()[0].y),
			 LONG((pDstObject)->Get_Collider()[1].x), LONG((pDstObject)->Get_Collider()[2].y) };

		for (auto& pSrcObject : *plistSrc)
		{


			rMonster = { LONG((pSrcObject)->Get_Collider()[0].x), LONG((pSrcObject)->Get_Collider()[0].y),
			 LONG((pSrcObject)->Get_Collider()[1].x), LONG((pSrcObject)->Get_Collider()[2].y) };



			if (IntersectRect(&rc, &rPlayer, &rMonster)) {
				m_fBulletFPSTime += CTime_Manager::Get_Instance()->Get_DeltaTime();

				if (1.f <= m_fBulletFPSTime) //0.035 설정시 6마리 ~50fps ,4마리는 6~7fps  //8마리부턴 움직임이상현상발생
				{
					m_fBulletFPSTime = 0.f;
					//충돌시 플레이어 HP 감소 처리


					++m_collisionCount;

					if (pDstObject->Get_AttackState())
					{
						//++m_iAttackCount;
						
						//if (m_iAttackCount == 1)
						{
							

							pSrcObject->Set_HP(pDstObject->Get_Damage());
							//몬스터 공격받음 전달.
							pSrcObject->Set_beAttacked();
							pSrcObject->Set_beAttackTarget(ID::PLAYER);



							if (pSrcObject->Get_Hp() < 0)
							{
								//이때 확실히 리스트에서 없애야 크리티컬 이펙트가 쌓이지않음
							   // pSrcObject->Set_State();
								pDstObject->Set_AttackStateOFF();
								pSrcObject->Set_Life();

							}
							pDstObject->Set_AttackCount(0);


							//powerbullet화살 맞을시 이펙트 효과 생성!

							if (pDstObject->Get_Info().ID == ID::PlayerPowerBullet)
							{

								pCriticalEffect = new CriticalEffect;
								pCriticalEffect->Ready_GameObject();

								dynamic_cast<CriticalEffect*>(pCriticalEffect)->Set_target(pSrcObject->Get_Info().vPos);
								dynamic_cast<CriticalEffect*>(pCriticalEffect)->Set_Life(1);
								CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(ID::criticalEffect, pCriticalEffect);


								pCDmgNumber = new CTDmgNumber;
								pCDmgNumber->Ready_GameObject();

								dynamic_cast<CTDmgNumber*>(pCDmgNumber)->Set_target(pSrcObject->Get_Info().vPos);
								dynamic_cast<CTDmgNumber*>(pCDmgNumber)->Set_Life(1);
								CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(ID::NUMBER, pCDmgNumber);




							}
							else if (pDstObject->Get_bulletid() == Bullet_ID::default
								|| pDstObject->Get_Info().ID == ID::ChoSun
								)
							{

								CSoundMgr::Get_Instance()->PlaySound(L"Bullet_Arrow_Hit1.wav", CSoundMgr::PLAYER);

								pDmgNumber = new DmgNumber;
								pDmgNumber->Ready_GameObject();

								dynamic_cast<DmgNumber*>(pDmgNumber)->Set_target(pSrcObject->Get_Info().vPos);
								dynamic_cast<DmgNumber*>(pDmgNumber)->Set_Life(1);
								CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(ID::NUMBER, pDmgNumber);


							}
							else if (pDstObject->Get_bulletid() == Bullet_ID::fire)
							{
								CSoundMgr::Get_Instance()->PlaySound(L"magic_fireball_hit2.wav", CSoundMgr::PLAYER);


								pCriticalEffect = new CriticalEffect;
								pCriticalEffect->Ready_GameObject();

								dynamic_cast<CriticalEffect*>(pCriticalEffect)->Set_target(pSrcObject->Get_Info().vPos);
								dynamic_cast<CriticalEffect*>(pCriticalEffect)->Set_Life(1);
								CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(ID::criticalEffect, pCriticalEffect);


								pFirearrowEffect = new FireArrowSkill;
								dynamic_cast<FireArrowSkill*>(pFirearrowEffect)->Set_target(pSrcObject->Get_Info().vPos);
								int dir = pDstObject->Get_Dir();
								dynamic_cast<FireArrowSkill*>(pFirearrowEffect)->Set_Dir(dir);
								dynamic_cast<FireArrowSkill*>(pFirearrowEffect)->Set_Life(1);
								pFirearrowEffect->Ready_GameObject();

								CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(ID::criticalEffect, pFirearrowEffect);


								pCDmgNumber = new CTDmgNumber;
								pCDmgNumber->Ready_GameObject();

								dynamic_cast<CTDmgNumber*>(pCDmgNumber)->Set_target(pSrcObject->Get_Info().vPos);
								dynamic_cast<CTDmgNumber*>(pCDmgNumber)->Set_Life(1);
								CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(ID::NUMBER, pCDmgNumber);






							}




						}
						// m_collisionCount = 0;

					}
					
				}
				//pSrcObject->Set_State();
				//++m_collisionCount;



			//dynamic_cast<CPlayer*>(pDstObject)->Set_Life();//플레이어 체력감소





			}
			else
			{

			}


		}





	}
}

void Collison_Manager::Collision_PlayerAttackBoss(list<CGameObject*>* plistDest, list<CGameObject*>* plistSrc)
{

	if (m_pGameObject_Manager->Get_ObjectList()[tophp].empty())
		m_listGameObject[tophp] = m_pGameObject_Manager->Get_ObjectList()[tophp];	//CGameObject* pObject;

	RECT rc = {};
	RECT rPlayer = {};
	RECT rMonster = {};
	list<CGameObject*>::iterator iter = plistSrc->begin();

	for (auto& pDstObject : *plistDest)
	{
		int player_Collider = pDstObject->Get_Current_Collider();
		rPlayer = { LONG((pDstObject)->Get_Collider()[0].x), LONG((pDstObject)->Get_Collider()[0].y),
			 LONG((pDstObject)->Get_Collider()[1].x), LONG((pDstObject)->Get_Collider()[2].y) };

		for (auto& pSrcObject : *plistSrc)
		{


			rMonster = { LONG((pSrcObject)->Get_Collider()[0].x), LONG((pSrcObject)->Get_Collider()[0].y),
			 LONG((pSrcObject)->Get_Collider()[1].x), LONG((pSrcObject)->Get_Collider()[2].y) };

			//if (pSrcObject->Get_Id() == 3)


			//if (m_listBullet.empty())


			if (IntersectRect(&rc, &rPlayer, &rMonster)) {
				m_fBulletFPSTime += CTime_Manager::Get_Instance()->Get_DeltaTime();

				if (1.f <= m_fBulletFPSTime) //0.035 설정시 6마리 ~50fps ,4마리는 6~7fps  //8마리부턴 움직임이상현상발생
				{
					m_fBulletFPSTime = 0.f;
					//충돌시 플레이어 HP 감소 처리


					++m_collisionCount;

					if (pDstObject->Get_AttackState())
					{
						//++m_iAttackCount;

						//if (m_iAttackCount == 1)
						{
							
							dynamic_cast<TopHP*>(m_listGameObject[tophp].front())->Set_TopHP(0.2);

							//dynamic_cast<TopHP*>(pDstObject)->Set_TopHP(0.5);
							//몬스터 공격받음 전달.
							//pSrcObject->Set_beAttacked();
							//pSrcObject->Set_beAttackTarget(ID::ChoSun);





							//if (dynamic_cast<TopHP*>(m_listGameObject[tophp].front())->Get_TopHP() < 1)


							//pSrcObject->Set_HP(pDstObject->Get_Damage());
							//몬스터 공격받음 전달.
							pSrcObject->Set_beAttacked();
							pSrcObject->Set_beAttackTarget(ID::PLAYER);



							if (dynamic_cast<TopHP*>(m_listGameObject[tophp].front())->Get_TopHP() < 1)
							{
								//이때 확실히 리스트에서 없애야 크리티컬 이펙트가 쌓이지않음
							   // pSrcObject->Set_State();
								pDstObject->Set_AttackStateOFF();
								dynamic_cast<DAEMA_Boss*>(pSrcObject)->Set_Dead();
								pSrcObject->Set_StateKey(L"Dead");

							}
							pDstObject->Set_AttackCount(0);


							//powerbullet화살 맞을시 이펙트 효과 생성!

							if (pDstObject->Get_Info().ID == ID::PlayerPowerBullet)
							{

								pCriticalEffect = new CriticalEffect;
								pCriticalEffect->Ready_GameObject();

								dynamic_cast<CriticalEffect*>(pCriticalEffect)->Set_target(pSrcObject->Get_Info().vPos);
								dynamic_cast<CriticalEffect*>(pCriticalEffect)->Set_Life(1);
								CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(ID::criticalEffect, pCriticalEffect);


								pCDmgNumber = new CTDmgNumber;
								pCDmgNumber->Ready_GameObject();

								dynamic_cast<CTDmgNumber*>(pCDmgNumber)->Set_target(pSrcObject->Get_Info().vPos);
								dynamic_cast<CTDmgNumber*>(pCDmgNumber)->Set_Life(1);
								CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(ID::NUMBER, pCDmgNumber);




							}
							else if (pDstObject->Get_bulletid() == Bullet_ID::default
								|| pDstObject->Get_Info().ID == ID::ChoSun
								)
							{

								CSoundMgr::Get_Instance()->PlaySound(L"Bullet_Arrow_Hit1.wav", CSoundMgr::PLAYER);

								pDmgNumber = new DmgNumber;
								pDmgNumber->Ready_GameObject();

								dynamic_cast<DmgNumber*>(pDmgNumber)->Set_target(pSrcObject->Get_Info().vPos);
								dynamic_cast<DmgNumber*>(pDmgNumber)->Set_Life(1);
								CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(ID::NUMBER, pDmgNumber);


							}
							else if (pDstObject->Get_bulletid() == Bullet_ID::fire)
							{
								CSoundMgr::Get_Instance()->PlaySound(L"magic_fireball_hit2.wav", CSoundMgr::PLAYER);


								pCriticalEffect = new CriticalEffect;
								pCriticalEffect->Ready_GameObject();

								dynamic_cast<CriticalEffect*>(pCriticalEffect)->Set_target(pSrcObject->Get_Info().vPos);
								dynamic_cast<CriticalEffect*>(pCriticalEffect)->Set_Life(1);
								CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(ID::criticalEffect, pCriticalEffect);


								pFirearrowEffect = new FireArrowSkill;
								dynamic_cast<FireArrowSkill*>(pFirearrowEffect)->Set_target(pSrcObject->Get_Info().vPos);
								int dir = pDstObject->Get_Dir();
								dynamic_cast<FireArrowSkill*>(pFirearrowEffect)->Set_Dir(dir);
								dynamic_cast<FireArrowSkill*>(pFirearrowEffect)->Set_Life(1);
								pFirearrowEffect->Ready_GameObject();

								CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(ID::criticalEffect, pFirearrowEffect);


								pCDmgNumber = new CTDmgNumber;
								pCDmgNumber->Ready_GameObject();

								dynamic_cast<CTDmgNumber*>(pCDmgNumber)->Set_target(pSrcObject->Get_Info().vPos);
								dynamic_cast<CTDmgNumber*>(pCDmgNumber)->Set_Life(1);
								CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(ID::NUMBER, pCDmgNumber);






							}




						}
						// m_collisionCount = 0;

					}

				}
				//pSrcObject->Set_State();
				//++m_collisionCount;



			//dynamic_cast<CPlayer*>(pDstObject)->Set_Life();//플레이어 체력감소





			}
			else
			{

			}


		}





	}
}

void Collison_Manager::Collision_BuldingAttack(list<CGameObject*>* plistDest, list<CGameObject*>* plistSrc)
{

	if (!m_pGameObject_Manager->Get_listTopHP().empty())
		m_listGameObject[tophp] = m_pGameObject_Manager->Get_listTopHP();	//CGameObject* pObject;

	

	RECT rc = {};
	RECT rPlayer = {};
	RECT rMonster = {};
	list<CGameObject*>::iterator iter = plistSrc->begin();

	for (auto& pDstObject : *plistDest)
	{
		

		pDstObject->Set_Collider(dynamic_cast<CMapObject*>(pDstObject)->Get_Collider34());

		rPlayer = { LONG(dynamic_cast<CMapObject*>(pDstObject)->Get_Collider34()[0].x), LONG(dynamic_cast<CMapObject*>(pDstObject)->Get_Collider34()[0].y),
			 LONG(dynamic_cast<CMapObject*>(pDstObject)->Get_Collider34()[1].x), LONG(dynamic_cast<CMapObject*>(pDstObject)->Get_Collider34()[2].y) };

		//rPlayer = { LONG((pDstObject)->Get_Collider()[0].x), LONG((pDstObject)->Get_Collider()[0].y),
		//	 LONG((pDstObject)->Get_Collider()[1].x), LONG((pDstObject)->Get_Collider()[2].y) };

		for (auto& pSrcObject : *plistSrc)
		{


			rMonster = { LONG((pSrcObject)->Get_Collider()[0].x), LONG((pSrcObject)->Get_Collider()[0].y),
			 LONG((pSrcObject)->Get_Collider()[1].x), LONG((pSrcObject)->Get_Collider()[2].y) };

			//if (pSrcObject->Get_Id() == 3)


			//if (m_listBullet.empty())


			if (IntersectRect(&rc, &rPlayer, &rMonster)) {
				m_fUpdateFPSTime += CTime_Manager::Get_Instance()->Get_DeltaTime();

				if (0.4 <= m_fUpdateFPSTime) //0.035 설정시 6마리 ~50fps ,4마리는 6~7fps  //8마리부턴 움직임이상현상발생
				{
					m_fUpdateFPSTime = 0.f;
					//충돌시 플레이어 HP 감소 처리


					++m_collisionCount;

					if (pSrcObject->Get_AttackState()) //몬스터 공격상태!
					{
						++m_iAttackCount;

						if (m_iAttackCount == 1)
						{



							if(!m_listGameObject[tophp].empty())
							dynamic_cast<TopHP*>(m_listGameObject[tophp].front())->Set_TopHP(0.05);

							//dynamic_cast<TopHP*>(pDstObject)->Set_TopHP(0.5);
							//몬스터 공격받음 전달.
							//pSrcObject->Set_beAttacked();
							//pSrcObject->Set_beAttackTarget(ID::ChoSun);





							 if(dynamic_cast<TopHP*>(m_listGameObject[tophp].front())->Get_TopHP()<1)
							{
								//이때 확실히 리스트에서 없애야 크리티컬 이펙트가 쌓이지않음
							   // pSrcObject->Set_State();
								pSrcObject->Set_AttackStateOFF();
								//pDstObject->Set_Life();

							}
							pDstObject->Set_AttackCount(0);


							pDmgNumber = new DmgNumber;
							pDmgNumber->Ready_GameObject();
						
							dynamic_cast<DmgNumber*>(pDmgNumber)->Set_target(pDstObject->Get_Info().vPos);
							dynamic_cast<DmgNumber*>(pDmgNumber)->Set_Life(1);
							CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(ID::NUMBER, pDmgNumber);



							////powerbullet화살 맞을시 이펙트 효과 생성!
							//
							//if (pDstObject->Get_Info().ID == ID::BOSS)
							//{
							//
							//
							//	pCDmgNumber = new CdmgNumber2;
							//	pCDmgNumber->Ready_GameObject();
							//
							//	dynamic_cast<CdmgNumber2*>(pCDmgNumber)->Set_target(pSrcObject->Get_Info().vPos);
							//	dynamic_cast<CdmgNumber2*>(pCDmgNumber)->Set_Life(1);
							//	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(ID::NUMBER, pCDmgNumber);
							//
							//}
							//
							//
							//
							//
							//if (pDstObject->Get_Info().ID == ID::PlayerPowerBullet)
							//{
							//
							//	pCriticalEffect = new CriticalEffect;
							//	pCriticalEffect->Ready_GameObject();
							//
							//	dynamic_cast<CriticalEffect*>(pCriticalEffect)->Set_target(pSrcObject->Get_Info().vPos);
							//	dynamic_cast<CriticalEffect*>(pCriticalEffect)->Set_Life(1);
							//	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(ID::criticalEffect, pCriticalEffect);
							//
							//
							//	pCDmgNumber = new CTDmgNumber;
							//	pCDmgNumber->Ready_GameObject();
							//
							//	dynamic_cast<CTDmgNumber*>(pCDmgNumber)->Set_target(pSrcObject->Get_Info().vPos);
							//	dynamic_cast<CTDmgNumber*>(pCDmgNumber)->Set_Life(1);
							//	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(ID::NUMBER, pCDmgNumber);
							//
							//
							//
							//
							//}
							//else if (pDstObject->Get_bulletid() == Bullet_ID::default
							//	|| pDstObject->Get_Info().ID == ID::ChoSun
							//	)
							//{
							//
							//	pDmgNumber = new DmgNumber;
							//	pDmgNumber->Ready_GameObject();
							//
							//	dynamic_cast<DmgNumber*>(pDmgNumber)->Set_target(pSrcObject->Get_Info().vPos);
							//	dynamic_cast<DmgNumber*>(pDmgNumber)->Set_Life(1);
							//	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(ID::NUMBER, pDmgNumber);
							//
							//
							//}
							//else if (pDstObject->Get_bulletid() == Bullet_ID::fire)
							//{
							//	pCriticalEffect = new CriticalEffect;
							//	pCriticalEffect->Ready_GameObject();
							//
							//	dynamic_cast<CriticalEffect*>(pCriticalEffect)->Set_target(pSrcObject->Get_Info().vPos);
							//	dynamic_cast<CriticalEffect*>(pCriticalEffect)->Set_Life(1);
							//	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(ID::criticalEffect, pCriticalEffect);
							//
							//
							//	pFirearrowEffect = new FireArrowSkill;
							//	dynamic_cast<FireArrowSkill*>(pFirearrowEffect)->Set_target(pSrcObject->Get_Info().vPos);
							//	int dir = pDstObject->Get_Dir();
							//	dynamic_cast<FireArrowSkill*>(pFirearrowEffect)->Set_Dir(dir);
							//	dynamic_cast<FireArrowSkill*>(pFirearrowEffect)->Set_Life(1);
							//	pFirearrowEffect->Ready_GameObject();
							//
							//	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(ID::criticalEffect, pFirearrowEffect);
							//
							//
							//	pCDmgNumber = new CTDmgNumber;
							//	pCDmgNumber->Ready_GameObject();
							//
							//	dynamic_cast<CTDmgNumber*>(pCDmgNumber)->Set_target(pSrcObject->Get_Info().vPos);
							//	dynamic_cast<CTDmgNumber*>(pCDmgNumber)->Set_Life(1);
							//	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(ID::NUMBER, pCDmgNumber);
							//
							//
							//
							//
							//
							//
							//}




						}
						// m_collisionCount = 0;

					}
					else
						m_iAttackCount = 0;
				}
				//pSrcObject->Set_State();
				//++m_collisionCount;



			//dynamic_cast<CPlayer*>(pDstObject)->Set_Life();//플레이어 체력감소





			}
			else
			{

			}


		}





	}
}

void Collison_Manager::Collision_Melee(list<CGameObject*>* plistDest, list<CGameObject*>* plistSrc)
{
	RECT rc = {};
	RECT rPlayer = {};
	RECT rMonster = {};
	list<CGameObject*>::iterator iter = plistSrc->begin();

	for (auto& pDstObject : *plistDest)
	{
		int player_Collider = pDstObject->Get_Current_Collider();
		rPlayer = { LONG((pDstObject)->Get_Collider()[0].x), LONG((pDstObject)->Get_Collider()[0].y),
			 LONG((pDstObject)->Get_Collider()[1].x), LONG((pDstObject)->Get_Collider()[2].y) };

		for (auto& pSrcObject : *plistSrc)
		{


			rMonster = { LONG((pSrcObject)->Get_Collider()[0].x), LONG((pSrcObject)->Get_Collider()[0].y),
			 LONG((pSrcObject)->Get_Collider()[1].x), LONG((pSrcObject)->Get_Collider()[2].y) };

			//if (pSrcObject->Get_Id() == 3)


			//if (m_listBullet.empty())


			if (IntersectRect(&rc, &rPlayer, &rMonster)) {
				m_fUpdateFPSTime += CTime_Manager::Get_Instance()->Get_DeltaTime();

				if (0.4 <= m_fUpdateFPSTime) //0.035 설정시 6마리 ~50fps ,4마리는 6~7fps  //8마리부턴 움직임이상현상발생
				{
					m_fUpdateFPSTime = 0.f;
					//충돌시 플레이어 HP 감소 처리


					++m_collisionCount;

					if (pDstObject->Get_AttackState())
					{
						++m_iAttackCount;

						if (m_iAttackCount == 1)
						{
							pObject = CGameObject_Manager::Get_Instance()->Get_ObjectList()[ID::PlayerHP].front();

							dynamic_cast<CHPBar_Player*>(pObject)->Set_TopHP(0.005);
							//pSrcObject->Set_HP(pDstObject->Get_Damage());
							//몬스터 공격받음 전달.
							pSrcObject->Set_beAttacked();
							//pSrcObject->Set_beAttackTarget(ID::ChoSun);
							CSoundMgr::Get_Instance()->PlaySound(L"sura_attack.wav", CSoundMgr::MONSTER);




							if (dynamic_cast<CHPBar_Player*>(pObject)->Get_TopHP() < 1)//pSrcObject->Get_Hp() < 0
							{
								//이때 확실히 리스트에서 없애야 크리티컬 이펙트가 쌓이지않음
							   // pSrcObject->Set_State();
								pDstObject->Set_AttackStateOFF();
								//pSrcObject->Set_Life();

							}
							pDstObject->Set_AttackCount(0);


							//powerbullet화살 맞을시 이펙트 효과 생성!

							if (pDstObject->Get_Info().ID == ID::BOSS)
							{


								pCDmgNumber = new CdmgNumber2;
								pCDmgNumber->Ready_GameObject();

								dynamic_cast<CdmgNumber2*>(pCDmgNumber)->Set_target(pSrcObject->Get_Info().vPos);
								dynamic_cast<CdmgNumber2*>(pCDmgNumber)->Set_Life(1);
								CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(ID::NUMBER, pCDmgNumber);

							}




							if (pDstObject->Get_Info().ID == ID::PlayerPowerBullet)
							{

								pCriticalEffect = new CriticalEffect;
								pCriticalEffect->Ready_GameObject();

								dynamic_cast<CriticalEffect*>(pCriticalEffect)->Set_target(pSrcObject->Get_Info().vPos);
								dynamic_cast<CriticalEffect*>(pCriticalEffect)->Set_Life(1);
								CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(ID::criticalEffect, pCriticalEffect);


								pCDmgNumber = new CTDmgNumber;
								pCDmgNumber->Ready_GameObject();

								dynamic_cast<CTDmgNumber*>(pCDmgNumber)->Set_target(pSrcObject->Get_Info().vPos);
								dynamic_cast<CTDmgNumber*>(pCDmgNumber)->Set_Life(1);
								CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(ID::NUMBER, pCDmgNumber);




							}
							else if (pDstObject->Get_bulletid() == Bullet_ID::default
								|| pDstObject->Get_Info().ID == ID::ChoSun
								)
							{

								pDmgNumber = new DmgNumber;
								pDmgNumber->Ready_GameObject();

								dynamic_cast<DmgNumber*>(pDmgNumber)->Set_target(pSrcObject->Get_Info().vPos);
								dynamic_cast<DmgNumber*>(pDmgNumber)->Set_Life(1);
								CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(ID::NUMBER, pDmgNumber);


							}
							else if (pDstObject->Get_bulletid() == Bullet_ID::fire)
							{
								pCriticalEffect = new CriticalEffect;
								pCriticalEffect->Ready_GameObject();

								dynamic_cast<CriticalEffect*>(pCriticalEffect)->Set_target(pSrcObject->Get_Info().vPos);
								dynamic_cast<CriticalEffect*>(pCriticalEffect)->Set_Life(1);
								CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(ID::criticalEffect, pCriticalEffect);


								pFirearrowEffect = new FireArrowSkill;
								dynamic_cast<FireArrowSkill*>(pFirearrowEffect)->Set_target(pSrcObject->Get_Info().vPos);
								int dir = pDstObject->Get_Dir();
								dynamic_cast<FireArrowSkill*>(pFirearrowEffect)->Set_Dir(dir);
								dynamic_cast<FireArrowSkill*>(pFirearrowEffect)->Set_Life(1);
								pFirearrowEffect->Ready_GameObject();

								CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(ID::criticalEffect, pFirearrowEffect);


								pCDmgNumber = new CTDmgNumber;
								pCDmgNumber->Ready_GameObject();

								dynamic_cast<CTDmgNumber*>(pCDmgNumber)->Set_target(pSrcObject->Get_Info().vPos);
								dynamic_cast<CTDmgNumber*>(pCDmgNumber)->Set_Life(1);
								CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(ID::NUMBER, pCDmgNumber);






							}




						}
						// m_collisionCount = 0;

					}
					else
						m_iAttackCount = 0;
				}
				//pSrcObject->Set_State();
				//++m_collisionCount;



			//dynamic_cast<CPlayer*>(pDstObject)->Set_Life();//플레이어 체력감소





			}
			else
			{

			}


		}





	}
}

void Collison_Manager::Collision_Skill(list<CGameObject*>* plistDest, list<CGameObject*>* plistSrc)
{
	RECT rc = {};
	RECT rPlayer = {};
	RECT rMonster = {};
	list<CGameObject*>::iterator iter = plistSrc->begin();

	for (auto& pDstObject : *plistDest)
	{
		int player_Collider = pDstObject->Get_Current_Collider();
		rPlayer = { LONG((pDstObject)->Get_Collider()[0].x), LONG((pDstObject)->Get_Collider()[0].y),
			 LONG((pDstObject)->Get_Collider()[1].x), LONG((pDstObject)->Get_Collider()[2].y) };

		for (auto& pSrcObject : *plistSrc)
		{


			rMonster = { LONG((pSrcObject)->Get_Collider()[0].x), LONG((pSrcObject)->Get_Collider()[0].y),
			 LONG((pSrcObject)->Get_Collider()[1].x), LONG((pSrcObject)->Get_Collider()[2].y) };

			//if (pSrcObject->Get_Id() == 3)


			//if (m_listBullet.empty())


			if (IntersectRect(&rc, &rPlayer, &rMonster)) {
				m_fUpdateFPSTime += CTime_Manager::Get_Instance()->Get_DeltaTime();

				if (1.f <= m_fUpdateFPSTime) //0.035 설정시 6마리 ~50fps ,4마리는 6~7fps  //8마리부턴 움직임이상현상발생
				{
					m_fUpdateFPSTime = 0.f;
					//충돌시 플레이어 HP 감소 처리


					++m_collisionCount;

					if (pDstObject->Get_AttackState())
					{
						++m_iAttackCount;

						if (m_iAttackCount == 1)
						{

							pObject = CGameObject_Manager::Get_Instance()->Get_ObjectList()[ID::PlayerHP].front();

							dynamic_cast<CHPBar_Player*>(pObject)->Set_TopHP(1);

							//pSrcObject->Set_HP(pDstObject->Get_Damage());
							//몬스터 공격받음 전달.
							pSrcObject->Set_beAttacked();
							//pSrcObject->Set_beAttackTarget(ID::ChoSun);





							if (dynamic_cast<CHPBar_Player*>(pObject)->Get_TopHP() < 1)
							{
								//이때 확실히 리스트에서 없애야 크리티컬 이펙트가 쌓이지않음
							   // pSrcObject->Set_State();
								pDstObject->Set_AttackStateOFF();
								pSrcObject->Set_Life();

							}
							pDstObject->Set_AttackCount(0);


							//powerbullet화살 맞을시 이펙트 효과 생성!

							if (pDstObject->Get_Info().ID == ID::BOSS)
							{


								pCDmgNumber = new CdmgNumber2;
								pCDmgNumber->Ready_GameObject();

								dynamic_cast<CdmgNumber2*>(pCDmgNumber)->Set_target(pSrcObject->Get_Info().vPos);
								dynamic_cast<CdmgNumber2*>(pCDmgNumber)->Set_Life(1);
								CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(ID::NUMBER, pCDmgNumber);

							}




							if (pDstObject->Get_Info().ID == ID::PlayerPowerBullet)
							{

								pCriticalEffect = new CriticalEffect;
								pCriticalEffect->Ready_GameObject();

								dynamic_cast<CriticalEffect*>(pCriticalEffect)->Set_target(pSrcObject->Get_Info().vPos);
								dynamic_cast<CriticalEffect*>(pCriticalEffect)->Set_Life(1);
								CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(ID::criticalEffect, pCriticalEffect);


								pCDmgNumber = new CTDmgNumber;
								pCDmgNumber->Ready_GameObject();

								dynamic_cast<CTDmgNumber*>(pCDmgNumber)->Set_target(pSrcObject->Get_Info().vPos);
								dynamic_cast<CTDmgNumber*>(pCDmgNumber)->Set_Life(1);
								CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(ID::NUMBER, pCDmgNumber);




							}
							else if (pDstObject->Get_bulletid() == Bullet_ID::default
								|| pDstObject->Get_Info().ID == ID::ChoSun
								)
							{

								pDmgNumber = new DmgNumber;
								pDmgNumber->Ready_GameObject();

								dynamic_cast<DmgNumber*>(pDmgNumber)->Set_target(pSrcObject->Get_Info().vPos);
								dynamic_cast<DmgNumber*>(pDmgNumber)->Set_Life(1);
								CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(ID::NUMBER, pDmgNumber);


							}
							else if (pDstObject->Get_bulletid() == Bullet_ID::fire)
							{
								pCriticalEffect = new CriticalEffect;
								pCriticalEffect->Ready_GameObject();

								dynamic_cast<CriticalEffect*>(pCriticalEffect)->Set_target(pSrcObject->Get_Info().vPos);
								dynamic_cast<CriticalEffect*>(pCriticalEffect)->Set_Life(1);
								CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(ID::criticalEffect, pCriticalEffect);


								pFirearrowEffect = new FireArrowSkill;
								dynamic_cast<FireArrowSkill*>(pFirearrowEffect)->Set_target(pSrcObject->Get_Info().vPos);
								int dir = pDstObject->Get_Dir();
								dynamic_cast<FireArrowSkill*>(pFirearrowEffect)->Set_Dir(dir);
								dynamic_cast<FireArrowSkill*>(pFirearrowEffect)->Set_Life(1);
								pFirearrowEffect->Ready_GameObject();

								CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(ID::criticalEffect, pFirearrowEffect);


								pCDmgNumber = new CTDmgNumber;
								pCDmgNumber->Ready_GameObject();

								dynamic_cast<CTDmgNumber*>(pCDmgNumber)->Set_target(pSrcObject->Get_Info().vPos);
								dynamic_cast<CTDmgNumber*>(pCDmgNumber)->Set_Life(1);
								CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(ID::NUMBER, pCDmgNumber);






							}




						}
						// m_collisionCount = 0;

					}
					else
						m_iAttackCount = 0;
				}
				//pSrcObject->Set_State();
				//++m_collisionCount;



			//dynamic_cast<CPlayer*>(pDstObject)->Set_Life();//플레이어 체력감소





			}
			else
			{

			}


		}





	}
}

void Collison_Manager::Collision_PlayerHeal(list<CGameObject*>* plistDest, list<CGameObject*>* plistSrc)
{

	RECT rc = {};
	RECT rPlayer = {};
	RECT rMonster = {};
	list<CGameObject*>::iterator iter = plistSrc->begin();

	for (auto& pDstObject : *plistDest)
	{
		int player_Collider = pDstObject->Get_Current_Collider();
		rPlayer = { LONG((pDstObject)->Get_Collider()[0].x), LONG((pDstObject)->Get_Collider()[0].y),
			 LONG((pDstObject)->Get_Collider()[1].x), LONG((pDstObject)->Get_Collider()[2].y) };

		for (auto& pSrcObject : *plistSrc)
		{


			rMonster = { LONG((pSrcObject)->Get_Collider()[0].x), LONG((pSrcObject)->Get_Collider()[0].y),
			 LONG((pSrcObject)->Get_Collider()[1].x), LONG((pSrcObject)->Get_Collider()[2].y) };

			//if (pSrcObject->Get_Id() == 3)


			//if (m_listBullet.empty())


			if (IntersectRect(&rc, &rPlayer, &rMonster)) {
				m_fUpdateFPSTime += CTime_Manager::Get_Instance()->Get_DeltaTime();

				if (1.f <= m_fUpdateFPSTime) //0.035 설정시 6마리 ~50fps ,4마리는 6~7fps  //8마리부턴 움직임이상현상발생
				{
					m_fUpdateFPSTime = 0.f;
					//충돌시 플레이어 HP 감소 처리


					++m_collisionCount;

					if (pDstObject->Get_AttackState())
					{
						++m_iAttackCount;

						//if (m_iAttackCount == 1)
						{

							pObject = CGameObject_Manager::Get_Instance()->Get_ObjectList()[ID::PlayerHP].front();

							if (dynamic_cast<CHPBar_Player*>(pObject)->Get_TopHP() < 172)
							{
							dynamic_cast<CHPBar_Player*>(pObject)->Set_TopHP_Plus(1);
							pCDmgNumber = new CdmgNumber2;
							pCDmgNumber->Ready_GameObject();
							D3DXVECTOR3 tSize = { 1,1,1 };
							pCDmgNumber->Set_size(tSize);
							pCDmgNumber->Set_StateKey(L"HealNumber");
							dynamic_cast<CdmgNumber2*>(pCDmgNumber)->Set_target(pSrcObject->Get_Info().vPos);
							dynamic_cast<CdmgNumber2*>(pCDmgNumber)->Set_Life(1);
							CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(ID::NUMBER, pCDmgNumber);
							}

							//pSrcObject->Set_HP(pDstObject->Get_Damage());
							//몬스터 공격받음 전달.
							pSrcObject->Set_beAttacked();
							//pSrcObject->Set_beAttackTarget(ID::ChoSun);







							//if (dynamic_cast<CHPBar_Player*>(pObject)->Get_TopHP() >=172)
							{
								//이때 확실히 리스트에서 없애야 크리티컬 이펙트가 쌓이지않음
							   // pSrcObject->Set_State();
								//pDstObject->Set_AttackStateOFF();
								//pSrcObject->Set_Life();

							}
							//pDstObject->Set_AttackCount(0);


							//powerbullet화살 맞을시 이펙트 효과 생성!

							if (pDstObject->Get_Info().ID == ID::BOSS)
							{


								pCDmgNumber = new CdmgNumber2;
								pCDmgNumber->Ready_GameObject();

								dynamic_cast<CdmgNumber2*>(pCDmgNumber)->Set_target(pSrcObject->Get_Info().vPos);
								dynamic_cast<CdmgNumber2*>(pCDmgNumber)->Set_Life(1);
								CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(ID::NUMBER, pCDmgNumber);

							}




							if (pDstObject->Get_Info().ID == ID::PlayerPowerBullet)
							{

								pCriticalEffect = new CriticalEffect;
								pCriticalEffect->Ready_GameObject();

								dynamic_cast<CriticalEffect*>(pCriticalEffect)->Set_target(pSrcObject->Get_Info().vPos);
								dynamic_cast<CriticalEffect*>(pCriticalEffect)->Set_Life(1);
								CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(ID::criticalEffect, pCriticalEffect);


								pCDmgNumber = new CTDmgNumber;
								pCDmgNumber->Ready_GameObject();

								dynamic_cast<CTDmgNumber*>(pCDmgNumber)->Set_target(pSrcObject->Get_Info().vPos);
								dynamic_cast<CTDmgNumber*>(pCDmgNumber)->Set_Life(1);
								CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(ID::NUMBER, pCDmgNumber);




							}
							else if (pDstObject->Get_bulletid() == Bullet_ID::default
								|| pDstObject->Get_Info().ID == ID::ChoSun
								)
							{

								pDmgNumber = new DmgNumber;
								pDmgNumber->Ready_GameObject();

								dynamic_cast<DmgNumber*>(pDmgNumber)->Set_target(pSrcObject->Get_Info().vPos);
								dynamic_cast<DmgNumber*>(pDmgNumber)->Set_Life(1);
								CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(ID::NUMBER, pDmgNumber);


							}
							else if (pDstObject->Get_bulletid() == Bullet_ID::fire)
							{
								pCriticalEffect = new CriticalEffect;
								pCriticalEffect->Ready_GameObject();

								dynamic_cast<CriticalEffect*>(pCriticalEffect)->Set_target(pSrcObject->Get_Info().vPos);
								dynamic_cast<CriticalEffect*>(pCriticalEffect)->Set_Life(1);
								CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(ID::criticalEffect, pCriticalEffect);


								pFirearrowEffect = new FireArrowSkill;
								dynamic_cast<FireArrowSkill*>(pFirearrowEffect)->Set_target(pSrcObject->Get_Info().vPos);
								int dir = pDstObject->Get_Dir();
								dynamic_cast<FireArrowSkill*>(pFirearrowEffect)->Set_Dir(dir);
								dynamic_cast<FireArrowSkill*>(pFirearrowEffect)->Set_Life(1);
								pFirearrowEffect->Ready_GameObject();

								CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(ID::criticalEffect, pFirearrowEffect);


								pCDmgNumber = new CTDmgNumber;
								pCDmgNumber->Ready_GameObject();

								dynamic_cast<CTDmgNumber*>(pCDmgNumber)->Set_target(pSrcObject->Get_Info().vPos);
								dynamic_cast<CTDmgNumber*>(pCDmgNumber)->Set_Life(1);
								CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(ID::NUMBER, pCDmgNumber);






							}




						}
						// m_collisionCount = 0;

					}
					//else
						m_iAttackCount = 0;
				}
				//pSrcObject->Set_State();
				//++m_collisionCount;



			//dynamic_cast<CPlayer*>(pDstObject)->Set_Life();//플레이어 체력감소





			}
			else
			{

			}


		}





	}


}

void Collison_Manager::Collision_MonstervsPlayer(list<CGameObject*>* plistDest, list<CGameObject*>* plistSrc)
{
	RECT rc = {};
	RECT rPlayer = {};
	RECT rMonster = {};
	list<CGameObject*>::iterator iter = plistSrc->begin();

	for (auto& pDstObject : *plistDest)
	{
		int player_Collider = pDstObject->Get_Current_Collider();
		rPlayer = { LONG((pDstObject)->Get_Collider()[0].x), LONG((pDstObject)->Get_Collider()[0].y),
			 LONG((pDstObject)->Get_Collider()[1].x), LONG((pDstObject)->Get_Collider()[2].y) };

		for (auto& pSrcObject : *plistSrc)
		{


			rMonster = { LONG((pSrcObject)->Get_Collider()[0].x), LONG((pSrcObject)->Get_Collider()[0].y),
			 LONG((pSrcObject)->Get_Collider()[1].x), LONG((pSrcObject)->Get_Collider()[2].y) };

			//if (pSrcObject->Get_Id() == 3)


			//if (m_listBullet.empty())


			if (IntersectRect(&rc, &rPlayer, &rMonster)) {
				m_fMonBulletFPSTime += CTime_Manager::Get_Instance()->Get_DeltaTime();

				if (1.f <= m_fMonBulletFPSTime) //0.035 설정시 6마리 ~50fps ,4마리는 6~7fps  //8마리부턴 움직임이상현상발생
				{

					m_fMonBulletFPSTime = 0.f;
					//충돌시 플레이어 HP 감소 처리


					++m_collisionCount;

					if (pSrcObject->Get_AttackState())
					{

						pDstObject->Set_HP(pSrcObject->Get_Damage());

						if (pDstObject->Get_Hp() < 0)
						{
							//이때 확실히 리스트에서 없애야 크리티컬 이펙트가 쌓이지않음
						   // pSrcObject->Set_State();
							pSrcObject->Set_AttackStateOFF();
							//pDstObject->Set_Life();


						}
						//pDstObject->Set_AttackCount(0);

						//powerbullet화살 맞을시 이펙트 효과 생성!

						//if (pDstObject->Get_Info().ID == ID::PlayerPowerBullet)
						{
							pDmgNumber = new DmgNumber;
							pDmgNumber->Ready_GameObject();
						
							dynamic_cast<DmgNumber*>(pDmgNumber)->Set_target(pDstObject->Get_Info().vPos);
							dynamic_cast<DmgNumber*>(pDmgNumber)->Set_Life(1);
							CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(ID::NUMBER, pDmgNumber);
						


							//pCriticalEffect = new CriticalEffect;
							//pCriticalEffect->Ready_GameObject();
							//
							//dynamic_cast<CriticalEffect*>(pCriticalEffect)->Set_target(pSrcObject->Get_Info().vPos);
							//dynamic_cast<CriticalEffect*>(pCriticalEffect)->Set_Life(1);
							//CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(ID::criticalEffect, pCriticalEffect);
							//
							//
							//pCDmgNumber = new CTDmgNumber;
							//pCDmgNumber->Ready_GameObject();
							//
							//dynamic_cast<CTDmgNumber*>(pCDmgNumber)->Set_target(pSrcObject->Get_Info().vPos);
							//dynamic_cast<CTDmgNumber*>(pCDmgNumber)->Set_Life(1);
							//CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(ID::NUMBER, pCDmgNumber);




						}
						//else if (pDstObject->Get_bulletid() == Bullet_ID::default
						//	|| pDstObject->Get_Info().ID == ID::ChoSun
						//	)
						//{
						//
						//	pDmgNumber = new DmgNumber;
						//	pDmgNumber->Ready_GameObject();
						//
						//	dynamic_cast<DmgNumber*>(pDmgNumber)->Set_target(pSrcObject->Get_Info().vPos);
						//	dynamic_cast<DmgNumber*>(pDmgNumber)->Set_Life(1);
						//	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(ID::NUMBER, pDmgNumber);
						//
						//
						//}
						//else if (pDstObject->Get_bulletid() == Bullet_ID::fire)
						//{
						//	pCriticalEffect = new CriticalEffect;
						//	pCriticalEffect->Ready_GameObject();
						//
						//	dynamic_cast<CriticalEffect*>(pCriticalEffect)->Set_target(pSrcObject->Get_Info().vPos);
						//	dynamic_cast<CriticalEffect*>(pCriticalEffect)->Set_Life(1);
						//	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(ID::criticalEffect, pCriticalEffect);
						//
						//
						//	pFirearrowEffect = new FireArrowSkill;
						//	dynamic_cast<FireArrowSkill*>(pFirearrowEffect)->Set_target(pSrcObject->Get_Info().vPos);
						//	int dir = pDstObject->Get_Dir();
						//	dynamic_cast<FireArrowSkill*>(pFirearrowEffect)->Set_Dir(dir);
						//	dynamic_cast<FireArrowSkill*>(pFirearrowEffect)->Set_Life(1);
						//	pFirearrowEffect->Ready_GameObject();
						//
						//	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(ID::criticalEffect, pFirearrowEffect);
						//
						//
						//	pCDmgNumber = new CTDmgNumber;
						//	pCDmgNumber->Ready_GameObject();
						//
						//	dynamic_cast<CTDmgNumber*>(pCDmgNumber)->Set_target(pSrcObject->Get_Info().vPos);
						//	dynamic_cast<CTDmgNumber*>(pCDmgNumber)->Set_Life(1);
						//	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(ID::NUMBER, pCDmgNumber);
						//
						//
						//
						//
						//
						//
						//}





						// m_collisionCount = 0;

					}
				}
				//pSrcObject->Set_State();
				//++m_collisionCount;



			//dynamic_cast<CPlayer*>(pDstObject)->Set_Life();//플레이어 체력감소





			}
			else
			{

			}


		}





	}
}

bool Collison_Manager::Collision_PlayerNPC(CGameObject * plistDest, CGameObject * plistSrc)
{
	RECT rc;
	RECT rPlayer;

	RECT MAP;
	DWORD dwSize = dynamic_cast<CMapObject*>(plistSrc)->Get_VecTile().size();
	CMapObject* pMap = dynamic_cast<CMapObject*>(plistSrc);

	rPlayer = { LONG((plistDest)->Get_Collider()[0].x), LONG((plistDest)->Get_Collider()[0].y),
				 LONG((plistDest)->Get_Collider()[1].x), LONG((plistDest)->Get_Collider()[2].y) };


	//for (size_t i = 0; i < dwSize; ++i)

		//if (pMap->Get_VecTile()[i]->byDrawID == 26)
		//{
		//
		//}


	MAP = { LONG((plistSrc)->Get_Collider()[0].x), LONG((plistSrc)->Get_Collider()[0].y),
		 LONG((plistSrc)->Get_Collider()[1].x), LONG((plistSrc)->Get_Collider()[2].y) };

	if (IntersectRect(&rc, &rPlayer, &MAP)) {


		//맵 Stage 이동!
		//CScene_Manager::Get_Instance()->Change_Scene_Manager(CScene_Manager::DAEMA);
		plistDest->ObjectKey = L"TurtleShip";
		return true;




	}
	return false;


}


//if(Collision_Line(pDstObject->Get_Info().vPos,pDstObject->Get_Info().vSize, 
		//	dynamic_cast<CRectangle*>(pSrcObject)->Get_Pos(),pSrcObject->Get_Info().vSize, dynamic_cast<CRectangle*>(pSrcObject)->Get_Id()))


//플레이어, 건물간 맵 이동 
bool Collison_Manager::Collision_RectEx(CGameObject* plistDest, CGameObject* plistSrc)
{
	RECT rc;
	RECT rPlayer;

	RECT MAP;
	DWORD dwSize = dynamic_cast<CMapObject*>(plistSrc)->Get_VecTile().size();
	CMapObject* pMap = dynamic_cast<CMapObject*>(plistSrc);

	rPlayer = { LONG((plistDest)->Get_Collider()[0].x), LONG((plistDest)->Get_Collider()[0].y),
				 LONG((plistDest)->Get_Collider()[1].x), LONG((plistDest)->Get_Collider()[2].y) };


	for (size_t i = 0; i < dwSize; ++i)
	{
		//if (pMap->Get_VecTile()[i]->byDrawID == 26)
		//{
		//
		//}

		 if (pMap->Get_VecTile()[i]->byDrawID == 2 && pMap->Get_Info().vPos)
		{
		
			 MAP = { LONG((pMap)->Get_Collider2()[0].x), LONG((pMap)->Get_Collider2()[0].y),
		 LONG((pMap)->Get_Collider2()[1].x), LONG((pMap)->Get_Collider2()[2].y) };
	//	MAP = { LONG((pMap)->Get_Info().vPos.x-80), LONG((pMap)->Get_Info().vPos.y-80),
	// LONG((pMap)->Get_Info().vPos.x+80), LONG((pMap)->Get_Info().vPos.y+80) };
		
		if (IntersectRect(&rc, &rPlayer, &MAP)) {
		
		
			//맵 Stage 이동!
			CScene_Manager::Get_Instance()->Change_Scene_Manager(CScene_Manager::DAEMA);
			return true;
		
		
		
		
			}
		
		
		}

		  if (pMap->Get_VecTile()[i]->byDrawID == 31)
		{
			MAP = { LONG((pMap)->Get_Collider31()[0].x), LONG((pMap)->Get_Collider31()[0].y),
		 LONG((pMap)->Get_Collider31()[1].x), LONG((pMap)->Get_Collider31()[2].y) };

			if (IntersectRect(&rc, &rPlayer, &MAP)) {


				//맵 Stage 이동!
				//CScene_Manager::Get_Instance()->Change_Scene_Manager(CScene_Manager::DAEMA);

				CScene_Manager::Get_Instance()->Change_Scene_Manager(CScene_Manager::HanYang);
				return true;


			}

		}
		else if (pMap->Get_VecTile()[i]->byDrawID == 33)
		{
			MAP = { LONG((pMap)->Get_Collider33()[0].x), LONG((pMap)->Get_Collider33()[0].y),
	 LONG((pMap)->Get_Collider33()[1].x), LONG((pMap)->Get_Collider33()[2].y) };

			if (IntersectRect(&rc, &rPlayer, &MAP)) {


				//맵 Stage 이동!
				CScene_Manager::Get_Instance()->Change_Scene_Manager(CScene_Manager::KwangHwa);
				return true;



			}
		}
		else if (pMap->Get_VecTile()[i]->byDrawID == 39)
		{
			MAP = { LONG((pMap)->Get_Collider39()[0].x), LONG((pMap)->Get_Collider39()[0].y),
	 LONG((pMap)->Get_Collider39()[1].x), LONG((pMap)->Get_Collider39()[2].y) };

			if (IntersectRect(&rc, &rPlayer, &MAP)) {


				//맵 Stage 이동!
				CScene_Manager::Get_Instance()->Change_Scene_Manager(CScene_Manager::STAGE);
				return true;
				;



			}
		}
		else if(pMap->Get_VecTile()[i]->byDrawID == 68)
		{
			MAP = { LONG((pMap)->Get_Collider68()[0].x), LONG((pMap)->Get_Collider68()[0].y),
		 LONG((pMap)->Get_Collider68()[1].x), LONG((pMap)->Get_Collider68()[2].y) };

			if (IntersectRect(&rc, &rPlayer, &MAP)) {


				//맵 Stage 이동!
				//CScene_Manager::Get_Instance()->Change_Scene_Manager(CScene_Manager::DAEMA);

				CScene_Manager::Get_Instance()->Change_Scene_Manager(CScene_Manager::KwangHwa2);
				return true;
				



			}

		
		}
		//else if (pMap->Get_VecTile()[i]->byDrawID == 66) //플레이어, 거북선 변신!
		// {
		//	 MAP = { LONG((pMap)->Get_Collider66()[0].x), LONG((pMap)->Get_Collider66()[0].y),
		//  LONG((pMap)->Get_Collider66()[1].x), LONG((pMap)->Get_Collider66()[2].y) };
		//
		//	 if (IntersectRect(&rc, &rPlayer, &MAP)) {
		//
		//
		//		 //맵 Stage 이동!
		//
		//		 plistDest->ObjectKey = L"TurtleShip";
		//		 return true;
		//
		//
		//
		//
		//	 }
		//
		//
		// }


	}
	return false;




}

bool Collison_Manager::Collision_RectQuest(CGameObject * plistDest, CGameObject * plistSrc,int scene)
{
	RECT rc;
	RECT rMouse;
	CGameObject* pObject;
	RECT Quest;
	//DWORD dwSize = dynamic_cast<CMapObject*>(plistSrc)->Get_VecTile().size();
	//CQuest* pQuest = dynamic_cast<CQuest*>(plistSrc);
	if (QuestOrder < 1)
	{

	
	rMouse = { LONG((plistDest)->Get_Collider()[0].x), LONG((plistDest)->Get_Collider()[0].y),
				 LONG((plistDest)->Get_Collider()[1].x), LONG((plistDest)->Get_Collider()[2].y) };


	
    Quest = { LONG((plistSrc)->Get_Collider()[0].x), LONG((plistSrc)->Get_Collider()[0].y),
		 LONG((plistSrc)->Get_Collider()[1].x), LONG((plistSrc)->Get_Collider()[2].y) };

			if (GetAsyncKeyState(VK_LBUTTON) & 0x0001)
			{
				if (IntersectRect(&rc, &rMouse, &Quest)) {

					++QuestOrder;
					CGameObject_Manager::Get_Instance()->Set_QuestOn();
					if (QuestOrder == 1)
					{

					pObject = new CQuest;
					if (FAILED(pObject->Ready_GameObject()))
						return E_FAIL;

					if (scene == 4)
					{
						pObject->Set_StateKey(L"Quest3");

					}
					else if (scene == 5)
					{
						pObject->Set_StateKey(L"Quest5");

					}


					dynamic_cast<CQuest*>(pObject)->QuestChange();
					CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(ID::Quest, pObject);
					QuestOrder = 0;
					return true;
					}
					else if (plistSrc->Get_Info().ID==ID::UI && QuestOrder == 2)
					{
						CGameObject_Manager::Get_Instance()->Release_Quest();
						//CGameObject_Manager::Get_Instance()->
						pObject = new CQuest;
						if (FAILED(pObject->Ready_GameObject()))
							return E_FAIL;
						pObject->Set_StateKey(L"Quest2");
						dynamic_cast<CQuest*>(pObject)->QuestChange();

						CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(ID::Quest, pObject);
						return true;

					}
					//else if (plistSrc->Get_Info().ID == ID::UI && QuestOrder == 3)
					//{
					//	CGameObject_Manager::Get_Instance()->Set_QuestOFF();
					//
					//	++QuestOrder;
					//	CGameObject_Manager::Get_Instance()->Release_Quest();
					//	//리스트에서 퀘스트창 삭제하기!
					//	return true;
					//
					//}
					//else if (plistSrc->Get_Info().ID == ID::UI && QuestOrder ==4)
					//{
					//	CGameObject_Manager::Get_Instance()->Set_QuestOFF();
					//
					//	++QuestOrder;
					//	CGameObject_Manager::Get_Instance()->Release_Quest();
					//	//리스트에서 퀘스트창 삭제하기!
					//	return true;
					//
					//}



				}
			}
		

	}
	return false;
}

bool Collison_Manager::Collision_RectQuest2(CGameObject * plistDest, CGameObject * plistSrc, int scene)
{
	RECT rc;
	RECT rMouse;
	CGameObject* pObject;
	RECT Quest;
	//DWORD dwSize = dynamic_cast<CMapObject*>(plistSrc)->Get_VecTile().size();
	//CQuest* pQuest = dynamic_cast<CQuest*>(plistSrc);

	if (QuestOrder < 3)
	{

	
	rMouse = { LONG((plistDest)->Get_Collider()[0].x), LONG((plistDest)->Get_Collider()[0].y),
				 LONG((plistDest)->Get_Collider()[1].x), LONG((plistDest)->Get_Collider()[2].y) };



	Quest = { LONG((plistSrc)->Get_Collider()[0].x), LONG((plistSrc)->Get_Collider()[0].y),
		 LONG((plistSrc)->Get_Collider()[1].x), LONG((plistSrc)->Get_Collider()[2].y) };

	if (GetAsyncKeyState(VK_LBUTTON) & 0x0001)
	{
		if (IntersectRect(&rc, &rMouse, &Quest)) {

			++QuestOrder;
			CGameObject_Manager::Get_Instance()->Set_QuestOn();
			//if (QuestOrder == 1)
			//{
			//
			//	pObject = new CQuest;
			//	if (FAILED(pObject->Ready_GameObject()))
			//		return E_FAIL;
			//
			//	dynamic_cast<CQuest*>(pObject)->QuestChange();
			//	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(ID::Quest, pObject);
			//	//++QuestOrder;
			//	return true;
			//}
			 if (plistSrc->Get_Info().ID == ID::UI && QuestOrder == 2)
			{
				CGameObject_Manager::Get_Instance()->Release_Quest();
				//CGameObject_Manager::Get_Instance()->
				pObject = new CQuest;
				if (FAILED(pObject->Ready_GameObject()))
					return E_FAIL;

				if (scene == 4)
				{
					pObject->Set_StateKey(L"Quest4");

				}
				else
				{

				pObject->Set_StateKey(L"Quest2");
				}
				CGameObject_Manager::Get_Instance()->Set_QuestOn();
				dynamic_cast<CQuest*>(pObject)->QuestChange();

				CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(ID::Quest, pObject);
				return true;

			}
			else if (plistSrc->Get_Info().ID == ID::UI && QuestOrder == 3)
			{
				CGameObject_Manager::Get_Instance()->Set_QuestOFF();

				QuestOrder = 0;
				CGameObject_Manager::Get_Instance()->Release_Quest();
				//리스트에서 퀘스트창 삭제하기!
				return true;

			}


		}
	}


	}
	return false;
}

void Collison_Manager::Collision_Sphere(list<CGameObject*>* plistDest, list<CGameObject*>* plistSrc)
{
}

bool Collison_Manager::Collision_Line(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 * pos2, D3DXVECTOR3 size2, int Monster_id)
{
	return false;
}

bool Collison_Manager::Check_Sphere(const INFO * pDstInfo, const INFO * pSrcInfo)
{
	return false;
}

bool Collison_Manager::Check_Rect(const INFO * pDstInfo, const INFO * pSrcInfo, float * pOutX, float * pOutY)
{
	return false;
}
