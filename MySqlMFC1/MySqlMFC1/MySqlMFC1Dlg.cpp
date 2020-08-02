
// MySqlMFC1Dlg.cpp : ���� ����
//

#include "stdafx.h"
#include "MySqlMFC1.h"
#include "MySqlMFC1Dlg.h"
#include "afxdialogex.h"
//
//
//#include <crtdbg.h> // _CrtDumpMemoryLeaks() ����ϱ�����
//#if _DEBUG #define new(_NORMAL_BLOCK, __FILE__, __LINE__) 
//#define malloc(s) _malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__) 
//#endif // ���࿡�� �޸� ������ ������ �˷���.

//test 20 07 20
// ��ž���� Ȯ�� �Ϸ� ���� �۾��ص��� ���� ������� (git) 

// #include <vector>
// fine _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
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


// CMySqlMFC1Dlg ��ȭ ����



CMySqlMFC1Dlg::CMySqlMFC1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MYSQLMFC1_DIALOG, pParent)
	, m_Host(_T(""))
	, m_User(_T(""))
	, m_Passwd(_T(""))
	, m_DB(_T(""))
	, m_Port(_T(""))
	, m_Query(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMySqlMFC1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_HOST, m_Host);
	DDX_Text(pDX, IDC_EDIT_USER, m_User);
	DDX_Text(pDX, IDC_EDIT_PASSWD, m_Passwd);
	DDX_Text(pDX, IDC_EDIT_DB, m_DB);
	DDX_Text(pDX, IDC_EDIT_PORT, m_Port);
	DDX_Control(pDX, IDC_EDIT_HOST, m_EditHost);
	DDX_Control(pDX, IDC_EDIT_USER, m_EditUser);
	DDX_Control(pDX, IDC_EDIT_PASSWD, m_EditPasswd);
	DDX_Control(pDX, IDC_EDIT_DB, m_EditDB);
	DDX_Control(pDX, IDC_EDIT_PORT, m_EditPort);
	DDX_Control(pDX, IDC_EDIT_QUERY, m_EditQuery);
	DDX_Text(pDX, IDC_EDIT_QUERY, m_Query);
	DDX_Control(pDX, IDC_LIST_QUERY, m_List);
	DDX_Control(pDX, IDC_TREE_SCHEMA, m_Tree);
	DDX_Control(pDX, IDC_EDIT1, m_QueryStatus);
}

BEGIN_MESSAGE_MAP(CMySqlMFC1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CMySqlMFC1Dlg::OnBnClickedButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_DISCONNECT, &CMySqlMFC1Dlg::OnBnClickedButtonDisconnect)
	ON_BN_CLICKED(IDC_BUTTON_EXECUTE, &CMySqlMFC1Dlg::OnBnClickedButtonExecute)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CMySqlMFC1Dlg::OnBnClickedButtonClear)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_SCHEMA, &CMySqlMFC1Dlg::OnTvnSelchangedTreeSchema)
END_MESSAGE_MAP()


// CMySqlMFC1Dlg �޽��� ó����

BOOL CMySqlMFC1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	mysql_init(&Conn);
	// ������ ���� �Դϴ� //
	// ������ ���� �Դϴ� //
	m_EditHost.SetWindowText(_T("127.0.0.1"));
	m_EditUser.SetWindowText(_T("root"));
	m_EditPasswd.SetWindowText(_T("manager"));
	m_EditPort.SetWindowText(_T("3306"));
	m_EditDB.SetWindowText(_T("world"));
	// m_EditQuery.SetWindowText(_T("INSERT INTO Customer (ID, Name, Age, Address) VALUES (3, 'ȫ�浿', 2, '����')"));
	m_EditQuery.SetWindowText(_T("Select * from country"));
	


	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CMySqlMFC1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CMySqlMFC1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CMySqlMFC1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMySqlMFC1Dlg::OnBnClickedButtonConnect()
{
	UpdateData(TRUE);
	CT2A Const_Host(m_Host); // CString -> const char *
	CT2A Const_User(m_User);
	CT2A Const_Passwd(m_Passwd);
	CT2A Const_DB(m_DB);
	unsigned int Unsinged_Port = atoi((CStringA)m_Port);  // CString -> unsigned int
	ConnPtr = mysql_real_connect(&Conn, Const_Host, Const_User, Const_Passwd, Const_DB, Unsinged_Port, (char*)NULL, 0);

	if (ConnPtr != NULL) {
		MysqlInit();
	}
	else {
		CString Error_CString = (CString)mysql_error(&Conn); // const char * -> CString
		AfxMessageBox(Error_CString); // Mysql ���� ���� �޼���
	}
}


