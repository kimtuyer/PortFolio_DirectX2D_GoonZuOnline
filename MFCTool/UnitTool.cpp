// UnitTool.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MFCTool.h"
#include "UnitTool.h"
#include "afxdialogex.h"
#include "FileInfo.h"
#include "MainFrm.h"
#include "MFCToolView.h"

// CUnitTool ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CUnitTool, CDialog)

CUnitTool::CUnitTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_UNITTOOL, pParent)
	, m_wstrSrc(_T(""))
	, m_wstrDst(_T(""))
	, m_wstrName(_T(""))
	, m_iAtt(0)
	, m_iDef(0)
{
}

CUnitTool::~CUnitTool()
{
	//map<wstring, UNITINFO*>::iterator& iter = m_mapUnitInfo.begin(); 

	for (pair<const wstring, UNITINFO*>& rPair : m_mapUnitInfo)
		Safe_Delete(rPair.second); 
	m_mapUnitInfo.clear(); 
}

void CUnitTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_wstrSrc);
	DDX_Text(pDX, IDC_EDIT2, m_wstrDst);
	DDX_Text(pDX, IDC_EDIT3, m_wstrName);
	DDX_Text(pDX, IDC_EDIT4, m_iAtt);
	DDX_Text(pDX, IDC_EDIT5, m_iDef);
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
	DDX_Control(pDX, IDC_RADIO1, m_Radio[����]);
	DDX_Control(pDX, IDC_RADIO2, m_Radio[����]);
	DDX_Control(pDX, IDC_RADIO3, m_Radio[����]);

	DDX_Control(pDX, IDC_CHECK1, m_CheckBox[0]);
	DDX_Control(pDX, IDC_CHECK2, m_CheckBox[1]);
	DDX_Control(pDX, IDC_CHECK3, m_CheckBox[2]);

	DDX_Control(pDX, IDC_PICTURE1, m_Picture);
	DDX_Control(pDX, IDC_COMBO2, m_combobox);
	DDX_Control(pDX, IDC_LIST2, m_ListBox2);
}


BEGIN_MESSAGE_MAP(CUnitTool, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CUnitTool::OnBnClickedSendData)
	ON_BN_CLICKED(IDC_BUTTON2, &CUnitTool::OnBnClickedAddUnitData)
	ON_LBN_SELCHANGE(IDC_LIST1, &CUnitTool::OnLbnSelchangeRenderUnitInfo)
	ON_BN_CLICKED(IDC_BUTTON3, &CUnitTool::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CUnitTool::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CUnitTool::OnBnClickedButton5)
	ON_WM_DROPFILES()
	ON_CBN_SELCHANGE(IDC_COMBO2, &CUnitTool::OnCbnSelchangeCombo2)
	ON_LBN_SELCHANGE(IDC_LIST2, &CUnitTool::OnLbnSelchangeList2)
END_MESSAGE_MAP()


// CUnitTool �޽��� ó�����Դϴ�.


void CUnitTool::OnBnClickedSendData()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE); 
	m_wstrDst = m_wstrSrc; 
	UpdateData(FALSE); 
	
}


void CUnitTool::OnBnClickedAddUnitData()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE); 
	UNITINFO* pUnitInfo = new UNITINFO{};
//	ZeroMemory(pUnitInfo, sizeof(UNITINFO));  ����ü �ȿ� wstring �� �־ ���θ޸� ���� 
	// ���� ����. 

	map<wstring, UNITINFO*>::iterator iter = m_mapUnitInfo.find(m_wstrName.GetString());
	if (m_mapUnitInfo.end() != iter)
	{
		Safe_Delete(pUnitInfo); 
		return; 
	}
	pUnitInfo->wstrName = m_wstrName; 
	//m_wstrName = pUnitInfo->wstrName;  // ��ȯ��Ģ�� �������� �ʳ�. 
	pUnitInfo->iAtt = m_iAtt; 
	pUnitInfo->iDef = m_iDef; 
	;
	for (int i = 0; i < JOBEND; ++i)
	{
		if (m_Radio[i].GetCheck())
		{
			pUnitInfo->byJob = i;
			break;
		}
	}
	if (m_CheckBox[0].GetCheck())
		pUnitInfo->byItem |= ��;
	if (m_CheckBox[1].GetCheck())
		pUnitInfo->byItem |= Ȱ; 
	if (m_CheckBox[2].GetCheck())
		pUnitInfo->byItem |= ��;

	m_mapUnitInfo.emplace(pUnitInfo->wstrName, pUnitInfo); 
	m_ListBox.AddString(pUnitInfo->wstrName);
	UpdateData(FALSE); 
}


