// BarcodegenDlg.h : ͷ�ļ�
//

#pragma once

typedef struct
{
	BYTE head_magic[4];
	BYTE board_id;
	BYTE board_variant_id;
	BYTE board_pcb_revision;
	BYTE serial_number_pcb[8];
	BYTE serial_number_tla[8];
	BYTE product_number[8];
	BYTE ems_code;
	BYTE test_ict[10];
	BYTE test_eol[10];
	BYTE test_fate[10];
	BYTE som_header;
	BYTE reserve;
}Raymarine_apollo_header;

// CBarcodegenDlg �Ի���
class CBarcodegenDlg : public CDialog
{
// ����
public:
	CBarcodegenDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_BARCODEGEN_DIALOG };

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
	afx_msg void OnBnClickedExit();
protected:
	virtual void OnCancel();
	virtual void OnOK();
public:
	afx_msg void OnDeltaposSpinsn(NMHDR *pNMHDR, LRESULT *pResult);
};
