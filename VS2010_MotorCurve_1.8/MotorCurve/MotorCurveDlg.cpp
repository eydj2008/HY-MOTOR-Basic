
// MotorCurveDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MotorCurve.h"
#include "MotorCurveDlg.h"
#include "MotorSpeedDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define Pi 3.141592653589793

// CMotorCurveDlg 对话框




CMotorCurveDlg::CMotorCurveDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMotorCurveDlg::IDD, pParent)
{
	L1 = 22.0;
	R1 = 2.0;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMotorCurveDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Data, m_Data);
	DDX_Control(pDX, IDC_MakeData, m_MakeData);
	DDX_Control(pDX, IDC_MircoStep, m_MircoStep);
	DDX_Control(pDX, IDC_MircoMAX, m_MircoMAX);
	DDX_Text(pDX, IDC_EDIT3, L1);
	DDX_Text(pDX, IDC_EDIT6, R1);
}

BEGIN_MESSAGE_MAP(CMotorCurveDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_MakeData, &CMotorCurveDlg::OnBnClickedMakedata)
	ON_BN_CLICKED(IDC_BUTTON1, &CMotorCurveDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMotorCurveDlg::OnBnClickedButton2)
	ON_STN_CLICKED(IDC_YONYON, &CMotorCurveDlg::OnStnClickedYonyon)
	ON_WM_MOUSEMOVE()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CMotorCurveDlg 消息处理程序

BOOL CMotorCurveDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	CString sValue = L"128";	//128*3/2 = 192   256*3/2 = 384
	//sValue.Format("%d",255-m_slider.GetPos()); 
	SetDlgItemText(IDC_MircoStep,sValue);
	sValue = L"255";
	SetDlgItemText(IDC_MircoMAX,sValue);
	sValue = L"48";
	SetDlgItemText(IDC_EDIT1,sValue);
	sValue = L"380";
	SetDlgItemText(IDC_EDIT2,sValue);
	sValue = L"22.0";
	SetDlgItemText(IDC_EDIT3,sValue);
	sValue = L"150";
	SetDlgItemText(IDC_EDIT4,sValue);
	sValue = L"10";
	SetDlgItemText(IDC_EDIT5,sValue);
	sValue = L"2.0";
	SetDlgItemText(IDC_EDIT6,sValue);


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMotorCurveDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMotorCurveDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// 2-PHASE STEPPER MOTOR-----------------------------------
void CMotorCurveDlg::OnBnClickedMakedata()
{
	// TODO: 在此添加控件通知处理程序代码 double folat
	
	UINT i=0;
	UINT SinData=0;
	UINT CosData=0;
	double	m_SinAngle=0;
	double	m_CosAngle=0;
	CString sValue; //=_T("0");
	CString DataValue; //=_T("0");
	CString sValueMircoStep;
	CString sValueMircoMAX;

	GetDlgItemTextW(IDC_MircoStep,sValueMircoStep);
	UINT MircoStep = _ttoi( sValueMircoStep );
	
	GetDlgItemTextW(IDC_MircoMAX,sValueMircoMAX);
	double MircoMAX = (double)_ttoi( sValueMircoMAX );


	//--------------------------------------------------------
	sValue.Format(_T("%d"),MircoStep*2);
	DataValue += _T("//-------------------------------------------\r\n");
	DataValue += L"const u8 SinData["+sValue+L"]={\r\n";
	for (i=0;i<MircoStep*2;i++)
	{
		m_SinAngle = sin((double)90/MircoStep*i*Pi/180);

		if (m_SinAngle<0)
			SinData = abs((int)(MircoMAX*m_SinAngle-0.51));
		else
			SinData = abs((int)(MircoMAX*m_SinAngle+0.51));
		 

		sValue.Format(_T("%d"),SinData); 

		DataValue += sValue + _T(",");
		if (i && (i+1)%16==0)	DataValue += _T("\r\n"); //指定换行
	}
	DataValue += _T("};\r\n");

	sValue.Format(_T("%d"),MircoStep*2);
	DataValue += _T("//-------------------------------------------\r\n");
	DataValue += L"const u8 CosData["+sValue+L"]={\r\n";
	for (i=0;i<MircoStep*2;i++)
	{

		m_CosAngle = cos((double)90/MircoStep*i*Pi/180);

		if (m_CosAngle<0)
			CosData = abs((int)(MircoMAX*m_CosAngle-0.51));
		else
			CosData= abs((int)(MircoMAX*m_CosAngle+0.51));

		sValue.Format(_T("%d"),CosData); 

		DataValue += sValue + _T(",");
		if (i && (i+1)%16==0)	DataValue += _T("\r\n"); //指定换行
	}
	DataValue += _T("};\r\n");
	SetDlgItemTextW(IDC_Data,DataValue);
	
	//AfxMessageBox(L"生成数据成功!");

}


void CMotorCurveDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	//AfxMessageBox(L"速度数据!");

	CWnd* m_pMainWnd;
	CMotorSpeedDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();

}

// 3-PHASE STEPPER MOTOR-----------------------------------
void CMotorCurveDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	
	UINT i=0;
	UINT SinData=0;
	UINT CosData=0;
	double	m_SinAngle=0;
	double	m_CosAngle=0;
	CString sValue; //=_T("0");
	CString DataValue; //=_T("0");
	//CString sValueMircoStep;
	//CString sValueMircoMAX;

	GetDlgItemTextW(IDC_MircoStep,sValue);
	UINT MircoStep = _ttoi(sValue);
	
	//GetDlgItemTextW(IDC_MircoMAX,sValueMircoMAX);
	//double MircoMAX = (double)_ttoi( sValueMircoMAX )/2;

	GetDlgItemTextW(IDC_EDIT1,sValue);
	UINT PWMcycleTime = _ttoi(sValue);
	//UINT PWMcycleTime = 48; //US

	GetDlgItemTextW(IDC_EDIT4,sValue);
	UINT Frequency = _ttoi(sValue);
	//UINT Frequency = 72; //MHZ

	UINT PWMMaxCycle = PWMcycleTime*Frequency; //PWMcycleTime/(1/Frequency);


	GetDlgItemTextW(IDC_EDIT2,sValue);
	UINT U1 = _ttoi(sValue);
	//UINT U1 = 60;//(*V*)

	//double L1 = 22; //(*mH*)
	//double R1 = 2; //(*R*)

	GetDlgItemTextW(IDC_EDIT5,sValue);
	UINT I1 = _ttoi(sValue);
	//UINT I1 = 10;//(*设计电流 应该小于U/R A*)

	//TEST?---
	sValue.Format(L"%2.3f",(double)1000/PWMcycleTime);
	SetDlgItemText(IDC_STATIC_KHZ,sValue+L"KHZ");
	
	UpdateData(TRUE);  //从对话框获取数据   DDX_Text()
	//UpdateData(FALSE); //将转换结果显示在对话框中
	//sValue.Format(L"%f",R1);
	//AfxMessageBox(L"R1 = "+sValue);

	double maxpulse = PWMMaxCycle*(1 - I1/(U1/R1)); // N(*余量*)
	double MircoMAX = (PWMMaxCycle - maxpulse)/2;

	sValue.Format(L"%d",PWMMaxCycle);
	CString sValue1;
	sValue1.Format(L"%f",MircoMAX);
	AfxMessageBox(L"PWMMaxCycle = "+sValue+L"\n"+L"MircoMAX = "+sValue1);

	//-------------------------------------------------------------------
	sValue.Format(_T("%d"),MircoStep*3*2); // 2 Pi 360度
	DataValue += _T("//-------------------------------------------\r\n");
	DataValue += L"const u16 PhaseAData["+sValue+L"]={\r\n";
	for (i=0;i<MircoStep*3*2;i++)
	{
		m_SinAngle = sin((double)90/(MircoStep*3/2)*i*Pi/180)+1;

		if (m_SinAngle<0)
			SinData = abs((int)(MircoMAX*m_SinAngle-0.51));
		else
			SinData = abs((int)(MircoMAX*m_SinAngle+0.51));


		sValue.Format(_T("%d"),SinData); 

		DataValue += sValue + _T(",");
		if (i && (i+1)%16==0)	DataValue += _T("\r\n"); //指定换行
	}
	DataValue += _T("};\r\n");

	//-------------------------------------------------------------------
	sValue.Format(_T("%d"),MircoStep*3*2);
	DataValue += _T("//-------------------------------------------\r\n");
	DataValue += L"const u16 PhaseBData["+sValue+L"]={\r\n";
	for (i=0;i<MircoStep*3*2;i++)
	{
		m_SinAngle = sin(((double)90/(MircoStep*3/2)*i+120)*Pi/180)+1;

		if (m_SinAngle<0)
			SinData = abs((int)(MircoMAX*m_SinAngle-0.51));
		else
			SinData = abs((int)(MircoMAX*m_SinAngle+0.51));


		sValue.Format(_T("%d"),SinData); 

		DataValue += sValue + _T(",");
		if (i && (i+1)%16==0)	DataValue += _T("\r\n"); //指定换行
	}
	DataValue += _T("};\r\n");

	//-------------------------------------------------------------------
	sValue.Format(_T("%d"),MircoStep*3*2);
	DataValue += _T("//-------------------------------------------\r\n");
	DataValue += L"const u16 PhaseCData["+sValue+L"]={\r\n";
	for (i=0;i<MircoStep*3*2;i++)
	{
		m_SinAngle = sin(((double)90/(MircoStep*3/2)*i+240)*Pi/180)+1;

		if (m_SinAngle<0)
			SinData = abs((int)(MircoMAX*m_SinAngle-0.51));
		else
			SinData = abs((int)(MircoMAX*m_SinAngle+0.51));
		

		sValue.Format(_T("%d"),SinData); 

		DataValue += sValue + _T(",");
		if (i && (i+1)%16==0)	DataValue += _T("\r\n"); //指定换行
	}
	DataValue += _T("};\r\n");

	//-------------------------------------------------------------------
	SetDlgItemTextW(IDC_Data,DataValue);
}


