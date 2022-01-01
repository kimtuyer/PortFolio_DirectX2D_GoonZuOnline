#include "stdafx.h"
#include "CCamera.h"
#include "GameObject.h"
IMPLEMENT_SINGLETON(CCamera)


CCamera::CCamera() :
	m_pTarget(nullptr)
{
}

CCamera::~CCamera()
{

	//SAFE_RELEASE(m_pTarget);
}

void CCamera::SetTarget(CGameObject * pObj)
{
	if (m_pTarget)
		m_pTarget = nullptr;

	
	m_pTarget = pObj;

	//카메라가 더이상 타겟을 따라가지 않고 고정할 경우 대비 m_pTarget을 null처리
	//예외처리 상황 만들어둠
	
}

bool CCamera::Init(const D3DXVECTOR3 & tPos, const RESOLUTION & tRS, const RESOLUTION & tWorldRS)
{
	m_tPos = tPos; //카메라영역의 좌 상단점을 표시
	m_tClientRS = tRS;
	m_tWorldRS = tWorldRS;
	WorldRS = { float(tWorldRS.iW),float(tWorldRS.iH) };
	m_tPivot = { 0.7f,0.5f,1 };
	return true;
}

void CCamera::Input(float fDeltaTime)
{
}

void CCamera::Render(float fDeltaTime)
{
	float fLeftArea = m_tClientRS.iW*m_tPivot.x;
	float fRightArea = m_tClientRS.iW - fLeftArea;
	float fTopArea = m_tClientRS.iH* m_tPivot.y;
	float fBottomArea = m_tClientRS.iH - fTopArea;


	m_ColliderInfo[0] = { fLeftArea ,fTopArea };
	m_ColliderInfo[1] = { fRightArea,fTopArea };
	m_ColliderInfo[2] = { fRightArea,fBottomArea };
	m_ColliderInfo[3] = { fLeftArea,fBottomArea };
	m_ColliderInfo[4] = { fLeftArea ,fTopArea };

	//D3DXMatrixTranslation(&matTrans, tPos.x, tPos.y, 0.f);
	//D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);

	//D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x + CScroll_Manager::Get_Instance()->Get_Scroll(CScroll_Manager::eSB_HORZ), m_tInfo.vPos.y + CScroll_Manager::Get_Instance()->Get_Scroll(CScroll_Manager::eSB_VERT), 0.f);
	//matWorld = matScale * matTrans;
	//pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo_Manager(L"Player", L"Stand", (DWORD)m_tFrame.fFrameStart);
	 //fCenterX = pTexInfo->tImageInfo.Width >> 1; 
	 //fCenterY = pTexInfo->tImageInfo.Height >> 1; 


	//D3DXVECTOR2 vLine[5]{ {m_ColliderInfo.left,}, {200.f, 100.f},{ 200.f, 200.f },{ 100.f, 200.f },{ 100.f, 100.f }, };
	//CGraphic_Device::Get_Instance()->Get_Line()->SetWidth(20); 

	//CGraphic_Device::Get_Instance()->Get_Line()->Draw(m_ColliderInfo, 5, D3DCOLOR_ARGB(255, 0, 0, 0));
	//CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);

}

void CCamera::Update(float fDeltaTime)
{
	if (m_pTarget)
	{
		//if (m_pTarget->GetScene())
		//{
		//
		//}
		m_tCameraLoc = 1;
		D3DXVECTOR3 tPos = m_pTarget->Get_Info().vPos;
		D3DXVECTOR3 tPivot = { 0,0,0 };

		D3DXVECTOR3	tSize;
			tSize.y = m_pTarget->Get_TexInfo()->tImageInfo.Height;
			tSize.x = m_pTarget->Get_TexInfo()->tImageInfo.Width;

		//플레이어 타겟
	 fL = tPos.x - tPivot.x* tSize.x;
	 fT = tPos.y - tPivot.y* tSize.y;
	 fR = fL + tSize.x;
	 fB = fT + tSize.y;

		//카메라 안 클라이언트 영역
	fLeftArea = m_tClientRS.iW*m_tPivot.x;
	fRightArea = m_tClientRS.iW-fLeftArea;
	fTopArea = m_tClientRS.iH* m_tPivot.y;
	fBottomArea = m_tClientRS.iH- fTopArea;

		//플레이어가 카메라영역 왼쪽바깥위치
		if (tPos.x <= fLeftArea)
			m_tPos.x = 0.f;
		//플레이어가 카메라영역 오른쪽 바깥위치
		else if (tPos.x >= m_tWorldRS.iW - fRightArea)
		{
			m_tPos.x = m_tWorldRS.iW - m_tClientRS.iW; 
		}


		else //카메라영역 안
			m_tPos.x = tPos.x - m_tClientRS.iW* m_tPivot.x;

		//플레이어가 카메라영역 위쪽바깥위치
		if (tPos.y<= fTopArea)
			m_tPos.y = 0.f;
		//플레이어가 카메라영역 아래쪽 바깥위치
		else if (tPos.y >= m_tWorldRS.iH -fBottomArea)
			m_tPos.y = m_tWorldRS.iH - m_tClientRS.iH;

		else //카메라영역 안
			m_tPos.y = tPos.y - m_tClientRS.iH* m_tPivot.y;







	}
}

void CCamera::Scroll(float x, float y)
{
}
