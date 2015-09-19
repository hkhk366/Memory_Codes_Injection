// guaDlg.cpp : implementation file
//

#include "stdafx.h"
#include "gua.h"
#include "guaDlg.h"
#include "windows.h"
#include "tlhelp32.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
void xunlu(HANDLE handle_chuanru,DWORD x_chuanru,DWORD y_chuanru);
void shiquwupin(HANDLE handle_chuanru,DWORD wupinid_chuanru);
/////////////////////////////////////////////////////////////////////////////
// CGuaDlg dialog
int GetProcessIdByName()
{
	HANDLE myhProcess;
	PROCESSENTRY32 mype;
	mype.dwSize = sizeof(PROCESSENTRY32); 
	BOOL mybRet;
	myhProcess=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0); 
	mybRet=Process32First(myhProcess,&mype);
	while(mybRet)
	{
		if(strcmp("zhengtu.dat",mype.szExeFile)==0)//"QQ.exe"为指定的进程名
		{
			//this->m_x=(int)mype.th32ProcessID;
			//CString s1;
			//s1.Format("%d",(int)mype.th32ProcessID);
			//AfxMessageBox(s1);
			return (int)mype.th32ProcessID;
		}
		else
			mybRet=Process32Next(myhProcess,&mype);
	}
	return 0;
}

CGuaDlg::CGuaDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGuaDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGuaDlg)
	m_wupinming = _T("");
	m_jiange = 5000;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGuaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGuaDlg)
	DDX_Control(pDX, IDC_LIST1, m_syslist);
	DDX_Text(pDX, IDC_EDIT1, m_wupinming);
	DDX_Text(pDX, IDC_EDIT2, m_jiange);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGuaDlg, CDialog)
	//{{AFX_MSG_MAP(CGuaDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGuaDlg message handlers

BOOL CGuaDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_syslist.SetExtendedStyle(m_syslist.GetExtendedStyle()|LVS_EX_CHECKBOXES | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_syslist.InsertColumn(0,"ID",LVCFMT_LEFT,50,-1);
	m_syslist.InsertColumn(1,"PID",LVCFMT_LEFT,50,-1);
	m_syslist.InsertColumn(2,"用户名",LVCFMT_LEFT,100,-1);


	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CGuaDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CGuaDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

__declspec(naked) void zoulucall(DWORD *pxy)
{
	__asm
	{ //esp+4
		
            mov eax,dword ptr [esp+4] //xy
			mov ebx,dword ptr [eax]  //x
			mov edx,dword ptr [eax+4] //y
			

			mov eax,dword ptr ds:[0xF8FD2C]
			mov ecx,dword ptr ds:[eax+0x55C]
			push 0x0
			push 0x0
			push edx//Y坐标
			push ebx//X坐标
			mov edx,0x00501B60
			call edx
			ret 
	}
}

__declspec(naked) void shiquwupincall(DWORD *pxy)
{
	__asm
	{ //esp+4
		//	mov eax,dword ptr [esp+4] //xy
		//	mov ebx,dword ptr [eax]  //第一个参数
            mov eax,dword ptr [esp+4] 
            mov ebx,dword ptr [eax]  //传入参数，然后下面给edi
            mov edx,0xF8FD2C
            mov edx,[edx]
            mov edx,[edx+0x55c]

            mov edi,ebx
            push 0x0                                                ;----------------------少加这个参数 不加就导致堆栈溢出了
            push edi
            mov ecx,edx
            mov esi,edx
            mov edx,0x004EA330
            call edx
            ret

	}
}






void CGuaDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	m_syslist.DeleteAllItems();
	HANDLE hProcessSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 pe32 = {0};
	pe32.dwSize = sizeof(PROCESSENTRY32);
	BOOL bWork = Process32First(hProcessSnapshot, &pe32);
	while (bWork)
	{
		
		bWork = Process32Next(hProcessSnapshot, &pe32);
		if(strcmp("zhengtu.dat",pe32.szExeFile)==0)//"QQ.exe"为指定的进程名
		{
			CString csExeFile,temptext; int listindex;
			csExeFile.Format("%s",pe32.szExeFile);
			temptext.Format("%d",m_syslist.GetItemCount()+1);
			listindex=m_syslist.InsertItem(m_syslist.GetItemCount(),temptext);
			temptext.Format("%d",pe32.th32ProcessID);
			m_syslist.SetItemText(listindex,1,temptext);
			
			HANDLE temphandle;
			temphandle=::OpenProcess(PROCESS_ALL_ACCESS,FALSE,(DWORD)pe32.th32ProcessID);
			DWORD buf;
			char ganmename[20];
			ReadProcessMemory(temphandle, (LPVOID)(0xf8fd2c), &buf, 4, NULL );
			ReadProcessMemory(temphandle, (LPVOID)(buf+0x55c), &buf, 4, NULL );
			ReadProcessMemory(temphandle, (LPVOID)(buf+0x4), &ganmename, 20, NULL );
			CloseHandle(temphandle);
			m_syslist.SetItemText(listindex,2,ganmename);

		}
	}
	CloseHandle(hProcessSnapshot);
	UpdateData(FALSE);
	
	

}


