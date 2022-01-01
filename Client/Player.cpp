#include "stdafx.h"
#include "Player.h"
#include "CAStar_Manager.h"
#include "CCamera.h"
#include "Terrain.h"
#include "CMouse.h"
#include "Bullet_Player.h"
#include "GameObject_Manager.h"
#include "Key_Manager.h"
#include "CSkill1_Player.h"
#include "PowerBullet_Player.h"
#include "FireArrow_Player.h"
#include "WaterArrow_Player.h"


CPlayer::CPlayer()
//	:m_tInfo({})
	: m_tFrame({}), pMouse(nullptr), pSkill(nullptr),
	m_fSpeed(0), pTerrain(nullptr), m_pGameObject_Manager(CGameObject_Manager::Get_Instance())
{
	ZeroMemory(&m_tInfo, sizeof(INFO));



}


CPlayer::~CPlayer()
{
	Release_GameObject();

}
HRESULT CPlayer::Ready_GameObject()
{

	//m_tInfo.vPos = { 850.f, 420.f, 0.f };
	m_tInfo.vPos = { 860.f, 420.f, 0.f };

	m_HP = 10000;
	vMouse = { 0, 0, 0.f };
	m_tInfo.vDir = { 1.f, 1.f, 0.f };
	m_tInfo.vSize = { 1.f, 1.f, 0.f };
	m_tFrame = { 0.f, 6.f };
	m_fSpeed = 100.f;
	ObjectKey = L"Player";
	StateKey = L"Stand";
	D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);

	pMouse = dynamic_cast<CMouse*>(CGameObject_Manager::Get_Instance()->Get_Mouse());


	//pBullet = new PowerBullet_Player;
	//m_pGameObject_Manager->Add_GameObject_Manager(ID::PlayerBullet, pBullet);

	pBullet2 = new PowerBullet_Player;
	m_pGameObject_Manager->Add_GameObject_Manager(ID::PlayerBullet, pBullet2);

	pBullet3 = new PowerBullet_Player;
	m_pGameObject_Manager->Add_GameObject_Manager(ID::PlayerBullet, pBullet3);
	return S_OK;
}

void CPlayer::FrameMove(float fSpeed)
{
	m_tFrame.fFrameStart += m_tFrame.fFrameEnd * CTime_Manager::Get_Instance()->Get_DeltaTime() * fSpeed;
	if (m_tFrame.fFrameEnd < m_tFrame.fFrameStart)
		m_tFrame.fFrameStart = 0.f;
}

void CPlayer::MovePlayer()
{




	list<TILE*>& BestList = CAStar_Manager::Get_Instance()->Get_BestList();
	if (BestList.empty())
		return;
	pTerrain = dynamic_cast<CTerrain*>(CGameObject_Manager::Get_Instance()->Get_Terrain());
	int index = pTerrain->Get_TileIndex(m_tInfo.vPos);

	m_tInfo.vDir = BestList.front()->vPos - m_tInfo.vPos;
	m_tInfo.vDir2 = BestList.back()->vPos - m_tInfo.vPos;

	if (abs((BestList.back()->iIndex - index)) % (TILEX * 2) == 0 && m_tInfo.vDir.y > 0)
	{
		StateKey = L"Walk"; //Down

		D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);

	}
	else if (abs((BestList.back()->iIndex - index)) % (TILEX * 2) == 0 && m_tInfo.vDir.y < 0) //up
	{
		StateKey = L"WalkUp";

		D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);



	}
	else if (m_tInfo.vDir.x < 0 && abs((BestList.back()->iIndex - index)) < 10)
	{
		StateKey = L"WalkLeft";

		D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);

	}
	else if (m_tInfo.vDir.x > 0 && abs((BestList.back()->iIndex - index)) < 10)
	{
		StateKey = L"WalkLeft";

		D3DXMatrixScaling(&matScale, -m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);

	}
	//왼쪽 대각선 LU
	else if (m_tInfo.vDir.x < 0 && m_tInfo.vDir.y >0)
	{
		StateKey = L"WalkLD";

		D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);

	}
	//왼쪽 대각선 LD

	else if (m_tInfo.vDir.x < 0 && m_tInfo.vDir.y < 0)
	{
		StateKey = L"WalkLU";
		D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);


	}

	//오른 대각선 LU
	else if (m_tInfo.vDir.x > 0 && m_tInfo.vDir.y > 0)
	{
		StateKey = L"WalkLD";

		D3DXMatrixScaling(&matScale, -m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);

	}
	//오른 대각선 LD

	else if (m_tInfo.vDir.x > 0 && m_tInfo.vDir.y < 0)
	{
		StateKey = L"WalkLU";

		D3DXMatrixScaling(&matScale, -m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);


	}

	else
	{
		StateKey = L"Stand";
		D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);

	}

	if (nullptr == pTexInfo)
		return;
	//D3DXMATRIX matScale, matTrans, matWorld; 
	//D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
	//이미지 반전시, scaling 값 x or y반전 시켜서!!!




	float fDist = D3DXVec3Length(&m_tInfo.vDir);
	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);

	if (3.f > fDist)
		BestList.pop_front();
	m_tInfo.vPos += m_tInfo.vDir * CTime_Manager::Get_Instance()->Get_DeltaTime() * m_fSpeed;












}



