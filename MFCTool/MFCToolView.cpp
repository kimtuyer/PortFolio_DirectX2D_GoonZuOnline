
// MFCToolView.cpp : CMFCToolView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "MFCTool.h"
#endif

#include "MFCToolDoc.h"
#include "MFCToolView.h"
#include "MainFrm.h"
#include "Terrain.h"
#include "MapUnit.h"
#include "MapUnit_Summon.h"
#include "Form.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCToolView
HWND g_hWND; 
IMPLEMENT_DYNCREATE(CMFCToolView, CScrollView)

BEGIN_MESSAGE_MAP(CMFCToolView, CScrollView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_MBUTTONDOWN()
	ON_WM_MOUSEMOVE()
//	ON_WM_PAINT()
END_MESSAGE_MAP()

// CMFCToolView ����/�Ҹ�

CMFCToolView::CMFCToolView()
	:m_pGraphic_Device(CGraphic_Device::Get_Instance())
	, m_pTerrain(nullptr)
	//, m_pSingle_Texture(nullptr)
{
	m_pos = { 0,0 };
	m_pos2 = { 0,0 };
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CMFCToolView::~CMFCToolView()
{
	Safe_Delete(m_pTerrain);
	CTexture_Manager::Destroy_Instance();
	m_pGraphic_Device->Destroy_Instance(); 
}

BOOL CMFCToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CMFCToolView �׸���

void CMFCToolView::OnDraw(CDC* /*pDC*/)
{
	CMFCToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	m_pGraphic_Device->Render_Begin(); 

	//SeaMap Sea4
	
	//const TEXINFO* pTexInfo2 = CTexture_Manager::Get_Instance()->Get_TexInfo_Manager(L"StartMap", L"Map");
	const TEXINFO* pTexInfo2 = CTexture_Manager::Get_Instance()->Get_TexInfo_Manager(L"SeaMap1", L"Sea1");
	//1�� �ػ���
	//1.5, 1.5
	//const TEXINFO* pTexInfo2 = CTexture_Manager::Get_Instance()->Get_TexInfo_Manager(L"SeaMap2", L"Sea2");
	//2�� ��ȭ�� ����


	//const TEXINFO* pTexInfo2 = CTexture_Manager::Get_Instance()->Get_TexInfo_Manager(L"StartMap", L"Map");
	
	//const TEXINFO* pTexInfo2 = CTexture_Manager::Get_Instance()->Get_TexInfo_Manager(L"DAEMA1", L"DAEMA1");
	//2.1 ,1.3 

	//const TEXINFO* pTexInfo2 = CTexture_Manager::Get_Instance()->Get_TexInfo_Manager(L"DAEMA2", L"DAEMA2");



	if (nullptr == pTexInfo2)
		return;



	D3DXMATRIX matScale, matTrans, matWorld;
	D3DXMatrixScaling(&matScale, 1.5, 1.5, 0.f);
	D3DXMatrixTranslation(&matTrans, 0 - GetScrollPos(SB_HORZ), 0 - GetScrollPos(SB_VERT), 0.f);
	matWorld = matScale * matTrans;

	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
	m_pGraphic_Device->Get_Sprite()->Draw(pTexInfo2->pTexture,nullptr, nullptr, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	//CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo2->pTexture, nullptr, &D3DXVECTOR3(0, 0, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));


	if (m_pos.x != 0 && m_pos2.x !=0)
	{

	CGraphic_Device::Get_Instance()->Get_Sprite()->End();
	D3DXVECTOR2 vLine[5]{ { m_pos.x,m_pos.y}, {m_pos2.x,m_pos.y},{ m_pos2.x,m_pos.y+m_pos2.x-m_pos.x},{m_pos.x, m_pos.y + m_pos2.x - m_pos.x },{ m_pos.x,m_pos.y }, };
	//CGraphic_Device::Get_Instance()->Get_Line()->SetWidth(20); 

	CGraphic_Device::Get_Instance()->Get_Line()->Draw(vLine, 5, D3DCOLOR_ARGB(255, 0, 0, 0));
	CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);
	}



	if (!m_pMapObject->m_vecMapObject.empty())
		m_pMapObject->Render_MapUnit();
	if (!m_pMapUnit_Summon->m_vecMapObject.empty())
		m_pMapUnit_Summon->Render_MapUnit_Summon();


	m_pTerrain->Render_Terrain();
	m_pGraphic_Device->Render_End(); 
}


// CMFCToolView �μ�

BOOL CMFCToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CMFCToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CMFCToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CMFCToolView ����

#ifdef _DEBUG
void CMFCToolView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CMFCToolView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CMFCToolDoc* CMFCToolView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCToolDoc)));
	return (CMFCToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCToolView �޽��� ó����


void CMFCToolView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	++m_count;
	if (m_count == 1)
	{

		m_pos.x = point.x;
		m_pos.y = point.y;

	}
	else if (m_count == 2)
	{

		m_pos2.x = point.x;
		m_pos2.y = point.y;

	}
	else if (m_count > 2)
	{
		m_pos.x = point.x;
		m_pos.y = point.y;

		m_pos2.x = 0;
		m_pos2.y = 0;




		m_count = 1;
	}

	

	D3DXVECTOR3 vMouse{ float(point.x) + GetScrollPos(SB_HORZ), float(point.y) + GetScrollPos(SB_VERT), 0.f };
	// �� ���� byDrawID ������ 
	// WinApp -> MainFrame -> SecondSplitter -> Form -> MapTool -> byDrawID 
	CMainFrame* pMain = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd()); 
	CForm* pForm = dynamic_cast<CForm*>(pMain->m_SecondSplitter.GetPane(1, 0)); 
	BYTE byDrawID = pForm->m_tMapTool.m_byDrawID; 

	//pForm->m_tMapTool.m_tMapObject.OnLbnSelchangeList1

	m_pTerrain->Tile_Change_Terrain(vMouse, byDrawID,1);

	//�÷��̾ �������� ���콺��ǥ�� Ÿ��/������Ʈ �Ѵ� �ʿ���.
	//
	//���� ���콺 l��ư�� �ߺ�,
	
	//m_pMapObject->Update_MapUnit(vMouse);


	Invalidate(FALSE);
	CScrollView::OnLButtonDown(nFlags, point);
}


