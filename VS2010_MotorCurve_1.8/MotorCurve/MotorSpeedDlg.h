#pragma once


// CMotorSpeedDlg 对话框

class CMotorSpeedDlg : public CDialog
{
	DECLARE_DYNAMIC(CMotorSpeedDlg)

public:
	CMotorSpeedDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMotorSpeedDlg();
	BOOL ErrorData(UINT data);

	virtual void OnFinalRelease();

// 对话框数据
	enum { IDD = IDD_MOTORSPEED_DIALOG };
public:
		//double	temp1;
		//UINT	StepMAX;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	afx_msg void OnBnClickedMotorspeedmake();
	CEdit m_C0;
	CEdit m_StepMAX;
	CEdit m_SpeedData;
	virtual BOOL OnInitDialog();
	CEdit m_K1;
	CEdit m_K2;
	CEdit m_TAO;
	CEdit m_K0;
	CEdit m_B0;
	CEdit m_B1;
	CEdit m_Crystal;
	CEdit m_Frequency;
	CEdit m_MicroSpeed;
	CEdit m_COUP;
	afx_msg void OnNMClickSyslink1(NMHDR *pNMHDR, LRESULT *pResult);
};