int CPlayer::Update_GameObject()
{

	if (ObjectKey == L"TurtleShip")
		m_tFrame.fFrameEnd = 10.f;

	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{


		m_AttackState = 0;

		pMouse->Set_StateKey(L"MouseClick");
		//m_AttackState = 1;
		D3DXVECTOR3 vScroll = CScroll_Manager::Get_Instance()->Get_Scroll();
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
		//플레이어가 월드좌표에서 카메라피벗 이상 이동시
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



		pMouse->Set_Pos(vMouse);



		int PlayerIndex = pTerrain->Get_TileIndex(m_tInfo.vPos);
		int index = pTerrain->Get_TileIndex(vPt);
		int Mouseindex = pTerrain->Get_TileIndex(vMouse);
		//D3DXVECTOR3 vMouse{ float(pt.x) - vScroll.x, float(pt.y) - vScroll.y , 0.f };
		CAStar_Manager::Get_Instance()->StartAStar_Manager(m_tInfo.vPos, vMouse);
	}

	else if ((GetAsyncKeyState(VK_RBUTTON) & 0x8000) &&
		GetAsyncKeyState(VK_F1) & 0x8000)
	{

		m_AttackState = 1;

		pMouse->Set_StateKey(L"MouseAttack");

		D3DXVECTOR3 vpos = CCamera::Get_Instance()->GetPos();
		D3DXVECTOR3 vPivot = CCamera::Get_Instance()->Get_Pivoit();

		D3DXVECTOR3 vCamera = { vpos.x*vPivot.x, vpos.y*vPivot.y, 0 };
		POINT pt{};
		GetCursorPos(&pt);
		ScreenToClient(g_hWND, &pt);

		//pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo_Manager(L"Player", StateKey, (DWORD)m_tFrame.fFrameStart);
		pTerrain = dynamic_cast<CTerrain*>(CGameObject_Manager::Get_Instance()->Get_Terrain());

		D3DXVECTOR3 vPt = { float(pt.x),float(pt.y),0 };
		D3DXVECTOR3 vMouse;

		//플레이어가 월드좌표에서 카메라피벗 이상 이동시
		if (m_tInfo.vPos.x >= CCamera::Get_Instance()->GetWorld().x*vPivot.x)
			vMouse = { float(pt.x) + vCamera.x + float(pTexInfo->tImageInfo.Width)*(0.45f)
			, float(pt.y) + vCamera.y, 0.f };



		else if (m_tInfo.vPos.y >= CCamera::Get_Instance()->GetWorld().y*vPivot.y)
			vMouse = { float(pt.x) + vCamera.x
			, float(pt.y) + vCamera.y + float(pTexInfo->tImageInfo.Height)*(0.5f), 0.f };


		else
			vMouse = { float(pt.x) + vCamera.x
			, float(pt.y) + vCamera.y, 0.f };



		int PlayerIndex = pTerrain->Get_TileIndex(m_tInfo.vPos);
		int index = pTerrain->Get_TileIndex(vPt);
		int Mouseindex = pTerrain->Get_TileIndex(vMouse);


		m_fShotFPSTime += CTime_Manager::Get_Instance()->Get_DeltaTime();
		if (0.7f <= m_fShotFPSTime) //0.035 설정시 6마리 ~50fps ,4마리는 6~7fps  //8마리부턴 움직임이상현상발생
		{

			m_fShotFPSTime = 0.f;
			DashShot(vMouse,pBullet, Bullet_ID::power);
			//DashShot(vMouse, pBullet);




		}

	}
	else if ((GetAsyncKeyState(VK_RBUTTON) & 0x8000) &&
	GetAsyncKeyState(VK_F2) & 0x8000)
	{
	CSoundMgr::Get_Instance()->PlaySound(L"Bullet_Fireball_Fire1.wav", CSoundMgr::PLAYER);


	m_AttackState = 1;

	pMouse->Set_StateKey(L"MouseAttack");

	D3DXVECTOR3 vpos = CCamera::Get_Instance()->GetPos();
	D3DXVECTOR3 vPivot = CCamera::Get_Instance()->Get_Pivoit();

	D3DXVECTOR3 vCamera = { vpos.x*vPivot.x, vpos.y*vPivot.y, 0 };
	POINT pt{};
	GetCursorPos(&pt);
	ScreenToClient(g_hWND, &pt);

	//pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo_Manager(L"Player", StateKey, (DWORD)m_tFrame.fFrameStart);
	pTerrain = dynamic_cast<CTerrain*>(CGameObject_Manager::Get_Instance()->Get_Terrain());

	D3DXVECTOR3 vPt = { float(pt.x),float(pt.y),0 };
	D3DXVECTOR3 vMouse;

	//플레이어가 월드좌표에서 카메라피벗 이상 이동시
	if (m_tInfo.vPos.x >= CCamera::Get_Instance()->GetWorld().x*vPivot.x)
		vMouse = { float(pt.x) + vCamera.x + float(pTexInfo->tImageInfo.Width)*(0.45f)
		, float(pt.y) + vCamera.y, 0.f };



	else if (m_tInfo.vPos.y >= CCamera::Get_Instance()->GetWorld().y*vPivot.y)
		vMouse = { float(pt.x) + vCamera.x
		, float(pt.y) + vCamera.y + float(pTexInfo->tImageInfo.Height)*(0.5f), 0.f };


	else
		vMouse = { float(pt.x) + vCamera.x
		, float(pt.y) + vCamera.y, 0.f };



	int PlayerIndex = pTerrain->Get_TileIndex(m_tInfo.vPos);
	int index = pTerrain->Get_TileIndex(vPt);
	int Mouseindex = pTerrain->Get_TileIndex(vMouse);


	m_fShotFPSTime += CTime_Manager::Get_Instance()->Get_DeltaTime();
	if (0.7f <= m_fShotFPSTime) //0.035 설정시 6마리 ~50fps ,4마리는 6~7fps  //8마리부턴 움직임이상현상발생
	{

		m_fShotFPSTime = 0.f;
		DashShot(vMouse, pBullet, Bullet_ID::fire);
		//DashShot(vMouse, pBullet);




	}

	}



	else if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
	{
	
	CSoundMgr::Get_Instance()->PlaySound(L"Bullet_Arrow_Fire1.wav", CSoundMgr::PLAYER);

		m_AttackState = 1;

		pMouse->Set_StateKey(L"MouseAttack");

		D3DXVECTOR3 vpos = CCamera::Get_Instance()->GetPos();
		D3DXVECTOR3 vPivot = CCamera::Get_Instance()->Get_Pivoit();

		D3DXVECTOR3 vCamera = { vpos.x*vPivot.x, vpos.y*vPivot.y, 0 };
		POINT pt{};
		GetCursorPos(&pt);
		ScreenToClient(g_hWND, &pt);

		pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo_Manager(L"Player", StateKey, (DWORD)m_tFrame.fFrameStart);
		pTerrain = dynamic_cast<CTerrain*>(CGameObject_Manager::Get_Instance()->Get_Terrain());

		D3DXVECTOR3 vPt = { float(pt.x),float(pt.y),0 };
		D3DXVECTOR3 vMouse;

		//플레이어가 월드좌표에서 카메라피벗 이상 이동시
		if (m_tInfo.vPos.x >= CCamera::Get_Instance()->GetWorld().x*vPivot.x)
			vMouse = { float(pt.x) + vCamera.x + float(pTexInfo->tImageInfo.Width)*(0.45f)
		   , float(pt.y) + vCamera.y, 0.f };



		else if (m_tInfo.vPos.y >= CCamera::Get_Instance()->GetWorld().y*vPivot.y)
			vMouse = { float(pt.x) + vCamera.x
		   , float(pt.y) + vCamera.y + float(pTexInfo->tImageInfo.Height)*(0.5f), 0.f };


		else
			vMouse = { float(pt.x) + vCamera.x
	   , float(pt.y) + vCamera.y, 0.f };



		int PlayerIndex = pTerrain->Get_TileIndex(m_tInfo.vPos);
		int index = pTerrain->Get_TileIndex(vPt);
		int Mouseindex = pTerrain->Get_TileIndex(vMouse);


		m_fShotFPSTime += CTime_Manager::Get_Instance()->Get_DeltaTime();
		if (0.3f <= m_fShotFPSTime) //0.035 설정시 6마리 ~50fps ,4마리는 6~7fps  //8마리부턴 움직임이상현상발생
		{

			m_fShotFPSTime = 0.f;
			Shot(vMouse);
		}











	}


	else
	{
		D3DXVECTOR3 vpos = CCamera::Get_Instance()->GetPos();
		D3DXVECTOR3 vPivot = CCamera::Get_Instance()->Get_Pivoit();
		D3DXVECTOR3 vCamera = { vpos.x, vpos.y, 0 };
		POINT pt{};
		GetCursorPos(&pt);
		ScreenToClient(g_hWND, &pt);

		//Screento
		//pTerrain = dynamic_cast<CTerrain*>(CGameObject_Manager::Get_Instance()->Get_Terrain());

		D3DXVECTOR3 vPt = { float(pt.x),float(pt.y),0 };
		vMouse = { float(pt.x) + vCamera.x, float(pt.y) + vCamera.y, 0.f };



		pMouse->Set_Pos(vMouse);
		pMouse->Set_StateKey(L"MouseStand");
		//StateKey = L"Stand";
	}
	//Late_Update_GameObject();
	return OBJ_NOEVENT;
}
void CPlayer::Late_Update_GameObject()
{

	FrameMove(0.5f);

	if (m_AttackState == 0)
		MovePlayer();

	if (m_AttackState==0 && CAStar_Manager::Get_Instance()->Get_BestList().empty())
		StateKey = L"Stand";
	



}