void CMotorCurveDlg::OnStnClickedYonyon()
{
	// TODO: Add your control notification handler code here
	ShellExecute(NULL, L"open", L"http://yonyon.taobao.com", NULL, NULL, SW_SHOWNORMAL);
	 


} 

bool bTxt = false;

void CMotorCurveDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	 CRect rcStatic; 
     GetDlgItem(IDC_YONYON)->GetWindowRect(&rcStatic); 
     ScreenToClient(&rcStatic); 

	 if( point.x > rcStatic.left && 
		 point.x < rcStatic.right && 
		 point.y > rcStatic.top  && 
		 point.y < rcStatic.bottom
		)
	 {	 
		 //MessageBox(NULL,L"OK",MB_OK);
		 //HCURSOR hCur = LoadCursor( NULL , IDC_CROSS ) ;
         //::SetCursor(hCur);
		 /*
	 	   		//改变背景色
		COLORREF m_NewColor = RGB(255,0,255);
		CBrush *pOldBrush;
		CBrush cBrush;
		CRect rect;

		GetDlgItem(IDC_YONYON)->GetClientRect(rect);  //得到控件区域
		CDC* pDC = GetDlgItem(IDC_YONYON)->GetDC();   //得到控件DC
		
		cBrush.CreateSolidBrush(m_NewColor);         //用新的颜色建立新画刷
		pOldBrush = pDC->SelectObject(&cBrush);       //选择新画刷，并保存旧画刷
		pDC->FillRect(rect, &cBrush);                 //重绘控件背景
		pDC->SelectObject(pOldBrush);                 //恢复画刷
		*/
	 }
	 else
	 {	
		 //bTxt = false;
		 /*
	 	COLORREF m_NewColor = RGB(255,255,255);
		CBrush *pOldBrush;
		CBrush cBrush;
		CRect rect;

		GetDlgItem(IDC_YONYON)->GetClientRect(rect);  //得到控件区域
		CDC* pDC = GetDlgItem(IDC_YONYON)->GetDC();   //得到控件DC
		
		cBrush.CreateSolidBrush(m_NewColor);         //用新的颜色建立新画刷
		pOldBrush = pDC->SelectObject(&cBrush);       //选择新画刷，并保存旧画刷
		pDC->FillRect(rect, &cBrush);                 //重绘控件背景
		pDC->SelectObject(pOldBrush);                 //恢复画刷
		*/
	 }

	CDialogEx::OnMouseMove(nFlags, point);
}
 



HBRUSH CMotorCurveDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here
	

		if( IDC_YONYON == pWnd->GetDlgCtrlID())
		{
		   pDC->SetTextColor(RGB(255,0,0));
		}

	// TODO:  Return a different brush if the default is not desired
	return hbr;
}