void CUnitTool::OnLbnSelchangeRenderUnitInfo()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE); 
	//for (int i = 0; i < JOBEND; ++i)
	//{
	//	m_Radio[i].SetCheck(FALSE);
	//	m_CheckBox[i].SetCheck(FALSE); 
	//}
	int iIndex = m_ListBox.GetCurSel();
	if (LB_ERR == iIndex)
		return; 

	CString wstrUnitName;
	m_ListBox.GetText(iIndex, wstrUnitName); 
	
	//
	int i = 0;
	for (; i < wstrUnitName.GetLength(); ++i)
	{
		// isdigit 0~ 9������ �������� �ƴ����� �Ǻ����ִ� �Լ�. 
		if (isdigit(wstrUnitName[i]))
			break;
	}
	wstrUnitName.Delete(0, i);
	m_byDrawID = _ttoi(wstrUnitName.GetString());
	
	const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo_Manager(L"MapUnit_Summon", L"Summon", m_byDrawID);
	if (nullptr == pTexInfo)
		return;


	CGraphic_Device::Get_Instance()->Render_Begin();
	D3DXMATRIX matScale, matTrans, matWorld;
	float fRatioX = float(WINCX) / float(pTexInfo->tImageInfo.Width); //MAPUNIT_SUMMONCX;
	float fRatioY = float(WINCY) / float(pTexInfo->tImageInfo.Height);//MAPUNIT_SUMMONCX;
	D3DXMatrixScaling(&matScale, fRatioX, fRatioY, 0.f);
	D3DXMatrixTranslation(&matTrans, WINCX/2, WINCY/2, 0.f);
	matWorld = matScale * matTrans;

	
	float fCenterX = pTexInfo->tImageInfo.Width >> 1;
	float fCenterY = pTexInfo->tImageInfo.Height >> 1;

	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
	CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	

	CGraphic_Device::Get_Instance()->Render_End(m_Picture.m_hWnd);


	//


	map<wstring, UNITINFO*>::iterator iter = m_mapUnitInfo.find(wstrUnitName.GetString());

	if (iter == m_mapUnitInfo.end())
		return; 

	m_wstrName = iter->second->wstrName; 
	m_iAtt = iter->second->iAtt; 
	m_iDef = iter->second->iDef; 


	//m_Radio[iter->second->byJob].SetCheck(TRUE);
	// 0000 0100
	// 0000 0001 &
	// 0000 0000

	//if (iter->second->byItem & ��)
	//	m_CheckBox[0].SetCheck(TRUE); 
	//if (iter->second->byItem & Ȱ)
	//	m_CheckBox[1].SetCheck(TRUE); 
	//if (iter->second->byItem & ��)
	//	m_CheckBox[2].SetCheck(TRUE); 

	UpdateData(FALSE); 
}

// delete 
void CUnitTool::OnBnClickedButton3()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int iIndex = m_ListBox.GetCurSel(); 
	CString wstrFindName; 
	m_ListBox.GetText(iIndex, wstrFindName); 
	auto& iter_find = m_mapUnitInfo.find(wstrFindName.GetString()); 

	if (iter_find == m_mapUnitInfo.end())
		return; 

	Safe_Delete(iter_find->second); 
	m_mapUnitInfo.erase(iter_find); 

	m_ListBox.DeleteString(iIndex); 
}