void CPlayer::Render_GameObject()
{

	pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo_Manager(ObjectKey, StateKey, (DWORD)m_tFrame.fFrameStart);

	fCenterX = pTexInfo->tImageInfo.Width >> 1;
	fCenterY = pTexInfo->tImageInfo.Height >> 1;

	D3DXVECTOR3 tPos = m_tInfo.vPos; //- m_tInfo.vSize;// * m_tPivot;

	tPos -= CCamera::Get_Instance()->GetPos();
	//else
	//	tPos -= CCamera::Get_Instance()->GetPos();


	//m_ColliderInfo[0] = { tPos.x - 150 ,tPos.y - 100 };
	//m_ColliderInfo[1] = { m_ColliderInfo[0].x + 300,tPos.y - 100 };
	//m_ColliderInfo[2] = { m_ColliderInfo[1].x,tPos.y + 120 };
	//m_ColliderInfo[3] = { m_ColliderInfo[0].x,m_ColliderInfo[2].y };
	//m_ColliderInfo[4] = { tPos.x - 150 ,tPos.y - 100 };

	m_ColliderInfo[0] = { tPos.x - 75 ,tPos.y - 50 };
	m_ColliderInfo[1] = { m_ColliderInfo[0].x + 150,tPos.y - 50 };
	m_ColliderInfo[2] = { m_ColliderInfo[1].x,m_ColliderInfo[1].y + 120 };
	m_ColliderInfo[3] = { m_ColliderInfo[0].x,m_ColliderInfo[2].y };
	m_ColliderInfo[4] = { tPos.x - 75 ,tPos.y - 50 };

	D3DXMatrixTranslation(&matTrans, tPos.x, tPos.y, 0.f);
	//D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);

	//D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x + CScroll_Manager::Get_Instance()->Get_Scroll(CScroll_Manager::eSB_HORZ), m_tInfo.vPos.y + CScroll_Manager::Get_Instance()->Get_Scroll(CScroll_Manager::eSB_VERT), 0.f);
	matWorld = matScale * matTrans;
	//pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo_Manager(L"Player", L"Stand", (DWORD)m_tFrame.fFrameStart);
	 //fCenterX = pTexInfo->tImageInfo.Width >> 1; 
	 //fCenterY = pTexInfo->tImageInfo.Height >> 1; 



	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
	CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	//CGraphic_Device::Get_Instance()->Get_Sprite()->End();
	////D3DXVECTOR2 vLine[5]{ {m_ColliderInfo.left,}, {200.f, 100.f},{ 200.f, 200.f },{ 100.f, 200.f },{ 100.f, 100.f }, };
	////CGraphic_Device::Get_Instance()->Get_Line()->SetWidth(20); 
	//
	//CGraphic_Device::Get_Instance()->Get_Line()->Draw(m_ColliderInfo, 5, D3DCOLOR_ARGB(255, 0, 0, 0));
	//CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);

}