void CMFCToolView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
	SetScrollSizes(MM_TEXT, CSize(TILECX * TILEX, (TILECY >> 1) * TILEY)); 
	g_hWND = m_hWnd; 
	//GetScrollPos(); 
	// â�� ũ�⸦ �����Ҳ���.. â�� ũ�⸦ �����Ϸ��� ? MainFrame �� ���̸� ���;� �ؿ�. 
	// �װ͵� ����� �غ��߰ڳ׿� ? 
	// CMainFrame, CView, CDocument 
	// CWinApp 
	CMainFrame* pMain = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd()); 
	RECT rcMain{}; 
	pMain->GetWindowRect(&rcMain); 
	SetRect(&rcMain, 0, 0, rcMain.right - rcMain.left, rcMain.bottom - rcMain.top); 
// 	rcMain.right = rcMain.right - rcMain.left; 
// 	rcMain.left = 0; 
// 	rcMain.bottom = rcMain.bottom - rcMain.top; 
// 	rcMain.top = 0;
	RECT rcView{}; 
	GetClientRect(&rcView); 
	int iGapX = rcMain.right - rcView.right; //1440 - 1420 = 20
	int iGapY = rcMain.bottom - rcView.bottom; 

	pMain->SetWindowPos(nullptr, 0, 0, WINCX + iGapX + 1, WINCY + iGapY + 1, SWP_NOMOVE); 

	if (FAILED(m_pGraphic_Device->Ready_Graphic_Device()))
	{
		ERR_MSG(L"Ready_Graphic_Device");
		return;
	}

	//m_pSingle_Texture = new CSingle_Texture; 
	//if (FAILED(m_pSingle_Texture->Insert_Texture(L"../Texture/Cube.png")))
		//return; 
	// L"../Texture/Cube.png", L"Cube"
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI, 
		L"../Texture/Stage/Player/Attack/AKIHA_AKI01_00%d.png",
		L"Player", L"Attack", 6)))
		return; 
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Player/Dash/AKIHA_AKI13_00%d.png",
		L"Player", L"Dash", 11)))
		return;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_SINGLE,
		L"../Texture/Stage/Tile/Town.png", L"StartMap", L"Map", 1)))
		return;


	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_SINGLE,
			L"../Texture/Stage/Tile/Sea3.png", L"SeaMap1", L"Sea1", 1)))
		return;


	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_SINGLE,
			L"../Texture/Stage/Tile/Sea4.png", L"SeaMap2", L"Sea2", 1)))
		return ;


	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_SINGLE,
		L"../Texture/Stage/Tile/0.bmp", L"DAEMA1", L"DAEMA1", 1)))
		return;


	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_SINGLE,
		L"../Texture/Stage/Tile/1.bmp", L"DAEMA2", L"DAEMA2", 1)))
		return;


	m_pTerrain = new CTerrain;
	if (FAILED(m_pTerrain->Ready_Terrain()))
		return;
	m_pTerrain->Set_View(this); 

	m_pMapObject = new MapUnit;
	if (FAILED(m_pMapObject->Ready_MapUnit()))
		return;
	m_pMapObject->Set_View(this);

	m_pMapUnit_Summon = new MapUnit_Summon;
	if (FAILED(m_pMapUnit_Summon->Ready_MapUnit_Summon()))
		return;
	m_pMapUnit_Summon->Set_View(this);




	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
}