// Save
void CUnitTool::OnBnClickedButton4()
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
		vector<INFO*>&vecMapObject = pView->m_pMapUnit_Summon->m_vecMapObject;
		DWORD dwByte = 0;
		for (auto& pTile : vecMapObject)
			WriteFile(hFile, pTile, sizeof(INFO), &dwByte, nullptr);

		//DWORD dwByte = 0; 
		//DWORD dwStringCount = 0; 
		//for (auto& rPair : m_mapUnitInfo)
		//{
		//	dwStringCount = (rPair.second->wstrName.GetLength() + 1) * sizeof(wchar_t);
		//	WriteFile(hFile, &dwStringCount, sizeof(DWORD), &dwByte, nullptr); 
		//	WriteFile(hFile, rPair.second->wstrName.GetString(), dwStringCount, &dwByte, nullptr);
		//	WriteFile(hFile, &rPair.second->iAtt, sizeof(int), &dwByte, nullptr);
		//	WriteFile(hFile, &rPair.second->iDef, sizeof(int), &dwByte, nullptr);
		//	WriteFile(hFile, &rPair.second->byJob, sizeof(BYTE), &dwByte, nullptr);
		//	WriteFile(hFile, &rPair.second->byItem, sizeof(BYTE), &dwByte, nullptr);
		//}
		CloseHandle(hFile); 
	}
}

// Load
void CUnitTool::OnBnClickedButton5()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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

		pView->m_pMapUnit_Summon->Release_MapUnit_Summon();

		//m_ListBox.ResetContent();
		//for (auto& rPair : m_mapUnitInfo)
		//	Safe_Delete(rPair.second); 
		//m_mapUnitInfo.clear(); 

		DWORD dwByte = 0;
		DWORD dwStringCount = 0;
		TCHAR* szBuf = nullptr; 
		INFO* pUnitInfo = nullptr; 
		while (true)
		{
			pUnitInfo = new INFO;
			ReadFile(hFile, pUnitInfo, sizeof(INFO), &dwByte, nullptr);
			pView->m_pMapUnit_Summon->m_vecMapObject.push_back(pUnitInfo);

			
			if (0 == dwByte)
			{
				Safe_Delete(pUnitInfo);
				break; 

			}
			//szBuf = new TCHAR[dwStringCount]; 
			//ReadFile(hFile, szBuf, dwStringCount, &dwByte, nullptr);
			////pUnitInfo->wstrName = szBuf;
			//Safe_Delete_Array(szBuf); 
			//ReadFile(hFile, &pUnitInfo->iAtt, sizeof(int), &dwByte, nullptr);
			//ReadFile(hFile, &pUnitInfo->iDef, sizeof(int), &dwByte, nullptr);
			//ReadFile(hFile, &pUnitInfo->byJob, sizeof(BYTE), &dwByte, nullptr);
			//ReadFile(hFile, &pUnitInfo->byItem, sizeof(BYTE), &dwByte, nullptr);

			//m_mapUnitInfo.emplace(pUnitInfo->wstrName, pUnitInfo); 
			//m_ListBox.AddString(pUnitInfo->wstrName);
		}
		pView->Invalidate(FALSE);

		CloseHandle(hFile);
	}

}


void CUnitTool::OnDropFiles(HDROP hDropInfo)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	int iSize = DragQueryFile(hDropInfo, 0xffffffff, nullptr, 0);

	TCHAR szBuf[MAX_PATH] = L"";
	CString wstrRelativePath;
	for (int i = 0; i < iSize; ++i)
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


BOOL CUnitTool::OnInitDialog()
{
	//if (nullptr == m_pMapUnit_Summon.GetSafeHwnd())
	//	m_pMapUnit_Summon.Create(IDD_MapObject);
	CDialog::OnInitDialog();
	//m_ListBox2.AddString(_T("1"));

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CUnitTool::OnCbnSelchangeCombo2()
{
	int iIndex=m_combobox.GetCurSel();
	if (LB_ERR == iIndex)
		return;
	CString wstrUnitName;
	m_combobox.GetLBText(iIndex, wstrUnitName);
	TCHAR szFileName[MAX_PATH]{};
	lstrcpy(szFileName, wstrUnitName.GetString());
	m_ListBox2.AddString(szFileName);
	UpdateData(FALSE);

	//int iIndex = m_ListBox.GetCurSel();
	//if (LB_ERR == iIndex)
	//	return;
	//
	//CString wstrUnitName;
	//m_ListBox.GetText(iIndex, wstrUnitName);

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CUnitTool::OnLbnSelchangeList2()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}