void CPlayer::Release_GameObject()
{
	CAStar_Manager::Destroy_Instance();

}

HRESULT CPlayer::Shot(D3DXVECTOR3& GoalPos)
{
	m_AttackState = 1;

	m_tInfo.vDir = GoalPos - m_tInfo.vPos;

	int index = pTerrain->Get_TileIndex(m_tInfo.vPos);
	int Targetindex = pTerrain->Get_TileIndex(GoalPos);

	if (abs(Targetindex - index) % (TILEX * 2) == 0 && m_tInfo.vDir.y > 0)
	{
		StateKey = L"Attack"; //Down

		D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);

	}
	else if (abs(Targetindex - index) % (TILEX * 2) == 0 && m_tInfo.vDir.y < 0) //up
	{
		StateKey = L"AttackUp";

		D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);



	}
	else if (m_tInfo.vDir.x < 0 && abs((Targetindex - index)) < 10)
	{
		StateKey = L"AttackLeft";

		D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);

	}
	else if (m_tInfo.vDir.x > 0 && abs((Targetindex - index)) < 10)
	{
		StateKey = L"AttackLeft";

		D3DXMatrixScaling(&matScale, -m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);

	}
	//왼쪽 대각선 LU
	else if (m_tInfo.vDir.x < 0 && m_tInfo.vDir.y >0)
	{
		StateKey = L"AttackLD";

		D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);

	}
	//왼쪽 대각선 LD

	else if (m_tInfo.vDir.x < 0 && m_tInfo.vDir.y < 0)
	{
		StateKey = L"AttackLU";
		D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);


	}

	//오른 대각선 LU
	else if (m_tInfo.vDir.x > 0 && m_tInfo.vDir.y > 0)
	{
		StateKey = L"AttackLD";

		D3DXMatrixScaling(&matScale, -m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);

	}
	//오른 대각선 LD

	else if (m_tInfo.vDir.x > 0 && m_tInfo.vDir.y < 0)
	{
		StateKey = L"AttackLU";

		D3DXMatrixScaling(&matScale, -m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);


	}


	pBullet = new Bullet_Player;


	//pBullet= m_pGameObject_Manager->Get_PlayerBullet();
	dynamic_cast<Bullet_Player*>(pBullet)->Set_targetPos(m_tInfo.vPos, GoalPos);
	dynamic_cast<Bullet_Player*>(pBullet)->Set_Life(1);
	if (FAILED(pBullet->Ready_GameObject()))
		return E_FAIL;

	m_pGameObject_Manager->Add_GameObject_Manager(ID::PlayerBullet, pBullet);

	//pBullet->Release_GameObject();
	return S_OK;

}

