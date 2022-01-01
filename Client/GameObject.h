#pragma once

enum Bullet_ID{default,fire,water,power};
enum  Dir_ID {Down1,Up1,Left1,Right1,LD1,LU1,RD1,RU1};

class CGameObject abstract
{
public:
	explicit CGameObject();
	virtual ~CGameObject();

public:
	virtual HRESULT Ready_GameObject()PURE; 
	virtual int Update_GameObject()PURE; 
	virtual void Late_Update_GameObject()PURE; 
	virtual void Render_GameObject()PURE; 
	virtual void Release_GameObject() PURE; 

	void Set_Info(INFO* tInfo) {
		m_tInfo.byDrawID=tInfo->byDrawID;
		m_tInfo.vPos = tInfo->vPos;
		m_tInfo.byOption = tInfo->byOption;
		m_tInfo.ID = tInfo->ID;
		m_tInfo.iAttack_Target = tInfo->iAttack_Target;




	}


	void Set_size(D3DXVECTOR3 tSize) {
		m_tInfo.vSize = tSize;
	}




	void Set_Pos(D3DXVECTOR3 tPos) {
		m_tInfo.vPos = tPos;
	}
	INFO Get_Info() { return m_tInfo; }
	TEXINFO* Get_TexInfo() {
		return pTexInfo
			;
	}
	D3DXVECTOR2* Get_Collider()
	{
		return m_ColliderInfo;
	}
	void Set_Collider(D3DXVECTOR2* collider)
	{
		m_ColliderInfo[0] = collider[0];
		m_ColliderInfo[1] = collider[1];
		m_ColliderInfo[2] = collider[2];
		

	}



	int Get_Current_Collider() {
		return m_Current_Collider
			;
	}
	void Set_StateKey(wstring wStatekey) {
		StateKey = wStatekey
			;
	}

	int Get_Life() {
		return m_life
			;
	}
	void Set_Life()
	{
		m_life = OBJ_DEAD;
	}



	int Get_State() {
		return m_State
			;
	}
	void Set_State()
	{
		 m_State = OBJ_DEAD;
	}
	void Set_StateON()
	{
		m_State = 0;
	}



	void Set_HP(int damage)
	{
		m_HP -= damage;
	}
	int Get_Hp() {
		return m_HP;
	}

	void Set_Damage(int damage)
	{
		m_Damage = damage;
	}
	int Get_Damage() {
		return m_Damage;
	}

	void Set_AttackCount(int damage)
	{
		m_AttackCount= damage;
	}
	int Get_AttackCount() {
		return m_AttackCount;
	}


	//현재 오브젝트가 공격 상태인지 체크!
	void Set_AttackStateOFF()
	{
		m_bAttackState = false;
	}

	void Set_AttackStateOn()
	{
		m_bAttackState = true;
	}
	bool Get_AttackState() {
		return m_bAttackState;
	}


	int Get_bulletid() {
		return m_ebullet;
	}


	void Set_Dir(int i) { m_eDir = i; }

	int Get_Dir() {return m_eDir; }

	//공격을 받았는지 여부 체크!
	void Set_beAttacked() { m_beAttacked = true; }

	bool Get_beAttacked() { return m_beAttacked ; }


	void Set_beAttackTarget(int id) { m_beAttackedTarget = id; }


	wstring ObjectKey;
protected:
	int m_eDir;
	
	
	
	INFO m_tInfo;
	D3DXVECTOR2 m_ColliderInfo[5]; //m_tInfo에서 left,top 좌표 , left,top에서 right,bottom좌표
	int m_Current_Collider = Collider_AniMotion::End;
	
	float fCenterX = 0;
	float fCenterY = 0;
	wstring StateKey;

	int m_State=0;
	D3DXMATRIX matScale, matTrans, matWorld;
	TEXINFO* pTexInfo;

	int m_life = 0;
	int m_HP=200;
	int m_Damage = 30;
	int m_AttackCount = 0;

	bool m_bAttackState = false;
	Bullet_ID m_ebullet;


	bool m_beAttacked = false;
	int m_beAttackedTarget = ID::END;

};

