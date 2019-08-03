
// MotorCurveDlg.h : 头文件
//

#pragma once

//#include"SinCos.h"

// CMotorCurveDlg 对话框
class CMotorCurveDlg : public CDialogEx
{
// 构造
public:
	CMotorCurveDlg(CWnd* pParent = NULL);	// 标准构造函数
	double L1; //(*mH*)
	double R1; //(*R*)

	//CSinCos		m_MotorCurve;
// 对话框数据
	enum { IDD = IDD_MOTORCURVE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	CEdit m_Data;
	CButton m_MakeData;
	CEdit m_MircoStep;
	afx_msg void OnBnClickedMakedata();
	CEdit m_MircoMAX;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnStnClickedYonyon();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
