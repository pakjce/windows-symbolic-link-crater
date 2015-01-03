
// SYMLinkCreaterDlg.h : 헤더 파일
//

#pragma once
#include "afxshelllistctrl.h"
#include "afxwin.h"
#include "afxshelltreectrl.h"
#include "locale.h"


// CSYMLinkCreaterDlg 대화 상자
class CSYMLinkCreaterDlg : public CDialogEx
{
// 생성입니다.
public:
	CSYMLinkCreaterDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SYMLINKCREATER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
//	CMFCShellListCtrl m_src_list;
//	CMFCShellListCtrl m_dst_list;
	CEdit m_src_edit;
	CEdit m_dst_edit;
	afx_msg void OnBnClickedButton1();

	CString currPath;

	CEdit m_src_name;

	void updatePath(void);
//	BOOL m_isFolder;
	CMFCShellTreeCtrl m_src_list;
	CMFCShellTreeCtrl m_dst_list;
//	afx_msg void OnClickMfcshelltreeSrc(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSelchangedMfcshelltreeSrc(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSelchangedMfcshelltreeDst(NMHDR *pNMHDR, LRESULT *pResult);
};
