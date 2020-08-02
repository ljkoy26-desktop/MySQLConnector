
// MySqlMFC1Dlg.h : ��� ����
//

#pragma once

#include "stdafx.h"
//#include <mysql.h>
#include "include\mysql.h"
#include <iostream>
// #include <string>
#include "afxwin.h"
#include "CString"
#include "afxcmn.h"
#include <vector>
using namespace std;
// CMySqlMFC1Dlg ��ȭ ����
//#pragma comment(lib, "libmySQL.lib")	
class CMySqlMFC1Dlg : public CDialogEx
{
// �����Դϴ�.
public:
	CMySqlMFC1Dlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYSQLMFC1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:	

	MYSQL Conn;
	MYSQL * ConnPtr = NULL;
	MYSQL_RES* Result;
	MYSQL_ROW Row;
	int Stat;

	CString m_Host;
	CString m_User;
	CString m_Passwd;
	CString m_DB;
	CString m_Port;
	CString m_Query;
	
	afx_msg void OnBnClickedButtonConnect();
	CEdit m_EditHost;
	CEdit m_EditUser;
	CEdit m_EditPasswd;
	CEdit m_EditDB;
	CEdit m_EditPort;
	CEdit m_EditQuery;
	CEdit m_QueryStatus;
	CTreeCtrl m_Tree;
	CListCtrl m_List;
		
	afx_msg void OnBnClickedButtonDisconnect();
	afx_msg void OnBnClickedButtonExecute();
	afx_msg void OnBnClickedButtonClear();
	void QueryShow(const char *query);
	void ShowInertColumn();
	void ShowInsertItem();
	void ShowSchemaBrowser();
	void DeleteSchemaBrowser();
	void ShowDataBases();
	void MysqlInit();
	void CreateRoot(vector<CString>& v_DB, vector<HTREEITEM>& v_Root, MYSQL_RES* res);
	void CreateNode(vector<CString>& v_DB, vector<CString>& v_Schema, vector<HTREEITEM>& v_Root, MYSQL_RES* res);
	template<typename T> void VectorClear(vector<T>& v1);
	afx_msg void OnTvnSelchangedTreeSchema(NMHDR *pNMHDR, LRESULT *pResult);
	
	void QueryStatus();
};
