#pragma once
#include "afxwin.h"
#include "MapUnit_Summon.h"

// CUnitTool 대화 상자입니다.

class CUnitTool : public CDialog
{
	DECLARE_DYNAMIC(CUnitTool)

public:
	CUnitTool(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CUnitTool();
	MapUnit_Summon m_pMapUnit_Summon;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UNITTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	// 이건테스트용. 
	CString m_wstrSrc;
	CString m_wstrDst;
	afx_msg void OnBnClickedSendData();
	// UnitData
	CString m_wstrName;
	int m_iAtt;
	int m_iDef;
	CListBox m_ListBox;
	CButton m_Radio[JOBEND];
	CButton m_CheckBox[3];
	afx_msg void OnBnClickedAddUnitData();
	afx_msg void OnLbnSelchangeRenderUnitInfo();
	BYTE m_byDrawID;

private:
	map<wstring, UNITINFO*> m_mapUnitInfo; 
	vector<INFO*>m_vecUnitIInfo;

public:
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	CStatic m_Picture;
	afx_msg void OnDropFiles(HDROP hDropInfo);
	virtual BOOL OnInitDialog();
	CComboBox m_combobox;
	afx_msg void OnCbnSelchangeCombo2();
	CListBox m_ListBox2;
	afx_msg void OnLbnSelchangeList2();
};