void CMySqlMFC1Dlg::OnBnClickedButtonDisconnect()
{
	mysql_close(ConnPtr);
	OnBnClickedButtonClear();
	DeleteSchemaBrowser();
	AfxMessageBox(_T("������ ���� �߽��ϴ�"));
}


void CMySqlMFC1Dlg::OnBnClickedButtonExecute() // ��������
{
	if (ConnPtr == NULL) {
		//AfxMessageBox(_T("DB�� ������� �ʾҽ��ϴ�"));
		m_QueryStatus.SetWindowTextW(_T("DB�� ������� ����"));
		return;
	}
	UpdateData(TRUE);
	CT2A Const_Query(m_Query); // CString -> const char *	
	Stat = mysql_query(ConnPtr, Const_Query);
	

	if (Stat != 0) {
 		//AfxMessageBox(_T("������ �������� ���߽��ϴ�"));
		m_QueryStatus.SetWindowTextW(_T("���� �������"));
		return;
	}
	else {		
		m_QueryStatus.SetWindowTextW(_T("���� ����Ϸ�"));
		Result = mysql_store_result(&Conn); // ������ ������ ����ϴ� 
		QueryShow(Const_Query); // ���� ������ �����ش�
		return;
	}
}


void CMySqlMFC1Dlg::QueryShow(const char *query) // ���� ������ �����ش�
{
	if (Result == 0) { // SELECT ���� �ƴҰ�� ���� �������� �ʽ��ϴ�

	}
	else { // Select , show �� ���
		OnBnClickedButtonClear();
		ShowInertColumn(); // ������ ������ ����մϴ�
		ShowInsertItem(); // ������ ������ ����մϴ�
		mysql_free_result(Result); // ��� ����
		m_List.SetExtendedStyle(m_List.GetExtendedStyle() | LVS_EX_GRIDLINES); // �׸��� ������ �׷��ݴϴ�
	}

}

void CMySqlMFC1Dlg::ShowInertColumn() // ������ ������ ����մϴ�
{
	MYSQL_FIELD *Column_field;
	for (int i = 0; (Column_field = mysql_fetch_field(Result)); i++) {
		CString ColName = (CString)Column_field->name;
		m_List.InsertColumn(i, ColName, LVCFMT_LEFT, 100);// Column_field->charsetnr); // �ڷ����� ���� �����ϴ� �÷��� ũ�Ⱑ �޶����ϴ�
	}
}

void CMySqlMFC1Dlg::OnBnClickedButtonClear()
{
	CHeaderCtrl *pHeaderCtrl;
	pHeaderCtrl = m_List.GetHeaderCtrl();
	int Coulmn_Count = pHeaderCtrl->GetItemCount();
	m_List.DeleteAllItems();

	for (int i = 0; i <= Coulmn_Count; i++)
	{
		pHeaderCtrl->DeleteItem(i);
		m_List.DeleteColumn(0);
	}
}
		// m_List.InsertItem(row, Row[0] ? (CString)Row[0] : _T("<NULL>"));
		// m_List.SetItemText(row, col, Row[col] ? (CString)Row[col] : _T("<NULL>"));