HRESULT CPlayer::DashShot(D3DXVECTOR3 &GoalPos,CGameObject* pBullet, int ArrowNumber)
{
	m_AttackState = 1;

	m_tInfo.vDir = GoalPos - m_tInfo.vPos;

	int index = pTerrain->Get_TileIndex(m_tInfo.vPos);
	int Targetindex = pTerrain->Get_TileIndex(GoalPos);

	if (abs(Targetindex - index) % (TILEX * 2) == 0 && m_tInfo.vDir.y > 0)
	{
		StateKey = L"PlayerDash"; //Down
		//D3DXVECTOR3 GoalPos2 = { GoalPos.x-60,GoalPos.y,0 };
		//D3DXVECTOR3 GoalPos3 = { GoalPos.x + 60,GoalPos.y,0 };
		//
		//
		//dynamic_cast<PowerBullet_Player*>(pBullet2)->Set_targetPos(m_tInfo.vPos, GoalPos2);
		//dynamic_cast<PowerBullet_Player*>(pBullet)->Set_targetPos(m_tInfo.vPos, GoalPos);
		//dynamic_cast<PowerBullet_Player*>(pBullet3)->Set_targetPos(m_tInfo.vPos, GoalPos3);

		D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);

	}
	else if (abs(Targetindex - index) % (TILEX * 2) == 0 && m_tInfo.vDir.y < 0) //up
	{
		StateKey = L"PlayerDashUp";

		D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);



	}
	else if (m_tInfo.vDir.x < 0 && abs((Targetindex - index)) < 10)
	{
		StateKey = L"PlayerDashLeft";

		D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);

	}
	else if (m_tInfo.vDir.x > 0 && abs((Targetindex - index)) < 10)
	{
		StateKey = L"PlayerDashLeft";

		D3DXMatrixScaling(&matScale, -m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);

	}
	//왼쪽 대각선 LU
	else if (m_tInfo.vDir.x < 0 && m_tInfo.vDir.y >0)
	{
		StateKey = L"PlayerDashLD";

		D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);

	}
	//왼쪽 대각선 LD

	else if (m_tInfo.vDir.x < 0 && m_tInfo.vDir.y < 0)
	{
		StateKey = L"PlayerDashLU";
		D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);


	}

	//오른 대각선 LU
	else if (m_tInfo.vDir.x > 0 && m_tInfo.vDir.y > 0)
	{
		StateKey = L"PlayerDashLD";

		D3DXMatrixScaling(&matScale, -m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);

	}
	//오른 대각선 LD

	else if (m_tInfo.vDir.x > 0 && m_tInfo.vDir.y < 0)
	{
		StateKey = L"PlayerDashLU";

		D3DXMatrixScaling(&matScale, -m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);


	}


	if(ArrowNumber==Bullet_ID::fire)
	{
		pBullet = new FireArrow_Player;

		dynamic_cast<FireArrow_Player*>(pBullet)->Set_targetPos(m_tInfo.vPos, GoalPos);
		dynamic_cast<FireArrow_Player*>(pBullet)->Set_Life(1);
		if (FAILED(pBullet->Ready_GameObject()))
			return E_FAIL;

		m_pGameObject_Manager->Add_GameObject_Manager(ID::PlayerBullet, pBullet);
	
	}

	else if (ArrowNumber == Bullet_ID::power)
	{
		pSkill = new CSkill1_Player;


		//pBullet= m_pGameObject_Manager->Get_PlayerBullet();
		dynamic_cast<CSkill1_Player*>(pSkill)->Set_targetPos(m_tInfo.vPos, GoalPos);
		dynamic_cast<CSkill1_Player*>(pSkill)->Set_Life(1);
		if (FAILED(pSkill->Ready_GameObject()))
			return E_FAIL;

		m_pGameObject_Manager->Add_GameObject_Manager(ID::Effect, pSkill);
		//if (0.02f <= m_fBulletFPSTime) //0.035 설정시 6마리 ~50fps ,4마리는 6~7fps  //8마리부턴 움직임이상현상발생
		{

			//m_fBulletFPSTime = 0.f;



			pBullet = new PowerBullet_Player;

			dynamic_cast<PowerBullet_Player*>(pBullet)->Set_targetPos(m_tInfo.vPos, GoalPos);
			dynamic_cast<PowerBullet_Player*>(pBullet)->Set_Life(1);
			if (FAILED(pBullet->Ready_GameObject()))
				return E_FAIL;

			m_pGameObject_Manager->Add_GameObject_Manager(ID::PlayerBullet, pBullet);

		}
	}
	else if (ArrowNumber == Bullet_ID::water)
	{

	}


	


	
	
	return S_OK;
}


