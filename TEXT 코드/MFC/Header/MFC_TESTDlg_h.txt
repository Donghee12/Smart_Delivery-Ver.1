
// MFC_TESTDlg.h : header file
//

#pragma once


// CMFCTESTDlg dialog
class CMFCTESTDlg : public CDialogEx
{
// Construction
public:
	CMFCTESTDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_TEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString dl_name;
	CString dl_addr;
	CString dl_ph;
	afx_msg void OnBnClickedButtonCreate();
	afx_msg void OnBnClickedButtonCancel();
	afx_msg void OnBnClickedGroupProd();
	afx_msg void OnBnClickedGroupBrand();
};