void CGuaDlg::OnCheck1() 
{
	// TODO: Add your control notification handler code here
	CButton *pCheckbox = (CButton*)GetDlgItem(IDC_CHECK1);
    if(pCheckbox->GetCheck())                // 被选中
    {
        SetTimer(1,300,NULL);

    }
    else          // 没有选中
    {
        KillTimer(1);
    } 
}
HANDLE chuandi1;
DWORD chuandi2;
void CGuaDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent=1)
	{
		int a=m_syslist.GetItemCount();
		for (int i=1;i<=a;i++)
		{
			if (m_syslist.GetCheck(i-1)==TRUE)//判断是否打钩
			{
				CString temptext=m_syslist.GetItemText(i-1,1);
				HANDLE temphandle;
				temphandle=::OpenProcess(PROCESS_ALL_ACCESS,FALSE,(DWORD)(::atoi(temptext)));
				DWORD buf[20];
				char ganmename[20];
				
				//	int j=0;//数组循环
				ReadProcessMemory(temphandle, (LPVOID)(0xf8fd2c), &buf[1], 4, NULL );
				ReadProcessMemory(temphandle, (LPVOID)(buf[1]+0x4e0), &buf[2], 4, NULL );//数组首地址
				ReadProcessMemory(temphandle, (LPVOID)(buf[1]+0x4e4), &buf[3], 4, NULL );//数组尾地址
				int aa=((buf[3]-buf[2])/4)-1;
				for (int j=0;j<=aa;j++)
				{
					ReadProcessMemory(temphandle, (LPVOID)(buf[2]+j*0x4), &buf[4], 4, NULL );


					ReadProcessMemory(temphandle, (LPVOID)(buf[4]+0x4), &ganmename, 20, NULL );//读地面物品名称
					GetDlgItemText(IDC_EDIT1,temptext);
					if (ganmename==temptext)
					{
						temptext.Format("%d",buf[4]);
						TRACE("这里");
						TRACE(temptext);


						ReadProcessMemory(temphandle, (LPVOID)(buf[4]+0x2c), &buf[5], 4, NULL );//读地面物品X
						ReadProcessMemory(temphandle, (LPVOID)(buf[4]+0x30), &buf[6], 4, NULL );//读地面物品y
						xunlu(temphandle,buf[5],buf[6]);
						shiquwupin(temphandle,buf[4]);
					//	chuandi1=temphandle;chuandi2=buf[4];
					//	SetTimer(2,6000,NULL);
						break;
					}
					
				}

			
			CloseHandle(temphandle);	
			}
		}
		TRACE("\n");

	}
	if (nIDEvent=2)
	{
		shiquwupin(chuandi1,chuandi2);
		KillTimer(2);
	}

	CDialog::OnTimer(nIDEvent);
}

void CGuaDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
 	HANDLE temphandle;
 	temphandle=::OpenProcess(PROCESS_ALL_ACCESS,FALSE,(DWORD)(6252));
	shiquwupin(temphandle,(DWORD)0x068F9D10);


 	CloseHandle(temphandle);
	

}
void xunlu(HANDLE handle_chuanru,DWORD x_chuanru,DWORD y_chuanru)
{
	HANDLE temphandle;
	temphandle=handle_chuanru;
	PVOID FarCall=VirtualAllocEx(temphandle,NULL,0x8FFF,MEM_COMMIT,PAGE_EXECUTE_READWRITE);
	PVOID CallArg=VirtualAllocEx(temphandle,NULL,sizeof(int)*2,MEM_COMMIT,PAGE_READWRITE);
	DWORD byWrite;DWORD xy[2];
	WriteProcessMemory(temphandle,FarCall,zoulucall,0x8FFF,&byWrite);
//	TRACE("\n addr=%x \n",FarCall);
	xy[0]=x_chuanru;
	xy[1]=y_chuanru;
	WriteProcessMemory(temphandle,CallArg,xy,sizeof(DWORD)*2,&byWrite);
	HANDLE th=CreateRemoteThread(temphandle,NULL,NULL,( LPTHREAD_START_ROUTINE)FarCall,CallArg,NULL,NULL);
	WaitForSingleObject(th,0xFFFFFFF);//等待 ...
	VirtualFreeEx(temphandle,FarCall,0x8FFF,MEM_DECOMMIT);
	VirtualFreeEx(temphandle,CallArg,sizeof(int)*2,MEM_DECOMMIT);
}

void shiquwupin(HANDLE handle_chuanru,DWORD wupinid_chuanru)
{
	HANDLE temphandle;
	temphandle=handle_chuanru;
	PVOID FarCall=VirtualAllocEx(temphandle,NULL,0x8FFF,MEM_COMMIT,PAGE_EXECUTE_READWRITE);
	PVOID CallArg=VirtualAllocEx(temphandle,NULL,sizeof(int)*2,MEM_COMMIT,PAGE_READWRITE);
	DWORD byWrite;DWORD xy[2];
	WriteProcessMemory(temphandle,FarCall,shiquwupincall,0x8FFF,&byWrite);
	TRACE("\n addr=%x \n",FarCall);
	xy[0]=wupinid_chuanru;
	WriteProcessMemory(temphandle,CallArg,xy,sizeof(DWORD)*2,&byWrite);
	HANDLE th=CreateRemoteThread(temphandle,NULL,NULL,( LPTHREAD_START_ROUTINE)FarCall,CallArg,NULL,NULL);
	WaitForSingleObject(th,0xFFFFFFF);//等待 ...
	VirtualFreeEx(temphandle,FarCall,0x8FFF,MEM_DECOMMIT);
	VirtualFreeEx(temphandle,CallArg,sizeof(int)*2,MEM_DECOMMIT);
}