void CMySqlMFC1Dlg::ShowInsertItem()
{
	for(unsigned int row = 0; (Row = mysql_fetch_row(Result)); row++) {
		m_List.InsertItem(row, (CString)Row[0]);

		for (unsigned int col = 1; col < Result->field_count; col++)
			m_List.SetItemText(row, col, (CString)Row[col]);
	}
}

void CMySqlMFC1Dlg::ShowSchemaBrowser()
{
	Result = mysql_store_result(ConnPtr);

	std::vector<CString> Vector_DB;
	std::vector<CString> Vector_Schema;
	std::vector<HTREEITEM> m_hRootVector; // �������� Ʈ�������� �߰�

	CreateRoot(Vector_DB, m_hRootVector, Result); // DB ��Ʈ ������ �߰� 
	CreateNode(Vector_DB, Vector_Schema, m_hRootVector, Result); // DB ��Ʈ ������ �߰�
	

}

void CMySqlMFC1Dlg::DeleteSchemaBrowser()
{
	m_Tree.DeleteAllItems();
}

void CMySqlMFC1Dlg::ShowDataBases()
{
}

void CMySqlMFC1Dlg::CreateRoot(vector<CString>& v_DB, vector<HTREEITEM>& v_Root, MYSQL_RES* res)
{
	int DB_Count = res->row_count;
	for (int i = 0; Row = mysql_fetch_row(res); i++) { // ��Ʈ ��� ���� (show databases)
		v_DB.push_back((CString)Row[0]); // ���� DB�� ��Ҹ� �߰��մϴ�.
		v_Root.resize(v_DB.size()); // �߰��� ������ ũ�⸸ŭ ������¡ �մϴ�
		v_Root[i] = m_Tree.InsertItem(v_DB[i], 0, 1); // ��Ʈ ������ �߰� (DB)
	}
	mysql_free_result(res); // ��� ����

}

void CMySqlMFC1Dlg::CreateNode(vector<CString>& v_DB, vector<CString>& v_Schema, vector<HTREEITEM>& v_Root, MYSQL_RES* res)
{
	CString Table_Query = L"show tables from ";
	CString Table_Query_Temp = Table_Query;

	for (int i = 0; i < v_DB.size(); i++) {
		Table_Query_Temp += v_DB[i];
		mysql_query(ConnPtr, CT2A(Table_Query_Temp));
		Result = mysql_store_result(ConnPtr); // shwo tables from information_schema

		for (int j = 0; Row = mysql_fetch_row(Result); j++) {
			v_Schema.push_back((CString)Row[0]);
			m_Tree.InsertItem(v_Schema[j], 2, 2, v_Root[i], TVI_LAST);
		}
		VectorClear(v_Schema);
		Table_Query_Temp = Table_Query;
		mysql_free_result(Result);
	}
	VectorClear(v_DB);
	VectorClear(v_Root);
}

template<typename T> void CMySqlMFC1Dlg::VectorClear(vector<T>& v1) // ���� �޸� ����
{
	v1.clear();
	vector<T>().swap(v1);
}
void CMySqlMFC1Dlg::MysqlInit() // ���ڿ� ����
{
	AfxMessageBox(_T("���Ἲ��"));
	mysql_query(ConnPtr, "set session character_set_connection=euckr;");
	mysql_query(ConnPtr, "set session character_set_results=euckr;");
	mysql_query(ConnPtr, "set session character_set_client=euckr;");

	mysql_query(ConnPtr, "show databases;");
	ShowSchemaBrowser();
}


void CMySqlMFC1Dlg::OnTvnSelchangedTreeSchema(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	
	//m_hSelectItem = pNMTreeView->itemNew.hItem; // ���缱�õ� �������� �ڵ鰪�� ��������� ����
	//CString strSel = m_Tree.GetItemText(m_hSelectItem); // ���õ� �������� �ؽ�Ʈ�� ���ͼ�

	*pResult = 0;
}


void CMySqlMFC1Dlg::QueryStatus()
{
	// m_QueryStatus.SetWindowTextW();
}
