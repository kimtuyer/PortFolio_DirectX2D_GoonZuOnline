#pragma once
class CGameObject;

class CCamera
{
	DECLARE_SINGLETON(CCamera)

	CCamera();
	~CCamera();
private:
	D3DXVECTOR3 m_tPos;
	D3DXVECTOR3 m_tPlayerPos;


	RESOLUTION m_tClientRS;
	RESOLUTION m_tWorldRS;
	D3DXVECTOR2 WorldRS;

	D3DXVECTOR2 m_ColliderInfo[5];
	D3DXVECTOR3 m_tPivot;
	class CGameObject* m_pTarget;
	int m_tCameraLoc=0;
	float fL;
	float fT;
	float fR;
	float fB;

	//카메라 안 클라이언트 영역
	float fLeftArea		;
	float fRightArea	;
	float fTopArea		;
	float fBottomArea	;

//public:
//
//	RESOLUTION GetClientRS()
//	{
//		return m_tClientRS;
//	}
//
//
public:
	D3DXVECTOR3 GetPlayerPos() const
	{
		return m_tPlayerPos;
	}

	int GetLoc()
	{
		return m_tCameraLoc;
	}
public:
	D3DXVECTOR3 GetPos() const
	{
		return m_tPos;
	}
	D3DXVECTOR2 GetWorld() {

		return  WorldRS;
		
	}


public:
	void SetTarget(class CGameObject* pObj);

	//void SetPivot(const POSITION& tPivot)
	//{
	//	m_tPivot = tPivot;
	//}
	void SetPivot(float x, float y)
	{
		m_tPivot = { x,y ,0};
	}
	D3DXVECTOR3 Get_Pivoit()
	{
		return m_tPivot
			;
	}

	//
	//void SetPos(const POSITION& tPos)
	//{
	//	m_tPos = tPos;
	//}
	//void SetPos(float x, float y)
	//{
	//	m_tPos = POSITION(x, y);
	//}
	void SetClientResolution(const RESOLUTION& tRS)
	{
		m_tClientRS = tRS;
	}
	void SetClientResolution(int x, int y)
	{
		m_tClientRS = RESOLUTION(x, y);
	}

	void SetWorldResolution(const RESOLUTION& tWorldRS)
	{
		m_tWorldRS = tWorldRS;
	}
	void SetWorldResolution(int x, int y)
	{
		m_tWorldRS = RESOLUTION(x, y);
	}


public:
	bool Init(const D3DXVECTOR3& tPos, const RESOLUTION& tRS,
		const RESOLUTION& tWorldRS);

	void Input(float fDeltaTime);
	void Update(float fDeltaTime);

	void Render(float fDeltaTime);

	void Scroll(float x, float y);
};

