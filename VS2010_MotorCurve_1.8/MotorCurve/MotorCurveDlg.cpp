
// MotorCurveDlg.cpp : ʵ���ļ�
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

// CMotorCurveDlg �Ի���




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


// CMotorCurveDlg ��Ϣ�������

BOOL CMotorCurveDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
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


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMotorCurveDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMotorCurveDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// 2-PHASE STEPPER MOTOR-----------------------------------
void CMotorCurveDlg::OnBnClickedMakedata()
{
	// TODO: �ڴ���ӿؼ�֪ͨ���������� double folat
	
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
		if (i && (i+1)%16==0)	DataValue += _T("\r\n"); //ָ������
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
		if (i && (i+1)%16==0)	DataValue += _T("\r\n"); //ָ������
	}
	DataValue += _T("};\r\n");
	SetDlgItemTextW(IDC_Data,DataValue);
	
	//AfxMessageBox(L"�������ݳɹ�!");

}


void CMotorCurveDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//AfxMessageBox(L"�ٶ�����!");

	CWnd* m_pMainWnd;
	CMotorSpeedDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();

}

// 3-PHASE STEPPER MOTOR-----------------------------------
void CMotorCurveDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
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
	//UINT I1 = 10;//(*��Ƶ��� Ӧ��С��U/R A*)

	//TEST?---
	sValue.Format(L"%2.3f",(double)1000/PWMcycleTime);
	SetDlgItemText(IDC_STATIC_KHZ,sValue+L"KHZ");
	
	UpdateData(TRUE);  //�ӶԻ����ȡ����   DDX_Text()
	//UpdateData(FALSE); //��ת�������ʾ�ڶԻ�����
	//sValue.Format(L"%f",R1);
	//AfxMessageBox(L"R1 = "+sValue);

	double maxpulse = PWMMaxCycle*(1 - I1/(U1/R1)); // N(*����*)
	double MircoMAX = (PWMMaxCycle - maxpulse)/2;

	sValue.Format(L"%d",PWMMaxCycle);
	CString sValue1;
	sValue1.Format(L"%f",MircoMAX);
	AfxMessageBox(L"PWMMaxCycle = "+sValue+L"\n"+L"MircoMAX = "+sValue1);

	//-------------------------------------------------------------------
	sValue.Format(_T("%d"),MircoStep*3*2); // 2 Pi 360��
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
		if (i && (i+1)%16==0)	DataValue += _T("\r\n"); //ָ������
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
		if (i && (i+1)%16==0)	DataValue += _T("\r\n"); //ָ������
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
		if (i && (i+1)%16==0)	DataValue += _T("\r\n"); //ָ������
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
	 	   		//�ı䱳��ɫ
		COLORREF m_NewColor = RGB(255,0,255);
		CBrush *pOldBrush;
		CBrush cBrush;
		CRect rect;

		GetDlgItem(IDC_YONYON)->GetClientRect(rect);  //�õ��ؼ�����
		CDC* pDC = GetDlgItem(IDC_YONYON)->GetDC();   //�õ��ؼ�DC
		
		cBrush.CreateSolidBrush(m_NewColor);         //���µ���ɫ�����»�ˢ
		pOldBrush = pDC->SelectObject(&cBrush);       //ѡ���»�ˢ��������ɻ�ˢ
		pDC->FillRect(rect, &cBrush);                 //�ػ�ؼ�����
		pDC->SelectObject(pOldBrush);                 //�ָ���ˢ
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

		GetDlgItem(IDC_YONYON)->GetClientRect(rect);  //�õ��ؼ�����
		CDC* pDC = GetDlgItem(IDC_YONYON)->GetDC();   //�õ��ؼ�DC
		
		cBrush.CreateSolidBrush(m_NewColor);         //���µ���ɫ�����»�ˢ
		pOldBrush = pDC->SelectObject(&cBrush);       //ѡ���»�ˢ��������ɻ�ˢ
		pDC->FillRect(rect, &cBrush);                 //�ػ�ؼ�����
		pDC->SelectObject(pOldBrush);                 //�ָ���ˢ
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