void CMFCToolView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	switch (nChar)
	{
	case VK_F1:
	{

		if (!m_pMapObject->m_vecMapObject.empty())
			m_pMapObject->m_vecMapObject.pop_back();
		break;
	}
	case VK_F2:
	{
		if (!m_pMapUnit_Summon->m_vecMapObject.empty())

			m_pMapUnit_Summon->m_vecMapObject.pop_back();
		break;

	}
	case VK_SPACE:
	{
		POINT point;
		GetCursorPos(&point);
		ScreenToClient(&point);
		break;

	}
	case 65:
	{

	}
	break;
	}


	Invalidate(FALSE);

	CScrollView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CMFCToolView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	// �� ���� byDrawID ������ 
	// WinApp -> MainFrame -> SecondSplitter -> Form -> MapTool -> byDrawID 



	D3DXVECTOR3 vMouse{ float(point.x) + GetScrollPos(SB_HORZ), float(point.y) + GetScrollPos(SB_VERT), 0.f };
	CMainFrame* pMain = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());

	CForm* pForm2 = dynamic_cast<CForm*>(pMain->m_SecondSplitter.GetPane(1, 0));
	


	BYTE byDrawID2 = pForm2->m_tMapTool.m_tMapObject.m_byDrawID;
	m_pMapObject->Change_MapUnit(vMouse, byDrawID2, 1);


	Invalidate(FALSE);

	CScrollView::OnRButtonDown(nFlags, point);
}


void CMFCToolView::OnMButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	D3DXVECTOR3 vMouse{ float(point.x) + GetScrollPos(SB_HORZ), float(point.y) + GetScrollPos(SB_VERT), 0.f };
	// �� ���� byDrawID ������ 
	// WinApp -> MainFrame -> SecondSplitter -> Form -> MapTool -> byDrawID 
	CMainFrame* pMain = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());

	//pMain->m_MainSplitter.GetPane(0, 1)->get



	CForm* pForm2 = dynamic_cast<CForm*>(pMain->m_SecondSplitter.GetPane(1, 0));



	BYTE byDrawID2 = pForm2->m_tUnitTool.m_byDrawID;
	m_pMapUnit_Summon->Change_MapUnit_Summon(vMouse, byDrawID2, 1);

	Invalidate(FALSE);
	CScrollView::OnMButtonDown(nFlags, point);
}


void CMFCToolView::OnMouseMove(UINT nFlags, CPoint point)
{
	//m_pos = point;
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
        		//m_pos = point;
	}
	CScrollView::OnMouseMove(nFlags, point);
}


//void CMFCToolView::OnPaint()
//{
//	CPaintDC dc(this); // device context for painting
//					   // TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
//					   // �׸��� �޽����� ���ؼ��� CScrollView::OnPaint()��(��) ȣ������ ���ʽÿ�.
//}
