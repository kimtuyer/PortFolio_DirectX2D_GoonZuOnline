// MapTool.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MFCTool.h"
#include "MapTool.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "MFCToolView.h"
#include "Terrain.h"
#include "FileInfo.h"


// CMapTool ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CMapTool, CDialog)

CMapTool::CMapTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_MAPTOOL, pParent)
	, m_byDrawID(0)
{

}

CMapTool::~CMapTool()
{
}

void CMapTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
	DDX_Control(pDX, IDC_PICTURE, m_Picture);
}


BEGIN_MESSAGE_MAP(CMapTool, CDialog)
	ON_WM_DROPFILES()
	ON_LBN_SELCHANGE(IDC_LIST1, &CMapTool::OnLbnSelchangeTile)
	ON_BN_CLICKED(IDC_BUTTON1, &CMapTool::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON6, &CMapTool::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON2, &CMapTool::OnBnClickedAdd_Mapobject)
END_MESSAGE_MAP()


// CMapTool �޽��� ó�����Դϴ�.


void CMapTool::OnDropFiles(HDROP hDropInfo)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	int iSize = DragQueryFile(hDropInfo, 0xffffffff, nullptr, 0); 

	TCHAR szBuf[MAX_PATH] = L""; 
	CString wstrRelativePath; 
	for (int i = 0 ; i < iSize ; ++i)
	{
		DragQueryFile(hDropInfo, i, szBuf, MAX_PATH); 
		wstrRelativePath = CFileInfo::ConvertRelativePath(szBuf); 
		CString wstrFileNameAndExtension = PathFindFileName(szBuf); 
		TCHAR szFileName[MAX_PATH]{}; 
		lstrcpy(szFileName, wstrFileNameAndExtension.GetString()); 

		PathRemoveExtension(szFileName);

		m_ListBox.AddString(szFileName);
	}
	m_ListBox.SetHorizontalExtent(500); 
	UpdateData(FALSE); 
	CDialog::OnDropFiles(hDropInfo);
}


void CMapTool::OnLbnSelchangeTile()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	UpdateData(TRUE);
	int iIndex = m_ListBox.GetCurSel(); 
	CString wstrFileName;
	m_ListBox.GetText(iIndex, wstrFileName);
	int i = 0;
	for ( ; i < wstrFileName.GetLength(); ++i)
	{
		// isdigit 0~ 9������ �������� �ƴ����� �Ǻ����ִ� �Լ�. 
		if(isdigit(wstrFileName[i]))
			break;
	}
	wstrFileName.Delete(0, i);
	m_byDrawID = _ttoi(wstrFileName.GetString());

	CGraphic_Device::Get_Instance()->Render_Begin(); 
	D3DXMATRIX matScale, matTrans, matWorld; 
	float fRatioX = float(WINCX) / TILECX; 
	float fRatioY = float(WINCY) / TILECY; 
	D3DXMatrixScaling(&matScale, fRatioX, fRatioY, 0.f); 
	D3DXMatrixTranslation(&matTrans, 400.f, 300.f, 0.f); 
	matWorld = matScale * matTrans; 
	
	const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo_Manager(L"Terrain", L"Tile", m_byDrawID); 
	if (nullptr == pTexInfo)
		return; 
	float fCenterX = pTexInfo->tImageInfo.Width >> 1; 
	float fCenterY = pTexInfo->tImageInfo.Height >> 1; 

	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld); 
	CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255)); 

	CGraphic_Device::Get_Instance()->Render_End(m_Picture.m_hWnd);
	UpdateData(FALSE);
}

//Save
void CMapTool::OnBnClickedButton1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CFileDialog Dlg(FALSE, // �ٸ��̸����� ����. ���� TRUE ���� ����. 
		L"dat",// ����Ʈ Ȯ���� 
		L"*.dat",// ����Ʈ ���� �̸� 
		OFN_OVERWRITEPROMPT);// ����� ��� �޽��� ����ְڴ�. 
	TCHAR szCurDir[MAX_PATH]{};
	GetCurrentDirectory(MAX_PATH, szCurDir);
	//D:\�ں���\118C\D2D\Framework_v1
	PathRemoveFileSpec(szCurDir);
	lstrcat(szCurDir, L"\\Data");
	Dlg.m_ofn.lpstrInitialDir = szCurDir;
	if (IDOK == Dlg.DoModal())
	{
		CString wstrFilePath = Dlg.GetPathName();
		HANDLE hFile = CreateFile(wstrFilePath.GetString(), GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
		if (INVALID_HANDLE_VALUE == hFile)
			return;
		CMainFrame* pMain = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
		CMFCToolView* pView = dynamic_cast<CMFCToolView*>(pMain->m_MainSplitter.GetPane(0, 1));
		const vector<TILE*>& vecTile = pView->m_pTerrain->Get_VecTile();
		DWORD dwByte = 0; 
		for (auto& pTile : vecTile)
			WriteFile(hFile, pTile, sizeof(TILE), &dwByte, nullptr); 

		CloseHandle(hFile); 
	}
}

//Load
void CMapTool::OnBnClickedButton6()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CFileDialog Dlg(TRUE, // �ٸ��̸����� ����. ���� TRUE ���� ����. 
		L"dat",// ����Ʈ Ȯ���� 
		L"*.dat",// ����Ʈ ���� �̸� 
		OFN_OVERWRITEPROMPT);// ����� ��� �޽��� ����ְڴ�. 
	TCHAR szCurDir[MAX_PATH]{};
	GetCurrentDirectory(MAX_PATH, szCurDir);
	//D:\�ں���\118C\D2D\Framework_v1
	PathRemoveFileSpec(szCurDir);
	lstrcat(szCurDir, L"\\Data");
	Dlg.m_ofn.lpstrInitialDir = szCurDir;
	if (IDOK == Dlg.DoModal())
	{
		CString wstrFilePath = Dlg.GetPathName();
		HANDLE hFile = CreateFile(wstrFilePath.GetString(), GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
		if (INVALID_HANDLE_VALUE == hFile)
			return;
		CMainFrame* pMain = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
		CMFCToolView* pView = dynamic_cast<CMFCToolView*>(pMain->m_MainSplitter.GetPane(0, 1));
		pView->m_pTerrain->Release_Terrain(); 
		DWORD dwByte = 0;
		TILE* pTile = nullptr; 
		while (true)
		{
			pTile = new TILE; 
			ReadFile(hFile, pTile, sizeof(TILE), &dwByte, nullptr);

			if (0 == dwByte)
			{
				Safe_Delete(pTile); 
				break; 
			}
			pView->m_pTerrain->Set_Tile(pTile); 
		}
		pView->Invalidate(FALSE); 
		CloseHandle(hFile); 
	}
}


void CMapTool::OnBnClickedAdd_Mapobject()
{
	m_tMapObject.ShowWindow(SW_SHOW);

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


BOOL CMapTool::OnInitDialog()
{
	if (nullptr == m_tMapObject.GetSafeHwnd())
		m_tMapObject.Create(IDD_MapObject);
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
