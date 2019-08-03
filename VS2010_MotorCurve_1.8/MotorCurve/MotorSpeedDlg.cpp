// MotorSpeedDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MotorCurve.h"
#include "MotorSpeedDlg.h"
#include "afxdialogex.h"


// CMotorSpeedDlg �Ի���

IMPLEMENT_DYNAMIC(CMotorSpeedDlg, CDialog)

CMotorSpeedDlg::CMotorSpeedDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMotorSpeedDlg::IDD, pParent)
{

	EnableAutomation();

}

CMotorSpeedDlg::~CMotorSpeedDlg()
{
}

void CMotorSpeedDlg::OnFinalRelease()
{
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease�����ཫ�Զ�
	// ɾ���ö����ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣


	CDialog::OnFinalRelease();
}

void CMotorSpeedDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_C0, m_C0);
	DDX_Control(pDX, IDC_EDIT_StepMAX, m_StepMAX);
	DDX_Control(pDX, IDC_MOTORSPEEDDATA, m_SpeedData);
	DDX_Control(pDX, IDC_EDIT_K0, m_K0);
	DDX_Control(pDX, IDC_EDIT_B0, m_B0);
	DDX_Control(pDX, IDC_EDIT_K1, m_K1);
	DDX_Control(pDX, IDC_EDIT_B1, m_B1);
	DDX_Control(pDX, IDC_EDIT_K2, m_K2);
	DDX_Control(pDX, IDC_EDIT_TAO, m_TAO);
	DDX_Control(pDX, IDC_EDIT_Crystal, m_Crystal);
	DDX_Control(pDX, IDC_EDIT_Frequency, m_Frequency);

	DDX_Control(pDX, IDC_EDIT_MicroStep, m_MicroSpeed);
	DDX_Control(pDX, IDC_EDIT_C0UP, m_COUP);
}


BEGIN_MESSAGE_MAP(CMotorSpeedDlg, CDialog)
	ON_BN_CLICKED(IDC_MOTORSPEEDMAKE, &CMotorSpeedDlg::OnBnClickedMotorspeedmake)
	ON_NOTIFY(NM_CLICK, IDC_SYSLINK1, &CMotorSpeedDlg::OnNMClickSyslink1)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CMotorSpeedDlg, CDialog)
END_DISPATCH_MAP()

// ע��: ������� IID_IMotorSpeedDlg ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡��� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {1B091111-D76E-4A92-84FC-2E89486E3697}
static const IID IID_IMotorSpeedDlg =
{ 0x1B091111, 0xD76E, 0x4A92, { 0x84, 0xFC, 0x2E, 0x89, 0x48, 0x6E, 0x36, 0x97 } };

BEGIN_INTERFACE_MAP(CMotorSpeedDlg, CDialog)
	INTERFACE_PART(CMotorSpeedDlg, IID_IMotorSpeedDlg, Dispatch)
END_INTERFACE_MAP()


// CMotorSpeedDlg ��Ϣ�������


