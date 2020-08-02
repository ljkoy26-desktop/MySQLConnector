
// MySqlMFC1Dlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "MySqlMFC1.h"
#include "MySqlMFC1Dlg.h"
#include "afxdialogex.h"
//
//
//#include <crtdbg.h> // _CrtDumpMemoryLeaks() 사용하기위해
//#if _DEBUG #define new(_NORMAL_BLOCK, __FILE__, __LINE__) 
//#define malloc(s) _malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__) 
//#endif // 몇행에서 메모리 누수가 나는지 알려줌.

//test 20 07 20
// 데탑에서 확인 완료 이제 작업해도됨 사용법 대충알음 (git) 

// #include <vector>
// fine _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CMySqlMFC1Dlg 대화 상자



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


// CMySqlMFC1Dlg 메시지 처리기

BOOL CMySqlMFC1Dlg::OnInitDialog()
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	mysql_init(&Conn);
	// 디버깅용 셋팅 입니다 //
	// 디버깅용 셋팅 입니다 //
	m_EditHost.SetWindowText(_T("127.0.0.1"));
	m_EditUser.SetWindowText(_T("root"));
	m_EditPasswd.SetWindowText(_T("manager"));
	m_EditPort.SetWindowText(_T("3306"));
	m_EditDB.SetWindowText(_T("world"));
	// m_EditQuery.SetWindowText(_T("INSERT INTO Customer (ID, Name, Age, Address) VALUES (3, '홍길동', 2, '서울')"));
	m_EditQuery.SetWindowText(_T("Select * from country"));
	


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMySqlMFC1Dlg::OnPaint()
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
		AfxMessageBox(Error_CString); // Mysql 연결 실패 메세지
	}
}


void CMySqlMFC1Dlg::OnBnClickedButtonDisconnect()
{
	mysql_close(ConnPtr);
	OnBnClickedButtonClear();
	DeleteSchemaBrowser();
	AfxMessageBox(_T("연결을 해제 했습니다"));
}


void CMySqlMFC1Dlg::OnBnClickedButtonExecute() // 쿼리실행
{
	if (ConnPtr == NULL) {
		//AfxMessageBox(_T("DB가 연결되지 않았습니다"));
		m_QueryStatus.SetWindowTextW(_T("DB가 연결돼지 않음"));
		return;
	}
	UpdateData(TRUE);
	CT2A Const_Query(m_Query); // CString -> const char *	
	Stat = mysql_query(ConnPtr, Const_Query);
	

	if (Stat != 0) {
 		//AfxMessageBox(_T("쿼리를 실행하지 못했습니다"));
		m_QueryStatus.SetWindowTextW(_T("쿼리 수행실패"));
		return;
	}
	else {		
		m_QueryStatus.SetWindowTextW(_T("쿼리 수행완료"));
		Result = mysql_store_result(&Conn); // 쿼리의 내용을 담습니다 
		QueryShow(Const_Query); // 쿼리 내용을 보여준다
		return;
	}
}


void CMySqlMFC1Dlg::QueryShow(const char *query) // 쿼리 내용을 보여준다
{
	if (Result == 0) { // SELECT 문이 아닐경우 값을 저장하지 않습니다

	}
	else { // Select , show 의 경우
		OnBnClickedButtonClear();
		ShowInertColumn(); // 쿼리의 제목을 출력합니다
		ShowInsertItem(); // 쿼리의 내용을 출력합니다
		mysql_free_result(Result); // 결과 비우기
		m_List.SetExtendedStyle(m_List.GetExtendedStyle() | LVS_EX_GRIDLINES); // 그리드 라인을 그려줍니다
	}

}

void CMySqlMFC1Dlg::ShowInertColumn() // 쿼리의 제목을 출력합니다
{
	MYSQL_FIELD *Column_field;
	for (int i = 0; (Column_field = mysql_fetch_field(Result)); i++) {
		CString ColName = (CString)Column_field->name;
		m_List.InsertColumn(i, ColName, LVCFMT_LEFT, 100);// Column_field->charsetnr); // 자료형에 따라 수용하는 컬럼의 크기가 달라집니다
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
	std::vector<HTREEITEM> m_hRootVector; // 벡터형식 트리아이템 추가

	CreateRoot(Vector_DB, m_hRootVector, Result); // DB 루트 아이템 추가 
	CreateNode(Vector_DB, Vector_Schema, m_hRootVector, Result); // DB 노트 아이템 추가
	

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
	for (int i = 0; Row = mysql_fetch_row(res); i++) { // 루트 노드 구성 (show databases)
		v_DB.push_back((CString)Row[0]); // 벡터 DB의 요소를 추가합니다.
		v_Root.resize(v_DB.size()); // 추가된 벡터의 크기만큼 리사이징 합니다
		v_Root[i] = m_Tree.InsertItem(v_DB[i], 0, 1); // 루트 아이템 추가 (DB)
	}
	mysql_free_result(res); // 결과 비우기

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

template<typename T> void CMySqlMFC1Dlg::VectorClear(vector<T>& v1) // 벡터 메모리 스왑
{
	v1.clear();
	vector<T>().swap(v1);
}
void CMySqlMFC1Dlg::MysqlInit() // 문자열 셋팅
{
	AfxMessageBox(_T("연결성공"));
	mysql_query(ConnPtr, "set session character_set_connection=euckr;");
	mysql_query(ConnPtr, "set session character_set_results=euckr;");
	mysql_query(ConnPtr, "set session character_set_client=euckr;");

	mysql_query(ConnPtr, "show databases;");
	ShowSchemaBrowser();
}


void CMySqlMFC1Dlg::OnTvnSelchangedTreeSchema(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	
	//m_hSelectItem = pNMTreeView->itemNew.hItem; // 현재선택된 아이템의 핸들값을 멤버변수에 저장
	//CString strSel = m_Tree.GetItemText(m_hSelectItem); // 선택된 아이템의 텍스트를 얻어와서

	*pResult = 0;
}


void CMySqlMFC1Dlg::QueryStatus()
{
	// m_QueryStatus.SetWindowTextW();
}
