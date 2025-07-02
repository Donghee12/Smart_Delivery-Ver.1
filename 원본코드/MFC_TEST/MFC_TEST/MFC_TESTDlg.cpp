
// MFC_TESTDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFC_TEST.h"
#include "MFC_TESTDlg.h"
#include "afxdialogex.h"

#include "db_user_info.h"
#include "database_config.h" 
#include "database.h"  // 데이터베이스 관련 함수 선언
#include "im_qrcode.hpp"

#include <iostream>
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;


/* GLOBAL VARIABLES */

int mfc_g_prod_select = 0;
int mfc_g_brand_select = 0;
string mfc_g_str_product = {};
string mfc_g_str_brand = {};


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
	
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	
END_MESSAGE_MAP()


// CMFCTESTDlg dialog



CMFCTESTDlg::CMFCTESTDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC_TEST_DIALOG, pParent)
	, dl_name(_T(""))
	, dl_addr(_T(""))
	, dl_ph(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCTESTDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NAME, dl_name);
	DDX_Text(pDX, IDC_EDIT_ADDR, dl_addr);
	DDX_Text(pDX, IDC_EDIT_PH, dl_ph);
}

BEGIN_MESSAGE_MAP(CMFCTESTDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CREATE, &CMFCTESTDlg::OnBnClickedButtonCreate)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CMFCTESTDlg::OnBnClickedButtonCancel)
	ON_COMMAND(IDC_RADIO_TV, &CMFCTESTDlg::OnBnClickedGroupProd)
	ON_COMMAND(IDC_RADIO_SMART, &CMFCTESTDlg::OnBnClickedGroupProd)
	ON_COMMAND(IDC_RADIO_LAP, &CMFCTESTDlg::OnBnClickedGroupProd)
	ON_COMMAND(IDC_RADIO_SAMSUNG, &CMFCTESTDlg::OnBnClickedGroupBrand)
	ON_COMMAND(IDC_RADIO_APPLE, &CMFCTESTDlg::OnBnClickedGroupBrand)
END_MESSAGE_MAP()


// CMFCTESTDlg message handlers

BOOL CMFCTESTDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCTESTDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCTESTDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCTESTDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCTESTDlg::OnBnClickedGroupProd()
{
	int nSelectedRadio = GetCheckedRadioButton(IDC_RADIO_TV, IDC_RADIO_LAP);


	switch (nSelectedRadio)
	{
	case IDC_RADIO_TV:
		mfc_g_prod_select = 1;
		break;

	case IDC_RADIO_LAP:
		mfc_g_prod_select = 2;
		break;

	case IDC_RADIO_SMART:
		mfc_g_prod_select = 3;
		break;

	default:
		mfc_g_prod_select = 0;
		break;
	}

	mfc_g_str_product = selectProduct(mfc_g_prod_select); // db_user_info.cpp

}


void CMFCTESTDlg::OnBnClickedGroupBrand()
{
	int nSelectedRadio = GetCheckedRadioButton(IDC_RADIO_SAMSUNG, IDC_RADIO_APPLE);

	switch (nSelectedRadio)
	{
	case IDC_RADIO_SAMSUNG:
		mfc_g_brand_select = 1;
		break;
	case IDC_RADIO_APPLE:
		mfc_g_brand_select = 2;
		break;
	default:
		AfxMessageBox(_T("No option is selected"));
		mfc_g_brand_select = 0;
		break;
	}

	mfc_g_str_brand = selectManufacturer(mfc_g_brand_select); // db_user_info.cpp
}


void mfc_resetData()
{
	mfc_g_prod_select = 0;
	mfc_g_brand_select = 0;
	mfc_g_str_product = {};
	mfc_g_str_brand = {};
}	


void CMFCTESTDlg::OnBnClickedButtonCreate()
{
	GetDlgItem(IDC_EDIT_NAME)->GetWindowText(dl_name);    // 필드 정보 추출
	GetDlgItem(IDC_EDIT_ADDR)->GetWindowText(dl_addr);    
	GetDlgItem(IDC_EDIT_PH)->GetWindowText(dl_ph);      

	
	string str_name, str_addr, str_ph;

	str_name = (CT2A(dl_name.GetString())); // Cstring -> string 변환
	str_addr = (CT2A(dl_addr.GetString()));
	str_ph = (CT2A(dl_ph.GetString()));


	int error_flag = 0; 
	string error = {};

	Connection* conn = db_connect_to(db_config); //DB 연결
	conn->setSchema("test_db");


	int customer_exists = db_checkCustomerExists(conn, str_name, str_ph); // 기존 고객 확인

	if (customer_exists == -1) // 예외 처리
	{
		AfxMessageBox(_T("ERROR IN CUSTOMER CHECK"));
		mfc_resetData();
		return;
	}

	if (customer_exists == 0) // 신규 고객 확인
	{
		 error = db_insertCustomerData(conn, str_name, str_addr, str_ph); // 고객 정보 추가
		if (!error.empty())
		{
			AfxMessageBox(_T(error.c_str()));
		}
	}
	
	int customer_id = db_getCustomerId(conn, str_name, str_addr, str_ph); 
	int price = getProductPrice(mfc_g_str_product, mfc_g_str_brand);

	error = db_insertProductData(conn, mfc_g_str_product, mfc_g_str_brand, price, customer_id); // 주문 정보 추가

	if (!error.empty()) // 예외 처리
	{
		AfxMessageBox(_T(error.c_str()));
	}


	string order_num = to_string(db_getOrderId(conn, mfc_g_str_product, mfc_g_str_brand, customer_id));
	Mat img = qr_inputData(order_num); // QR에 주문 번호 저장
	Mat img_resize;
	resize(img, img_resize, Size(50, 50), 0, 0, INTER_NEAREST);

	
	string img_name = "Images\\" + order_num + ".jpg"; 
	
	imwrite(img_name, img_resize);  // qr코드 저장 (.jpg파일)
	
	mfc_resetData(); 
	OnBnClickedButtonCancel(); // 필드 정보 리셋

}


void CMFCTESTDlg::OnBnClickedButtonCancel()
{
	GetDlgItem(IDC_EDIT_NAME)->SetWindowText(_T(""));    // dl_name is the class variable
	GetDlgItem(IDC_EDIT_ADDR)->SetWindowText(_T(""));     // dl_addr is the class variable
	GetDlgItem(IDC_EDIT_PH)->SetWindowText(_T(""));       // dl_ph is the class variable
	((CButton*)GetDlgItem(IDC_RADIO_TV))->SetCheck(BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_RADIO_LAP))->SetCheck(BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_RADIO_SMART))->SetCheck(BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_RADIO_SAMSUNG))->SetCheck(BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_RADIO_APPLE))->SetCheck(BST_UNCHECKED);
}