void CMotorSpeedDlg::OnBnClickedMotorspeedmake()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	#define  Crystal			16     	//�����С��M
	#define  Frequency			8     		//��Ƶֵ
	#define  K              	1      	//Kx-B
	#define  B              	3
	//#define  C0				    77.830000	 //208  2.4 /48  4
	//#define  ValTotal           514     //��������
	#define  StartI             0		//���忪ʼ����ֵ   �������еڼ������ݿ�ʼȡ��
	#define  TimerAValMAX       65535   //2^16    16λ   255 8λ
	//#define  NewlineValue       16		//�����������20
	U16 StepValue[5] ={16,16,16,16,16};    //ϸ����
	U16 PostionGap[5]={2,16,128,512,800};   //��ϸ��λ��

	BOOL MAXStepDataFlag = 0;
	BOOL MAXMicroStepDataFlag = 0;
	UINT i=0;
	UINT SpeedData=0;
	UINT StratData=0;
	UINT BrakeData=0;	

	CString sValue=_T("00000000");
	CString sValueMin=_T("00000000");
	CString sValueMax=_T("00000000");
	CString DataValue; //=_T("0");
	//--------------------------------------------------------------
	DataValue += _T("//-------------------------------------------\r\n");
	GetDlgItemTextW(IDC_EDIT_C0,sValue);
	DataValue += L"// double C0 = "+sValue+L"------- \r\n";
	double C0 = _ttof( sValue );

	GetDlgItemTextW(IDC_EDIT_C0UP,sValue);
	DataValue += L"// double C0UP = "+sValue+L"------- \r\n";
	double C0UP = _ttof( sValue );

	GetDlgItemTextW(IDC_EDIT_A1,sValue);
	DataValue += L"// double a1 = "+sValue+L"------- \r\n";
	double f_a1 = _ttof( sValue );

	GetDlgItemTextW(IDC_EDIT_A2,sValue);
	DataValue += L"// double a2 = "+sValue+L"------- \r\n";
	double f_a2 = _ttof( sValue );


	GetDlgItemTextW(IDC_EDIT_StepMAX,sValue);
	DataValue += L"// StepMAX = "+sValue+L"------- \r\n";
	UINT StepMAX = _ttoi( sValue);

	GetDlgItemTextW(IDC_EDIT_K0,sValue);
	DataValue += L"// K0 = "+sValue+L"------- \r\n";
	double u_K0 = _ttof( sValue );

	GetDlgItemTextW(IDC_EDIT_B0,sValue);
	DataValue += L"// B0 = "+sValue+L"------- \r\n";
	double u_B0 = _ttof( sValue );

	GetDlgItemTextW(IDC_EDIT_K1,sValue);
	DataValue += L"// K1 = "+sValue+L"------- \r\n";
	double u_K1 = _ttof( sValue );

	GetDlgItemTextW(IDC_EDIT_B1,sValue);
	DataValue += L"// B1 = "+sValue+L"------- \r\n";
	double u_B1 = _ttof( sValue );

	GetDlgItemTextW(IDC_EDIT_K2,sValue);
	DataValue += L"// K2 = "+sValue+L"------- \r\n";
	double u_K2 = _ttof( sValue );

	GetDlgItemTextW(IDC_EDIT_TAO,sValue);
	DataValue += L"// double �� = "+sValue+L"------- \r\n";
	double u_TAO = _ttof( sValue );




	GetDlgItemTextW(IDC_EDIT_Crystal,sValue);
	DataValue += L"// ʱ��Ƶ�� = "+sValue+L"------- \r\n";
	UINT u_Crystal = _ttoi( sValue );

	GetDlgItemTextW(IDC_EDIT_Frequency,sValue);
	DataValue += L"// ��Ƶֵ = "+sValue+L"------- \r\n";
	UINT u_Frequency = _ttoi( sValue );

	GetDlgItemTextW(IDC_EDIT_MicroStep,sValue);
	DataValue += L"// ϸ���� = "+sValue+L"------- \r\n";
	UINT u_MicroStep = _ttoi( sValue );
	//----------------------------------------------------------------------
	DataValue += _T("//-------------------------------------------\r\n");
	//----------------------------------------------------------------------
	//=====================================================================================
	double MotorSpeed = C0*(sqrt(double(StepMAX+1))-sqrt(double(StepMAX)));		//ms/step
	//MotorSpeed = (double)K*60/(MotorSpeed*200/1000)-B;
	MotorSpeed = (double)u_K0*60/(MotorSpeed*200/1000)-u_B0; //rpm
	sValueMax.Format(_T("%5.2f"),MotorSpeed); 

	MotorSpeed = C0*(sqrt(double(1+1))-sqrt(double(1)));
	MotorSpeed = (double)u_K0*60/(MotorSpeed*200/1000)-u_B0;
	sValueMin.Format(_T("%5.2f"),MotorSpeed); 

	AfxMessageBox(L"��������ٶ� ="+sValueMin+L"--"+sValueMax+L" R/Min");
	//----------------------------------------------------------------------
	DataValue += L"// ��������ٶ� = "+sValueMin+L"--"+sValueMax+L" r/min-------------------------------------------\r\n";
	//----------------------------------------------------------------------
	sValue.Format(_T("%d"),StepMAX);
	DataValue += _T("//-------------------------------------------\r\n");
	DataValue += L"const u16 SpeedCurveTimerVal["+sValue+L"]={\r\n";
	for (i=1;i<=StepMAX;i++)
	{
		double Cn = C0*(sqrt(double(i+1))-sqrt(double(i)));
		//Cn = (double)K*60/(Cn*200/1000)-B;
     	Cn = (double)u_K0*60/(Cn*200/1000)-u_B0;

      if(i<=PostionGap[0])
            Cn = 60*1000/(Cn*200)/StepValue[0];
      else if((i>PostionGap[0])&&(i<=PostionGap[1]))
            Cn = 60*1000/(Cn*200)/StepValue[1];
      else if((i>PostionGap[1])&&(i<=PostionGap[2]))
            Cn = 60*1000/(Cn*200)/StepValue[2];
      else if((i>PostionGap[2])&&(i<=PostionGap[3]))
            Cn = 60*1000/(Cn*200)/StepValue[3];
      else if((i>PostionGap[3])&&(i<=PostionGap[4]))
            Cn = 60*1000/(Cn*200)/StepValue[4];
      
      //double TimerAVal = 65535-Cn*1000/(double(1)/Crystal*Frequency);    
      double TimerAVal = 65535-Cn*1000/(double(1)/u_Crystal*u_Frequency);
	  SpeedData  = abs(int(TimerAVal+0.5)); // //��������	 

	  if (ErrorData(SpeedData)) MAXStepDataFlag = 1;

		sValue.Format(_T("%d"),SpeedData); 

		DataValue += sValue + _T(",");

		if (i && (i+1)%20==0)	DataValue += _T("\r\n"); //ָ������

	}
	DataValue += _T("\r\n};\r\n");
