
// MotorCurveDlg.h : ͷ�ļ�
//

#pragma once

//#include"SinCos.h"

// CMotorCurveDlg �Ի���
class CMotorCurveDlg : public CDialogEx
{
// ����
public:
	CMotorCurveDlg(CWnd* pParent = NULL);	// ��׼���캯��
	double L1; //(*mH*)
	double R1; //(*R*)

	//CSinCos		m_MotorCurve;
// �Ի�������
	enum { IDD = IDD_MOTORCURVE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
