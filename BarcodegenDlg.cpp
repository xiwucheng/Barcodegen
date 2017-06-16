// BarcodegenDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Barcodegen.h"
#include "BarcodegenDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBarcodegenDlg �Ի���




CBarcodegenDlg::CBarcodegenDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBarcodegenDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBarcodegenDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CBarcodegenDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_EXIT, &CBarcodegenDlg::OnBnClickedExit)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPINSN, &CBarcodegenDlg::OnDeltaposSpinsn)
END_MESSAGE_MAP()


// CBarcodegenDlg ��Ϣ�������

BOOL CBarcodegenDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	SetDlgItemText(IDC_PCBSN,TEXT("0000"));
	CSpinButtonCtrl* pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_SPINSN);
	pSpin->SetBuddy(GetDlgItem(IDC_PCBSN));
	pSpin->SetRange(0,9999);
	EnableMenuItem(::GetSystemMenu(m_hWnd,FALSE),SC_CLOSE,MF_BYCOMMAND|MF_DISABLED);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CBarcodegenDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
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
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR CBarcodegenDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CBarcodegenDlg::OnBnClickedExit()
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
}

void CBarcodegenDlg::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class

	//CDialog::OnCancel();
}

void CBarcodegenDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	CString szMap,szTmp;
	CString serial_number;
	BYTE snBuff[sizeof(Raymarine_apollo_header)] = {0};
	Raymarine_apollo_header header = {
		'A','P','S','0',
		0x01,//board_id
		0x01,//board_variant_id
		0x04,//board_pcb_revision
		'0','0','0','0','0','0','0',0x00,//serial_number_pcb
		'0','0','0','0','0','0','0','0',//serial_number_tla
		'1','0','0','6','1','8','8',0x00,//product_number
		'0',//ems_code
		0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,//test ict
		0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,//test eol
		0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,//test fate
		0x01,//som header
		0xff};
	CDateTimeCtrl* pick = (CDateTimeCtrl*)GetDlgItem(IDC_DATETIMEPICKER1);
	CTime tm;
	pick->GetTime(tm);
	CString datetime;
	datetime.Format(TEXT("%02d%d"),tm.GetMonth(),tm.GetYear()-2010);
	GetDlgItemText(IDC_PCBSN,serial_number);
	if (serial_number.GetLength() != 4)
	{
		MessageBox(TEXT("��ȷ�����кų���Ϊ4λ!"),TEXT("����"),MB_ICONERROR);
		return;
	}
	for( int i=0;i<3;i++)
	{
		header.serial_number_pcb[i] = (BYTE)datetime.GetAt(i);
	}
	for( int i=0;i<4;i++)
	{
		header.serial_number_pcb[i+3] = (BYTE)serial_number.GetAt(i);
	}
	BYTE* p= (BYTE*)&header;
	for (int i=0;i<8;i++)
	{
		szTmp.Format(TEXT(" 00%02XH:%02X %02X %02X %02X %02X %02X %02X %02X       %c%c%c%c%c%c%c%c\r\n"),
			i*8,
			*(p+i*8),*(p+i*8+1),*(p+i*8+2),*(p+i*8+3),*(p+i*8+4),*(p+i*8+5),*(p+i*8+6),*(p+i*8+7),
			isprint(*(p+i*8))?*(p+i*8):'.',isprint(*(p+i*8+1))?*(p+i*8+1):'.',isprint(*(p+i*8+2))?*(p+i*8+2):'.',isprint(*(p+i*8+3))?*(p+i*8+3):'.',
			isprint(*(p+i*8+4))?*(p+i*8+4):'.',isprint(*(p+i*8+5))?*(p+i*8+5):'.',isprint(*(p+i*8+6))?*(p+i*8+6):'.',isprint(*(p+i*8+7))?*(p+i*8+7):'.');
		szMap += szTmp;
	}
	for (int i=0; i< 64; i++)
	{
		if (isprint(*(p+i)))
		{
			snBuff[i]=*(p+i);
		}
		else
		{
			snBuff[i]='.';
		}
	}
	CStatic* pText = (CStatic*)GetDlgItem(IDC_MAPVIEW);
	CDC* pdc = pText->GetDC();
	CRect rc;
	CFont lf;
	pText->GetClientRect(&rc);
	pdc->SaveDC();
	lf.CreateFont(16, 0, 0, 0, FW_NORMAL, 0, FALSE, FALSE,
	  ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
	  FIXED_PITCH | FF_ROMAN, TEXT("Fixedsys"));
	pdc->SelectObject(&lf);
	pdc->DrawText(szMap,&rc,DT_NOPREFIX);
	pdc->RestoreDC(-1);
	lf.DeleteObject();
	CFile fp;
	if (fp.Open(TEXT("barcode.bin"),CFile::modeCreate|CFile::modeReadWrite|CFile::typeBinary))
	{
		fp.Write(&header,sizeof(header));
		fp.Close();
	}
	if (fp.Open(TEXT("sn.txt"),CFile::modeCreate|CFile::modeNoTruncate|CFile::modeReadWrite|CFile::typeBinary))
	{
		fp.SeekToEnd();
		fp.Write(snBuff,sizeof(snBuff));
		fp.Write("\r\n",2);
		fp.Close();
	}
	CButton* pBtn = (CButton*)GetDlgItem(IDC_AUTOINC);
	if (pBtn->GetCheck() == BST_CHECKED)
	{
		int sn = GetDlgItemInt(IDC_PCBSN);
		CString ss;
		sn ++;
		sn = sn > 9999 ? 9999 : sn;
		ss.Format(TEXT("%04d"),sn);  
		SetDlgItemText(IDC_PCBSN,ss);
	}
	//CDialog::OnOK();
}

void CBarcodegenDlg::OnDeltaposSpinsn(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	int sn = GetDlgItemInt(IDC_PCBSN);
	CString ss;
	sn += pNMUpDown->iDelta;
	sn = sn > 9999 ? 9999 : sn;
	sn = sn < 0 ? 0 : sn;
	ss.Format(TEXT("%04d"),sn);  
	SetDlgItemText(IDC_PCBSN,ss);
	*pResult = 1;
}