//=====================================================================================
	//MotorSpeed = C0UP*(sqrt(double(u_MicroStep+1))-sqrt(double(u_MicroStep)));
	MotorSpeed = C0UP*(pow(double(1),f_a1) + pow(double(1),f_a2))+u_B1;	//rpm
	MotorSpeed = 1/(MotorSpeed/60*200/1000);	  //ms/step
	MotorSpeed = (double)u_K1*60/(MotorSpeed*200/1000);	//rpm	 Ϊ�˼���֮ǰ����
	sValueMin.Format(_T("%5.2f"),MotorSpeed); 

	//MotorSpeed = C0UP*(sqrt(double(1+1))-sqrt(double(1)));
	MotorSpeed = C0UP*(pow(double(u_MicroStep),f_a1) + pow(double(u_MicroStep),f_a2))+u_B1;
	MotorSpeed = 1/(MotorSpeed/60*200/1000);	  //ms/step
	MotorSpeed = (double)u_K1*60/(MotorSpeed*200/1000);
	sValueMax.Format(_T("%5.2f"),MotorSpeed); 

	//AfxMessageBox(L"��������ٶ� ="+sValueMin+L"--"+sValueMax+L" R/Min");
	//----------------------------------------------------------------------
	DataValue += L"// ��������ٶ�(Strat) = "+sValueMin+L"--"+sValueMax+L" r/min-------------------------------------------\r\n";

	//-------------------------------------------------------
	sValue.Format(_T("%d"),u_MicroStep); 
	//-------------------------------------------------------
	DataValue += _T("//-------------------------------------------\r\n");
	DataValue += L"const u16 SpeedCurveTimerValUp["+sValue+L"]={\r\n";
	for (i=1;i<=u_MicroStep;i++)
	{
		//double m_TimerMicroStep = u_K2*(double)exp(-double(i)/u_TAO);  //ms/sstep  ms/MicroStep
		//double CnUp = C0UP*(sqrt(double(i+1))-sqrt(double(i)));
     	double CnUp = C0UP*(pow(double(i),f_a1) + pow(double(i),f_a2))+u_B1;	   //rpm
		CnUp = 1/(CnUp/60*200/1000);	 //ms/step
		// --------SpeedData r/min-------------
		CnUp = (double)u_K1*60/(CnUp*200/1000);
		// --------ms/MicroStep----------------
        CnUp = 60*1000/(CnUp*200)/StepValue[0]; //ms/sstep
	  
		double TimerAVal = 65535-CnUp*1000/(double(1)/u_Crystal*u_Frequency);
		
		SpeedData  = abs(int(TimerAVal+0.5)); // //��������	 

	  if (ErrorData(SpeedData)) MAXMicroStepDataFlag = 1;

		sValue.Format(_T("%d"),SpeedData); 

		DataValue += sValue + _T(",");

		if (i && (i+1)%20==0)	DataValue += _T("\r\n"); //ָ������
	}
	DataValue += _T("\r\n};\r\n");

