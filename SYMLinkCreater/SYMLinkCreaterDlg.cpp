
// SYMLinkCreaterDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "SYMLinkCreater.h"
#include "SYMLinkCreaterDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSYMLinkCreaterDlg 대화 상자



CSYMLinkCreaterDlg::CSYMLinkCreaterDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSYMLinkCreaterDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSYMLinkCreaterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_src_edit);
	DDX_Control(pDX, IDC_EDIT2, m_dst_edit);
	DDX_Control(pDX, IDC_EDIT3, m_src_name);
	//  DDX_Check(pDX, IDC_CHECK1, m_isFolder);
	DDX_Control(pDX, IDC_MFCSHELLTREE_SRC, m_src_list);
	DDX_Control(pDX, IDC_MFCSHELLTREE_DST, m_dst_list);
}

BEGIN_MESSAGE_MAP(CSYMLinkCreaterDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CSYMLinkCreaterDlg::OnBnClickedButton1)


//	ON_NOTIFY(NM_CLICK, IDC_MFCSHELLTREE_SRC, &CSYMLinkCreaterDlg::OnClickMfcshelltreeSrc)
	ON_NOTIFY(TVN_SELCHANGED, IDC_MFCSHELLTREE_SRC, &CSYMLinkCreaterDlg::OnSelchangedMfcshelltreeSrc)
	ON_NOTIFY(TVN_SELCHANGED, IDC_MFCSHELLTREE_DST, &CSYMLinkCreaterDlg::OnSelchangedMfcshelltreeDst)
END_MESSAGE_MAP()


// CSYMLinkCreaterDlg 메시지 처리기
bool WUGetCurrentDirectory(CString& dir)
{
    UINT32 buflen=0;
    PWSTR buf=NULL;

    buflen = GetCurrentDirectoryW(buflen, buf);
    if (0 == buflen)
    {
        return false;
    }

    buf = (PWSTR) malloc(sizeof(WCHAR) * buflen);
    if (0 == GetCurrentDirectoryW(buflen, buf))
    {
        free(buf);
        return false;
    }
    
    dir = buf;
	free(buf);
	buf = NULL;
    return true;
}
BOOL CSYMLinkCreaterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	setlocale(LC_ALL, "");
	WUGetCurrentDirectory(currPath);
	//m_src_edit.SetWindowTextW(currPath);
	m_src_list.SelectPath(currPath);
	m_dst_list.SelectPath(currPath);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CSYMLinkCreaterDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CSYMLinkCreaterDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CSYMLinkCreaterDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSYMLinkCreaterDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	CStringW cmd, path_src, path_dst, dst_name;
	m_src_edit.GetWindowTextW(path_src);
	m_dst_edit.GetWindowTextW(path_dst);
	m_src_name.GetWindowTextW(dst_name);
	
	cmd = _T("/c mklink /d \"");
	cmd.Append(path_dst);
	cmd.Append(_T ("\\"));
	cmd.Append(dst_name);
	
	cmd.Append(_T ("\" \"") );
	cmd.Append(path_src);
	cmd.Append(_T ("\""));

	//AfxMessageBox(cmd);
	ShellExecute(NULL, _T("open"), _T("cmd"), cmd, NULL, SW_SHOW); 
	//const char* cmda;
	//cmda = (CStringA)cmd;
	
	// Refrash
	CString tmp_dir;
	m_dst_list.GetItemPath(tmp_dir, m_dst_list.GetSelectedItem());
	m_dst_list.SelectPath(tmp_dir);

	m_src_list.GetItemPath(tmp_dir, m_src_list.GetSelectedItem());
	m_src_list.SelectPath(tmp_dir);

	//system(cmda);
	
}





void CSYMLinkCreaterDlg::updatePath(void)
{
//	UpdateData (TRUE);

	CString src_dir, dst_dir;
	CString src_name;
	m_src_list.GetItemPath(src_dir, m_src_list.GetSelectedItem());
	m_dst_list.GetItemPath(dst_dir, m_dst_list.GetSelectedItem());

	src_name = m_src_list.GetItemText(m_src_list.GetSelectedItem());

	m_src_edit.SetWindowTextW(src_dir);
	m_src_name.SetWindowTextW(src_name);

	m_dst_edit.SetWindowTextW(dst_dir);

}


//void CSYMLinkCreaterDlg::OnClickMfcshelltreeSrc(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//	updatePath();
//	*pResult = 0;
//}


void CSYMLinkCreaterDlg::OnSelchangedMfcshelltreeSrc(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	updatePath();
	*pResult = 0;
}


void CSYMLinkCreaterDlg::OnSelchangedMfcshelltreeDst(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	updatePath();
	*pResult = 0;
}