//=====================================================================================
	MotorSpeed = u_K2*(double)exp(-double(u_MicroStep)/u_TAO); 
	MotorSpeed = (double)u_K1*60/(MotorSpeed*u_MicroStep*200/1000)+u_B1;
	sValueMax.Format(_T("%5.2f"),MotorSpeed); 

	MotorSpeed = u_K2*(double)exp(-double(1)/u_TAO); 
	MotorSpeed = (double)u_K1*60/(MotorSpeed*u_MicroStep*200/1000)+u_B1;
	sValueMin.Format(_T("%5.2f"),MotorSpeed);

	//AfxMessageBox(L"��������ٶ� ="+sValueMin+L"--"+sValueMax+L" R/Min");
	//----------------------------------------------------------------------
	DataValue += L"// ��������ٶ�(Brake) = "+sValueMin+L"--"+sValueMax+L" r/min-------------------------------------------\r\n";

	//-------------------------------------------------------
	sValue.Format(_T("%d"),u_MicroStep);
	//-------------------------------------------------------	
	DataValue += _T("//-------------------------------------------\r\n");
	DataValue += L"const u16 SpeedCurveTimerValDown["+sValue+L"]={\r\n";
	for (i=1;i<=u_MicroStep;i++)
	{
		double m_TimerMicroStep = u_K2*(double)exp(-double(i)/u_TAO);  //ms/sstep  ms/MicroStep
		// --------SpeedData r/min-------------
		m_TimerMicroStep = (double)u_K1*60/(m_TimerMicroStep*u_MicroStep*200/1000)+u_B1;

        m_TimerMicroStep = 60*1000/(m_TimerMicroStep*200)/StepValue[0];
	  
		//sValue.Format(_T("%d"),SinData); 
		//sValue.Format(_T("%d"),StratData); 
		double TimerAVal = 65535-m_TimerMicroStep*1000/(double(1)/u_Crystal*u_Frequency);
		SpeedData  = abs(int(TimerAVal+0.5)); // //��������	 

	  if (ErrorData(SpeedData)) MAXMicroStepDataFlag = 1;

		sValue.Format(_T("%d"),SpeedData); 

		DataValue += sValue + _T(",");

		if (i && (i+1)%20==0)	DataValue += _T("\r\n"); //ָ������
	}
	DataValue += _T("\r\n};\r\n");
	
	SetDlgItemTextW(IDC_MOTORSPEEDDATA,DataValue);
	
	//AfxMessageBox(L"�������ݳɹ�!");
	if (MAXStepDataFlag)
			AfxMessageBox(L"Step����̫��!");
	if (MAXMicroStepDataFlag)
			AfxMessageBox(L"MicroStep����̫��!");

}

BOOL CMotorSpeedDlg::ErrorData(UINT data)
{
	if (data >65535)
		return 1;
	else
		return 0;
}


BOOL CMotorSpeedDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CString sValue = L"77.83";
	SetDlgItemText(IDC_EDIT_C0,sValue); 

	sValue = L"0.130";
	SetDlgItemText(IDC_EDIT_C0UP,sValue);

	sValue = L"0.5";
	SetDlgItemText(IDC_EDIT_A1,sValue);

	sValue = L"0.5";
	SetDlgItemText(IDC_EDIT_A2,sValue);


	sValue = L"512";
	SetDlgItemText(IDC_EDIT_StepMAX,sValue);

	sValue = L"1.0";
	SetDlgItemText(IDC_EDIT_K0,sValue);

	sValue = L"3.0";
	SetDlgItemText(IDC_EDIT_B0,sValue);

	sValue = L"1.0";
	SetDlgItemText(IDC_EDIT_K1,sValue);
	sValue = L"1.0";
	SetDlgItemText(IDC_EDIT_B1,sValue);

	sValue = L"3.0";
	SetDlgItemText(IDC_EDIT_K2,sValue);
	sValue = L"46.30";
	SetDlgItemText(IDC_EDIT_TAO,sValue);

	sValue = L"16";
	SetDlgItemText(IDC_EDIT_Crystal,sValue);
	sValue = L"8";
	SetDlgItemText(IDC_EDIT_Frequency,sValue);

	sValue = L"64";
	SetDlgItemText(IDC_EDIT_MicroStep,sValue);
	


	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CMotorSpeedDlg::OnNMClickSyslink1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here

	ShellExecute(NULL, L"open", L"http://yonyon.taobao.com", NULL, NULL, SW_SHOWNORMAL);

	*pResult = 0;
}
